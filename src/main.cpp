#include <iostream>
#include "base_components_manager.h"
#include <ctime>

// TODO implement logger
// TOTO doxigen doc

int main() {

  time_t my_time = time(NULL);
  std::cout << "run done at: " << ctime(&my_time) << std::endl;
//  std::thread thread(BaseComponentsManager::test_event_loop, 1000 /*ms*/);
  auto& manager = BaseComponentsManager::getManager();
  int dummy;
  std::cin >> dummy;
}
