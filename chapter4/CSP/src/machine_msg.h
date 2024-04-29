#ifndef _MACHINE_MSG_H_
#define _MACHINE_MSG_H_

#include <string>
#include "message.h"

struct withdraw {
  std::string account;
  unsigned amount;
  mutable messaging::sender atm_queue;
  withdraw(const std::string& account_, unsigned amount_, messaging::sender atm_queue_)
      : account(account_), amount(amount_), atm_queue(atm_queue_) {
  }
};

struct withdrawOk {
  withdrawOk() {
    std::cout << "withdraw OK!" << std::endl;
  }
};

struct withdrawDenied {
  withdrawDenied() {
    std::cout << "withdraw denied!" << std::endl;
  }
};

struct withdrawCanceled {
  std::string account;
  unsigned amount;
  withdrawCanceled(std::string account_, unsigned amount_) : account(account_), amount(amount_) {
  }
};

struct withdrawPocessed {
  std::string account;
  unsigned amount;
  withdrawPocessed(std::string account_, unsigned amount_) : account(account_), amount(amount_) {
  }
};

struct cardInserted {
  std::string account;
  explicit cardInserted(const std::string& account_) : account(account_) {
  }
};

struct digitPressed {
  char digit;
  explicit digitPressed(char digit_) : digit(digit_) {
  }
};

struct clearLastPressed {
  clearLastPressed() {
    std::cout << "last pressed have been cleared" << std::endl;
  }
};

struct cardEjected {
  cardEjected() {
    std::cout << "the card have been ejected!" << std::endl;
  }
};

struct withdrawPressed {
  unsigned amount;
  withdrawPressed(unsigned amount_) : amount(amount_) {
  }
};

struct cancelPressed {
  cancelPressed() {
    std::cout << "cancel have been pressed." << std::endl;
  }
};

struct issueMoney {
  unsigned amount;
  issueMoney(unsigned amount_) : amount(amount_) {
  }
};

struct verifyPin {
  std::string account;
  std::string pin;
  mutable messaging::sender atm_queue;
  verifyPin(const std::string& account_, const std::string& pin_, messaging::sender atm_queue_)
      : account(account_), pin(pin_), atm_queue(atm_queue_) {
  }
};

struct pinVerified {
  pinVerified() {
    std::cout << "pin is verified." << std::endl;
  }
};

struct pinIncorrect {
  pinIncorrect() {
    std::cout << "pin is incorrect" << std::endl;
  }
};

struct displayEnterPin {
  displayEnterPin() {
    std::cout << "display enter pin" << std::endl;
  }
};

struct displayEnterCard {
  displayEnterCard() {
    std::cout << "display enter card." << std::endl;
  }
};

struct displayInsuffientFunds {
  displayInsuffientFunds() {
    std::cout << "funds are insuffient." << std::endl;
  }
};

struct displayWithdrawCanceled {
  displayWithdrawCanceled() {
    std::cout << "withdraw have been canceled." << std::endl;
  }
};

struct displayPinIncorrect {
  displayPinIncorrect() {
    std::cout << "pin is incorrect" << std::endl;
  }
};

struct displayWithdrawOptions {
  displayWithdrawOptions() {
    std::cout << "withdraw options." << std::endl;
  }
};

struct getBalance {
  std::string account;
  mutable messaging::sender atm_queue;
  getBalance(const std::string& account_, messaging::sender atm_queue_) : account(account_), atm_queue(atm_queue_) {
  }
};

struct balance {
  unsigned amount;
  explicit balance(unsigned amount_) : amount(amount_) {
  }
};

struct displayBalance {
  unsigned amount;
  explicit displayBalance(unsigned amount_) : amount(amount_) {
  }
};

struct balancePressed {
  balancePressed() {
    std::cout << "balance pressed." << std::endl;
  }
};

#endif  //! _MACHINE_MSG_H_