//
// Created by Simay Uygur- 22203328 -Section 1
//  17.03.2024
//


#include "DVDStoreManagementSystem.h"
#include <string>
#include <iostream>

DVDStoreManagementSystem::DVDStoreManagementSystem() {

    dvdArray = nullptr;
    dvdArraySize = 0;
    customerArray = nullptr;
    customerArraySize = 0;
    transactionHistory = nullptr;
    transactionSize = 0;
}

DVDStoreManagementSystem::~DVDStoreManagementSystem() {
    if(dvdArraySize!=0)
        delete[] dvdArray;
    if(customerArraySize != 0)
        delete[] customerArray;
    if(transactionSize != 0)
        delete[] transactionHistory;
}

void DVDStoreManagementSystem::addDVD(const string serialNo, const string title, const string director) {

    if(dvdArraySize == 0){  //initializing the array instead of new Dvd[0]   hoca söyledi
        dvdArray = new Dvd[1];
        dvdArray[0] = Dvd(serialNo, title, director);
        dvdArraySize++;
        cout << "DVD with serial number " << serialNo << " successfully added." << endl;
        return;
    }

    const int tempSizeDvd = dvdArraySize +1;  // I saw this in the slides
    const int tempSizeLastIndex = tempSizeDvd - 1;

    for(int a=0; a<dvdArraySize; a++){
        if(serialNo == dvdArray[a].getId()){
            cout << "Cannot add DVD. DVD with serial number "<< serialNo << " already exists."<< endl;
            return;
        }
    }

    Dvd* tempArrDvd = new Dvd[tempSizeDvd];
    for(int i=0; i<dvdArraySize; i++) {
        tempArrDvd[i] = dvdArray[i];
    }

    delete[] dvdArray;
    tempArrDvd[tempSizeLastIndex] = Dvd(serialNo, title, director);  // new operator gives the address therefore I must use it in the pointer array (different case )
    dvdArray = tempArrDvd;
    dvdArraySize++;
    cout << "DVD with serial number " << serialNo << " successfully added." << endl;
}

void DVDStoreManagementSystem::removeDVD(const string serialNo) {

    const int tempSizeDvd = dvdArraySize -1;  // I saw this in the slides
    const int foundDvdIndex = searchDvd(serialNo);

    if(foundDvdIndex == -1){
        cout << "Cannot remove DVD. DVD with serial number "<< serialNo << " not found."<< endl;
        return;
    }

    if(dvdArray[foundDvdIndex].getAvailability() == 0){
        cout << "Cannot remove DVD. DVD with serial number " << serialNo << " is currently rented by a customer." << endl;
        return;
    } // not available ise

    // 0 olursa işte arrayi oluşturmasın diyerekten
    if(dvdArraySize == 1){
        delete[] dvdArray;
        dvdArray = nullptr;
        dvdArraySize--;
        cout << "DVD with serial number " << serialNo << " successfully removed." << endl;
        return;
    }

    Dvd* tempArrDvd = new Dvd[tempSizeDvd];

    for(int i=0; i<dvdArraySize && i!= foundDvdIndex; i++) {
        tempArrDvd[i] = dvdArray[i];
    }

    // && foundDvdIndex + j < dvdArraySize - 1
    for(int j=0; j+ foundDvdIndex<tempSizeDvd && foundDvdIndex != (dvdArraySize-1) ; j++){
        tempArrDvd[foundDvdIndex + j] = dvdArray[foundDvdIndex + j +1];  // emin değilim
    }

    delete[] dvdArray;
    dvdArray = tempArrDvd;
    dvdArraySize--;
    cout << "DVD with serial number " << serialNo << " successfully removed." << endl;
}

void DVDStoreManagementSystem::addCustomer(const int customerID, const string name) {

    string id = to_string(customerID);  // for printing

    if(customerArraySize == 0){  //initializing the array instead of new Dvd[0]
        customerArray = new Customer[1];
        customerArray[0] = Customer(customerID, name);
        customerArraySize++;
        cout << "Customer with ID " << id << " successfully added." << endl;
        return;
    }

    const int tempSizeCustomer = customerArraySize +1;  // I saw this in the slides   now i think that this was only the case in the dynamic array declaration
    const int tempSizeLastIndexCustomer = tempSizeCustomer - 1;

    for(int a=0; a<customerArraySize; a++){
        if(customerID == customerArray[a].getId()){
            cout << "Cannot add customer. Customer with ID "<< id << " already exists."<< endl;
            return;
        }
    }

    // customerarraysize negatif olur mu sence hiç
    Customer* tempArrCus = new Customer[tempSizeCustomer];
    for(int i=0; i<customerArraySize; i++) {
        tempArrCus[i] = customerArray[i];
    }

    delete[] customerArray;
    tempArrCus[tempSizeLastIndexCustomer] = Customer(customerID, name);
    customerArray = tempArrCus;
    customerArraySize++;
    cout << "Customer with ID " << id << " successfully added." << endl;
}

