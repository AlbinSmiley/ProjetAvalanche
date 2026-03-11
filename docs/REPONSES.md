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
