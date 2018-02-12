#ifndef FILM_H
#define FILM_H

#include "video.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @class Film header-file film.h
 * @brief
 * La class Film dérivant de Multimedia.
 * Ses objets sont des films.
 * @see Multimedia
 */

class Film : public Video
{
private:
    int *timeTable = new int[10];
    int numChap;
public:
    /**
     * @brief Le constructeur ayant des paramètres par défaut.
     */
    Film();
    /**
     * @brief Le constructeur ayant des paramètres défines par des clients.
     */
    Film(std::string _media, std::string _fichier, const int *timeChaque, int _numChap);
    /**
     * @brief Le destructeur
     */
    ~Film();
    /**
     * @brief Modifier le table des durées
     */
    void setTimeTable(const int *timeChaque, const int numTimeChaque);
    /**
     * @brief Obtenir le table des durées
     */
    const int * getTimeTable() const;
    /**
     * @brief Obtenir le nombre de chapitre.
     */
    int getNumChap() const;
    /**
     * @brief Méthode override pour output les attributs vers ostream
     */
    void affichage(std::ostream& s) const override
    {
        s << media << " " << fichier << " " << numChap << std::endl;
    }
    /**
     * @brief Obtenir le durée d'un chapitre spécifié
     */
    void printTime(std::ostream& s, int numAffichage) const;
    /**
     * @brief Méthode override pour jouer le film
     */
    void jouer() const override;

    /**
     * @brief supprimer des opérateurs dangereux
     */
    Film(const Film& from) = delete;
    Film& operator = (const Film& from) = delete;
    /**
     * @brief Méthode override pour retourner le nom de la class.
     */
    const char* classname() const override {
        return "Film";
    }
    /**
     * @brief Méthode override pour écrire l'information ver flux sortée.
     */
    void write(std::ofstream & f) override {
        Multimedia::write(f);
        f << classname() << "\n" << media << "\n" << fichier << "\n";
        for (int i = 0; i<numChap; i++){
            f << timeTable[i];
            if (i<numChap-1){
                f << " ";
            }else{
                f << "\n";
            }
        }
        f << numChap << "\n" ;
    }
    /**
     * @brief Mérhode override pour relire l'objet de flux entrée.
     */
    void read(std::ifstream & f) override {
        Multimedia::read(f);
        getline(f, media);
        getline(f, fichier);
        std::string s;
        getline(f, s);
        int l = s.length();
        std::string pre = "";
        int totalNum = 1;
        for (int i=0; i<l; i++){
            if (s[i]==' '){
                timeTable[totalNum] = stoi(pre);
                pre = "";
                totalNum += 1;
            }else{
                pre += s[i];
            }
        }
        std::string s2;
        getline(f, s2);
        numChap = stoi(s2);
        cout<<totalNum<<endl;
        cout<<numChap<<endl;
        if (totalNum != numChap) {
            std::cerr << "not matched timeTable and numChap" << std::endl;
            exit(100);
        }
    }
};

#endif // FILM_H
