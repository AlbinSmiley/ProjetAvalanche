# Réponses aux question 
## Question P1.1 
### Comment représentez-vous ces vecteurs ? 
nous avons représenté un vecteur 3D par ses trois composantes reelles (x,y,z)
nous l'avons fait grâce à une classe vecteur3D qui stocke 3 double

### Comment sont-ils organisés : quels attributs ?
nos attributs sont : double x; double y; et double z; et ils sont privés

### quelles méthodes ? 
- `set_coord(int i, double valeur)` permet de modifier une valeur. i = 0 modifie x, i = 1 modifie y et i = 2 modifie z
- `affiche() const` affiche le vecteur sous la fomre x y z et c'est suivi d'un const car cela doit juste afficher et pas modifier le vecteur 
- `compare(const Vecteur3D& autre, const double &precision=1e-10) const` verifie si deux vecteurs sont égaux. On met autre et presision en const & pour éviter une copie et garantir qu’on ne les modifie pas.

### quels droits d'accès ?
private : les attributs (x,y,z) -> encapsulation et cela évite les modifications incohérantes. de plus nous avons vu en cours que les attributs devraient toujours etre privés
public : les méthodes afin d'utiliser et de modifier les vecteurs. 

## Question P4.1 : Avez-vous ajouté un constructeur de copie ? Pourquoi (justifier votre choix) ?
Oui, nous avons ajouté un constructeur de copie. En effet, il nous semble que la copie d'un élément de la class `Vecteur3D` ne semble pas si couteux en terme de capacité. Bien qu'une version par défaut suffisante soit fourni par le compilateur, ajouter le code dans la class ne coute rien, rends le code plus lisible et permet un meilleur contrôle sur celui ci dans le future. 

## Question P4.2 : Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur) ... 
### P4.2.a) que cela impliquerait-il au niveau des attributs de la classe ? 
Cela n'impliquerait pas grand chose on pourait simplement faire un constructeur qui prendrait en effet deux angles et une longueur et qui fairait les calcules nécéssaire pour la conversion en coordonnées cartésiennes ou bien on pourrait redéfinir la class pour que ces attribut soit exprimé en coordnonnée sphérique. 

### P4.2.b) quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ? (C'est d'ailleurs pour cela qu'on ne vous demande pas de faire un tel constructeur !)
Mais alors ce constructeur ne pourrait pas coéxister avec le constructeur pour des coordonnées cartésienne car l'un eclipserait l'autre vu que rien ne les distingue aux "yeux" du compilateur (même nombre d'arguement du constructeur et même type d'argument, trois `double`). Puisque la question est dans le cas où l'on _ajoute_ ce nouveau constructeur à la class déjà éxistante, en effet, on ne pourrait pas avoir ces deux constructeur dans la même class. 

## Question P5.1 : Comment avez-vous implémenté la masse des particules : comme attribut ou comme méthode ? 
La masse des particules est implémenté en tant qu'attribut. En effet la masse tout comme le rayon et la masse volumique ne sont pas susceptible de changer il parait logique que la masse soit un attribut. Qui plus est, par analogie, il est plus logique de considérer la masse comme un attribut, car "physiquement" cela fait parti des propriété intrinsec d'une particule. 

### sous question pour les méthode `ajouteForce`

### Question P6.1 : Comment proposez-vous de représenter les obstacles dans votre projet ? Cela modifie-t-il la classe "Particule" ? 
Nous avons choisi de représenter un obstacle par une classe distincte de celle des particules.
Non ça ne change pas notre classe particule car une particule et un obstacle n'ont pas le même rôle et une particule "n'est pas" un obstacle et un obstacle "n'est pas" une particule. 

### Question P8.1 : En terme de POO, quelle est donc la nature de la méthode dessine_sur() ?
nous avons décidé que la méthode dessine_sur() est une méthode virtuelle pure. Cela permet le polymorphisme et aussi que chaque objet dessinable puisse définir sa propre manière de s'afficher car on n'arrive pas à définir un manière générale. 

