#include "bank_state.h"
#include "interface_machine.h"
#include "teller_state.h"
#include <thread>

int main() {
  bank_machine bank;
  interface_machine interface_hardware;
  atm machine(bank.get_sender(), interface_hardware.get_sender());
  std::thread bank_thread(&bank_machine::run, &bank);
  std::thread if_thread(&interface_machine::run, &interface_hardware);
  std::thread atm_thread(&atm::run, &machine);
  messaging::sender atm_queue(machine.get_sender());
  bool quit_pressed = false;
  while (!quit_pressed) {
    char c = getchar();
    switch (c) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        atm_queue.send(digitPressed(c));
        break;
      case 'b':
        atm_queue.send(balancePressed());
        break;
      case 'w':
        atm_queue.send(withdrawPressed(50));
        break;
      case 'c':
        atm_queue.send(cancelPressed());
        break;
      case 'q':
        quit_pressed = true;
        break;
      case 'i':
        atm_queue.send(cardInserted("github123"));
        break;
    }
  }
  bank.done();
  machine.done();
  interface_hardware.done();
  bank_thread.join();
  atm_thread.join();
  if_thread.join();
}