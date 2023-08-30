#pragma once

#include <string>
#include <direct.h>
#include <ctime>
#include <iostream>

using namespace std;

class PastImages {
public:
    PastImages();
    void DeleteImage();
    void DeleteImagePrevious();
    string getDirectory();
    string getFileName();
    string getFullPath();
    int dirExists();
    tm getDate();
    int SaveImage();

private:
    string file_directory;
    string file_name;
    string full_path;

    string SaveToOldBackgrounds();
    void createDirectory();
   
};

#ifndef CMPE320_PASTIMAGES_PASTIMAGES_H
#define CMPE320_PASTIMAGES_PASTIMAGES_H

#endif //CMPE320_PASTIMAGES_PASTIMAGES_H
