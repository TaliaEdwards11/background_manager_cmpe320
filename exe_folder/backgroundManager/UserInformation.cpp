//
// Created by bencs on 2021-11-20.
//

#include "UserInformation.h"

//When a Birthday is entered, make sure it is in the format of "dd/mm/yyyy"

UserInformation::UserInformation() {}

UserInformation::UserInformation(string keywords) {
    currInterests = keywords;
    splitInterests(keywords);
}

UserInformation::UserInformation(string keywords, int wpref) {
    currInterests = keywords;
    weatherPref = wpref;
    splitInterests(keywords);
}

UserInformation::UserInformation(string keywords, int wpref, string birth, string theHoliday) {
    currInterests = keywords;
    weatherPref = wpref;
    birthday = birth;
    holiday = theHoliday;

    splitInterests(keywords);
    splitBirthday(birth);
}

string UserInformation::getPastSearches() const {
    return pastSearches;
}

int UserInformation::getWeatherPref() const {
    return weatherPref;
}

string UserInformation::getBirthday() const {
    return birthday;
}

string UserInformation::getCurrInterests() const {
    return currInterests;
}

string UserInformation::getFirstInterest() const {
    return firstInterest;
}

string UserInformation::getSecondInterest() const {
    return secondInterest;
}

string UserInformation::getThirdInterest() const {
    return thirdInterest;
}

string UserInformation::getImagePath() const {
    return imagePath;
}

int UserInformation::getDay() const {
    return day;
}

int UserInformation::getMonth() const {
    return month;
}

int UserInformation::getYear() const {
    return year;
}

string UserInformation::getHoliday() const {
    return holiday;
}

void UserInformation::setPastSearches(string temp) {
    pastSearches = temp;
}

void UserInformation::setWeatherPref(int temp) {
    weatherPref = temp;
}

void UserInformation::setBirthday(string temp) {
    birthday = temp;
}

void UserInformation::setCurrInterests(string temp) {
    currInterests = temp;
}

void UserInformation::setImagePath(string temp) {
    imagePath = temp;
}

void UserInformation::setHoliday(string temp) {
    holiday = temp;
}

int* UserInformation::getSpaces(string interests) {
    int length = interests.length();
    static int spaces[3];
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (interests[i] == ' ') {
            spaces[j] = i;
            j++;
        }
    }
    return spaces;
}
void UserInformation::splitBirthday(string birth) {
    int* spaces = getSpaces(birth);

    day = stoi(birth.substr(0, spaces[0]));
    month = stoi(birth.substr((spaces[0] + 1), (spaces[1] - spaces[0])));
    //year = stoi(birth.substr((spaces[1] + 1), (spaces[2] - spaces[1])));
    year = 0;
}


void UserInformation::splitInterests(string interests) {

    int* spaces = getSpaces(interests);

    firstInterest = interests.substr(0, spaces[0]);
    secondInterest = interests.substr((spaces[0] + 1), (spaces[1] - spaces[0]));
    thirdInterest = interests.substr((spaces[1] + 1), (spaces[2] - spaces[1]));

}

void UserInformation::storeBirthday() {
    //splitBirthday(birth);
    int d = getDay();
    int m = getMonth();
    int y = getYear();

    ofstream myfile;
    myfile.open("..\\BG_Manager\\birthday.txt");

    if (myfile.is_open()) {
        myfile << d << endl;
        myfile << m << endl;
        myfile << y << endl;
    }
    else {
        cout << "Could not open file." << endl;
    }
    myfile.close();

}

void UserInformation::storeHoliday() {
    string h = getHoliday();

    ofstream myfile;
    myfile.open("..\\BG_Manager\\holidays.txt", fstream::app);

    if (myfile.is_open()) {
        myfile << h << endl;
    }
    else {
        cout << "Could not open file." << endl;
    }
    myfile.close();
}

void UserInformation::storeWeatherPref() {
    int p = getWeatherPref();

    ofstream myfile;
    myfile.open("..\\BG_Manager\\weatherPreference.txt");

    if (myfile.is_open()) {
        myfile << p << endl;
    }
    else {
        cout << "Could not open file." << endl;
    }
    myfile.close();
}


