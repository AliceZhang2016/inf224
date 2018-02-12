#include "group.h"
#include <iostream>
#include <string>

/**
 * @class Group cpp-file group.cpp
 * @brief
 * Implémenter des méthodes définies dans group.h
 */

Group::Group(){
    groupName = "defaultGroupName";
}

Group::Group(std::string _groupName)
{
    groupName = _groupName;
}

Group::~Group()
{
    std::cout<<"detruit dans classe Group(avant reset)"<<std::endl;
    for (auto & i : (*this)) {
        i.reset();
    }
}

const std::string Group::getGroupName(){
    return groupName;
}

void Group::affichage(std::ostream& s){
    for (auto & i : (*this)) {
        if (i == NULL) {
            std::cout<<"pointeur null"<<std::endl;
            continue;
        }
        i->affichage(s);
    }
}
