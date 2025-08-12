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
    Transaction(const std::string& typ, double amnt, double post);
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
    protected:
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
        SavingsAccount& operator=(SavingsAccount&& other) noexcept;
        ~SavingsAccount () = default;

        void deposit(double amount) override;
        void withdraw(double amount) override;
        void monthEnd() override;
};

class CheckingAccount : public BankAccount {
        double overdraft;
    public:
        CheckingAccount(double overdraftSize);
        CheckingAccount(const CheckingAccount& other);
        CheckingAccount(CheckingAccount&& other) noexcept;
        CheckingAccount& operator=(const CheckingAccount& other);
        CheckingAccount& operator=(CheckingAccount&& other);
        void deposit(double amount) override;
        void withdraw(double amount) override;
        void monthEnd() override;
};

#endif