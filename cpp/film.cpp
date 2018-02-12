#include "film.h"
#include <iostream>

/**
 * @class Film cpp-file film.cpp
 * @brief
 * Implémenter des méthodes définies dans film.h
 */

Film::Film()
{
    media = "defaultFilm";
    fichier = "defaultFichier";
    timeTable[0] = 10;
    numChap = 1;
}

Film::Film(std::string _media, std::string _fichier, const int *timeChaque, int _numChap)
{
    media = _media;
    fichier = _fichier;

    numChap = _numChap;
    //*timeTable = *timeChaque;
    for (int i=0; i<numChap; i++){
        timeTable[i] = timeChaque[i];
    }
}

Film::~Film()
{
    std::cout << "le destructeur de classe Film" << std::endl;
    //delete [] timeTable;  // question 6-7
}

void Film::setTimeTable(const int *timeChaque, const int numTimeChaque)
{
    //*timeTable = *timeChaque;
    for (int i=0; i<numTimeChaque; i++){
        timeTable[i] = timeChaque[i];
    }
}

const int * Film::getTimeTable() const
{
    return timeTable;
}

int Film::getNumChap() const
{
    return numChap;
}

void Film::printTime(std::ostream& s, int numAffichage) const
{
    for (int i=0; i<numAffichage; i++){
        //s << "Yeah" << timeTable[0] << std::endl;
        s << timeTable[i] << " ";
    }
    s << std::endl;
}

void Film::jouer() const
{
    std::string c = "mpv " + fichier + media + " &";
    const char* cc = c.c_str();
    system(cc);
}

