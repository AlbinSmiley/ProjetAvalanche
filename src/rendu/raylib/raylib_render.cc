#include "raylib_render.h"
#include "Dalle.h"
#include "Particule.h"
#include "ParticuleNeige.h"
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

void dessineAxes(float l) {
  Vector3 origine = {0.0f, 0.0f, 0.0f};

  float r = 0.12f; // rayon de la base du cône
  float h = 0.3f;  // hauteur du cône

  // dessin de Ox
  DrawLine3D(origine, {l, 0.0f, 0.0f}, RED);
  DrawCylinderEx({l, 0.0f, 0.0f}, {l + h, 0.0f, 0.0f}, r, 0.0f, 8, RED);

  // dessin de Oy
  DrawLine3D(origine, {0.0f, l, 0.0f}, BLUE);
  DrawCylinderEx({0.0f, l, 0.0f}, {0.0f, l + h, 0.0f}, r, 0.0f, 8, BLUE);

  // dessin de Oz
  DrawLine3D(origine, {0.0f, 0.0f, l}, GREEN);
  DrawCylinderEx({0.0f, 0.0f, l}, {0.0f, 0.0f, l + h}, r, 0.0f, 8, GREEN);
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
  InitWindow(MIN_WINDOW_LARGEUR + PANEL_WIDTH, MIN_WINDOW_HAUTEUR,
             "Visualisation graphique");

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
    sys.set_dt(dt * vitesse_sim / 100.0);

    if (IsKeyPressed(KEY_L)) {
      deplacement = !deplacement;
    }

    if (deplacement) {
      UpdateCamera(&camera, CAMERA_FREE);
    }

    if (IsKeyPressed(KEY_P)) {
      lecture = !lecture;
    }

    if (lecture && !fenetre_ajout) {
      if (rk4) {
        sys.rk4_On();
      } else {
        sys.rk4_Off();
      }
      sys.evolue();
    }

    BeginScissorMode(PANEL_WIDTH, 0, MIN_WINDOW_LARGEUR, MIN_WINDOW_HAUTEUR);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    DrawGrid(200, 0.5f);
    dessineAxes(3.0f);
    sys.dessine_sur(*this);

    EndMode3D();
    EndScissorMode();

    dessinePanel(sys);

    EndDrawing();
  }
}

// fonction qui donne la couleur en fonction de la taille de la particule
Color couleurParLeRayon(double rayon) {
  rayon = (float)rayon;
  float hue = 360.0f * (4 * rayon * rayon) / (1 + 4 * rayon * rayon);
  Color c = ColorFromHSV(hue, 1.0f, 1.0f);
  return c;
}

// fonction qui dessine un vecteur en 3d, lambda représente la contraction de la
// longueur
// void DrawVector(Vecteur3D position, Vecteur3D direction, double lambda = 1) {
//   Vector3 startPosRaylib = toRaylib(position);
//   Vector3 endPosRaylib = toRaylib(position + lambda * direction);
//
//   double arrowLen = lambda * direction.norme();
//   if (arrowLen < cst::PRECISION) return;
//
//   float h = (float)(0.25 * arrowLen); // tête = 25% de la longueur de la
//   flèche float r = 0.4f * h;                 // rayon proportionnel à la
//   hauteur
//
//   // position de la base du cone à dessiner
//   Vecteur3D posBaseCone = position + lambda * direction - h * (~direction);
//   Vector3 posBaseConeRaylib = toRaylib(posBaseCone);
//
//   DrawLine3D(startPosRaylib, endPosRaylib, GRAY);
//   DrawCylinderEx(posBaseConeRaylib, endPosRaylib, r, 0.0f, 8, GRAY);
// }

