void Systeme::evolueRK4() {
  size_t n = particules.size();

  std::vector<Vecteur3D> p0(n);
  std::vector<Vecteur3D> v0(n);

  // rempli les valeurs initiales pour chaques particules
  for (size_t i = 0; i < n; i++) {
    p0[i] = particules[i]->get_position();
    v0[i] = particules[i]->get_vitesse();
  }

  // array de 4 vector représentant les quatres points de rk4 pour chaque
  // particules
  std::vector<Vecteur3D> kp[4];
  std::vector<Vecteur3D> kv[4];

  double coeff[] = {0.0, 0.5, 0.5, 1.0}; // offset pour chaque sous-pas

  for (int s = 0; s < 4; s++) {

    if (s > 0) {
      for (size_t i = 0; i < n; i++) {
        particules[i]->setPosition(p0[i] + kp[s - 1][i] * coeff[s]);
        particules[i]->setVitesse(v0[i] + kv[s - 1][i] * coeff[s]);
      }
    }

    calculerForces();

    kp[s].resize(n);
    kv[s].resize(n);

    for (size_t i = 0; i < n; i++) {
      kp[s][i] = particules[i]->get_vitesse() * dt;
      kv[s][i] = particules[i]->get_force() * (dt / particules[i]->get_masse());
    }
  }

  for (size_t i = 0; i < n; i++) {
    particules[i]->setPosition(
        p0[i] +
        (kp[0][i] + kp[1][i] * 2.0 + kp[2][i] * 2.0 + kp[3][i]) * (1.0 / 6.0));
    particules[i]->setVitesse(
        v0[i] +
        (kv[0][i] + kv[1][i] * 2.0 + kv[2][i] * 2.0 + kv[3][i]) * (1.0 / 6.0));
  }
}
