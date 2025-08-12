#include <BankSystem.hpp>

Transaction::Transaction(const std::string& typ, double amnt, double post) : type(typ), amount(amnt), postBalance(post) {}

Transaction::Transaction(const Transaction& other) : type(other.type), amount(other.amount), postBalance(other.postBalance) {}

Transaction::Transaction(Transaction&& other) noexcept : type(std::move(other.type)), amount(other.amount), postBalance(other.postBalance) {
    other.type.clear();
    other.amount = 0.0;
    other.postBalance = 0.0;
}

Transaction& Transaction::operator=(const Transaction& other) {
    if (this != &other) {
        type = other.type;
        amount = other.amount;
        postBalance = other.postBalance;
    }
    return *this;
}

Transaction& Transaction::operator=(Transaction&& other) noexcept {
    if (this != &other) {
        type = std::move(other.type);
        amount = other.amount;
        postBalance = other.postBalance;
        other.type.clear();
        other.amount = 0.0;
        other.postBalance = 0.0;
    }
    return *this;
}

TransactionLogger::TransactionLogger(const TransactionLogger& other) {
    for (auto t : other.log) {
        log.push_back(new Transaction(*t));
    }
}

TransactionLogger::TransactionLogger(TransactionLogger&& other) noexcept : log(std::move(other.log)) {
    other.log.clear();
}

TransactionLogger& TransactionLogger::operator=(const TransactionLogger& other) {
    if (this != &other) {
        for (auto t : other.log) {
            log.push_back(new Transaction(*t));
        }
    }
    return *this;
}

TransactionLogger& TransactionLogger::operator=(TransactionLogger&& other) noexcept {
    if (this != &other) {
        log = std::move(other.log);
        other.log.clear();
    }
    return *this;
}

TransactionLogger::~TransactionLogger() {
    for (auto t : log) delete t;
}

void TransactionLogger::addLog(Transaction* transaction) { log.push_back(transaction); }

BankAccount::BankAccount(const BankAccount& other) : balance(other.balance), logger(other.logger) {}

BankAccount::BankAccount(BankAccount&& other) noexcept : balance(other.balance), logger(std::move(other.logger)) {
    other.balance = 0.0;
}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        balance = other.balance;
        logger = other.logger;
    }
    return *this;
}

BankAccount& BankAccount::operator=(BankAccount&& other) noexcept {
    if (this != &other) {
        balance = other.balance;
        logger = std::move(other.logger);
        other.balance = 0.0;
    }
    return *this;
}

double BankAccount::getBalance() const {return balance;}

SavingsAccount::SavingsAccount(int precent) : rate(precent), monthCashBack(0) {}

SavingsAccount::SavingsAccount(const SavingsAccount& other) : BankAccount(other), rate(other.rate), monthCashBack(other.monthCashBack) {}

SavingsAccount::SavingsAccount(SavingsAccount&& other) noexcept : BankAccount(std::move(other)), rate(other.rate), monthCashBack(other.monthCashBack) {
    other.rate = 0;
    other.monthCashBack = 0.0;
}

SavingsAccount& SavingsAccount::operator=(const SavingsAccount& other) {
    if (this != &other) {
        BankAccount::operator=(other);
        rate = other.rate;
        monthCashBack = other.monthCashBack;
    }
    return *this;
}

SavingsAccount& SavingsAccount::operator=(SavingsAccount&& other) noexcept {
    if (this != &other) {
        rate = other.rate;
        monthCashBack = other.monthCashBack;
        other.rate = 0;
        monthCashBack = 0.0;
    }
    return *this;
}

void SavingsAccount::deposit(double amount) {
    monthCashBack += (amount / 100) * rate;
    balance += amount;
    logger.addLog(new Transaction("Savings acc: Deposit", amount, balance));
}

void SavingsAccount::withdraw(double amount) {
    if (amount > balance) {
        logger.addLog(new Transaction("Savings acc: Withdraw failure, insufficient funds!", amount, balance));
        return;
    }
    balance -= amount;
    logger.addLog(new Transaction("Savings acc: Withdraw", amount, balance));
}

void SavingsAccount::monthEnd() {
    balance += monthCashBack;
    logger.addLog(new Transaction("Savings acc: Monthly cashback", monthCashBack, balance));
}
 
CheckingAccount::CheckingAccount(double overdraftSize) : overdraft(overdraftSize) {}

CheckingAccount::CheckingAccount(const CheckingAccount& other) : BankAccount(other), overdraft(other.overdraft) {}

CheckingAccount::CheckingAccount(CheckingAccount&& other) noexcept : BankAccount(std::move(other)), overdraft(other.overdraft) {
    other.overdraft = 0.0;
}

CheckingAccount& CheckingAccount::operator=(const CheckingAccount& other) {
    if (this != &other) {
        BankAccount::operator=(other);
        overdraft = other.overdraft;
    }
    return *this;
}

CheckingAccount& CheckingAccount::operator=(CheckingAccount&& other) {
    BankAccount::operator=(std::move(other));
    if (this != &other) {
        overdraft = other.overdraft;
        other.overdraft = 0.0;
    }
    return *this;
}

void CheckingAccount::deposit(double amount) {
    balance += amount;
    logger.addLog(new Transaction("Checking acc: Deposit", amount, balance));
}

void CheckingAccount::withdraw(double amount) {
    if (balance - amount < overdraft) {
        logger.addLog(new Transaction("Checking acc: Withdraw failure, limit exceeded", amount, balance));
        return;
    }
    balance -= amount;
    logger.addLog(new Transaction("Checking acc: Withdraw", amount, balance));
}

void CheckingAccount::monthEnd() {
    logger.addLog(new Transaction("Checking acc: Month end", 0, balance));
}