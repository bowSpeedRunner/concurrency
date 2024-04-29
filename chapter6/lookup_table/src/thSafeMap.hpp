#include <map>
#include <mutex>
#include <vector>
#include <algorithm>
#include <shared_mutex>
#include <hashtable.h>
#include <utility>
#include <list>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class threadSafe_lookuptable {
 private:
  class bucket_type {
   private:
    using bucket_value = std::pair<Key, Value>;
    using bucket_data = std::list<bucket_value>;
    using bucket_iterator = typename bucket_data::const_iterator;
    bucket_data data;
    mutable std::shared_mutex mutex;
    friend class threadSafe_lookuptable;

    bucket_iterator find_entry_for(const Key& key) const {
      return std::find_if(data.begin(), data.end(), [&](const bucket_value& item) { return item.first == key; });
    }

   public:
    Value value_for(const Key& key, const Value& default_value) const {
      std::shared_lock<std::shared_mutex> lock(mutex);
      bucket_iterator find_entry = find_entry_for(key);
      return (find_entry == data.end()) ? default_value : find_entry->second;
    }

    void add_or_update_mapping(const Key& key, const Value& value) {
      std::unique_lock<std::shared_mutex> lock(mutex);
      bucket_iterator find_entry = find_entry_for(key);
      if (find_entry == data.end()) {
        data.emplace_back(bucket_value(key, value));
      } else {
        const_cast<Value&>(find_entry->second) = value;
      }
    }

    void remove_mapping(const Key& key) {
      std::unique_lock<std::shared_mutex> lock(mutex);
      const bucket_iterator find_entry = find_entry_for(key);
      if (find_entry != data.end()) {
        data.erase(find_entry);
      }
    }
  };
  std::vector<std::unique_ptr<bucket_type>> buckets;
  Hash hasher;
  bucket_type& get_bucket(const Key& key) const {
    const std::size_t bucket_index = hasher(key) % buckets.size();
    return *buckets[bucket_index];
  }

 public:
  using key_type = Key;
  using mapped_type = Value;
  using hash_type = Hash;
  threadSafe_lookuptable(unsigned num_buckets = 19, const Hash& hasher_ = Hash())
      : buckets(num_buckets), hasher(hasher_) {
    for (unsigned i = 0; i < num_buckets; ++i) {
      buckets[i].reset(new bucket_type);
    }
  }
  threadSafe_lookuptable(const threadSafe_lookuptable&) = delete;
  threadSafe_lookuptable& operator=(const threadSafe_lookuptable&) = delete;

  Value value_for(const Key& key, const Value& default_value = Value()) const {
    return get_bucket(key).value_for(key, default_value);
  }

  void add_or_updata_mapping(const Key& key, const Value& value) {
    get_bucket(key).add_or_update_mapping(key, value);
  }

  void remove_mapping(const Key& key) {
    get_bucket(key).remove_mapping(key);
  }

  std::map<Key, Value> get_map() const {
    std::vector<std::unique_lock<std::shared_mutex>> locks;
    for (unsigned i = 0; i < buckets.size(); ++i) {
      locks.emplace_back(std::unique_lock<std::shared_mutex>(buckets[i]->mutex));
    }
    std::map<Key, Value> res;
    for (unsigned i = 0; i < buckets.size(); ++i) {
      for (typename bucket_type::bucket_iterator it = buckets[i]->data.begin(); it != buckets[i]->data.end(); ++it) {
        res.emplace(*it);
      }
    }
    return res;
  }
};