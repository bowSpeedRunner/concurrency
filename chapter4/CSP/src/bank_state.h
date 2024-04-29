#ifndef _BANK_H_
#define _BANK_H_

#include "machine_msg.h"
class bank_machine {
 private:
  messaging::receiver incoming;
  unsigned balance;

 public:
  bank_machine() : balance(199) {
  }

  messaging::sender get_sender() {
    return incoming;
  }

  void done() {
    get_sender().send(messaging::close_queue());
  }
  void run() {
    try {
      for (;;) {
        incoming.wait()
            .handle<verifyPin>([&](const verifyPin& msg) {
              if (msg.pin == "2023") {
                msg.atm_queue.send(pinVerified());
              } else {
                msg.atm_queue.send(pinIncorrect());
              }
            })
            .handle<withdraw>([&](const withdraw& msg) {
              if (balance >= msg.amount) {
                msg.atm_queue.send(withdrawOk());
                balance -= msg.amount;
              } else {
                msg.atm_queue.send(withdrawDenied());
              }
            })
            .handle<getBalance>([&](const getBalance& msg) { msg.atm_queue.send(::balance(balance)); })
            .handle<withdrawPocessed>([&](const withdrawPocessed& msg) {})
            .handle<withdrawCanceled>([&](const withdrawCanceled& msg) {});
      }
    } catch (const messaging::close_queue&) {
    }
  }
};

#endif  //! _BANK_H_