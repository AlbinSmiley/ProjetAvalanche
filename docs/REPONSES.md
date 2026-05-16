# Réponses aux questions

## Question P1.1

### Comment représentez-vous ces vecteurs ?

Nous avons représenté un vecteur 3D par ses trois composantes réelles $(x, y, z)$.
Nous l'avons fait grâce à une classe `Vecteur3D` qui stocke 3 `double`.

### Comment sont-ils organisés : quels attributs ?

Nos attributs sont : `double x`, `double y` et `double z`, et ils sont privés.

### Quelles méthodes ?

- `set_coord(int i, double valeur)` : permet de modifier une valeur. `i = 0` modifie `x`, `i = 1` modifie `y` et `i = 2` modifie `z`.
- `affiche() const` : affiche le vecteur sous la forme `x y z`. Le `const` indique que la méthode ne modifie pas le vecteur.
- `compare(const Vecteur3D& autre, const double& precision=1e-10) const` : vérifie si deux vecteurs sont égaux. On passe `autre` et `precision` en `const &` pour éviter une copie et garantir qu'on ne les modifie pas.

### Quels droits d'accès ?

- `private` : les attributs `(x, y, z)` → encapsulation, cela évite les modifications incohérentes. De plus, nous avons vu en cours que les attributs devraient toujours être privés.
- `public` : les méthodes, afin de pouvoir utiliser et modifier les vecteurs.

## Question P4.1 : Avez-vous ajouté un constructeur de copie ? Pourquoi (justifier votre choix) ?

Non, le constructeur de copie par défaut est amplement suffisant ; il n'est pas nécessaire d'en créer un.

## Question P4.2 : Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur)

### P4.2.a) Que cela impliquerait-il au niveau des attributs de la classe ?

Cela n'impliquerait pas grand-chose : on pourrait simplement faire un constructeur qui prendrait deux angles et une longueur, et qui effectuerait les calculs nécessaires pour la conversion en coordonnées cartésiennes. On pourrait aussi redéfinir la classe pour que ses attributs soient exprimés en coordonnées sphériques, mais on ne pourrait alors plus avoir de constructeur cartésien.

### P4.2.b) Quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ?

Ce constructeur ne pourrait pas coexister avec le constructeur pour des coordonnées cartésiennes, car l'un éclipserait l'autre : rien ne les distingue aux yeux du compilateur (même nombre d'arguments et même type d'arguments, trois `double`). Puisque la question porte sur le cas où l'on *ajoute* ce nouveau constructeur à la classe déjà existante, on ne pourrait effectivement pas avoir ces deux constructeurs dans la même classe.

### P4.3 Quels opérateurs avez-vous introduits ?

Nous avons introduit tous les opérateurs usuels (`+`, `-`, …) ainsi que leurs opérateurs d'assignation associés (`+=`, `-=`, …). Nous avons également implémenté les opérateurs d'égalité `==` et `!=`, ainsi que l'opérateur vecteur unitaire `~` et vecteur opposé `-`.

## Question P5.1 : Comment avez-vous implémenté la masse des particules : comme attribut ou comme méthode ?

La masse des particules est implémentée en tant qu'attribut. En effet, la masse, tout comme le rayon et la masse volumique, n'est pas susceptible de changer ; il paraît donc logique qu'elle soit un attribut. Qui plus est, par analogie physique, il est plus naturel de considérer la masse comme une propriété intrinsèque d'une particule.

### Sous-question pour les méthodes `ajouteForce`

#### Peut-on ajouter les méthodes `ajouteForce` ?

Oui, c'est totalement possible : c'est le concept de surcharge. Les fonctions ont le même nom et la même portée, mais leurs arguments sont différents, donc il n'y a pas de problème.

## Question P6.1 : Comment proposez-vous de représenter les obstacles dans votre projet ? Cela modifie-t-il la classe `Particule` ?

Nous avons choisi de représenter un obstacle par une classe distincte de celle des particules.
Non, cela ne change pas notre classe `Particule`, car une particule et un obstacle n'ont pas le même rôle : une particule « n'est pas » un obstacle et un obstacle « n'est pas » une particule.

## Question P8.1 : En termes de POO, quelle est la nature de la méthode `dessine_sur()` ?

Nous avons décidé que la méthode `dessine_sur()` est une méthode virtuelle pure. Cela permet le polymorphisme et que chaque objet dessinable puisse définir sa propre manière de s'afficher, car il n'est pas possible de définir une manière générale.

## Question P8.2 : À quoi faut-il faire attention pour les classes contenant des pointeurs ? Quelle(s) solution(s) est/sont envisageable(s) ?

Il faut faire attention à la propriété des objets pointés, aux copies, à la destruction et aux risques de fuite mémoire ou de double destruction.

Si une classe contient des pointeurs, il faut se demander si le destructeur, le constructeur de copie et l'opérateur d'affectation doivent être redéfinis.

