#ifndef _dns_cache_h
#define _dns_cache_h
#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>
using dns_entry = uint64_t;
class dns_cache {
 public:
  dns_cache() = default;
  ~dns_cache() = default;
  dns_cache(const dns_cache&) = delete;
  dns_cache& operator=(const dns_cache&) = delete;
  dns_entry find_entry(const std::string&) const;
  void update_or_add_entry(const std::string&, const dns_entry&);

 private:
  std::map<std::string, dns_entry> entries;
  mutable std::shared_mutex entry_mutex;
};

dns_entry dns_cache::find_entry(const std::string& domin) const {
  std::shared_lock<std::shared_mutex> lk(entry_mutex);
  auto it = entries.find(domin);
  return (it == entries.end()) ? 0 : it->second;
}

void dns_cache::update_or_add_entry(const std::string& domin, const dns_entry& dns_details) {
  std::lock_guard<std::shared_mutex> lk(entry_mutex);
  entries[domin] = dns_details;
}

#endif  // !_dns_cache_h