void DVDStoreManagementSystem::removeCustomer(const int customerID) {

    const string id = to_string(customerID);
    const int tempSizeCustomer = customerArraySize -1;  // I saw this in the slides

    const int foundCustomerIndex = searchCustomer(customerID);

    if(foundCustomerIndex == -1){
        cout << "Cannot remove customer. Customer with ID "<< id <<" not found."<< endl;
        return;
    }

    if(customerArray[foundCustomerIndex].getNumOfRentedDvds() !=0 ){
        cout << "Cannot remove customer. Customer with ID "<< customerID <<  " has rented DVDs." << endl;
        return;
    }

    if(customerArraySize == 1) // tek bi element kalmışsa sona nullptr yaomak lazım unutmuşum bunu
    {
        delete[] customerArray;
        customerArray = nullptr;
        customerArraySize--;
        cout << "Customer with ID " << id << " successfully removed." << endl;
        return;
    }

    Customer* tempArrCustomer = new Customer[tempSizeCustomer];

    for(int i=0; i <customerArraySize && i!= foundCustomerIndex; i++) {
        tempArrCustomer[i] = customerArray[i];
    }

    for(int j=0; j+ foundCustomerIndex<tempSizeCustomer && foundCustomerIndex != (customerArraySize-1) ; j++){
        tempArrCustomer[foundCustomerIndex + j] = customerArray[foundCustomerIndex + j +1];  // emin değilim
    }

    delete[] customerArray;
    customerArray = tempArrCustomer;
    customerArraySize--;

    cout << "Customer with ID " << id << " successfully removed." << endl;
}

void DVDStoreManagementSystem::rentDVD(const int customerID, const string serialNo) {
    const int searchDvdIndex = searchDvd(serialNo);
    const int searchCustomerIndex = searchCustomer(customerID);

    if( searchDvdIndex == -1 && searchCustomerIndex ==-1){
        cout << "Cannot rent DVD. Customer with ID " << customerID << " and DVD with serial number " << serialNo << " not found." << endl;
    }
    else if(searchDvdIndex != -1 && searchCustomerIndex == -1){
        cout << "Cannot rent DVD. Customer with ID " << customerID <<  " not found." << endl;
    }
    else if(searchDvdIndex == -1){
        cout << "Cannot rent DVD. DVD with serial number " << serialNo << " not found." << endl;
    }
    else {
        bool availability = dvdArray[searchDvdIndex].getAvailability();
        if (availability == 0) {  // available değil ise
            /*
            if(customerArray[searchCustomerIndex].searchRentedDvds(serialNo) == -1) // if hte current customer hadnt rented
                cout << "Cannot rent DVD. DVD with serial number " << serialNo << " is not available." << endl;
            else{
                cout << "Customer has already rented DVD with serial number " << serialNo << "." <<endl;
            },
            */
            cout << "Cannot rent DVD. DVD with serial number " << serialNo << " is not available." << endl;
        } else {

            customerArray[searchCustomerIndex].addDvdRenting(dvdArray[searchDvdIndex]);
            dvdArray[searchDvdIndex].setAvailability(false);
            addTransactionToHistory(serialNo, customerID, 0); //rented
            cout << "DVD with serial number " << serialNo << " successfully rented by customer with ID " << customerID
                << "." << endl;

        }
    }
}

void DVDStoreManagementSystem::returnDVD(const int customerID, const string serialNo) {

    const int searchDvdIndex = searchDvd(serialNo);
    const int searchCustomerIndex = searchCustomer(customerID);

    //check for validity of the search index   -->   or the given parameters

    if( searchDvdIndex == -1 && searchCustomerIndex ==-1){
        cout << "Cannot return DVD. Customer with ID " << customerID << " and DVD with serial number " << serialNo << " not found." << endl;
    }
    else if(searchDvdIndex != -1 && searchCustomerIndex == -1){
        cout << "Cannot return DVD. Customer with ID " << customerID <<  " not found." << endl;
    }
    else if(searchDvdIndex == -1){
        cout << "Cannot return DVD. DVD with serial number " << serialNo << " not found." << endl;
    }
    else {
        int foundIndexRentedDvd = customerArray[searchCustomerIndex].searchRentedDvds(serialNo); // returns wheter the dvd is rented by that specific customer

        if(foundIndexRentedDvd == -1){
            cout << "Cannot return DVD. DVD with serial number "<< serialNo <<" not rented by customer with ID "<< customerID << "."<< endl;
        }
        else {
            customerArray[searchCustomerIndex].removeDvdReturning(dvdArray[searchDvdIndex]);
            dvdArray[searchDvdIndex].setAvailability(true);
            addTransactionToHistory(serialNo, customerID, 1); //returning 1

            cout << "DVD with serial number " << serialNo << " successfully returned by customer with ID " << customerID
                 << "."<<endl;
        }
    }
}

