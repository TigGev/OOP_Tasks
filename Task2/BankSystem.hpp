#ifndef BANKING_SYSTEM_HEADER
#define BANKING_SYSTEM_HEADER
#include <iostream>
#include <vector>
#include <string>
#include <iostream>



struct Transaction {
    std::string type;
    double amount;
    double postBalance;
    Transaction(std::string typ, double amnt, double post);
    Transaction(const Transaction& other);
    Transaction(Transaction&& other) noexcept;
    Transaction& operator=(const Transaction& other);
    Transaction& operator=(Transaction&& other) noexcept;
    ~Transaction() = default;
};

class TransactionLogger {
        std::vector<Transaction*> log;
    public:
        TransactionLogger() = default;
        TransactionLogger(const TransactionLogger& other);
        TransactionLogger(TransactionLogger&& other) noexcept;
        TransactionLogger& operator=(const TransactionLogger& other);
        TransactionLogger& operator=(TransactionLogger&& other) noexcept;
        ~TransactionLogger();

        void addLog(Transaction* transaction);
};

class BankAccount {
        double balance;
        TransactionLogger logger;
    public:
        BankAccount() = default;
        BankAccount(const BankAccount& other);
        BankAccount(BankAccount&& other) noexcept;
        BankAccount& operator=(const BankAccount& rhs);
        BankAccount& operator=(BankAccount&& rhs) noexcept;
        virtual ~BankAccount() = default;

        virtual void deposit(double amount) = 0;
        virtual void withdraw(double amount) = 0;  
        virtual double getBalance() const;
        virtual void monthEnd() = 0;
};

class SavingsAccount : public BankAccount {
        int rate;
        double monthCashBack;
    public:
        SavingsAccount(int precent);
        SavingsAccount(const SavingsAccount& other);
        SavingsAccount(SavingsAccount&& other) noexcept;
        SavingsAccount& operator=(const SavingsAccount& other);
        SavingsAccount& operator=(SavingsAccount&& other);
        ~SavingsAccount () = default;

        void deposit(double amount) override;
        void withdraw(double amount) override;
};

// class BankAccount {
    // protected:
        // double balance;
        // std::vector<std::string*> transactionHistory;
    // public:
        // BankAccount() = default;
        // BankAccount(const BankAccount& other) : balance(other.balance) {
            // for (auto i : other.transactionHistory) {
                // transactionHistory.push_back(new std::string(*i));
            // }
        // }
        // BankAccount(BankAccount&& other) noexcept : balance(other.balance), transactionHistory(std::move(other.transactionHistory)) {
            // other.transactionHistory.clear();
            // other.balance = 0.0;
        // }
        // BankAccount& operator=(const BankAccount& rhs) {
            // balance = rhs.balance;
            // for (auto i : transactionHistory) {
                // delete i;
            // }
            // for (auto i : rhs.transactionHistory) {
                // transactionHistory.push_back(new std::string(*i));
            // }
            // return *this;
        // }
        // BankAccount& operator=(BankAccount&& rhs) noexcept {
            // balance = rhs.balance;
            // for (auto i : transactionHistory) {
                // delete i;
            // }
            // transactionHistory.clear();
            // transactionHistory = std::move(rhs.transactionHistory);
// 
            // rhs.transactionHistory.clear();
            // balance = 0.0;
            // return *this;
        // }
        // virtual ~BankAccount() {
            // for (auto i : transactionHistory) delete i;
        // }
// 
        // virtual void deposit(double amount) = 0;
        // virtual void withdraw(double amount) = 0;  
        // virtual int balance() {return balance;}
// };
// 
// class SavingsAccount : public BankAccount {
        // int precent;
    // public:
        // SavingsAccount(int CBackPrecent) : precent(CBackPrecent) {}
        // SavingsAccount(const SavingsAccount& other) : BankAccount(other), precent(other.precent) {}
        // SavingsAccount(SavingsAccount&& other) noexcept : BankAccount(std::move(other)), precent(other.precent)  {
            // other.precent = 0;
        // }
        // SavingsAccount& operator=(const SavingsAccount& other) {
            // if (this != &other) {
                // BankAccount::operator=(other);
                // precent = other.precent;
            // }
            // return *this;
        // }
        // SavingsAccount& operator=(SavingsAccount&& other) {
            // if (this != &other) {
                // BankAccount::operator=(std::move(other));
                // precent = other.precent;
                // other.precent = 0;
            // }
            // return *this;
        // }
        // ~SavingsAccount () = default;
// 
        // void deposit(double amount) override {
            // double rate = (amount / 100) * precent;
            // balance += amount + rate;
            // std::string* msg = new std::string("deposit: ");
            // *msg += std::to_string(amount) + " + cashback: " + std::to_string(rate);
            // transactionHistory.push_back(msg);
        // }
// 
        // void withdraw(double amount) override {
            // std::string* msg = new std::string("withdraw: ");
            // if (amount > balance) {
                // *msg += "Failure - 'insufficend funds'";
                // transactionHistory.push_back(msg);
                // return;
            // }
            // balance -= amount;
            // *msg += std::to_string(amount);
        // }
// };
// 
// class CheckingAccount : public BankAccount {
        // double overdraft;
    // public:
        // CheckingAccount(double overdraftSize) : BankAccount(), overdraft(overdraftSize) {}
        // CheckingAccount(const CheckingAccount& other) : BankAccount(other), overdraft(other.overdraft) {}
        // CheckingAccount(CheckingAccount&& other) noexcept : BankAccount(std::move(other)), overdraft(other.overdraft) {
                // other.overdraft = 0.0;
        // }
        // CheckingAccount& operator=(const CheckingAccount& other) {
            // if (this != &other) {
                // BankAccount::operator=(other);
                // overdraft = other.overdraft;
            // }
            // return *this;
        // }
        // CheckingAccount& operator=(CheckingAccount&& other) {
            // if (this != &other) {
                // BankAccount::operator=(std::move(other));
                // overdraft = other.overdraft;
                // other.overdraft = 0.0;
            // }
            // return *this;
        // }
// 
        // void deposit(double amount) override {
            // balance += amount;
            // std::string* msg = new std::string("deposit: ");
            // *msg += std::to_string(amount);
            // transactionHistory.push_back(msg);
        // }
// 
        // void withdraw(double amount) override {
            // std::string* msg = new std::string("withdraw: ");
            // if (balance - amount < overdraft) {
                // *msg += "Failure - 'the overdraft amount exceeds the limit'";
                // transactionHistory.push_back(msg);
                // return;
            // }
            // *msg += std::to_string(amount);
            // transactionHistory.push_back(msg);
        // }
// };
#endif