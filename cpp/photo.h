#ifndef PHOTO_H
#define PHOTO_H

#include "multimedia.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @class Photo header-file photo.h
 * @brief
 * La class Film dérivant de Multimedia.
 * Ses objets sont des photos.
 * @see Multimedia
 */

class Photo : public Multimedia
{
protected:
    double latitude, longitude;/**La latitude et longitude de la photo.*/
public:
    /**
     * @brief Le constructeur ayant des paramètres par défaut.
     */
    Photo();
    /**
     * @brief Le constructeur ayant des paramètres défines par des clients.
     */
    Photo(std::string _media, std::string _fichier, double _latitude, double _longitude);
    /**
     * @brief Le destructeur
     */
    ~Photo();
    /**
     * @brief Modifier la latitude
     */
    void setLatitude(const double l);
    /**
     * @brief Modifier la longitude
     */
    void setLongitude(const double l);
    /**
     * @brief Obtenir la latitude
     */
    double getLatitude() const;
    /**
     * @brief Obtenir la longitude
     */
    double getLongitude() const;
    /**
     * @brief Méthode override pour output les attributs vers ostream
     */
    void affichage(std::ostream& s) const override
    {
        s << media << " " << fichier << " " << latitude<< " " << longitude << "  Yeah  " << std::endl;
    }
    /**
     * @brief Méthode override pour jouer le photo
     */
    void jouer() const override;

    /**
     * @brief Méthode override pour retourner le nom de la class.
     */
    const char* classname() const override {
        return "Photo";
    }
    /**
     * @brief Méthode override pour écrire l'information ver flux sortée.
     */
    void write(std::ofstream & f) override {
        Multimedia::write(f);
        f << classname() << "\n" << media << "\n" << fichier << "\n" << latitude << "\n" << longitude << "\n" ;
    }
    /**
     * @brief Mérhode override pour relire l'objet de flux entrée.
     */
    void read(std::ifstream & f) override {
        Multimedia::read(f);
        getline(f,media);
        getline(f,fichier);
        std::string s;
        getline(f,s);
        latitude = stod(s);
        getline(f,s);
        longitude = stod(s);
        //cout<<latitude<<" "<<longitude<<endl;
    }
};

#endif // PHOTO_H
