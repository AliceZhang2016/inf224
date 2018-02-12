#ifndef GROUP_H
#define GROUP_H
#include <list>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include "multimedia.h"

using MultiPtr = std::shared_ptr<Multimedia>;

/**
 * @class Group header-file group.h
 * @brief
 * La class est une liste des smart pointeurs de Multimedia.
 * @see Multimedia
 */


class Group : public std::list<MultiPtr>
{
private:
    std::string groupName;

public:
    /**
     * @brief Le constructeur ayant des paramètres par défaut.
     */
    Group();
    /**
     * @brief Le constructeur ayant des paramètres défines par des clients.
     */
    Group(std::string _groupName);
    /**
     * @brief Le destructeur
     */
    ~Group();
    /**
     * @brief Obtenir le nom du groupe
     */
    const std::string getGroupName();
    /**
     * @brief Méthode override pour output les attributs vers ostream
     */
    void affichage(std::ostream& s);
};


/*
class Group : public std::list<Multimedia*>
{    
private:
    std::string groupName;

public:
    Group();
    Group(std::string _groupName);
    ~Group();
    const std::string getGroupName();
    void affichage(std::ostream& s);
};
*/
#endif // GROUP_H
