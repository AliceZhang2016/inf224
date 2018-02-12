#include "multimedia.h"
#include <iostream>
#include <string>

Multimedia::Multimedia()
{
    media = "defautMedia";
    fichier = "defautFichier";
}

Multimedia::Multimedia(std::string _media, std::string _fichier)
{
    media = _media;
    fichier = _fichier;
}

Multimedia::~Multimedia()
{

}

std::string Multimedia::getMedia() const
{
    return media;
}

std::string Multimedia::getFichier() const
{
    return fichier;
}

void Multimedia::setMedia(const std::string m)
{
    media = m;
}

void Multimedia::setFichier(const std::string f)
{
    fichier = f;
}

void Multimedia::affichage(std::ostream& s) const
{
    s << media << fichier << std::endl;
}
