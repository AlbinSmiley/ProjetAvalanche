# PROGRESSION

<!-- Format : [fait/à faire] TACHE Durée (en minutes; remplacer les ??) -->

Vous pouvez ajouter vos propres tâches si vous le jugez utile
(p.ex. décomposition plus fine).

- [X] créer le JOURNAL      1
- [X] lire complètement le descriptif général   15
- [X] s'inscrire en binôme     0
- [X] fusionner les deux projets (y compris les fichiers JOURNAL) ??
- [X] Makefile                                                ??
- [X] Vecteur finis (pleinement opérationnels et testés)   ??
- [ ] fichier REPONSES                                          ??
- [X] Particules simples                                          ??
- [X] Obstacles                                            ??
- [ ] Dessinable + SupportADessin                                 ??
- [X] System                                                 ??
- [ ] exerciceP9 (simulation textuelle)                          ??
- [ ] Graphisme : cadre général (reprise des exemples tuto)     ??
- [ ] Graphisme : adaptation Ã  ce projet spécifique            ??
- [ ] Particules diverses                                         ??
- [ ] Amélioration du modèle                                      ??
- [ ] Meilleurs voisinages                                      ??
- [ ] fichier CONCEPTION                                          ??
- [ ] fichier README                                         ??
- [ ] fichier NOMS                                         ??
- [ ] rendu !                                              ??

======================================================================

# A FAIRE (PROCHAINE ETAPE)

Mettez ici ce que vous pensez devoir étre la ou les 2 prochaines étapes
pour chacun. Par exemple :

1. Faire en sorte d'éviter l'utilisation de getters (voir même totallement arrêter dans utiliser).

======================================================================

# SUIVI

## Semaine 2Â

Nous avons créé la classe Vecteur 3D en introduisant déjà les différents fichiers et le makefile.
Temps passé : 300 min

--------------------------------------------------

## Semaine 3Â

Nous avons modifier l'architecture du projet pour une meilleur lisibilité.

Temps passé : 30 min

--------------------------------------------------

## Semaine 4Â

Cette semaine nous avons améliorer la classe Vecteur3D en mettant en place des constructeurs, des méthodes et des surcharges d'opérateurs.

Nous avons également commencé a concevoir la classe Particule.

Temps passé : 240 min

--------------------------------------------------

## Semaine 5Â

Semaine du XX mars 2026

Cette semaine, j’ai implémenté la gestion des obstacles.

J’ai introduit une classe Obstacle représentant un objet géométrique fixe, défini par une position. J’ai ensuite implémenté la classe Plan (héritée de Obstacle), caractérisée par une normale unitaire, ainsi que la méthode PointPlusProche permettant de projeter un point sur le plan.

J’ai ajouté une interaction entre une particule et un obstacle en implémentant la méthode ajouteForce(Plan) dans la classe Particule, basée sur un modèle de type Lennard-Jones.

J’ai également créé la classe Dalle (héritée de Plan), qui représente une portion rectangulaire de plan, en ajoutant une longueur, une largeur et une direction unitaire.

Difficultés rencontrées : compréhension de l’héritage, gestion des erreurs de compilation et interprétation géométrique des projections.

Temps passé : 280 (fab) + 67 (albin) min

--------------------------------------------------

## Semaine 6Â

Semaine 6

- Mise en place de l’architecture d’affichage avec les classes Dessinable et SupportADessin pour séparer la simulation de la visualisation.
- Implémentation de la classe TextViewer permettant un affichage texte des objets du système.
- Modification des classes Particule, Obstacle, Plan, Dalle et Source pour les rendre dessinables via la méthode dessine_sur().
- Création de la classe Systeme contenant les particules, obstacles et sources. Ajout des méthodes d’ajout, des accesseurs et de l’opérateur << pour afficher le système complet.
- Mise en place de la simulation en mode text avec la class TextViewer. Un problème dont on ne savait pas l'origine à représenté des terreurs noctures pour Albin, le problème : une erreur de signe dans l'une des methodes ...
- Mise en place de fonctions et méthodes tierces qui on permit d'entrer les données dans des fichiers .txt. (Suivit d'une briève utilisation d'un minuscule programme python pour visualiser graphiquement les données et vérifier qu'elle faisait du sens)

Temps passé : 300 (fab) + 420 (albin) min

--------------------------------------------------

## Semaine 7Â

Dilemme interne quant au fait de vouloir utiliser OpenGL pour les graphisme (car Albin voyait dans les taches de cette semaine l'opportunité d'apprendre un nouvel outil), suivit d'un RAPIDE rappel à l'ordre après confrontation au concept de shaders...

Apprentissage de raylib en suivant le tuto du cours.

Mise en place des graphismes avec la class RaylibRender. Mise en place de la logique de l'implémentation des méthodes `dessine`. Ajout d'option graphique (boutons, état du système, ajout de particule et de plan, etc ...).

Absence de compréhension des consignes de la semaine ... suivit du choix personnel de la structure du projet avec les graphismes (la structure du projet était déjà pas mal alors on a opté pour juste ajouter un dossier `src/rendu` pour la représentation graphique/textuelle).

Temps passé : 480 min

--------------------------------------------------

## Semaine 8Â

Temps passé :  min

--------------------------------------------------

## Semaine 9Â

Temps passé :  min

--------------------------------------------------

## Semaine 10Â

Temps passé :  min

--------------------------------------------------

## Semaine 11Â
Cette semaine, j’ai implémenté une optimisation du calcul des interactions entre particules en utilisant une grille spatiale.(P12)

J’ai introduit une structure Triplet qui représentent les coordonnées entières des cases de la grille, ainsi qu’une classe Grille permettant de découper l’espace en cases de taille fixe.

J’ai ensuite modifié la méthode Systeme::evolue() pour qu'une particule interagisse uniquement avec les particules présentes dans sa case et dans les cases voisines directes.

Cela permet de réduire la complexité du calcul des interactions de O(N²) à O(N) (hypothèse que les particules sont suffisamment bien réparties dans l’espace)

Difficultés rencontrées : compréhension de l'énoncé et organisation des nouvelles classes dans l’architecture du projet.

Temps passé :  3h(fab) + (...) albin min

--------------------------------------------------

## Semaine 12Â
Cette semaine, j’ai implémenté une nouvelle optimisation du calcul des interactions entre particules en utilisant une table associative std::map (P13).
J'ai mis à jour la classe grille,Triplet et Syytème afin que notre code soit optimisé comme demandé dans l'exercice P13. 
j'ai aussi fait la classe ParticuleRoche car nous l'avions un peu laissé de cote 

Temps passé : 200 (fab) min + (albin) min

--------------------------------------------------

## Semaine 13Â

Temps passé :  min

--------------------------------------------------

## Semaine 14Â

Temps passé :  min
