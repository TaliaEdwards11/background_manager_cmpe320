/*
 * A background setter header file
 * Author: Coppers Pub
 */
#pragma once



#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>

#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"
#include <vector>
#include <time.h>
#include "UserInformation.h"
using namespace std;


int favouriteBackground1();
int skipBackground1();

//background setter class
class BackgroundSetter {
    //private variables
private:
    const wchar_t* nextImage;
    
    void deleteBG();
    string currBG();
    string currentBackground;
    string holidayCheck();
    void retrieveImageHoliday(string searchTerm);
    int FileUpdate(int day, int month, int year);
    

public:
    //constructors 
    BackgroundSetter();

    //accessors
    const wchar_t* getNextImage();

    // BG control fucntions
    int setBG(const wchar_t* imagePath);
    int checkPath();
    int favouriteBG();
    int skipBG();
    void loopPreviousBG();
    void loopFavouriteBG();
    int weatherCheck(string interest);
    

};