void RaylibRender::dessine(Particule const &part) {
  float rayon = (float)part.get_rayon();
  Vector3 pos = toRaylib(part.get_position());

  Color c = couleurParLeRayon(rayon);

  DrawSphere(pos, rayon, c);
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

void RaylibRender::dessinePanel(Systeme &sys) {
  DrawRectangle(0, 0, PANEL_WIDTH, MIN_WINDOW_HAUTEUR, LIGHTGRAY);
  DrawLine(PANEL_WIDTH, 0, PANEL_WIDTH, MIN_WINDOW_HAUTEUR, GRAY);

  GuiGroupBox({5, 5, 190, 100}, "Etat");
  DrawText(TextFormat("Particules : %d", (int)sys.getParticules().size()), 15,
           25, 18, BLACK);
  DrawText(TextFormat("Obstacles  : %d", (int)sys.getObstacles().size()), 15,
           50, 18, BLACK);
  DrawText(TextFormat("Sources    : %d", (int)sys.getSources().size()), 15, 75,
           18, BLACK);

  GuiGroupBox({5, 115, 190, 100}, "Ajouter");

  if (GuiButton({15, 135, 170, 30}, "Particule")) {
    fenetre_ajout = true;
    ajout_particule = true;
  }

  if (GuiButton({15, 160, 170, 30}, "Plan")) {
    fenetre_ajout = true;
    ajout_plan = true;
  }
  // on dit ce qui se passe lorsque on entre souhaite entrer une nouvelle
  // particule
  if (fenetre_ajout && ajout_particule) {
    fenetreParticule(sys);
  }
  if (fenetre_ajout && ajout_plan) {
    fenetrePlan(sys);
  }

  GuiGroupBox({5, 225, 190, 200}, "Simulation");
  GuiToggle({15, 245, 170, 30}, lecture ? "Stop" : "Play", &lecture);
  GuiToggle({15, 270, 170, 30}, deplacement ? "Bouger" : "S'arrêter",
            &deplacement);
  GuiToggle({15, 295, 170, 30}, rk4 ? "utiliser euler" : "utiliser rk4", &rk4);
  DrawText(TextFormat("Vitesse : %.1fx", vitesse_sim), 15, 328, 16, BLACK);
  GuiSlider({15, 347, 170, 20}, "0.1x", "5x", &vitesse_sim, 0.1f, 5.0f);
}

void RaylibRender::fenetreParticule(Systeme &sys) {
  DrawRectangle(0, 0, MIN_WINDOW_LARGEUR + PANEL_WIDTH, MIN_WINDOW_HAUTEUR,
                Fade(BLACK, 0.4f));

  Rectangle fenetre = {300, 200, 400, 420};
  if (GuiWindowBox(fenetre, "Nouvelle particule")) {
    fenetre_ajout = false;
    ajout_particule = false;
  }

  int lx = 320;
  int fx = 460;
  int fw = 220;
  int y = 240;

  // Position des label et des entrer
  GuiLabel({(float)lx, (float)y, 100, 25}, "Position x");
  GuiLabel({(float)lx, (float)(y + 30), 100, 25}, "Position y");
  GuiLabel({(float)lx, (float)(y + 60), 100, 25}, "Position z");
  if (GuiTextBox({(float)fx, (float)y, (float)fw, 25}, buf_px, 16, edit_px))
    edit_px = !edit_px;
  if (GuiTextBox({(float)fx, (float)(y + 30), (float)fw, 25}, buf_py, 16,
                 edit_py))
    edit_py = !edit_py;
  if (GuiTextBox({(float)fx, (float)(y + 60), (float)fw, 25}, buf_pz, 16,
                 edit_pz))
    edit_pz = !edit_pz;

  // vitesse
  y += 105;
  GuiLabel({(float)lx, (float)y, 100, 25}, "Vitesse x");
  GuiLabel({(float)lx, (float)(y + 30), 100, 25}, "Vitesse y");
  GuiLabel({(float)lx, (float)(y + 60), 100, 25}, "Vitesse z");
  if (GuiTextBox({(float)fx, (float)y, (float)fw, 25}, buf_vx, 16, edit_vx))
    edit_vx = !edit_vx;
  if (GuiTextBox({(float)fx, (float)(y + 30), (float)fw, 25}, buf_vy, 16,
                 edit_vy))
    edit_vy = !edit_vy;
  if (GuiTextBox({(float)fx, (float)(y + 60), (float)fw, 25}, buf_vz, 16,
                 edit_vz))
    edit_vz = !edit_vz;

  // rayon
  y += 105;
  GuiLabel({(float)lx, (float)y, 100, 25}, "Rayon");
  if (GuiTextBox({(float)fx, (float)y, (float)fw, 25}, buf_r, 16, edit_r))
    edit_r = !edit_r;

  // boutons
  y += 50;
  if (GuiButton({(float)lx, (float)y, 120, 30}, "Confirmer")) {
    sys.ajouteParticule(new ParticuleNeige(
        Vecteur3D(atof(buf_px), atof(buf_py), atof(buf_pz)),
        Vecteur3D(atof(buf_vx), atof(buf_vy), atof(buf_vz)), atof(buf_r)));
    fenetre_ajout = false;
    ajout_particule = false;
  }
  if (GuiButton({(float)lx + 140, (float)y, 120, 30}, "Annuler")) {
    fenetre_ajout = false;
    ajout_particule = false;
  }
}

void RaylibRender::fenetrePlan(Systeme &sys) {
  DrawRectangle(0, 0, MIN_WINDOW_LARGEUR + PANEL_WIDTH, MIN_WINDOW_HAUTEUR,
                Fade(BLACK, 0.4f));

  Rectangle fenetre = {300, 200, 400, 420};
  if (GuiWindowBox(fenetre, "Nouvel plan")) {
    fenetre_ajout = false;
    ajout_plan = false;
  }

  int lx = 320;
  int fx = 460;
  int fw = 220;
  int y = 240;

  // Position des label et des entrer
  GuiLabel({(float)lx, (float)y, 100, 25}, "Position x");
  GuiLabel({(float)lx, (float)(y + 30), 100, 25}, "Position y");
  GuiLabel({(float)lx, (float)(y + 60), 100, 25}, "Position z");
  if (GuiTextBox({(float)fx, (float)y, (float)fw, 25}, buf_px, 16, edit_px))
    edit_px = !edit_px;
  if (GuiTextBox({(float)fx, (float)(y + 30), (float)fw, 25}, buf_py, 16,
                 edit_py))
    edit_py = !edit_py;
  if (GuiTextBox({(float)fx, (float)(y + 60), (float)fw, 25}, buf_pz, 16,
                 edit_pz))
    edit_pz = !edit_pz;

  // // vitesse
  y += 105;
  GuiLabel({(float)lx, (float)y, 100, 25}, "Normale x");
  GuiLabel({(float)lx, (float)(y + 30), 100, 25}, "Normale y");
  GuiLabel({(float)lx, (float)(y + 60), 100, 25}, "Normale z");
  if (GuiTextBox({(float)fx, (float)y, (float)fw, 25}, buf_vx, 16, edit_vx))
    edit_vx = !edit_vx;
  if (GuiTextBox({(float)fx, (float)(y + 30), (float)fw, 25}, buf_vy, 16,
                 edit_vy))
    edit_vy = !edit_vy;
  if (GuiTextBox({(float)fx, (float)(y + 60), (float)fw, 25}, buf_vz, 16,
                 edit_vz))
    edit_vz = !edit_vz;

  y += 50;
  if (GuiButton({(float)lx, (float)y, 120, 30}, "Confirmer")) {
    sys.ajouteObstacle(
        new Plan(Vecteur3D(atof(buf_px), atof(buf_py), atof(buf_pz)),
                 Vecteur3D(atof(buf_vx), atof(buf_vy), atof(buf_vz))));
    fenetre_ajout = false;
    ajout_plan = false;
  }
  if (GuiButton({(float)lx + 140, (float)y, 120, 30}, "Annuler")) {
    fenetre_ajout = false;
    ajout_plan = false;
  }
}
