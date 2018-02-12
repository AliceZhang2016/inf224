#include "photo.h"
#include <iostream>
#include <string>

/**
 * @class Photo cpp-file photo.cpp
 * @brief
 * Implémenter des méthodes définies dans photo.h
 */

Photo::Photo()
{
    media = "defaultPhoto";
    fichier = "defaultFichier";
    latitude = 750.0;
    longitude = 1250.0;
}

Photo::Photo(std::string _media, std::string _fichier, double _latitude, double _longitude)
{
    media = _media;
    fichier = _fichier;
    longitude = _longitude;
    latitude = _latitude;
}

Photo::~Photo()
{

}

void Photo::setLatitude(const double l)
{
    latitude = l;
}

void Photo::setLongitude(const double l)
{
    longitude = l;
}

double Photo::getLatitude() const
{
    return latitude;
}

double Photo::getLongitude() const
{
    return longitude;
}

void Photo::jouer() const
{
    std::string c = "imagej " + fichier + media + " &";
    const char* cc = c.c_str();
    //std::cout << c << "  " << std::endl;
    //std::ifstream ifile(cc);
    //if (ifile){
    system(cc);
    //}else
    //{
    //    s<<"File not exist"<<std::endl;
    //}
}
