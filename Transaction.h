//
// Created by Simay Uygur- 22203328
//  17.03.2024
//


#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    enum TransactionType {
        RENTAL,
        RETURN,
        NONE
    };

    Transaction(TransactionType transactionType, const int& customerIdGiven, const std::string& serialNoGiven);
    Transaction();
    ~Transaction();

    TransactionType getType() const;
    int getCustomerID() const;
    const std::string& getSerialNo() const;

private:
    TransactionType type;
    int customerID;
    std::string serialNo;
};

#endif
