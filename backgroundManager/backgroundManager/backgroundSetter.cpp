
/*
 * A background setter cpp file
 * Author: Coppers Pub
 */
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>

#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"
#include <fstream>
#include <direct.h>
#include <algorithm>
#include <filesystem>
#include "PastImages.h"
using namespace std;

#include "backgroundSetter.h"


// called in main.cpp to save backgrounds
int favouriteBackground1() {
    BackgroundSetter newBG;
    
    return newBG.favouriteBG();
}
//called in main.cpp to change background
int skipBackground1() {
    BackgroundSetter newBG;
    return newBG.skipBG();
}


BackgroundSetter::BackgroundSetter() {
    nextImage = L"..\\BG_Manager\\images\\";

}

// set the background using windows api
int BackgroundSetter::setBG(const wchar_t* imagePath) {
    int success = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)imagePath, SPIF_UPDATEINIFILE);
    return success;
}

// check for needed directories
int BackgroundSetter::checkPath() {
    system("mkdir ..\\BG_Manager");
    system("mkdir ..\\BG_Manager\\images");
    system("mkdir ..\\BG_Manager\\favourites");
    system("mkdir ..\\BG_Manager\\previous");
    if (currBG() == "") {
        return 0;
    }
    return 1;

}



// favourite background 
// save background to C:\\BG_Manager\\favourites
int BackgroundSetter::favouriteBG() {
    string imageA = currBG();
    if (imageA != "") {
        imageA = "copy ..\\BG_Manager\\images\\" + imageA + " ..\\BG_Manager\\favourites";
        system(imageA.c_str());
    }
    return 1;
}

// if no more backgrounds are left add the favourites to have old liked backgrounds reappear
void BackgroundSetter::loopFavouriteBG() {
    string imageA = "xcopy ..\\BG_Manager\\favourites ..\\BG_Manager\\images /Y";
    system(imageA.c_str());
}


// if no more backgrounds are left add the favourites to have old liked backgrounds reappear
void BackgroundSetter::loopPreviousBG() {
    string imageA = "xcopy ..\\BG_Manager\\previous ..\\BG_Manager\\images /Y";
    system(imageA.c_str());
}

// find out what the current bg is
string BackgroundSetter::currBG() {
    
    system("cd \"..\\BG_Manager\\images\" && dir /b /a-d > ..\\imageNames.txt");
    ifstream file("..\\BG_Manager\\imageNames.txt");
   
    string image;
    if (file.is_open())
    {
        file >> image;
    }
    string imageA = "..\\BG_Manager\\images\\";
    file.close();
    //imageA += image;
    return image;
}

// delete the current bg 
void BackgroundSetter::deleteBG() {
    string imageA = currBG();
    imageA = "del ..\\BG_Manager\\images\\" + imageA;
    system(imageA.c_str());
}

// go to next bg and delete current one
int BackgroundSetter::skipBG() {
    
    string holiday = holidayCheck();
    
    if (currBG() == "") {
         loopFavouriteBG();
         setBG(getNextImage());
         return 0;
    }
    //deleteBG();
    setBG(getNextImage());
    
    
    return 1;
}

//get next image path in correct format for windows api 
const wchar_t* BackgroundSetter::getNextImage() {
    // retrieve all images from folder 
    string imageA = currBG();
    system("rmdir /s /q C:\\BG_Manager");
    system("mkdir C:\\BG_Manager\\temp");
    string command = "copy ..\\BG_Manager\\images\\" + imageA + " C:\\BG_Manager\\temp";
    system(command.c_str());
    string command2 = "copy ..\\BG_Manager\\images\\" + imageA + " ..\\BG_Manager\\previous";
    system(command2.c_str());
    //string newname = "C:\\BG_Manager\\temp\\currentBackground.jpg";
    //string oldname = "C:\\BG_Manager\\temp" + imageA;
    //string command1 = "ren "+oldname + " "+ newname;
    //system(command1.c_str());
   
    imageA = "C:\\BG_Manager\\temp\\"+imageA;
    CStringW imageB = imageA.c_str();
    nextImage = imageB.GetString();

    return nextImage;
}



void BackgroundSetter::retrieveImageHoliday(string searchTerms) {

    // Assumes the code is excecuted from the same folder as where the python script is stored
    // If it does not, you can provide it the absolute location of the RetrieveImage.py script
    string command = "echo Loading Backgrounds for " + searchTerms+"&& python3 RetrieveImageHoliday.py " + searchTerms;
    system(command.c_str());
}