Une solution est d'interdire la copie, une autre est de faire une copie profonde, et une autre encore est de ne pas posséder les objets pointés mais seulement les référencer. Dans notre projet, nous avons choisi de stocker des pointeurs sur les obstacles et les sources sans faire de copie profonde (c'est-à-dire que nous manipulons leurs adresses sans créer de copies des objets).

## Question P8.3 : Comment représentez-vous la classe système ?

La classe `Systeme` représente l'ensemble du système simulé. Elle contient un vecteur de particules, ainsi que des vecteurs de pointeurs vers des obstacles et des sources.

Les particules sont stockées directement, mais ce choix va sûrement changer étant donné qu'en semaine 10 il y aura plusieurs types de particules. Les obstacles et sources sont stockés par pointeurs afin de permettre le polymorphisme.

La classe fournit des méthodes pour ajouter des éléments, des accesseurs, une méthode `dessine_sur()` pour l'affichage polymorphe et un opérateur `<<` pour l'affichage textuel du système.

## Question P9.1 : Quelle est la complexité des algorithmes 1 et 2 de la méthode `evolue` ?

Les deux algorithmes ont la même complexité dans le pire cas. Notons $n$ le nombre de particules et $m$ le nombre d'obstacles.

Dans le premier algorithme, pour une particule la complexité est $O(1) + O(m) + O(n) + O(1) = O(m + n)$, en partant du principe que faire bouger les particules et ajouter une force est de complexité $O(1)$. Pour $n$ particules on multiplie la complexité par $n$, donc $O(mn + n^2)$.

Dans le second algorithme, pour une particule on trouve $O(1) + O(m) + O(n) = O(m + n)$. Pour toutes les particules on a également $O(mn + n^2)$, puis on reboucle sur toutes les particules en appliquant `bouger`, donc $O(mn + n^2) + O(n) = O(mn + n^2 + n) = O(mn + n^2)$ : on retrouve bien la même complexité.

Dans tout le projet, le nombre d'obstacles est négligeable comparé au nombre de particules, donc le terme $mn$ est négligeable et on obtient une complexité $O(n^2)$ pour les deux algorithmes.

## Question P12.1

La complexité temporelle dans le pire cas de cette solution est $O(n)$.

Chaque particule ne teste plus son interaction avec toutes les autres particules du système, mais seulement avec les particules contenues dans sa case et dans les cases voisines directes. Comme le nombre de particules dans ces cases est supposé négligeable devant $n$, le nombre de tests effectués pour une particule est en $O(1)$. Pour $n$ particules, on obtient donc une complexité totale en $O(n)$.

L'inconvénient principal de cette méthode est qu'il faut gérer une structure de données supplémentaire représentant les cases de l'espace. Il faut aussi mettre à jour les cases lorsque les particules se déplacent. De plus, il faut bien choisir la taille des cases : si elles sont trop grandes, on effectue trop de tests inutiles ; si elles sont trop petites, il y a beaucoup de cases à gérer. Et dans le pire cas où toutes les particules se retrouveraient dans la même case, la complexité redeviendrait $O(n^2)$.

## Question P12.2

Nous avons implémenté cette nouvelle méthode de calcul des interactions à l'aide d'une classe `Grille`. L'espace est découpé en cases de taille fixe, choisie supérieure à $2\sigma$.

Chaque particule est associée à une case grâce à ses coordonnées spatiales. Les cases sont stockées dans un tableau tridimensionnel contenant, pour chaque case, la liste des particules qui s'y trouvent.

Avant chaque évolution du système, la grille est reconstruite à partir des positions actuelles des particules. Pendant le calcul des forces d'interaction, une particule ne parcourt plus toutes les particules du système : elle parcourt uniquement les particules contenues dans sa case et dans les cases voisines directes.

Cette méthode a été implémentée dans la classe `Grille` et utilisée dans la méthode `Systeme::evolue()`.

## Question P13.1

Dans cette version, les cases sont stockées dans une table associative :

```cpp
map<Triplet, vector<Particule*>>
```

Pour chaque particule, on regarde sa case et les 26 cases voisines, soit un nombre constant de cases à consulter.

Avec une `map`, l'accès à une case coûte $O(\log M)$ (car `map` est souvent implémentée avec un arbre binaire rouge-noir), où $M$ est le nombre de cases non vides. Comme $M$ est au plus de l'ordre du nombre de particules $N$, on peut majorer ce coût par $O(\log N)$.

Si les particules sont suffisamment bien réparties, chaque case contient un nombre borné de particules. Le coût par particule est donc $O(\log N)$, et pour $N$ particules on obtient une complexité en $O(N \log N)$.

Cependant, dans le pire cas physique où toutes les particules se trouvent dans la même case, chaque particule doit encore interagir avec presque toutes les autres. Dans ce cas, on retombe sur une complexité en $O(N^2)$.

L'avantage principal par rapport à la solution précédente avec tableau tridimensionnel est que l'on ne stocke que les cases occupées, ce qui évite de réserver beaucoup de mémoire pour des cases vides. Cette solution est donc plus adaptée à un espace grand ou peu rempli, et elle ne nécessite pas de fixer à l'avance les dimensions de la grille.
