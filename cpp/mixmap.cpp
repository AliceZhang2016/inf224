#include "mixmap.h"

/**
 * @class Mixmap cpp-file mixmap.cpp
 * @brief
 * Implémenter des méthodes définies dans mixmap.h
 */

Mixmap::Mixmap()
{

}

std::shared_ptr<Film> Mixmap::creerFilm(std::string name)
{
    std::shared_ptr<Film> firstF(new Film());
    tableMultimedia[name] = firstF;
    return firstF;
}

std::shared_ptr<Photo> Mixmap::creerPhoto(std::string name)
{
    std::shared_ptr<Photo> firstP(new Photo());
    tableMultimedia[name] = firstP;
    return firstP;
}

std::shared_ptr<Video> Mixmap::creerVideo(std::string name)
{
    std::shared_ptr<Video> firstV(new Video());
    tableMultimedia[name] = firstV;
    return firstV;
}

std::shared_ptr<Film> Mixmap::creerFilm(std::string name, std::string _media, std::string _fichier, const int *timeChaque, int _numChap)
{
    //judge if the name is duplicated
    auto it = tableMultimedia.find(name);
    if (it != tableMultimedia.end()){
        throw nameDuplicatedException();
    }
    //judge if size is ok
    if (_numChap <= 0){
        throw sizeInvalidException();
    }

    for (int i = 0; i<_numChap; i++){
        if (timeChaque[i]<=0){
            throw sizeInvalidException();
        }
    }

    std::shared_ptr<Film> firstF(new Film(_media, _fichier, timeChaque, _numChap));
    tableMultimedia[name] = firstF;
    return firstF;
}

std::shared_ptr<Photo> Mixmap::creerPhoto(std::string name, std::string _media, std::string _fichier, double _latitude, double _longitude)
{
    //judge if the name is duplicated
    auto it = tableMultimedia.find(name);
    if (it != tableMultimedia.end()){
        throw nameDuplicatedException();
    }
    //judge if size is ok
    if (_latitude <= 0 || _longitude <= 0){
        throw sizeInvalidException();
    }

    std::shared_ptr<Photo> firstP(new Photo(_media, _fichier, _latitude, _longitude));
    tableMultimedia[name] = firstP;
    return firstP;
}

std::shared_ptr<Video> Mixmap::creerVideo(std::string name, std::string _media, std::string _fichier, int _duree)
{
    //judge if the name is duplicated
    auto it = tableMultimedia.find(name);
    if (it != tableMultimedia.end()){
        throw nameDuplicatedException();
    }
    //judge if size is ok
    if (_duree <= 0){
        throw sizeInvalidException();
    }

    std::shared_ptr<Video> firstV(new Video(_media, _fichier, _duree));
    tableMultimedia[name] = firstV;
    return firstV;
}

std::shared_ptr<Group> Mixmap::creerGroup(std::string name)
{
    //judge if the name is duplicated
    auto it = tableMultiGroup.find(name);
    if (it != tableMultiGroup.end()){
        throw nameDuplicatedException();
    }

    std::shared_ptr<Group> myGroup(new Group());
    tableMultiGroup[name] = myGroup;
    return myGroup;
}

std::shared_ptr<Group> Mixmap::creerGroup(std::string name, std::string _groupName)
{
    //judge if the name is duplicated
    auto it = tableMultiGroup.find(name);
    if (it != tableMultiGroup.end()){
        throw nameDuplicatedException();
    }

    if (_groupName == ""){
        return creerGroup(name);
    }
    std::shared_ptr<Group> myGroup(new Group(_groupName));
    tableMultiGroup[name] = myGroup;
    return myGroup;
}

void Mixmap::chercherDansMultiMedia(std::string name, std::ostream& s){
    auto it = tableMultimedia.find(name);
    if (it == tableMultimedia.end()) {
        std::cout<<"pas trouve dans tableMultiMedia"<<std::endl;
    } else {
        it -> second ->affichage(s);
        //it -> affichage(s);
    }
}

void Mixmap::chercherDansMultiGroup(std::string name, std::ostream& s){
    auto it = tableMultiGroup.find(name);
    if (it == tableMultiGroup.end()) {
        std::cout<<"pas trouve dans tableMultiGroup"<<std::endl;
    } else {
        it -> second -> affichage(s);
    }
}

