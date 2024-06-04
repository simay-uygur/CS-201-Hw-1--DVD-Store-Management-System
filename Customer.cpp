//
// Created by Simay Uygur- 22203328 -Section 1
//  17.03.2024
//


#include "Customer.h"
#include "Dvd.h"
#include <iostream>


Customer::Customer(const int cusId, const std::string& cusName)
{
    id = cusId;
    customerName = cusName;
    numDvdRented = 0;
    rentedDvds = nullptr;
}

Customer::Customer() {
    id = -100;
    customerName = "";
    numDvdRented = 0;
    rentedDvds = nullptr;
}

Customer::~Customer() {
    if(numDvdRented !=0){
        delete[] rentedDvds;  //ben zekiymişim
    }
}

int Customer::getId() const {
    return id;
}

void Customer::setId(const int no) {  // int girdiğini mi assumelayacağım
    id = no;
}

int Customer::getNumOfRentedDvds() const {
    return numDvdRented;
}

std::string Customer::getName() const {
    return customerName;
}

void Customer::setName(const std::string& name) {
    customerName = name;
}

void Customer::displayCustomer() const {
    std::cout << "Customer with ID " << id << " successfully added. this is the other method.." << std::endl;
}

void Customer::addDvdRenting(Dvd& dvdRenting ) {

    if(numDvdRented == 0 ){
        rentedDvds = new Dvd*[1];
        rentedDvds[0] = &dvdRenting;
        numDvdRented++;
        return;
    }

    const int tempSizeRentedDvds = numDvdRented +1;
    const int tempSizeLastIndexRented = tempSizeRentedDvds - 1;
    Dvd** tempArrDvd = new Dvd*[tempSizeRentedDvds];

    for(int i=0; i<numDvdRented; i++) {
        //umarım kopyalar
        tempArrDvd[i] = rentedDvds[i];
    }

    tempArrDvd[tempSizeLastIndexRented] = &dvdRenting;  //bakalım
    delete[] rentedDvds;
    rentedDvds = tempArrDvd;// burayı unutmuşum ağlicam ama en azından biraz debuglamayı öğrendim
    numDvdRented++;
}


void Customer::removeDvdReturning(Dvd &dvdRenting) {
    if(numDvdRented == 1){
        delete[] rentedDvds;
        rentedDvds = nullptr;
        numDvdRented--;
        return;
    }

    const int tempSizeRentedDvds = numDvdRented -1;  //bunu artı bırakmışım salak gibi yanlışlıkla
    const int foundIndexRentedDvd = searchRentedDvds(dvdRenting.getId());

    Dvd** tempArrRentedDvd = new Dvd*[tempSizeRentedDvds];

    for(int i=0; i < numDvdRented && i != foundIndexRentedDvd; i++) {
        tempArrRentedDvd[i] = rentedDvds[i];    // burada eşitleyip silmesi mantıklı mı pointer bunlar  biraz düşünücem olmadı printleyip nakmam gerekiyo şu an beynim yetmedi
    }

    // && foundDvdIndex + j < dvdArraySize - 1 bunu anlamadım
    for(int j=0; j+ foundIndexRentedDvd < tempSizeRentedDvds && foundIndexRentedDvd != (numDvdRented-1) ; j++){
        tempArrRentedDvd[foundIndexRentedDvd + j] = rentedDvds[foundIndexRentedDvd + j +1];
    }

    delete[] rentedDvds;
    rentedDvds = tempArrRentedDvd;
    numDvdRented--;

}

void Customer::showRentedDvds() const {
    std::cout << "rented dvd: " << std::endl;
    if(numDvdRented == 0)
        std::cout << "None. " << std::endl;
    for(int a=0; a<numDvdRented; a++){
        std::cout << rentedDvds[a]->to_stringDvd() << " .";
    }
    std::cout << std::endl;
}

int Customer::searchRentedDvds(const std::string& serialNo) {
    for(int i =0; i<numDvdRented && rentedDvds != nullptr; i++){
        if (serialNo == (rentedDvds[i])->getId())
            return i;
    }
    return -1;

}

void Customer::setNumOfRentedDvds(int num) {
    numDvdRented = num;
}

Customer& Customer::operator=(const Customer& right)
{
    if (&right != this)
    {
        this->setId(right.getId());
        this->setName(right.getName());
        this->setNumOfRentedDvds(right.getNumOfRentedDvds());

        if (right.getNumOfRentedDvds() != numDvdRented)
        {
            delete[] rentedDvds;
            rentedDvds = nullptr;
            numDvdRented = right.getNumOfRentedDvds();
            rentedDvds = new Dvd*[numDvdRented];
        }

        for (int i = 0; i < numDvdRented; i++)
        {
            rentedDvds[i] = new Dvd(*(right.rentedDvds[i])); // Perform deep copy
        }
    }

    return *this;
}
