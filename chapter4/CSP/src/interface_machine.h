#ifndef _INTERFACE_MACHINE_H_
#define _INTERFACE_MACHINE_H_

#include "machine_msg.h"
class interface_machine {
 private:
  messaging::receiver incoming;

 public:
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
            .handle<issueMoney>([&](const issueMoney& msg) { std::cout << "Issuing " << msg.amount << std::endl; })
            .handle<displayInsuffientFunds>(
                [&](const displayInsuffientFunds& msg) { std::cout << "Insufficient funds." << std::endl; })
            .handle<displayEnterPin>(
                [&](const displayEnterPin& msg) { std::cout << "Please enter your pin." << std::endl; })
            .handle<displayEnterCard>(
                [&](const displayEnterCard& msg) { std::cout << "Please enter your card." << std::endl; })
            .handle<displayBalance>([&](const displayBalance& msg) {
              std::cout << "The balance of your account is " << msg.amount << std::endl;
            })
            .handle<displayWithdrawOptions>([&](const displayWithdrawOptions& msg) {
              std::cout << "Withdraw 50? (w)" << std::endl;
              std::cout << "Display balance? (b)" << std::endl;
              std::cout << "Cancel? (c)" << std::endl;
            })
            .handle<displayWithdrawCanceled>(
                [&](const displayWithdrawCanceled& msg) { std::cout << "Withdrawal cancelled." << std::endl; })
            .handle<displayPinIncorrect>(
                [&](const displayPinIncorrect& msg) { std::cout << "Pin incorrect" << std::endl; })
            .handle<cardEjected>([&](const cardEjected& msg) { std::cout << "Ejecting card." << std::endl; });
      }
    } catch (messaging::close_queue&) {
    }
  }
};

#endif  //!_INTERFACE_MACHINE_H_