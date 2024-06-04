//
// Created by Simay Uygur- 22203328 -Section 1
//  17.03.2024
//


#ifndef DVD_H
#define DVD_H

#include <string>

class Dvd
{
public:
    Dvd();
    Dvd(const std::string serialNo, const std::string tit, const std::string dir);
    ~Dvd();

    std::string getId() const;
    void setId(const std::string no);
    std::string getDirector() const;
    void setDirector(const std::string dtr);
    bool getAvailability() const;
    void setAvailability(bool x);
    std::string getTitle() const;
    void setTitle(const std::string tit);
    std::string to_stringDvd();
    Dvd& operator=(const Dvd& right);
private:
    std::string serialNumber;
    bool isAvailable;
    std::string director;
    std::string title;
};

#endif
