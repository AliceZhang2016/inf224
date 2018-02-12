# inf224
project in school 2017-2018 telecomParistech

This project is to construct a connection between the server and client. All the code of server is written by C++. There are 2 versions of client, one is C++, another is JavaSwing which offers an interactive interface. 
Server should be lauched first, then open the client.

------
# 1. Run the code
## server (use C++)
```Javascript
cd cpp
make clean; make
make run-server
```
## client 
### use C++
```Javascript
cd cpp
make run-client
```
There are several commands that could be tapped in the command line: (written in French)

> chercher \<nom d'objet ou groupe dans le map\>

Pour chercher un objet ou groupe et afficher les attributs.

**Example:** chercher V1


> jouer \<nom d'un groupe dans le map\>

Pour jouer un media qui a le nom.

**Example:** jouer V2


> createG \<nom d'un groupe dans le map\> ; \<nom d'un groupe définie dans le 8ème étape\> (Remarque: \<nom d'un groupe définie dans le 8ème étape\> est optionnel)

Pour créer un groupe qui s'appelle \<nom d'un groupe\> et qui a le nom \<nom d'un groupe dans le map\> dans le map du groupe.

**Example1:** createG G1

**Example2:** createG G2 ; myGroup 
		

> createP \<nom d'un photo dans le map\> ; \<media\> ; \<fichier\> ; \<latitude\> ; \<longitude\> (Remarque: les derniers 4 paramètres sont optionnels)

Pour créer un photo qui ont les attributs associés (défault s'il n'y a pas de l'input des attributs) et qui a le nom \<nom d'un photo dans le map\> dans le map.

**Example1:** createP P5

**Example2:** createP P6 ; sky.jpg ; /home/Downloads/ ; 1200.0 ; 750.0 


> createV \<nom d'un video dans le map\> ; \<media\> ; \<fichier\> ; \<duree\> (Remarque: les derniers 3 paramètres sont optionnels)

Pour créer un vidéo qui ont les attributs associés (défault s'il n'y a pas de l'input des attributs) et qui a le nom \<nom d'un video dans le map\> dans le map.

**Example1:** createP V5

**Example2:** createP V6 ; Try.mp4 ; /home/Downloads/ ; 60 


> createF \<nom d'un film dans le map\> ; \<media\> ; \<fichier\> ; \<tableau des durées\> ; \<nombre des chapitres\> (Remarque: les derniers 4 paramètres sont optionnels)

Pour créer un film qui ont les attributs associés (défault s'il n'y a pas de l'input des attributs) et qui a le nom \<nom d'un film dans le map\> dans le map.

**Example1:** createF F5

**Example2:** createF F6 ; Try.mp4 ; /home/Downloads/ ; 10 20 30 ; 3 


> delete \<nom d'objet ou d'un groupe dans le map\>

Pour supprimer un objet qui a le nom dans le map.

**Example:** delete P1


### use Java Swing
```Javascript
cd swing
make clean; make
make run
```
After tapping the command "make run", it appears an interface with several buttons, and a textfield on the upper right corner to input the name of media.

- **chercher**: find and print the information of the media which have the name indicated in the textfield.

- **jouer**: play the media which have the name indicated in the textfield.

- **close**: close the interface.

# 2. Explaination for different part of code
### In the folder cpp/
- multimedia.h multimedia.cpp (Multimedia is the base class for the object "multi-media")
- photo.h photo.cpp (inherit Multimedia, responsible for the object "photo")
- video.h video.cpp (inherit Multimedia, responsible for the object "video")
- film.h film.cpp (inherit Video, responsible for the object "film")
- group.h group.cpp (it is in fact a list of smart pointers Multimedia*, it could contain all kinds of multimedia(photo,video,film))
- mixmap.h mixmap.cpp 
    - manages all the data(multimedia and group)
    - processRequest() is responsible for processing the request from client and giving the responses.
- client.cpp (connect the client the send request)

### In the folder swing
- infswing.java
connect with server, send request, design and show the interface.
