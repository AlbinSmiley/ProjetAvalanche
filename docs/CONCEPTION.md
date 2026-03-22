Pour la classe Vecteur3D : 
    il n'y a pas de relation d'héritage dans cette partie du projet. 
    encapsulation : nous avons mis les attributs (x,y,z) en privé Cela permet de protéger l’état interne de l’objet et de garantir que les modifications passent par les opérations prévues par la classe.les constructeurs, les opérateurs surchargés et les méthodes sont en public. Ce choix améliore la robustesse du code 
    
semaine 5 : 
## Obstacles

Les obstacles sont modélisés par une hiérarchie de classes.

- Obstacle : classe de base représentant un objet fixe, caractérisé par une position.
- Plan : hérite de Obstacle et représente un plan infini, défini par une normale unitaire. Il fournit une méthode permettant de calculer le point du plan le plus proche d’un point donné.
- Dalle : hérite de Plan et représente une portion rectangulaire de plan. Elle ajoute une longueur, une largeur et une direction unitaire (direction de la longueur). La direction de la largeur est donnée par le produit vectoriel entre la normale et la direction de longueur.

Cette organisation permet de structurer les différents types d’obstacles tout en réutilisant les propriétés communes.