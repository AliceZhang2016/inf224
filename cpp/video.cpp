#include "video.h"
#include <iostream>
#include <string>

/**
 * @class Video cpp-file video.cpp
 * @brief
 * Implémenter des méthodes définies dans video.h
 */


Video::Video()
{
    media = "defaultVideo";
    fichier = "defaultFichier";
    duree = 10;
}

Video::Video(std::string _media, std::string _fichier, int _duree)
{
    media = _media;
    fichier = _fichier;
    duree = _duree;
}

Video::~Video()
{

}

void Video::setDuree(const int t)
{
    duree = t;
}

int Video::getDuree() const
{
    return duree;
}

void Video::jouer() const
{
    std::string c = "mpv " + fichier + media + " &";
    const char* cc = c.c_str();
    system(cc);
}