void DVDStoreManagementSystem::showAllDVDs() const {

    cout << "DVDs in the system:" << endl;
    if(dvdArraySize ==0){
        cout<< "None"<< endl;
    }
    else{
        for(int j=0; j< dvdArraySize; j++){
            cout << "DVD: "<< dvdArray[j].getId() << ", Title: " << dvdArray[j].getTitle() << ", Director: " << dvdArray[j].getDirector() << ", " ;
            if(dvdArray[j].getAvailability() == 1){
                cout << "Available" << endl;
            }
            else{
                cout << "Rented" << endl;
            }
        }
    }
}

void DVDStoreManagementSystem::showAllCustomers() const {
    cout << "Customers in the system:" << endl;
    if(customerArraySize ==0){
        cout<< "None"<< endl;
    }
    else{
        for(int j=0; j<customerArraySize; j++){
            cout << "Customer: "<< to_string(customerArray[j].getId()) << ", Name: " << customerArray[j].getName() << ", DVDs Rented: " << customerArray[j].getNumOfRentedDvds() <<endl;

        }
    }

}

void DVDStoreManagementSystem::showDVD(const string serialNo) const {
    const int foundDvdIndex = searchDvd(serialNo);
    if(foundDvdIndex != -1 && foundDvdIndex < dvdArraySize ){ // başka şart var mıydı bilemedim
        cout << "DVD: "<< dvdArray[foundDvdIndex].getId() << ", Title: " << dvdArray[foundDvdIndex].getTitle() << ", Director: " << dvdArray[foundDvdIndex].getDirector() << ", " ;
        if(dvdArray[foundDvdIndex].getAvailability() == 1){  // belki bunun için de bi metot yaparım
            cout << "Available" << endl;
        }
        else{
            cout << "Rented" << endl;
        }
    }
    else{
        cout << "DVD with serial number "<< serialNo << " not found."<< endl;
    }

}

void DVDStoreManagementSystem::showCustomer(const int customerID) const {

    const int foundCustomerIndex = searchCustomer(customerID) ;

    if(foundCustomerIndex != -1 && foundCustomerIndex < customerArraySize ){ // başka şart var mıydı bilemedim
        //string id = to_string(customerArray[foundCustomerIndex].getId());    buna gerek yok ki neden koymuşum
        cout << "Customer: "<< customerID << ", Name: " << customerArray[foundCustomerIndex].getName() << ", DVDs Rented: " << customerArray[foundCustomerIndex].getNumOfRentedDvds() << endl;
    }

    else{
        cout << "Customer with ID "<< customerID << " not found."<< endl;
    }

}

void DVDStoreManagementSystem::showTransactionHistory() const {

    cout << "Transactions in the system:" << endl;
    if( transactionSize == 0){
        cout<< "None"<< endl;
    }
    else{
        for(int j=0; j< transactionSize; j++){
            string type;
            if(transactionHistory[j].getType() == Transaction::RENTAL)
                type = "Rental";
            else{
                type = "Return";
            }
            cout << "Transaction: "<< type << ", Customer: "<< transactionHistory[j].getCustomerID() << ", DVD: " << transactionHistory[j].getSerialNo()<< endl;

        }
    }
}

const int DVDStoreManagementSystem::searchDvd(const string serialNo) const {

    for(int y=0; y< dvdArraySize; y++){
        if(serialNo == dvdArray[y].getId()){
            return y;
        }
    }
    return -1;
}

const int DVDStoreManagementSystem::searchCustomer(const int customerId) const {

    for(int y=0; y< customerArraySize; y++){
        if(customerArray[y].getId() == customerId){
            return y;
        }
    }
    return -1;
}

void DVDStoreManagementSystem::addTransactionToHistory(const std::string& serialNo, int customerId, int choiceTransaction) {

    if (transactionSize == 0) {
        transactionHistory = new Transaction[1];
        if (choiceTransaction == 0)
            transactionHistory[0] = Transaction(Transaction::RENTAL, customerId, serialNo);
        else if(choiceTransaction ==1){
            transactionHistory[0] = Transaction(Transaction::RETURN, customerId, serialNo);
        }
        transactionSize++;  // i forgot that
        return;
    }
    const int size = transactionSize + 1;
    Transaction* tempHistory = new Transaction[size];

    for (int a = 0; a < transactionSize; a++) {
        tempHistory[a] = transactionHistory[a];
    }

    delete[] transactionHistory;

    if (choiceTransaction == 0)
        tempHistory[transactionSize] = Transaction(Transaction::RENTAL, customerId, serialNo);
    else if (choiceTransaction ==1){
        tempHistory[transactionSize] = Transaction(Transaction::RETURN, customerId, serialNo);
    }
    transactionHistory = tempHistory;
    transactionSize++;
}