void Mixmap::jouerMultiMedia(std::string name){
    auto it = tableMultimedia.find(name);
    if (it == tableMultimedia.end()) {
        std::cout<<"pas trouve dans tableMultimedia"<<std::endl;
    } else {
        it -> second -> jouer();
    }
}

void Mixmap::moveParNameDansMultiMedia(std::string name){
    auto it = tableMultimedia.find(name);
    if (it == tableMultimedia.end()) {
        std::cout<<"pas trouve ce media"<<std::endl;
    } else {
        tableMultimedia.erase(it);
    }
}

void Mixmap::moveParNameDansMultiGroup(std::string name){
    auto it = tableMultiGroup.find(name);
    if (it == tableMultiGroup.end()) {
        std::cout<<"pas trouve ce group"<<std::endl;
    } else {
        tableMultiGroup.erase(it);
    }
}

bool Mixmap::processRequest(TCPConnection& cnx, const string& request, string& response)
{
    TCPLock lock(cnx);
    cerr << "\nRequest: '" << request << "'" << endl;

    // 1) pour decouper la requête:
    // on peut par exemple utiliser stringstream et getline()
    vector<string> command;
    stringstream ss(request);
    string sousChaine;
    while (getline(ss,sousChaine,' '))
    {
        //cout << sousChaine << endl;
        command.push_back(sousChaine);
    }
    if (command[0] == MODE1){
        string fileName = "";
        for (unsigned int i=1; i<command.size(); i++){
            if (i==1){
                fileName += command[i];
            }else{
                fileName += " " + command[i];
            }
        }
        cout<<fileName<<endl;
        stringstream s;
        this->chercherDansMultiMedia(fileName, s);
        string ss = "";
        string a;
        while (1)
        {
            s >> a;
            if (s.fail()) break;
            if (ss == ""){
                ss += a;
            }else{
                ss += " "+a;
            }
        }
        response = ss;
        //response = "OK: " + request + " finding...";
        //cerr << "response: " << response << endl;
    }else if (command[0] == MODE2) {
        string fileName = "";
        for (unsigned int i=1; i<command.size(); i++){
            if (i==1){
                fileName += command[i];
            }else{
                fileName += " " + command[i];
            }
        }
        cout<<fileName<<endl;
        this->jouerMultiMedia(fileName);
        response = "OK: " + request + " playing...";
        //cerr << "response: " << response << endl;
    }else if (command[0] == MODE3) {
        cout<<"In the process of creating group" << endl;
        int currentCommandNum = 0;
        string currentCommand = "";
        string name = "";
        string groupeName = "";
        for (unsigned int i=1; i<command.size(); i++){
            if (command[i] == ";"){
                if (currentCommandNum >= 2){ 
                    // the number of attributs is larger than 2 (not only "name" and "groupeName")
                    response = "wrong request";
                    replace(response.begin(),response.end(),'\n',';');
                    cout<<response<<endl;
                    cerr << "response: " << response << endl;
                    // renvoyer false si on veut clore la connexion avec le client
                    return true;
                    //cerr << "response: " << response << endl;
                }
                if (currentCommandNum == 0){
                    name = currentCommand;
                }else{
                    groupeName = currentCommand;
                }
                currentCommand = "";
                currentCommandNum += 1;
                continue;
            }
            if (currentCommand==""){
                currentCommand += command[i];
            }else{
                currentCommand += " " + command[i];
            }
        }
        if (currentCommandNum == 0){
            name = currentCommand;
        }else{
            groupeName = currentCommand;
        }
        cout << name << endl;
        cout << groupeName << endl;
        try{
            creerGroup(name,groupeName);
            response = "create group successfully!";
            //cerr << "response: " << response << endl;
        }
        catch (nameDuplicatedException& me1){
            response = me1.what();
            //cerr << "response: " << response << endl;
        }
        
    }else if (command[0] == MODE4) {
        cout << "In the processs of creating photo" << endl;
        int currentCommandNum = 0;
        string currentCommand = "";
        string name = "";
        string media = "defaultPhoto";
        string fichier = "defaultFichier";
        double latitude = 750.0;
        double longitude = 1250.0;

        for (unsigned int i=1; i<command.size(); i++){
            if (command[i] == ";"){
                if (currentCommandNum >= 5){ 
                    response = "wrong request";
                    replace(response.begin(),response.end(),'\n',';');
                    cout<<response<<endl;
                    cerr << "response: " << response << endl;
                    // renvoyer false si on veut clore la connexion avec le client
                    return true;
                    //cerr << "response: " << response << endl;
                }
                if (currentCommandNum == 0){
                    name = currentCommand;
                }else if (currentCommandNum == 1){
                    media = currentCommand;
                }else if (currentCommandNum == 2){
                    fichier = currentCommand;
                }else if (currentCommandNum == 3){
                    latitude = stod(currentCommand);
                }else{
                    longitude = stod(currentCommand);
                }
                currentCommand = "";
                currentCommandNum += 1;
                continue;
            }
            if (currentCommand==""){
                currentCommand += command[i];
            }else{
                currentCommand += " " + command[i];
            }
        }
        if (currentCommandNum == 0){
            name = currentCommand;
        }else if (currentCommandNum == 4){
            longitude = stod(currentCommand);
        }else {
            response = "Not enough attributes";
            replace(response.begin(),response.end(),'\n',';');
            cout<<response<<endl;
            cerr << "response: " << response << endl;
            // renvoyer false si on veut clore la connexion avec le client
            return true;
            //cerr << "response: " << response << endl;
        }
        //cout << name << endl;
        //cout << media << endl;
        //cout << fichier << endl;
        //cout << latitude << endl;
        //cout << longitude << endl;
        try{
            creerPhoto(name,media,fichier,latitude,longitude);
            response = "create photo successfully!";
            //cerr << "response: " << response << endl;
        }
        catch (nameDuplicatedException& me1){
            response = me1.what();
            //cerr << "response: " << response << endl;
        }
        catch (sizeInvalidException& me2){
            response = me2.what();
        } 
    }else if (command[0] == MODE5) {
        cout << "In the processs of creating video" << endl;
        int currentCommandNum = 0;
        string currentCommand = "";
        string name = "";
        string media = "defaultVideo";
        string fichier = "defaultFichier";
        int duree = 10;

        for (unsigned int i=1; i<command.size(); i++){
            if (command[i] == ";"){
                if (currentCommandNum >= 4){ 
                    response = "wrong request";
                    replace(response.begin(),response.end(),'\n',';');
                    cout<<response<<endl;
                    cerr << "response: " << response << endl;
                    // renvoyer false si on veut clore la connexion avec le client
                    return true;
                }
                if (currentCommandNum == 0){
                    name = currentCommand;
                }else if (currentCommandNum == 1){
                    media = currentCommand;
                }else if (currentCommandNum == 2){
                    fichier = currentCommand;
                }else{
                    duree = stoi(currentCommand);
                }
                currentCommand = "";
                currentCommandNum += 1;
                continue;
            }
            if (currentCommand==""){
                currentCommand += command[i];
            }else{
                currentCommand += " " + command[i];
            }
        }
        if (currentCommandNum == 0){
            name = currentCommand;
        }else if (currentCommandNum == 3){
            duree = stoi(currentCommand);
        }else {
            response = "Not enough attributes";
            replace(response.begin(),response.end(),'\n',';');
            cout<<response<<endl;
            cerr << "response: " << response << endl;
            // renvoyer false si on veut clore la connexion avec le client
            return true;
        }
        try{
            creerVideo(name,media,fichier,duree);
            response = "create video successfully!";
        }
        catch (nameDuplicatedException& me1){
            response = me1.what();
        }
        catch (sizeInvalidException& me2){
            response = me2.what();
        }
    }else if (command[0] == MODE6) {
        cout << "In the processs of creating film" << endl;
        int currentCommandNum = 0;
        string currentCommand = "";
        string name = "";
        string media = "defaultFilm";
        string fichier = "defaultFichier";
        int *timeTable = new int[10];
        timeTable[0] = 10;
        int numChap = 1;

        int numInTable = 0;

        for (unsigned int i=1; i<command.size(); i++){
            if (command[i] == ";"){
                if (currentCommandNum >= 5){ 
                    response = "wrong request";
                    replace(response.begin(),response.end(),'\n',';');
                    cout<<response<<endl;
                    cerr << "response: " << response << endl;
                    // renvoyer false si on veut clore la connexion avec le client
                    return true;
                }
                if (currentCommandNum == 0){
                    name = currentCommand;
                }else if (currentCommandNum == 1){
                    media = currentCommand;
                }else if (currentCommandNum == 2){
                    fichier = currentCommand;
                }else if (currentCommandNum == 3){
                    cout << "currentCommand: " << currentCommand << endl;
                    string tempS = "";
                    for (unsigned int j = 0; j<currentCommand.length(); j++){
                        if (currentCommand[j] == ' '){
                            timeTable[numInTable] = stoi(tempS);
                            numInTable += 1;
                            tempS = "";
                        }else{
                            tempS += currentCommand[j];
                        }
                    }
                    if (tempS != ""){
                        timeTable[numInTable] = stoi(tempS);
                        numInTable += 1;
                        tempS = "";
                    }
                }else{
                    numChap = stoi(currentCommand);
                    //cout << "numInTable: "<<numInTable << endl;
                    //cout << "numChap: " << numChap << endl; 
                    if (numInTable != numChap){
                        response = "not matched";
                        replace(response.begin(),response.end(),'\n',';');
                        cout<<response<<endl;
                        cerr << "response: " << response << endl;
                        // renvoyer false si on veut clore la connexion avec le client
                        return true;
                    }
                }
                currentCommand = "";
                currentCommandNum += 1;
                continue;
            }
            if (currentCommand==""){
                currentCommand += command[i];
            }else{
                currentCommand += " " + command[i];
            }
        }
        if (currentCommandNum == 0){
            name = currentCommand;
        }else if (currentCommandNum == 4){
            numChap = stoi(currentCommand);
            if (numInTable != numChap){
                response = "not matched";
                replace(response.begin(),response.end(),'\n',';');
                cout<<response<<endl;
                cerr << "response: " << response << endl;
                // renvoyer false si on veut clore la connexion avec le client
                return true;
            }
        }else {
            response = "Not enough attributes";
            replace(response.begin(),response.end(),'\n',';');
            cout<<response<<endl;
            cerr << "response: " << response << endl;
            // renvoyer false si on veut clore la connexion avec le client
            return true;
        }

        cout<<name<<endl;
        cout<<media<<endl;
        cout<<fichier<<endl;
        for (int i = 0 ; i<numInTable; i++){
            cout<<timeTable[i]<<" ";
        }
        cout<<endl;
        cout<<numChap<<endl;

        try{
            creerFilm(name,media,fichier,timeTable,numChap);
            response = "create film successfully!";
        }
        catch (nameDuplicatedException& me1){
            response = me1.what();
        }
        catch (sizeInvalidException& me2){
            response = me2.what();
        }
    }else if (command[0] == MODE7) {
        string name = "";
        for (unsigned i = 1; i < command.size(); i++){
            if (command[i] == ";" && i < command.size()-1){
                response = "Bad request";
                replace(response.begin(),response.end(),'\n',';');
                cout<<response<<endl;
                cerr << "response: " << response << endl;
                // renvoyer false si on veut clore la connexion avec le client
                return true;
            }else if (name == ""){
                name += command[i];
            }else{
                name += " " + command[i];
            }
        }

        auto it = tableMultimedia.find(name);
        if (it != tableMultimedia.end()){
            tableMultimedia.erase(name);
            response = "Delete successfully.";
        }else{
            response = "Not find the media!";
        }
    }else {
        //cout << "No this command!" << endl;
        response = "No this command!";
        //cerr << "response: " << response << endl;
    }
    
    /*
    for (unsigned int j = 0; j < response.length(); j++){
        if (response[j] == '\n'){
            response[j]=';';
        }
    }
    */
    replace(response.begin(),response.end(),'\n',';');
    cout<<response<<endl;
    cerr << "response: " << response << endl;
    // renvoyer false si on veut clore la connexion avec le client
    return true;
}









