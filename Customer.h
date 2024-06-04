//
// Created by Simay Uygur- 22203328 -Section 1
//  17.03.2024
//


#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Dvd.h"

class Customer{
private:
    int id;
    std::string customerName;
    int numDvdRented; //initially not rented any (from the document)
    Dvd** rentedDvds;

public:
    Customer();
    Customer(const int cusId, const std::string& cusName); // bana önerdi clion reference yapmamı
    ~Customer();

    int getId() const;
    void setId(const int no);
    int getNumOfRentedDvds() const;

    std::string getName() const;
    void setName(const std::string& name);

    void displayCustomer() const;
    void addDvdRenting(Dvd& dvdRenting);
    void removeDvdReturning(Dvd& dvdRenting);

    void showRentedDvds() const;
    int searchRentedDvds(const std::string& serialNo);

    Customer& operator=(const Customer& right);

    void setNumOfRentedDvds(int num);
};


#endif
