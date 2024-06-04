//
// Created by Simay Uygur- 22203328 -Section 1
//  17.03.2024
//



#include "Dvd.h"
#include <string>


Dvd::Dvd(const std::string serialNo, const std::string tit, const std::string dir)
{
    serialNumber = serialNo;
    title = tit;
    director = dir;
    isAvailable = true;
}

Dvd::Dvd() {
    serialNumber ="0";
    title = "";
    director = "";
    isAvailable = true;
}

Dvd::~Dvd() {
    // Destructor, if needed
}

std::string Dvd::getId() const{
    return serialNumber;
}

void Dvd:: setId(const std::string no){
    serialNumber = no;
}

std::string Dvd::getDirector() const{
    return director;
}

void Dvd:: setDirector(const std::string dtr){
    director = dtr;
}

bool Dvd::getAvailability() const{
    return isAvailable;
}

void Dvd::setAvailability(bool x){
    isAvailable = x;
}

std::string Dvd::getTitle() const{
    return title;
}

//are those necessary? idk
void Dvd:: setTitle(const std:: string tit){
    title = tit;
}

std::string Dvd::to_stringDvd() {
    return "Dvd: " +title + " Dir: " + director + " Serial: "+ serialNumber + "Availability " + std::to_string(isAvailable);  //my meythod again it may be stupid
}

Dvd& Dvd::operator=(const Dvd& right) {
    if (this != &right) {
        // Copy member variables from right to this object
        this->setId(right.getId());
        this->setTitle(right.getTitle());
        this->setDirector(right.getDirector());
        this->setAvailability(right.getAvailability());

    }
    return *this;
}