### Question P8.2 : A quoi faut-il faire attention pour les classes contenant des pointeurs ? quelle(s) solution(s) est/sont envisageable(s)?
il faut faire attention à la propriété des objets pointés, aux copies, à la destruction et aux risques de fuite de mémoire ou de double destruction. 
Si une classe contient des pointeurs, il faut se demander si le destructeur, le constructeur de copie et l’opérateur d’affectation doivent être redéfinis.
Une solution est d'interdire la copie, une autre à faire une copie profonde, et une autre encore à ne pas posséder les objets pointés mais seulement les référencer. Dans notre projet nous avons choisi de stocker des pointeurs sur les obstacles et les sources sans faire la copie profonde.( c’est-à-dire que nous manipulons leurs adresses sans créer de copies des objets)

### Question P8.3 : Comment représentez-vous la classe système ? 
La classe Systeme représente l’ensemble du système simulé. Elle contient un vecteur de particules, ainsi que des vecteurs de pointeurs vers des obstacles et des sources.

Les particules sont stockées directement mais ce choix va surement changer étant donner qu'en semaine 10 il y aura plusieurs types de particules.Les obstacles et sources sont stockés par pointeurs afin de permettre le polymorphisme.

La classe fournit des méthodes pour ajouter des éléments, des accesseurs, une méthode dessine_sur() pour l’affichage polymorphe et un opérateur << pour l’affichage textuel du système.

### question P12.1 : 
La complexité temporelle pire cas de cette solution est O(N) .

Chaque particule ne teste plus son interaction avec toutes les autres particules du système, mais seulement avec les particules contenues dans sa case et dans les cases voisines directes. Comme le nombre de particules dans ces cases est supposé négligeable devant N, le nombre de tests effectués pour une particule est en O(1). Pour N particules, on obtient donc une complexité totale en O(N).

L’inconvénient principal de cette méthode est qu’il faut gérer une structure de données supplémentaire représentant les cases de l’espace. Il faut aussi mettre à jour les cases lorsque les particules se déplacent. De plus, il faut bien choisir la taille des cases : si elles sont trop grandes, on effectue trop de tests inutiles mais si elles sont trop petites il y a beaucoup de cases à gérer. Et dans le pire cas où toutes les particules se retrouveraient dans la même case, la complexité redeviendrait O(N²).

### question P12.2 : 
Nous avons implémenté cette nouvelle méthode de calcul des interactions à l’aide d’une classe Grille. L’espace est découpé en cases de taille fixe, choisie supérieure à 2σ.

Chaque particule est associée à une case grâce à ses coordonnées spatiales . Les cases sont stockées dans un tableau tridimensionnel contenant, pour chaque case, la liste des particules qui s’y trouvent.

Avant chaque évolution du système, la grille est reconstruite à partir des positions actuelles des particules. Pendant le calcul des forces d’interaction, une particule ne parcourt plus toutes les particules du système : elle parcourt uniquement les particules contenues dans sa case et dans les cases voisines directes.

Cette méthode a été implémentée dans la classe Grille et utilisée dans la méthode Systeme::evolue().

### question P13.1 : 
Dans cette version, les cases sont stockées dans une table associative :

map<Triplet, vector<Particule*>>

Pour chaque particule, on regarde sa case et les 26 cases voisines. Il y a donc un nombre constant de cases à consulter

Avec une map, l’accès à une case coûte O(log M) (car map est souvent implemnté avec un arbre binaire) où M est le nombre de cases non vides. Comme M est au plus de l’ordre du nombre de particules N, on peut majorer ce coût par O(log N).

Si les particules sont suffisamment bien réparties(dit dans P13), chaque case contient un nombre borné de particules. Le coût par particule est donc O(log N), et pour N particules on obtient une complexité en O(N log N).

Cependant, dans le pire cas physique où toutes les particules se trouvent dans la même case, chaque particule doit encore interagir avec presque toutes les autres. Dans ce cas, on retombe sur une complexité en O(N²).

L’avantage principal par rapport à la solution précédente avec tableau tridimensionnel est que l’on ne stocke que les cases occupées. Cela évite de bcp réserverde la mémoire pour des cases vides. Cette solution est donc plus adaptée à un espace grand ou peu rempli et elle ne nécessite pas de fixer à l’avance les dimensions de la grille