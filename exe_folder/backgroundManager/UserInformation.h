#pragma once
//
// Created by bencs on 2021-11-20.
//
//#pragma once

#include <string>
#include <iostream>
#include <fstream>
using namespace std;



class UserInformation {
public:

    UserInformation();
    UserInformation(string);
    UserInformation(string, int);
    UserInformation(string, int, string, string);
    string getPastSearches() const;
    string getBirthday() const;
    int getWeatherPref() const;
    string getCurrInterests() const;
    string getImagePath() const;
    string getFirstInterest() const;
    string getSecondInterest() const;
    string getThirdInterest() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    string getHoliday() const;


    void splitBirthday(string);
    void splitInterests(string);
    int* getSpaces(string);
    void setPastSearches(string);
    void setHoliday(string);
    void setBirthday(string);
    void setWeatherPref(int);
    void setCurrInterests(string);
    void setImagePath(string);
    void storeBirthday();
    void storeHoliday();
    void storeWeatherPref();
private:
    int day;
    int month;
    int year;
    string holiday;
    string birthday;
    string pastSearches;
    int weatherPref;
    string currInterests;
    string imagePath;
    string firstInterest;
    string secondInterest;
    string thirdInterest;
};



