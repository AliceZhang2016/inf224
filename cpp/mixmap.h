#ifndef MIXMAP_H
#define MIXMAP_H

#include <stdbool.h>
#include <string.h>

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <vector>
#include <sstream>
#include <exception>
#include <algorithm>

#include "multimedia.h"
#include "group.h"
#include "film.h"
#include "photo.h"
#include "video.h"
#include "tcpserver.h"

using namespace std;
using namespace cppu;

/**
 * @class Mixmap header-file mixmap.h
 * @brief
 * La class est pour la gestion des données (multimedia et groupe)
 * Il y a totalement 7 MODE pour le commande
 * @see Multimedia
 */

#define MODE1 "chercher"
#define MODE2 "jouer"
#define MODE3 "createG" //create groupe
#define MODE4 "createP" //create photo
#define MODE5 "createV" //create video
#define MODE6 "createF" //create film
#define MODE7 "delete" //delete a media from Multimedia

/**
 * @brief L'exception pour détecter si l'on crée plusieurs groupes ou objets ayant le même nom
 */
class nameDuplicatedException:public exception {
public:    
    //nameDuplicatedException():exception("ERROR! Name is duplicated.\n")    
    const char* what()const throw()//#1     
    {    
        return "ERROR! Name is duplicated.";    
    }  
};

/**
 * @brief L'exception pour détecter si le tableau de durées d'un Film a une taille nulle ou inférieure à zéro
 */
class sizeInvalidException:public exception {
public:    
    //lengthInvalidException():exception("ERROR! Invalid length of media.\n")    
    const char* what()const throw()//#1     
    {    
        return "ERROR! Invalid size of media.";    
    } 
};


class Mixmap
{
private:
    std::map<std::string, std::shared_ptr<Multimedia>> tableMultimedia;
    std::map<std::string, std::shared_ptr<Group>> tableMultiGroup;

public:
    /**
     * @brief Le constructeur.
     */
    Mixmap();
    /**
     * @brief Créer un film ayant le nom spécifié et des attributs par défault.
     */
    std::shared_ptr<Film> creerFilm(std::string name);
    /**
     * @brief Créer un vidéo ayant le nom spécifié et des attributs par défault.
     */
    std::shared_ptr<Video> creerVideo(std::string name);
    /**
     * @brief Créer un photo ayant le nom spécifié et des attributs par défault.
     */
    std::shared_ptr<Photo> creerPhoto(std::string name);
    /**
     * @brief Créer un film ayant le nom spécifié et des attributs spécifiés.
     */
    std::shared_ptr<Film> creerFilm(std::string name, std::string _media, std::string _fichier, const int *timeChaque, int _numChap);
    /**
     * @brief Créer un vidéo ayant le nom spécifié et des attributs spécifiés.
     */
    std::shared_ptr<Video> creerVideo(std::string name, std::string _media, std::string _fichier, int _duree);
    /**
     * @brief Créer un photo ayant le nom spécifié et des attributs spécifiés.
     */
    std::shared_ptr<Photo> creerPhoto(std::string name, std::string _media, std::string _fichier, double _latitude, double _longitude);
    /**
     * @brief Créer un groupe ayant le nom spécifié et des attributs par défault.
     */
    std::shared_ptr<Group> creerGroup(std::string name);
    /**
     * @brief Créer un groupe ayant le nom spécifié et des attributs spécifiés.
     */
    std::shared_ptr<Group> creerGroup(std::string name, std::string _groupName);
    /**
     * @brief chercher un média spécifié par un nom dans le tableu de Multimedia
     */
    void chercherDansMultiMedia(std::string name, std::ostream& s);
    /**
     * @brief chercher un groupe spécifié par un nom dans le tableu de Group
     */
    void chercherDansMultiGroup(std::string name, std::ostream& s);

    /**
     * @brief jouer un média spécifié par un nom dans le tableu de Multimedia
     */
    void jouerMultiMedia(std::string name);

    /**
     * @brief delete un média spécifié par un nom dans le tableu de Multimedia
     */
    void moveParNameDansMultiMedia(std::string name);
    /**
     * @brief delete un groupe spécifié par un nom dans le tableu de Group
     */
    void moveParNameDansMultiGroup(std::string name);

    /**
     * @brief pour connecter avec le client
     */
    bool processRequest(TCPConnection& cnx, const string& request, string& response);
};
#endif // MIXMAP_H
