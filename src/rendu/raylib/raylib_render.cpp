
#include "raylib_render.h"
#include "Vecteur3D.h"
#include "particule.h"
#include <rlgl.h>

RaylibRender::RaylibRender() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(800, 600, "Toupie");

  camera.position = {5.0f, 5.0f, 5.0f};
  camera.target = {0.0f, 1.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  SetTargetFPS(60);
}

RaylibRender::~RaylibRender() { CloseWindow(); }

void RaylibRender::run(Systeme &sys) {
  while (!WindowShouldClose()) {

    const auto dt = GetFrameTime();
    sys.set_dt(dt);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    DrawGrid(200, 0.5f);
    sys.dessine_sur(*this);
    sys.evolue();

    EndMode3D();
    EndDrawing();
  }
}

void RaylibRender::dessine(Particule const &part) {
  Vecteur3D vecteurPosition = part.get_position();
  double rayon = part.get_rayon();

  constexpr Vector3 positionParticule = {(float)positionParticule.get_x(),
                                         (float)positionParticule.get_y(),
                                         (float)positionParticule.get_z()};
  DrawSphere(positionParticule, rayon, LIME);
}

void RaylibRender::dessine(Systeme const &sys) {
  for (auto part : sys.getParticules()) {
    dessine(*part);
  }
}
