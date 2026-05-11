
CONCEPTION

Notre projet est organisé autour d’une séparation entre la simulation physique et l’affichage.

1. Classes de base

- Vecteur3D
  Classe utilitaire représentant les vecteurs de l’espace. Elle est utilisée pour les positions, vitesses, forces et directions.

- Aleatoire
  Classe permettant de générer des nombres aléatoires uniformes ou gaussiens. Elle est utilisée par la classe Source pour créer de nouvelles particules.

2. Classes de simulation

- Particule
  Représente une particule du système. Elle possède une position, une vitesse, un rayon, une masse volumique, une masse et une force. Elle peut recevoir différentes forces et être déplacée.

- Obstacle
  Classe abstraite représentant un obstacle fixe. Elle possède une position et une méthode virtuelle pure PointPlusProche(), car chaque type d’obstacle calcule différemment le point le plus proche d’une particule. Ce choix suit directement l’énoncé sur les obstacles. 

- Plan
  Hérite de Obstacle. Représente un obstacle plan défini par une position et une normale unitaire.

- Dalle
  Hérite de Plan. Représente une portion rectangulaire de plan. Elle ajoute une largeur, une longueur et une direction de longueur.

- Source
  Représente une source de particules. Elle contient une référence vers une particule modèle, une position, une vitesse moyenne initiale, des écarts-types, un débit et un état actif/inactif. Elle peut générer de nouvelles particules.

- Systeme
  Représente l’ensemble du système simulé. Il contient des particules, des obstacles et des sources. Le système connaît dans quel environnement on est et comment le temps avance.
 
3. Affichage

- Dessinable
  Classe abstraite pour tous les objets pouvant être affichés.

- SupportADessin
  Classe abstraite définissant une interface générale d’affichage.

- TextViewer
  Sous-classe de SupportADessin permettant un affichage en mode texte.

- RaylibRender
  Sous-classe de SupportADessin permettant un affichage graphique avec raylib.

Les classes Particule, Obstacle, Plan, Dalle, Source et Systeme héritent de Dessinable et possèdent une méthode dessine_sur().

4. héritage

La classe Dessinable est une classe abstraite qui représente tous les objets pouvant être affichés. Les classes Particule, Obstacle, Source et Systeme héritent de Dessinable.

La classe Obstacle est une classe abstraite représentant un obstacle général. La classe Plan hérite de Obstacle car un plan est un type particulier d’obstacle. La classe Dalle hérite de Plan car une dalle "est un" plan avec des dimensions finies.

La classe SupportADessin est une classe abstraite définissant une interface commune pour les différents types d’affichage. Les classes TextViewer et RaylibRender héritent de SupportADessin et implémentent chacune un mode de visualisation différent, respectivement en mode texte et en mode graphique.

5. Encapsulation 


Dans notre projet, l’encapsulation est assurée en rendant les attributs privés ou protégés, et en contrôlant leur accès par des méthodes publiques.

Dans la classe Vecteur3D, les coordonnées x_, y_ et z_ sont privées. Elles sont accessibles et modifiables uniquement via des getters et des setters, ainsi que par les opérateurs et méthodes de la classe.

Dans la classe Particule, les attributs position_, vitesse_, rayon_, rho_, masse_ et force_ sont privés. L’accès se fait par des getters, et la modification se fait par des méthodes comme setVitesse(), setRayon(), ajouteForce() et bouger().

Dans la classe Obstacle, l’attribut position est protégé. Cela permet aux classes dérivées comme Plan d’y accéder directement, tout en le cachant aux autres classes. L’accès extérieur se fait par getPosition().

Dans la classe Plan, l’attribut normale est protégé. Il est accessible par la classe Dalle qui hérite de Plan, tandis que l’accès extérieur se fait par getNormale().

Dans la classe Dalle, les attributs largeur, longueur et directionLongueur sont privés. Ils sont accessibles uniquement via des getters.

Dans la classe Source, les attributs modele_, position_, vitesse_moyenne_initial_, ecart_type_vitesse_initial_, ecart_type_rayons_, debit_ et etat_ sont privés. La source contrôle son comportement via les méthodes on(), off() et creation().

Dans la classe Systeme, les vecteurs de particules, d’obstacles et de sources sont privés, ainsi que les paramètres du milieu et du pas de temps. L’accès se fait par des getters et la modification par des méthodes comme ajouteParticule(), ajouteObstacle(), ajouteSource() et les setters du milieu.

Les classes Dessinable et SupportADessin ont des méthodes virtuelles.

Dans la classe TextViewer, l’attribut flot est privé. Dans la classe RaylibRender, l’attribut camera est privé. Cela permet à chaque classe de décider soi-meme comment afficher l'objet (afficher du texte ou en graphique ).


6. Optimisation des interactions entre particules

Pour améliorer les performances de la simulation, nous avons implémenté une grille spatiale permettant d’éviter de calculer les interactions entre toutes les particules du système.

- Triplet
  Structure représentant les coordonnées entières d’une case de la grille spatiale. Elle est utilisée comme clé dans une table associative.

- Grille
   Classe qui découpe l’espace en cases de taille fixe. Chaque case contient la liste des particules présentes dans cette zone de l’espace. Les cases sont stockées dans un tableau tridimensionnel, ce qui permet d’accéder directement à une case à partir de ses indices.

La classe Grille fournit des méthodes permettant 
- de déterminer dans quelle case se trouve une particule 
- d’ajouter une particule dans la bonne case 
- de reconstruire la grille à partir des positions actuelles des particules 
- de récupérer les particules situées dans les cases voisines d’une particule donnée

La méthode Systeme::evolue() a été modifiée pour utiliser cette grille. Au lieu de parcourir toutes les particules du système pour calculer les interactions, une particule n’interagit mtn qu’avec les particules contenues dans sa case et dans les cases voisines directes.

Cette méthode permet de réduire la complexité du calcul des interactions de O(N²) à O(N) (hypothèse que les particules sont suffisamment bien réparties dans l’espace)