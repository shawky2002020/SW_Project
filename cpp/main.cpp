#include "BankSystem.h"
#include <iostream>

int main() {
    std::cout << "--- Bank System Initializing ---\n";
    
    // Run the main system logic loop
    BankSystem::getInstance()->run();
    
    std::cout << "--- System Shutting Down ---\n";
    return 0;
}
