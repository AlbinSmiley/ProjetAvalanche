add_library(avalanche STATIC
    math/Vecteur3D.cc
    math/Aleatoire.cc
    obstacles/Obstacle.cc
    obstacles/Plan.cc
    obstacles/Dalle.cc
    physique/Particule.cc
    physique/Source.cc
    physique/Systeme.cc
    rendu/text/TextViewer.cc
    rendu/raylib/raylib_render.cpp
)

target_include_directories(avalanche PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/math
    ${CMAKE_CURRENT_SOURCE_DIR}/obstacles
    ${CMAKE_CURRENT_SOURCE_DIR}/physique
    ${CMAKE_CURRENT_SOURCE_DIR}/rendu
    ${CMAKE_CURRENT_SOURCE_DIR}/rendu/text
    ${CMAKE_CURRENT_SOURCE_DIR}/rendu/raylib
)

target_link_libraries(avalanche PUBLIC raylib)
