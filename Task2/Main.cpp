#include <BankSystem.hpp>
#include <iostream>

int main() {
    
    SavingsAccount savings(5);
    std::cout << "Created SavingsAccount with 5% interest rate\n";
  
    savings.deposit(1000.0);
    std::cout << "Savings: Deposited $1000. Balance: $" << savings.getBalance() << "\n";
    savings.withdraw(500.0);
    std::cout << "Savings: Withdrew $500. Balance: $" << savings.getBalance() << "\n";
    savings.withdraw(1000.0);
    std::cout << "Savings: Attempted to withdraw $1000. Balance: $" << savings.getBalance() << "\n";
    savings.monthEnd();
    std::cout << "Savings: After month-end cashback. Balance: $" << savings.getBalance() << "\n\n";
   
    CheckingAccount checking(200.0);
    std::cout << "Created CheckingAccount with $200 overdraft limit\n";

    checking.deposit(300.0);
    std::cout << "Checking: Deposited $300. Balance: $" << checking.getBalance() << "\n";
    checking.withdraw(400.0);
    std::cout << "Checking: Withdrew $400. Balance: $" << checking.getBalance() << "\n";
    checking.withdraw(100.0);
    std::cout << "Checking: Attempted to withdraw $100. Balance: $" << checking.getBalance() << "\n";
    checking.monthEnd();
    std::cout << "Checking: After month-end. Balance: $" << checking.getBalance() << "\n\n";

    std::cout << "Testing copy and move semantics:\n";
    SavingsAccount savingsCopy = savings;
    std::cout << "Savings copy balance: $" << savingsCopy.getBalance() << "\n";
    CheckingAccount checkingMoved = std::move(checking);
    std::cout << "Moved Checking balance: $" << checkingMoved.getBalance() << "\n";
    std::cout << "Original Checking balance after move: $" << checking.getBalance() << "\n";

    return 0;
}