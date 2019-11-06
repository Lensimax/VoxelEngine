# Informatique graphique
#### TP : Simplification de maillage

par Maxime Isnel

## Compiler le code

##### Sur Linux

Dependencies :

```sudo apt-get install -y build-essential cmake xorg-dev libgl1-mesa-dev libfreetype6-dev```

Pour compiler :

```cd build && cmake .. && make```

##### Sur Windows

Dependencies :

* mingw64 ou mingw32
* cmake

Pour compiler :

* Lancer ```Cmake```
* Configurer avec les ```Mingw Makefile``` pour compiler dans le dossier ```build```
* Lancer ```mingw64```
* Aller dans le dossier ```build```
* Compiler avec ```mingw32-make```

Pour lancer le programme :

 ```./green-engine```

## Fonctionnalités

Dans le programme, il y a une fenêtre qui gère la scène, qui contient (la lumière, la caméra, les objets de la scène). La fenêtre peut être redimensionnée. Quand vous cliquez sur un objet dans la liste d'objet vous voyez à droite toutes les informations concernant cet objet (position, mesh, orientation, ...).

Vous pouvez :

 * Ajouter des objets avec maillage en faisant ```Edit => Add MeshObject```. Vous pouvez ensuite changer le maillage chargé en changeant le chemin du fichier .OFF et en appuyant sur le bouton "Recreate"
 * Faire tourner les objets, les déplacers, ...
 * Afficher l'objet avec des ```WireFrame``` en faisant ```View => Toggle wire frame```
 * Simplifier le maillage en changeant la **résolution** après "vertices simplification" et en appuyant sur le bouton simplify. Cette résolution correspond à la grille qui permet de simplifier le maillage.

 ## Structure du code

 La scène est composé d'un arbre de ```ObjectEngine```, chaque ```ObjectEngine``` a un Transform qui permet de le déplacer. Les objets affichables contiennent un maillage et un matériau. Le materiau permet d'afficher l'objet et de changer le shading. Le maillage contient les informations données à OpenGL pour afficher l'objet. Le fichier ```Mesh.cpp``` dans le dossier "models" contient toutes les fonctions liées au maillage comme l'algorithme pour la **simplification**.
