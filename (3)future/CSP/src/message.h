/*
This file is main about message, including member sender, receiver and dispatcher. The message will be put into a
message queue, and when using message, you have to specialize it.
*/
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <iostream>

namespace messaging {
struct message_base {
  virtual ~message_base() {
  }
};

template <typename Msg>
struct specialized_message : message_base {
  Msg contents;
  explicit specialized_message(const Msg& contents_) : contents(contents_) {
  }
};

class message_queue {
 private:
  std::mutex mtx;
  std::condition_variable cv;
  std::queue<std::shared_ptr<message_base>> msq;

 public:
  template <typename T>
  void push(const T& msg) {
    std::lock_guard<std::mutex> lk(mtx);
    msq.push(std::make_shared<specialized_message<T>>(msg));
    cv.notify_all();
  }

  std::shared_ptr<message_base> wait_and_pop() {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, [&] { return !msq.empty(); });
    auto res = msq.front();
    msq.pop();
    return res;
  }
};

class sender {
 private:
  message_queue* q;

 public:
  sender() : q(nullptr) {
  }

  explicit sender(message_queue* q_) : q(q_) {
  }

  template <typename message>
  void send(const message& msg) {
    if (q) {
      q->push(msg);
    }
  }
};

class close_queue {
 public:
  close_queue() {
    std::cout << "Throw close queue signal!" << std::endl;
  }
};

template <typename previousDispatcher, typename Msg, typename Func>
class templateDispatcher {
 private:
  message_queue* q;
  previousDispatcher* prev;
  Func f;
  bool chained;
  templateDispatcher(const templateDispatcher&) = delete;
  templateDispatcher& operator=(const templateDispatcher&) = delete;
  template <typename Dispatcher, typename otherMsg, typename otherFunc>
  friend class templateDispatcher;

  void wait_and_disptach() {
    for (;;) {
      auto msg = q->wait_and_pop();
      if (dispatch(msg)) {
        break;
      }
    }
  }

  bool dispatch(const std::shared_ptr<message_base>& msg) {
    if (specialized_message<Msg>* specialized = dynamic_cast<specialized_message<Msg>*>(msg.get())) {
      f(specialized->contents);
      return true;
    } else {
      return prev->dispatch(msg);
    }
  }

 public:
  templateDispatcher(templateDispatcher&& other)
      : q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained) {
    other.chained = true;
  }
  templateDispatcher(message_queue* q_, previousDispatcher* prev_, Func&& f_)
      : q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false) {
    prev_->chained = true;
  }

  template <typename otherMsg, typename otherFunc>
  templateDispatcher<templateDispatcher, otherMsg, otherFunc> handle(otherFunc&& of) {
    return templateDispatcher<templateDispatcher, otherMsg, otherFunc>(q, this, std::forward<otherFunc>(of));
  }

  ~templateDispatcher() noexcept(false) {
    if (!chained) {
      wait_and_disptach();
    }
  }
};

class dispatcher {
 private:
  message_queue* q;
  bool chained;
  dispatcher(const dispatcher&) = delete;
  dispatcher& operator=(const dispatcher&) = delete;

  template <typename Dispatcher, typename Msg, typename Func>
  friend class templateDispatcher;

  void wait_and_dispatch() {
    for (;;) {
      auto msg = q->wait_and_pop();
      dispatch(msg);
    }
  }

  bool dispatch(const std::shared_ptr<message_base>& msg) {
    if (dynamic_cast<specialized_message<close_queue>*>(msg.get())) {
      throw close_queue();
    }
    return false;
  }

 public:
  dispatcher(dispatcher&& other) : q(other.q), chained(other.chained) {
    other.chained = true;
  }

  explicit dispatcher(message_queue* q_) : q(q_), chained(false) {
  }

  template <typename Msg, typename Func>
  templateDispatcher<dispatcher, Msg, Func> handle(Func&& f) {
    return templateDispatcher<dispatcher, Msg, Func>(q, this, std::forward<Func>(f));
  }

  ~dispatcher() noexcept(false) {
    if (!chained) {
      wait_and_dispatch();
    }
  }
};

class receiver {
 private:
  message_queue q;

 public:
  operator sender() {
    return sender(&q);
  }

  dispatcher wait() {
    return dispatcher(&q);
  }
};

}  // namespace messaging

#endif  //! _MESSAGE_H_