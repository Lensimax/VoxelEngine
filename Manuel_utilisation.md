# Manuel d'utilisation

## Controles

On lancement du jeu, vous controlez le personnage, vous pouvez :
* vous déplacer avec ZQSD
* tourner la caméra avec la souris

Si vous faites ```CTRL + U``` vous passez en mode "editeur" vous pouvez maintenant :
* Orienter la camera en appuyant sur le clic gauche de la souris et en déplaçant la souris
* Bouger la caméra sur les cotés en appuyant sur le clic droit de la souris
* ```CTRL + H``` pour afficher/cacher l'interface
* vous pouvez toujours déplacer le personnage et voir le terrain se charger



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
