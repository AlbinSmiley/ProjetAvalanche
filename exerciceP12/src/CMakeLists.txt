add_library(avalanche STATIC
    math/Vecteur3D.cc
    math/Aleatoire.cc
    physique/Source.cc
    physique/Systeme.cc
    physique/obstacles/Obstacle.cc
    physique/obstacles/Plan.cc
    physique/obstacles/Dalle.cc
    physique/particules/Particule.cc
    physique/particules/ParticuleNeige.cc
    physique/particules/ParticuleRoche.cc
    physique/Grille.cc
    rendu/text/TextViewer.cc
    rendu/raylib/raylib_render.cc

)

target_include_directories(avalanche PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/math
    ${CMAKE_CURRENT_SOURCE_DIR}/physique
    ${CMAKE_CURRENT_SOURCE_DIR}/physique/obstacles
    ${CMAKE_CURRENT_SOURCE_DIR}/physique/particules
    ${CMAKE_CURRENT_SOURCE_DIR}/rendu
    ${CMAKE_CURRENT_SOURCE_DIR}/rendu/text
    ${CMAKE_CURRENT_SOURCE_DIR}/rendu/raylib
)

target_link_libraries(avalanche PUBLIC raylib)
