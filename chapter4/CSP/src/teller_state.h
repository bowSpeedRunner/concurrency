#ifndef _TELLER_STATE_H_
#define _TELLER_STATE_H_

#include "machine_msg.h"
class atm {
 private:
  messaging::receiver incoming;
  messaging::sender bank;
  messaging::sender interface_hardware;
  void (atm::*state)();
  std::string account;
  unsigned withdraw_amount;
  std::string pin;

  void process_withdrawal() {
    incoming.wait()
        .handle<withdrawOk>([&](const withdrawOk& msg) {
          interface_hardware.send(issueMoney(withdraw_amount));
          bank.send(withdrawPocessed(account, withdraw_amount));
          state = &atm::done_processing;
        })
        .handle<withdrawDenied>([&](const withdrawDenied& msg) {
          interface_hardware.send(displayInsuffientFunds());
          state = &atm::done_processing;
        })
        .handle<cancelPressed>([&](const cancelPressed& msg) {
          bank.send(withdrawCanceled(account, withdraw_amount));
          interface_hardware.send(displayWithdrawCanceled());
          state = &atm::done_processing;
        });
  }

  void process_balance() {
    incoming.wait()
        .handle<balance>([&](const balance& msg) {
          interface_hardware.send(displayBalance(msg.amount));
          state = &atm::wait_for_action;
        })
        .handle<cancelPressed>([&](const cancelPressed& msg) { state = &atm::done_processing; });
  }

  void wait_for_action() {
    interface_hardware.send(displayWithdrawOptions());
    incoming.wait()
        .handle<withdrawPressed>([&](const withdrawPressed& msg) {
          withdraw_amount = msg.amount;
          bank.send(withdraw(account, msg.amount, incoming));
          state = &atm::process_withdrawal;
        })
        .handle<balancePressed>([&](const balancePressed& msg) {
          bank.send(getBalance(account, incoming));
          state = &atm::process_balance;
        })
        .handle<cancelPressed>([&](const cancelPressed& msg) { state = &atm::done_processing; });
  }

  void verify_pin() {
    incoming.wait()
        .handle<pinVerified>([&](const pinVerified& msg) { state = &atm::wait_for_action; })
        .handle<pinIncorrect>([&](const pinIncorrect& msg) {
          interface_hardware.send(displayPinIncorrect());
          state = &atm::done_processing;
        })
        .handle<cancelPressed>([&](const cancelPressed& msg) { state = &atm::done_processing; });
  }

  void getting_pin() {
    incoming.wait()
        .handle<digitPressed>([&](const digitPressed& msg) {
          const unsigned pin_length = 4;
          pin += msg.digit;
          if (pin.size() == pin_length) {
            bank.send(verifyPin(account, pin, incoming));
            state = &atm::verify_pin;
          }
        })
        .handle<clearLastPressed>([&](const clearLastPressed& msg) {
          if (!pin.empty()) {
            pin.pop_back();
          }
        })
        .handle<cancelPressed>([&](const cancelPressed& msg) { state = &atm::done_processing; });
  }

  void wait_for_card() {
    interface_hardware.send(displayEnterCard());
    incoming.wait().handle<cardInserted>([&](const cardInserted& msg) {
      account = msg.account;
      pin = "";
      interface_hardware.send(displayEnterPin());
      state = &atm::getting_pin;
    });
  }

  void done_processing() {
    interface_hardware.send(cardEjected());
    state = &atm::wait_for_card;
  }

  atm(const atm&) = delete;
  atm& operator=(const atm&) = delete;

 public:
  atm(messaging::sender bank_, messaging::sender interface_hardware_)
      : bank(bank_), interface_hardware(interface_hardware_) {
  }

  messaging::sender get_sender() {
    return incoming;
  }

  void done() {
    get_sender().send(messaging::close_queue());
  }
  
  void run() {
    state = &atm::wait_for_card;
    try {
      for (;;) {
        (this->*state)();
      }
    } catch (const messaging::close_queue&) {
    }
  }
};

#endif  //! _TELLER_STATE_H_