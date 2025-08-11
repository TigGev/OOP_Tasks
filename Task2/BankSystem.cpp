#include <BankSystem.hpp>

Transaction::Transaction(std::string typ, double amnt, double post) : type(typ), amount(amnt), postBalance(post) {}

Transaction::Transaction(const Transaction& other) : type(other.type), amount(other.amount), postBalance(other.postBalance) {}

Transaction::Transaction(Transaction&& other) noexcept : type(std::move(other.type)), amount(other.amount), postBalance(other.postBalance) {
    other.type.clear();
    other.amount = 0.0;
    other.postBalance = 0.0;
}

Transaction& Transaction::operator=(const Transaction& other) {
    type = other.type;
    amount = other.amount;
    postBalance = other.postBalance;
}

Transaction& Transaction::operator=(Transaction&& other) noexcept {
    type = std::move(other.type);
    amount = other.amount;
    postBalance = other.postBalance;
    other.type.clear();
    other.amount = 0.0;
    other.postBalance = 0.0;
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
    for (auto t : other.log) {
        log.push_back(new Transaction(*t));
    }
}

TransactionLogger& TransactionLogger::operator=(TransactionLogger&& other) noexcept {
    log = std::move(other.log);
    other.log.clear();
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
    balance = other.balance;
    logger = other.logger;
}

BankAccount& BankAccount::operator=(BankAccount&& other) noexcept {
    balance = other.balance;
    logger = std::move(other.logger);
    other.balance = 0.0;
}

double BankAccount::getBalance() const {return balance;}

SavingsAccount::SavingsAccount(int precent) : rate(precent), monthCashBack(0) {}

SavingsAccount::SavingsAccount(const SavingsAccount& other) : BankAccount(other), rate(other.rate), monthCashBack(other.monthCashBack) {}

SavingsAccount::SavingsAccount(SavingsAccount&& other) noexcept : BankAccount(std::move(other)), rate(other.rate), monthCashBack(other.monthCashBack) {
    other.rate = 0;
    other.monthCashBack = 0.0;
}
