//
// Created by Simay Uygur- 22203328
//  17.03.2024
//

#include "Transaction.h"
#include <iostream>    // sonra silerim bunu belki

Transaction::Transaction(TransactionType transactionType, const int& customerIdGiven, const std::string& serialNoGiven)
{
    this->type = transactionType;
    this->customerID = customerIdGiven;
    this->serialNo = serialNoGiven;
}

Transaction::TransactionType Transaction::getType() const {
    return type;
}

int Transaction::getCustomerID() const {
    return customerID;
}

const std::string& Transaction::getSerialNo() const {
    return serialNo;
}

Transaction::~Transaction() = default;

Transaction::Transaction() {
    serialNo = "";
    type = NONE;  //ben ekledim
    customerID = 0;
    //std::cout << "deafoukt one "<< customerID << " ser, "<<  serialNo << std::endl ;
}

