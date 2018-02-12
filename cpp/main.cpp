//
//  main.cpp
//  

#ifndef VERSION_TRUC
#define VERSION_TRUC

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cxxabi.h>
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"
#include "mixmap.h"

const int PORT = 3331;

using namespace std;

Multimedia * createMultimedia_ori(string className){
    if (className == "Photo"){
        return new Photo();
    }else if (className == "Video"){
        return new Video();
    }else if (className == "Film"){
        return new Film();
    }else {
        cerr << "Wrong class name" << endl;
        exit(500);
    }
}

shared_ptr<Multimedia> createMultimedia(string className){
    if (className == "Photo"){
        std::shared_ptr<Photo> firstP(new Photo());
        return firstP;
    }else if (className == "Video"){
        std::shared_ptr<Video> firstV(new Video());
        return firstV;
    }else if (className == "Film"){
        std::shared_ptr<Film> firstF(new Film());
        return firstF;
    }else {
        cerr << "Wrong class name" << endl;
        exit(500);
    }
}

int main(int argc, char* argv[]) {
    //std::cout << "Hello World" << std::endl;
    /////////////////////////////////////////////////////// 3ème étape
    /*
    Multimedia *firstM = new Multimedia("HelloWorld", "123");
    firstM->affichage(std::cout);
    firstM->setMedia("deux");
    firstM->affichage(std::cout);
    Photo *firstP = new Photo();
    firstP->affichage(std::cout);
    Video *firstV = new Video();
    firstV->affichage(std::cout);
    */
    //////////////////////////////////////////////////////// 4-5ème étape
    /*
    int size = 3;
    Multimedia ** medias = new Multimedia * [size];
    unsigned int count = 0;
    medias[count++] = new Photo("sky.jpg","~/Downloads/",1200,1200);
    medias[count++] = new Photo();
    medias[count++] = new Video("eyeMovie.mp4","~/Downloads/",10);
    for (int i=0; i<size; i++)
    {
        medias[i]->jouer();
    }
    */
    ////////////////////////////////////////////////////// 6-7ème étape
    /*
    int *timeChaqueIni = new int[1];
    timeChaqueIni[0] = 30;
    Film *firstFilm = new Film("eyeMovie.mp4","~/Downloads/",timeChaqueIni,1);
    delete [] timeChaqueIni;
    //Film *firstFilm = new Film();
    //firstFilm->setFichier("hi");
    std::cout << firstFilm->getNumChap() << std::endl;
    firstFilm->printTime(std::cout, 1);

    int *timeChaque = new int[6];
    //int *hi = new int[6];
    for (int i=0; i<6; i++){
        timeChaque[i] = i*10;
        std::cout<< timeChaque[i] << " ";
    }
    std::cout<<std::endl;
    */

    //if (timeChaque && hi) {
      //  std::cout<< "pupu" << std::endl;
    //}

    //hi = timeChaque;
    /* test simpme
    *hi = *timeChaque;
    for (int i=0; i<6; i++){
        hi[i] = timeChaque[i];
    }

    for (int i=0; i<6; i++){
        std::cout<< hi[i] << " ";
    }
    std::cout<<std::endl;

    timeChaque[2]=100;

    for (int i=0; i<6; i++){
        std::cout<< hi[i] << " ";
    }
    std::cout<<std::endl;
    */

    /*
    firstFilm->setTimeTable(timeChaque,6);
    firstFilm->printTime(std::cout, 6);
    timeChaque[2]=100;
    delete [] timeChaque;
    firstFilm->printTime(std::cout, 6);
    */

    /////////////////////////////////////////////////8ème étape
    /*
    Group myGroup("firstGroup");
    myGroup.getGroupName();
    */
    //Photo *firstP = new Photo();
    //Video *firstV = new Video();
    //Film *firstF = new Film();

    //////////////////////////////////////////////////9ème étape

    // // c'est un pointeur null; (on peut le détecter dans la fonction affichage)
    // // std::shared_ptr<Photo> firstP;
    /*
    std::shared_ptr<Photo> firstP(new Photo());
    std::shared_ptr<Video> firstV(new Video());
    std::shared_ptr<Film> firstF(new Film());

    myGroup.push_back(firstP);
    myGroup.push_back(firstV);
    myGroup.push_back(firstF);

    myGroup.affichage(std::cout);
    */

    ////////////////////////////////////////////////////10ème étape
    /*
    Mixmap *firstMix = new Mixmap();
    firstMix->creerFilm("F1");
    firstMix->creerPhoto("P1");
    firstMix->creerVideo("V1");
    firstMix->creerPhoto("P2","sky.jpg","~/Downloads/",1200,1200);
    firstMix->creerVideo("V2","eyeMovie.mp4","~/Downloads/",10);
    //firstMix->chercherDansMultiMedia("F1",std::cout);
    //firstMix->jouerMultiMedia("V2");
    firstMix->jouerMultiMedia("P2");
    std::cout<<"hahaha"<<std::endl;
    firstMix->moveParNameDansMultiMedia("P2");
    firstMix->jouerMultiMedia("P2");
    */

    ///////////////////////////////////////////////////11ème étape + can be used to test 13 ème étape
    
    // cree le TCPServer
    shared_ptr<TCPServer> server(new TCPServer());

    // cree l'objet qui gère les données
    shared_ptr<Mixmap> base(new Mixmap());
    cout << "YeahhhFromMain" << endl;

    //Ajouter des medias differents dans le mixmap;
    base->creerFilm("F1");
    base->creerPhoto("P1");
    base->creerVideo("V1");
    base->creerPhoto("P2","sky.jpg","~/Downloads/inf224/",1200,1200);
    base->creerVideo("V2","Try.mp4","~/Downloads/inf224/",10);

    cout << "create avec succes" << endl;
    // le serveur appelera cette méthode chaque fois qu'il y a une requête
    server->setCallback(*base, &Mixmap::processRequest);

    // lance la boucle infinie du serveur
    cout << "Starting Server on port " << PORT << endl;
    int status = server->run(PORT);


    // en cas d'erreur
    if (status < 0) {
      cerr << "Could not start Server on port " << PORT << endl;
      return 1;
    }

    return 0;
    
    
    /////////////////////////////////////////////////////12ème étape
    //////////////test writing part...
    /*
    //creer des medias
    int *timeChaqueIni = new int[1];
    timeChaqueIni[0] = 30;
    Film *firstFilm = new Film("Try.mp4","~/Downloads/inf224/",timeChaqueIni,1);
    Photo *firstPhoto = new Photo("sky.jpg","~/Downloads/inf224/",1200,1200);
    Video *firstVideo = new Video();
    
    //string fileName = "~/Downloads/infEx12.txt"; //Why the absolute path is wrong?
    string fileName = "infEx12.txt";
    cout<<fileName<<endl;
    ofstream f(fileName);
    if (!f){
        cerr << "Can't open file " << fileName << endl;
        return 400;
    }
    firstFilm->write(f);
    firstPhoto->write(f);
    firstVideo->write(f);
    f.close();
    return 200;
    */
    ///////////// test reading part...
    /*
    string fileName = "infEx12.txt";
    cout << fileName << endl;
    ifstream f(fileName);
    if (!f){
        cerr << "Can't open file" << fileName << endl;
        return 401;
    }
    //vector <Multimedia *> objects;
    Group myGroup("firstGroup"); 
    string className;
    while (getline(f, className)){
        //Multimedia *obj = createMultimedia_ori(className);
        shared_ptr<Multimedia> obj = createMultimedia(className);
        if (obj){
            obj->read(f);
        }
        if (f.fail()){
            cerr << "Read error in" << fileName << endl;
            //delete obj;
            exit(501);
        }else{
            //objects.push_back(obj);
            myGroup.push_back(obj);
        }
    }
    f.close();
    myGroup.affichage(std::cout);
    
    //objects[0]->affichage(std::cout);
    //objects[0]->jouer();
    //objects[1]->affichage(std::cout);
    //objects[2]->affichage(std::cout);
    */

}
#endif
