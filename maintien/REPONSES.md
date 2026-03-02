# Réponses aux question 
## Question P1.1 
**Comment représentez-vous ces vecteurs ?**

nous avons représenté un vecteur 3D par ses trois composantes reelles (x,y,z)
nous l'avons fait grâce à une classe vecteur3D qui stocke 3 double

**Comment sont-ils organisés : quels attributs ?** 

nos attributs sont : double x; double y; et double z; et ils sont privés

**quelles méthodes ?** 
- set_coord(int i, double valeur) permet de modifier une valeur. i = 0 modifie x, i = 1 modifie y et i = 2 modifie z
- affiche() const affiche le vecteur sous la fomre x y z et c'est suivi d'un const car cela doit juste afficher et pas modifier le vecteur 
- compare(const Vecteur3D& autre, const double &precision=1e-10) const verifie si deux vecteurs sont égaux. On met autre et presision en const & pour éviter une copie et garantir qu’on ne les modifie pas.

**quels droits d'accès ?**

private : les attributs (x,y,z) -> encapsulation et cela évite les modifications incohérantes. de plus nous avons vu en cours que les attributs devraient toujours etre privés
public : les méthodes afin d'utiliser et de modifier les vecteurs. 
