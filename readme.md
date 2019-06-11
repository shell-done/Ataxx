# Jeu Ataxx - Projet de C++
### Alexandre THOMAS
----

### Description
A l'origine, Ataxx est un jeu d'arcade sortie en 1990 développé et édité par Leland. L'objectif étant de posséder le plus de pion sur le plateau.
L'objectif de ce projet est la réalisation de ce jeu en C++ avec le framework Qt

### Règles du jeu
Ce jeu possède des règles très simples :
Deux joueurs d'affrontent sur un plateau de 7x7 cases. Un pion de chaque jouer est placé aux extrémité de chaques diagonales. Le jeu se joue en tour par tour. A chaque tour, un joueur sélectionne l'un de ses pions, à ce moment, deux chois s'offrent à lui. Il peut déplacer son pion sur une case adjacente (diagonales incluses) à sa case de départ. Dans ce cas, son pion est dupliqué. Il possède maintenant un pion sur sa case de départ et un sur sa case d'arrivée. Il peut aussi déplacer son pion à deux cases de distances. Dans ce cas, le pion est simplement déplacé sans être dupliqué. Après avoir déplacé son pion, les pions du joueur adverse adjacent deviennet de la couleur du joueur actuel. Le tour se finit et c'est à l'autre joueur de jouer. La partie s'arrête lorsque l'un des deux joueurs ne peut plus jouer, dans ce cas c'est celui qui a le plus de pions qui gagne.

### Réalisation et compilation
Ce projet a été réalisé avec le framework Qt en version 5.10.1 sous l'IDE QtCreator. La compilation de ce projet requiert l'utilisation du fichier qmake ataxx.pro fourni avec les sources. De plus, un fichier de ressources (fichier .qrc) a été utilisé.
Pour profiter pleinement des fonctionnalités qui seront détaillées plus loin, merci de placer les dossier /langs et /textures packs au même endroit que l'éxécutable. Pour en savoir plus, merci de lire la section "Ressources externes".

### Execution du jeu
Comme demandé, le jeu est jouable de deux manières différentes, en version console ou graphique. Il est aussi possible de lancer les deux versions en même temps, dans ce cas, la console ne sert que d'affichage et ne récupère pas les entrées.
La version console ne servant que pour tester le moteur de jeu, les possiblités de celles-ci sont très limitées

Pour lancer le jeu dans différent mode :
 + Mode console : `./ataxx --mode console`
 + Mode graphique : `./ataxx --mode graphic`
 + Mode mixe (console et graphique) : `./ataxx --mode mixed`

Par défaut, le mode graphique est utilisé.

### Fonctionnalités ajoutées
Dans le cadre de ce projet, nous avions la liberté d'ajouter les fonctionnalités qui nous semblaient intéressantes. Voici donc la liste des fonctionnalités ajoutées :

##### Langues
Le jeu dispose de fichiers de langues permettant de jouer en Anglais ou en Français. Il est aussi possible de créer son propre fichier de langue et de l'ajouter au dossier ./langs. Celle-ci sera disponible dans le jeu. Pour en savoir plus, merci de lire la section "Ressources externes"

##### Packs de textures
Inspiré du célèbre jeu Minecraft, le jeu propose un système de pack de texture. Il est possible de créer son propre pack ou d'utiliser ceux déjà disponibles. Cela provoque un changement des couleurs, des images, de la police et des sons du jeu. Pour savoir comment créer son propre texture pack, merci de lire la section "Ressources externes"

Note en plus : Le pack "CIR Rennes" avec nos têtes n'est évidemment destiné qu'au rendu du projet et ne sera pas publié en ligne.

##### Plus de joueurs
Le jeu peut maintenant se jouer de 2 à 4 joueurs, le placement des pions sur la grille changeant en fonction du nombre de joueur. De plus, en fonction des packs de textures, chaque joueur possède un pion différent et une image différente.

##### Taille de la carte
La taille de la carte peut maintenant varier de 5x5 à 12x12 cases

##### Obstacles
Il est possible de générer des murs sur le plateau. Ceux-ci sont générés aléatoirement avec une chance sur dix d'apparaître sur chaque case

##### Version en ligne
Une version en ligne a été envisagée, cependant elle n'a pas été réalisé par manque de temps

### Ressources externes
##### Fonctionnement
Les ressources externes sont les langues et les packs de textures. Ceux-ci n'ont volontairement pas été inclus dans le projet dans le fichier .qrc. Cela pour permettre à n'importe qui de créer, d'ajouter, de modifier ou de supprimer un pack de textures ou une langue.

Cependant, cela demande de placer les dossiers au bon endroit pour le programme. Il suffit de placer les dossiers ./langs et ./textures packs dans le même dossier que l'exéctuable pour que celui-ci s'en serve. Si ces dossiers ne sont pas aux bons endroit, un message d'erreur apparaitra dans la console. Le jeu sera quand même jouable car les ressources minimales ont été incluses dans le fichier .qrc. Cependant, aucun son ne sera joué et il sera impossible de changer de langue ou de pack de texture.

##### Fichiers de langue
Pour créer son propre fichier de langue, il faut créer un fichier avec l'extension .lang dans le dossier ./langs
A la première ligne de ce fichier, il faut écrire le nom de la langue
Sur les autres lignes, il faut écrire les traductions. Pour cela, merci de se baser sur les fichiers de langues existants.

##### Pack de textures
Pour créer son propre pack de texture, il faut créer un dossier dans le dossier ./textures packs. Dans ce dossier, ajouter un fichier appelé pack.conf. Sur la première ligne, ajouter pack_name = [NOM DE VOTRE PACK] et sur la deuxième ligne description = [DESCRIPTION DE VOTRE PACK].
D'autres informations peuvent être ajoutées à ce fichier :
 + `use_accents = [true/false]` : Précise si le programme doit afficher le texte avec ou sans les accents (utiles pour certaines polices)
 + `primary_color = r,g,b` avec r,g,b des entiers compris entre 0 et 255 : Définit la couleur principale
 + `secondary_color = r,g,b` avec r,g,b des entiers compris entre 0 et 255 : Définit la couleur secondaire
 + `tertiary_color = r,g,b` avec r,g,b des entiers compris entre 0 et 255 : Définit la couleur tertiaire

Il est aussi possible d'ajouter sa propre police. Pour cela, il suffit d'ajouter un fichier nommé 'font.ttf' dans le dossier du pack de textures. Si ce fichier n'est pas présent, il est aussi possible d'ajouter la ligne `font = [FONT_NAME]` dans le fichier pack.conf. Celle-ci sera utilisée si elle est installée sur votre système.

Pour le reste, il suffit d'ajouter les images dans les bons dossiers. Pour cela, merci de vous baser sur les packs de textures existants.
 
### License
Le projet est sous license MIT, pour plus d'information, merci de se reporter au fichier LICENSE

### Auteur
Ce projet a été réalisé par [Alexandre THOMAS](https://alexandre-thomas.fr) dans le cadre du cours de C++ de deuxième année du cycle informatique et réseaux à l'[ISEN](https://www.isen.fr/) Rennes.

