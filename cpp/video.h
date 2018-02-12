#ifndef VIDEO_H
#define VIDEO_H
#include "multimedia.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @class Video header-file video.h
 * @brief
 * La class Video dérivant de Multimedia.
 * Ses objets sont des videos.
 * @see Multimedia
 */

class Video : public Multimedia
{
protected:
    int duree; /**La durée d'un vidéo.*/
public:
    /**
     * @brief Le constructeur ayant des paramètres par défaut.
     */
    Video();
    /**
     * @brief Le constructeur ayant des paramètres défines par des clients.
     */
    Video(std::string _media, std::string _fichier, int _duree);
    /**
     * @brief Le destructeur
     */
    ~Video();
    /**
     * @brief Modifier la durée
     */
    void setDuree(const int t);
    /**
     * @brief Obtenir la durée
     */
    int getDuree() const;
    /**
     * @brief Méthode override pour output les attributs vers ostream
     */
    void affichage(std::ostream& s) const override
    {
        s << media << " " << fichier << " " << duree << std::endl;
    }
    /**
     * @brief Méthode override pour jouer le video
     */
    void jouer() const override;

    /**
     * @brief Méthode override pour retourner le nom de la class.
     */
    const char* classname() const override {
        return "Video";
    }
    /**
     * @brief Méthode override pour écrire l'information ver flux sortée.
     */
    void write(std::ofstream & f) override {
        Multimedia::write(f);
        f << classname() << "\n" << media << "\n" << fichier << "\n" << duree << "\n" ;
    }
    /**
     * @brief Mérhode override pour relire l'objet de flux entrée.
     */
    void read(std::ifstream & f) override {
        Multimedia::read(f);
        getline(f, media);
        getline(f, fichier);
        std::string s;
        getline(f,s);
        duree = stoi(s);
    }
};

#endif // VIDEO_H
