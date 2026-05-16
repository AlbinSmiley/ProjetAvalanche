#include "raylib_render.h"
#include "Dalle.h"
#include "Particule.h"
#include "Vecteur3D.h"
#include "constantes.h"
#include "raylib.h"
#include <rlgl.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

Vector3 toRaylib(Vecteur3D const &vec) {
  return {(float)vec.get_x(), (float)vec.get_z(), (float)vec.get_y()};
}

void dessineAxes(float longueur) {
  Vector3 origine = {0.0f, 0.0f, 0.0f};
  DrawLine3D(origine, {longueur, 0.0f, 0.0f}, RED);
  DrawSphere({longueur, 0.0f, 0.0f}, 0.1f, RED);

  DrawLine3D(origine, {0.0f, longueur, 0.0f}, BLUE);
  DrawSphere({0.0f, longueur, 0.0f}, 0.1f, BLUE);

  DrawLine3D(origine, {0.0f, 0.0f, longueur}, GREEN);
  DrawSphere({0.0f, 0.0f, longueur}, 0.1f, GREEN);
}

void dessinePlan(Vecteur3D const &n, Vecteur3D const &pos, float longueur,
                 float largeur, Color couleur) {

  Vecteur3D e_ref = (abs(n.get_x()) < cst::PRECISION) ? Vecteur3D(1, 0, 0)
                                                      : Vecteur3D(0, 1, 0);

  Vecteur3D u = (e_ref ^ n);
  Vecteur3D v = (u ^ n);
  u = ~u;
  v = ~v;

  Vecteur3D OA = pos + longueur * u + largeur * v;
  Vecteur3D OB = pos + longueur * u - largeur * v;
  Vecteur3D OC = pos - longueur * u - largeur * v;
  Vecteur3D OD = pos - longueur * u + largeur * v;

  // on dessine deux triangles collés qui forme un plan
  DrawTriangle3D(toRaylib(OA), toRaylib(OB), toRaylib(OD), couleur);
  DrawTriangle3D(toRaylib(OD), toRaylib(OB), toRaylib(OC), couleur);

  // il faut également dessiner la face arrière
  DrawTriangle3D(toRaylib(OD), toRaylib(OB), toRaylib(OA), couleur);
  DrawTriangle3D(toRaylib(OC), toRaylib(OB), toRaylib(OD), couleur);
}

void dessineDalle(Vecteur3D const &n, Vecteur3D const &pos,
                  Vecteur3D const &e_L, Vecteur3D const &e_l, float longueur,
                  float largeur, Color couleur) {

  Vecteur3D OA = pos;
  Vecteur3D OB = pos + longueur * e_L;
  Vecteur3D OC = pos + longueur * e_L + largeur * e_l;
  Vecteur3D OD = pos + largeur * e_l;

  // on dessine deux triangles collés qui forme un plan
  DrawTriangle3D(toRaylib(OA), toRaylib(OB), toRaylib(OD), couleur);
  DrawTriangle3D(toRaylib(OD), toRaylib(OB), toRaylib(OC), couleur);

  // il faut également dessiner la face arrière
  DrawTriangle3D(toRaylib(OD), toRaylib(OB), toRaylib(OA), couleur);
  DrawTriangle3D(toRaylib(OC), toRaylib(OB), toRaylib(OD), couleur);
}

RaylibRender::RaylibRender() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(800, 600, "Visualisation graphique");

  camera.position = {10.0f, 10.0f, 10.0f};
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  SetTargetFPS(60);
}

RaylibRender::~RaylibRender() { CloseWindow(); }

void RaylibRender::run(Systeme &sys) {
  while (!WindowShouldClose()) {

    const auto dt = GetFrameTime();
    sys.set_dt(dt / 100.0);

    if (IsKeyPressed(KEY_L)) {
      deplacement = !deplacement;
    }

    if (deplacement) {
      UpdateCamera(&camera, CAMERA_FREE);
    }

    if (IsKeyPressed(KEY_P)) {
      lecture = !lecture;
    }

    if (lecture) {
      sys.evolue();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    DrawGrid(200, 0.5f);
    dessineAxes(3.0f);
    sys.dessine_sur(*this);

    EndMode3D();

    DrawText("Pause : P", 5, 5, 20, BLACK);
    DrawText("X", 5, 40, 20, RED);
    DrawText("Y", 25, 40, 20, GREEN);
    DrawText("Z", 45, 40, 20, BLUE);

    EndDrawing();
  }
}

void RaylibRender::dessine(Particule const &part) {
  double rayon = part.get_rayon();

  Vector3 positionParticule = toRaylib(part.get_position());
  DrawSphere(positionParticule, (float)rayon, LIME);
}

void RaylibRender::dessine(Plan const &plan) {
  Vecteur3D cameraPos(camera.position.x, camera.position.z, camera.position.y);
  float dist = (float)(cameraPos - plan.getPosition()).norme();
  float taille = dist * 3.0f;

  dessinePlan(plan.getNormale(), plan.getPosition(), taille, taille,
              Fade(DARKGRAY, 0.25f));
}

void RaylibRender::dessine(Dalle const &dalle) {
  dessineDalle(dalle.getNormale(), dalle.getPosition(),
               dalle.getDirectionLongueur(), dalle.getDirectionLargeur(),
               (float)dalle.getLongueur(), (float)dalle.getLargeur(),
               Fade(DARKGRAY, 0.25f));
}

void RaylibRender::dessine(Systeme const &sys) {
  for (auto part : sys.getParticules()) {
    part->dessine_sur(*this);
  }
  for (auto obst : sys.getObstacles()) {
    obst->dessine_sur(*this);
  }
}
