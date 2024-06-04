//
// Created by Simay Uygur- 22203328 -Section 1
//  17.03.2024
//

#ifndef DVDSTOREMANAGEMENTSYSTEM_H
#define DVDSTOREMANAGEMENTSYSTEM_H

#include "Dvd.h"
#include "Customer.h"
#include "Transaction.h"
using namespace std;
class DVDStoreManagementSystem {

private:
    Dvd* dvdArray;
    Customer* customerArray;
    Transaction* transactionHistory;
    int dvdArraySize;
    int customerArraySize;
    int transactionSize;

public:
    DVDStoreManagementSystem();
    ~DVDStoreManagementSystem();
    void addDVD( const string serialNo, const string title, const string director );
    void removeDVD( const string serialNo );
    void addCustomer( const int customerID, const string name );
    void removeCustomer( const int customerID );
    void rentDVD( const int customerID, const string serialNo );
    void returnDVD( const int customerID, const string serialNo );
    void showAllDVDs() const;
    void showAllCustomers() const;
    void showDVD( const string serialNo ) const;
    void showCustomer( const int customerID ) const;
    void showTransactionHistory() const;  // don't change these

    // my methods
    const int searchDvd(const string serialNo) const;
    const int searchCustomer(const int customerId) const;
    void addTransactionToHistory(const std::string& serialNo, int customerId, int choiceTransaction);

};


#endif
