#pragma once 

#include "Vecteur3D.h"

/* 
    Ici on préfère poser toute les constantes dans un fichier à part pour une meilleur lisibilité et pour que tout soit au même endroit.   

    Il s'agit donc de constantes mathématiques et physique. 
*/

namespace cst {
// precision des calcules d'égalité
inline constexpr double PRECISION = 1e-10; 

// pas temporel
inline constexpr double DT = 0.001 ; // s

// nombre irrationnel
inline constexpr double PI = 3.14159265358979323846264338328 ;
inline constexpr double E  = 2.71828182845904523536028747135 ; // pas forcément nécéssaire mais bon on sait jamais 

// constantes physique 
inline const Vecteur3D G(0.0,0.0,-9.81e3) ; // mm/s²

inline constexpr double RHO_PARTICULE = 1.0 ; // mg/mm³
inline constexpr double RHO_MILIEU = 1.3e-3 ; // mg/mm³

inline constexpr double ETA_MILIEU = 1.3e-2 ; // mg/mm*s

inline constexpr double SIGMA = 0.885 ; // mm
inline constexpr double EPSILON = 25 ; // mg*mm³/s²
}
