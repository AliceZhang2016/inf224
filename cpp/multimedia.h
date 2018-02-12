#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Multimedia
{
protected:
    std::string media;
    std::string fichier;
public:
    Multimedia();
    Multimedia(std::string _media, std::string _fichier);
    ~Multimedia();
    std::string getMedia() const;
    std::string getFichier() const;
    void setMedia(const std::string m);
    void setFichier(const std::string f);
    virtual void affichage(std::ostream& s) const;
    virtual void jouer() const = 0;
    
    virtual void write(std::ofstream & f){
        cout<<"Writing..."<<endl;
    }
    virtual void read(std::ifstream & f){
        cout<<"Reading..."<<endl;
    }
    virtual const char* classname() const {
        return "Multimedia";
    }
    
};

#endif // MULTIMEDIA_H
