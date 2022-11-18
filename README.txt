-> Liste des fichiers :

main.c				-> Contient les fonction lié au lancement ou au chargement d'une partie

perlin.h/perlin.c		-> Contient des fonctions qui permettent de reproduire un bruit de perlin
				-> ce qui servira à générer la map de façcon procédurale (ces fonctions ont été trouvé sur 					-> internet et sont utilisées à bonne escient)

item.h/item.c			-> Contient tous les différents items et une fonction permettant d'en
				-> chosir un aléatoirement

map.h/map.c			-> Contient la structure Bloc et les fonctions qui permettent de
				-> générer et d'afficher la map

player.h/player.c		-> Contient les fonctions qui permettent de gérer le joueur

mob.h/mob.c			-> Contient les fonctions qui permettent de gérer les mobs


-> Aucune blibliothèques externes n'est nécessaire.

-> Compilation et lancement du jeu :

Pour compiler le projet il vous suffit de lancer la commande "make".
Pour supprimer les fichier ".o" vous pouvez lancer la commande make clean
Pour lancer le jeu une fois la commande "make" effectué pous utiliser la commande "./ProjectC"

-> Liste des fonctionnalités : 

- Le jeu se déroule sur un plateau bidimensionel avec une taille que le joueur peut chosir.
- Le personnage peut se déplacer sur la map et a des contraintes de déplacement en fonction des blocs.
- Le personnage peut intéragir avec des blocs (peut détruire les arbres et ouvrir les coffres).
- Le joueur peut ouvrir un menu qui lui permet de sauvegarder la partie (état du monde, des mobs et du joueur).
- Au démarrage du jeu le joueur peut soit démarrer une nouvelle partie soit reprendre la dernière partie sauvegarder.
- Au démarrage d'une partie le joueur peut choisir la taille de la map et son nom.
- Des monstres apparaissent sur la map au début de la partie et peuvent intéragir avec le joueur.
- Lorsque le joueur croisent un monstre, il attaque le monstres et le monstre attaque le joueur automatiquement. Les deux      ont une probabilité de mettre un coup critique et d'esquiver qui est la même. Si le joueur possède une épée il met plus de   dégats et s'il possède un casque il prend moins de dégats.
- Un système d'affichage de point de vie constant permet de savoir l'état du personnage.
- Le joueur peut se soigner en mangeant de la nourriture.
- Lorsque le joueur tue un monstre il gagne de l'éxpérience ce qui lui permet de monter en niveau.
- Les monstres lorsqu'ils sont à moins de 20 blocs du joueur, se déplacent vers celui-ci.
- La map se génére procéduralement et crée un environnement cohérent.
- L'affichage du monde au joueur est progressif : seules les parties exploré sont visibles
- L'affichage est limité, le personnage ne voit que ce qu'il y a devant lui (limité par la distance et par les obstacles).
- Un système d'inventaire (de taille limitée) est implémenté.
- Un système de coffres qui se remplissent aléatoirement avec deux items (Le joueur peut en choisir qu'un seul dans chaque   coffres).
- Un affichage en couleur est réalisée.

-> Manuel utilisateur :

Lorsque le jeu commence le joueur peut soit créer une nouvelle partie, soit charger la dernière partie sauvegardée.

Dans le cas où on lance une nouvelle partie on va devoir entrer la taille des cotés de la map puis entrer notre nom de joueur. Sinon, dans le cas où l'on veut choisir de charger une partie on aura juste à choisir de charger la game et cela se fera automatiquement. A la suite de ces deux actions la map apparaît.

Glossaire des différents affichages :

La roche	-> représentée par un '#' gris
La terre	-> représentée par un '#' rouge
L'arbre		-> représenté par un 'T' vert
Le sable 	-> représenté par un 's' jaune
L'eau 		-> représenté par un '~' bleu
Le coffre 	-> représenté par un '@' magenta
Le monstre	-> représenté par un 'M' bleu ciel
Le personnage 	-> représenté par un 'ᐃ' ou un 'ᐁ' ou un 'ᐅ' ou un 'ᐊ' bleu ciel

Une fois la map apparue il y a différentes actions possibles en fonction de la touche sur laquelle le joueur appuie : 

z = monter
s = descendre
q = gauche
d = droite
i = voir l'inventaire
r = manger (si le joueur à de la nourriture dans son inventaire) 
t = détruire les arbres autours du joueur
m = ouvrir le menu (pour sauvegarder / quitter le jeu)

Lorsque l'on marche sur un coffre on peut choisir entre deux objets, lorsque le joueur prend l'objet le coffre disparait et l'objet apparait dans l'inventaire. Si le joueur entre une valeur erroné le coffre disparait également.

Lorsque l'on rencontre un monstre, le personnage attaque automatiquement le monstre et réciproquement le monstre attaque le joueur. Il y a une certaine probabilité que le personnage ou le monstre esquive, ou alors inflige un coup critique.
