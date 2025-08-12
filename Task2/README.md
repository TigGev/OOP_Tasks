Bank Account Hierarchy Project
Overview
This project implements a bank account system in C++ that demonstrates the Rule of 5, inheritance, and proper encapsulation. It includes two types of bank accounts: SavingsAccount and CheckingAccount, with a transaction logging system.
Features

BankAccount: Abstract base class with pure virtual methods for deposit, withdraw, and month-end processing.
SavingsAccount: Supports deposits, withdrawals, and monthly interest accrual based on a specified rate.
CheckingAccount: Supports deposits, withdrawals with an overdraft limit, and month-end processing.
TransactionLogger: Manages a heap-allocated log of transactions, implementing the Rule of 5.
Rule of 5: All classes (Transaction, TransactionLogger, BankAccount, SavingsAccount, CheckingAccount) properly implement copy/move constructors and assignment operators.
Encapsulation: Private balances with public access methods, validation for negative amounts, and logging for invalid operations.

Files

BankSystem.hpp: Header file with class definitions.
BankSystem.cpp: Implementation of class methods.
main.cpp: Demonstrates account operations, transaction logging, and copy/move semantics.
Makefile: Builds the project.
README.md: This file.

Requirements

C++11 or later
g++ compiler
Standard C++ library

Build Instructions

Ensure you have g++ installed.
Run make to compile the project.
Run ./bank_system to execute the program.
Use make clean to remove object files and the executable.

Usage
The main.cpp file demonstrates:

Creating SavingsAccount and CheckingAccount objects.
Performing deposits and withdrawals.
Handling invalid operations (e.g., withdrawing beyond balance or overdraft limit).
Applying month-end processing (interest for SavingsAccount).
Testing copy and move semantics.

Example Output
Created SavingsAccount with 5% interest rate
Savings: Deposited $1000. Balance: $1000
Savings: Withdrew $500. Balance: $500
Savings: Attempted to withdraw $1000. Balance: $500
Savings: After month-end cashback. Balance: $525

Created CheckingAccount with $200 overdraft limit
Checking: Deposited $300. Balance: $300
Checking: Withdrew $400. Balance: $-100
Checking: Attempted to withdraw $100. Balance: $-100
Checking: After month-end. Balance: $-100

Testing copy and move semantics:
Savings copy balance: $525
Moved Checking balance: $-100
Original Checking balance after move: $0

Notes

The project avoids exceptions for invalid operations, instead logging failures as specified.
TransactionLogger properly manages heap memory with Rule of 5 compliance.
SavingsAccount calculates interest as a percentage of deposits made during the month, applied at month-end.
CheckingAccount allows withdrawals up to the overdraft limit.
