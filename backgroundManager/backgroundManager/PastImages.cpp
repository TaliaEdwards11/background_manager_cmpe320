#include "PastImages.h"
#include <sys/stat.h>
#include <fstream>
using namespace std;

PastImages::PastImages() {
    string from = SaveToOldBackgrounds();
    full_path = from;
    file_directory = from.substr(0, 24); //This will need to change because it's in relation to my computer.
    file_name = from.substr(25, from.size()); //This will need to change because it's in relation to my computer.
}

string PastImages::SaveToOldBackgrounds() {
    int result;
    struct stat sb;
    const char* folder = "C:\\BG_Manager\\previous";

    if (stat(folder, &sb) != 0) {
        createDirectory();
    }

    tm date = getDate();
    int day = date.tm_mday;
    int month = 1 + date.tm_mon;
    int year = 1900 + date.tm_year;
    int hour = date.tm_hour;
    int min = date.tm_min;
    int sec = date.tm_sec;
    //Need to change, in relation to my computer.
    string myString = "..\\BG_Manager\\previous\\" + to_string(day) + "-" + to_string(month) + "-" + to_string(year) + "_" + to_string(hour) + "." + to_string(min) + "." + to_string(sec) + ".jpg";

    //Need to change, in relation to my computer.
    const char oldname[] = "C:\\Users\\renne\\AppData\\Roaming\\Microsoft\\Windows\\Themes\\CachedFiles\\CachedImage_3000_2000_POS4.jpg";
    const char* filename = myString.c_str();

    result = rename(oldname, filename);
    if (result == 0)
        puts("File successfully renamed");
    else {
        perror("Error renaming file");
    }
    return myString;
}

void PastImages::createDirectory() {
    //need to change, in relation to my computer.
    _mkdir("..\\BG_Manager\\previous");
    return;
}


string PastImages::getDirectory() {
    return file_directory;
}

string PastImages::getFileName() {
    return file_name;
}

string PastImages::getFullPath() {
  system("cd \"C:\\BG_Manager\\temp\" && dir /b /a-d > ..\\imageNames.txt");
    ifstream file("C:\\BG_Manager\\imageNames.txt");

    string image;
    if (file.is_open())
    {
        file >> image;
    }
    file.close();
    //string imageA = "..\\BG_Manager\\previous\\";

    //imageA += image;
    return image;
    
   // return full_path;
}
tm PastImages::getDate() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    return newtime;
}

void PastImages::DeleteImage() {
    string fileName = "..\\BG_Manager\\images\\" + getFullPath();
    //string command = "del ..\\BG_Manager\\images\\" + fileName;
    //system(command.c_str());
    int result = remove(fileName.c_str());
   
}

int PastImages::SaveImage() {
    string fileName = getFullPath();
    //string command = "del ..\\BG_Manager\\images\\" + fileName;
    //system(command.c_str());
    if (fileName != "") {
        string command1 = "copy C:\\BG_Manager\\temp\\" + fileName + " ..\\BG_Manager\\favourites";
        system(command1.c_str());
    }
    return 1;

}

void PastImages::DeleteImagePrevious() {
    string fileName = "..\\BG_Manager\\previous\\" + getFullPath();
    //string command = "del ..\\BG_Manager\\images\\" + fileName;
    //system(command.c_str());
    int result = remove(fileName.c_str());
    

}