string BackgroundSetter::holidayCheck() {
    // check current day and month
    struct tm newtime;
    __time64_t long_time;
    char timebuf[26];
    errno_t err;

    //time as integer
    _time64(&long_time);
    //local time
    err = _localtime64_s(&newtime, &long_time);
    int day = newtime.tm_mday;
    int month = newtime.tm_mon + 1;
    int year = newtime.tm_year;
    int status = FileUpdate(day, month, year);
    if (status == 1) {
        return "";
    }
    // read date from file for bd 
    vector<string> bd;
    vector<string> holidays;
    ifstream BDFile("..\\BG_Manager\\birthday.txt");
    //check if it failed
    string c1;
    if (!(BDFile.fail())) {
        //read the file line by line
        while (BDFile >> c1) {
            //push to the vectors
            bd.push_back(c1);
        }
        BDFile.close();


        if (stoi(bd[0]) == day && stoi(bd[1]) == month) {
            retrieveImageHoliday("birthday");

            return "birthday";
        }
    }

    ifstream HolidayFile("..\\BG_Manager\\holidays.txt");
    //check if it failed
    string name;
    string dd;
    string mm;
    
    if (!(HolidayFile.fail())) {
        //read the file line by line
        //each time split in 3 based on columns
        while (HolidayFile >> name >> dd >> mm) {
            //push to the vectors
            holidays.push_back(name);
            holidays.push_back(dd);
            holidays.push_back(mm);
            if (stoi(holidays[1]) == day && stoi(holidays[2]) == month) {
                HolidayFile.close();
                retrieveImageHoliday(holidays[0]);
                return holidays[0];

            }
            else {
                holidays.clear();
            }
        }
        HolidayFile.close();
        return "";


    }

}

int BackgroundSetter::FileUpdate(int day, int month, int year) {
    ifstream DateFile("..\\BG_Manager\\done.txt");
    //check if it failed
    string dd;
    string mm;
    string yyyy;
    if (!(DateFile.fail())) {
        //read the file line by line
        DateFile >> dd >> mm >> yyyy;

        DateFile.close();


        if (stoi(dd) == day && stoi(mm) == month && stoi(yyyy) == year) {
            return 1;
        }



        ofstream DateFileOutput;
        DateFileOutput.open("..\\BG_Manager\\done.txt");
        DateFileOutput << day << " " << month << " " << year;
        DateFileOutput.close();
    }

    return 0;
}

int BackgroundSetter::weatherCheck(string interest) {
     
   
  
    ifstream WeatherFile("..\\BG_Manager\\weatherPreference.txt");
    //check if it failed
    string enabled;
    if (!(WeatherFile.fail())) {
        //read the file line by line
        //WeatherFile >> enabled;
        WeatherFile >> enabled;
        WeatherFile.close();


        if (stoi(enabled) == 0) {
            return 0;
        }
        else {
            //call spencer weather api
            string command0 = "python getCurrentWeather.py ";
            system(command0.c_str());
            ifstream WeatherWordFile("..\\BG_Manager\\weather.txt");
            //check if it failed
            
            string weather = "";
            if (!(WeatherWordFile.fail())) {
                //read the file line by line
                WeatherWordFile >> weather;

                WeatherWordFile.close();
            }

            
            string weatherInterest = weather + "+" + interest;

            //disable weather for next interest
            UserInformation temp;
            temp.setWeatherPref(0);
            temp.storeWeatherPref();

            //

            string command = "echo Loading Backgrounds for " + weatherInterest + " && python3 RetrieveImage.py " + weatherInterest;
            system(command.c_str());

            //check today's date 
            PastImages dateGetter;
            tm date = dateGetter.getDate();
            int day = date.tm_mday;
            int month = 1 + date.tm_mon;
            int year = 1900 + date.tm_year;
            int hour = date.tm_hour;
            int min = date.tm_min;
            int sec = date.tm_sec;

            //rename files with name
            /*
            weatherInterest.erase(remove(weatherInterest.begin(), weatherInterest.end(), '+'), weatherInterest.end());
            string rename = "rename ..\\BG_Manager\\images\\0"+ weatherInterest + " 00" + to_string(day) + to_string(month)+ to_string(year)+to_string(hour)+to_string(min)+to_string(sec);
            string rename1 = "rename ..\\BG_Manager\\images\\1" + weatherInterest + " 01" + to_string(day) + to_string(month) + to_string(year) + to_string(hour) + to_string(min) + to_string(sec);
            string rename2 = "rename ..\\BG_Manager\\images\\2" + weatherInterest+ " 02" + to_string(day) + to_string(month) + to_string(year) + to_string(hour) + to_string(min) + to_string(sec);
            system(rename.c_str());
            system(rename1.c_str());
            system(rename2.c_str());
            */

            // change file names to current date and time
            //delete old file names with old day and time 
            //change bg 
            //skipBackground1();
            return 1;

        }
    }

       
        




}

