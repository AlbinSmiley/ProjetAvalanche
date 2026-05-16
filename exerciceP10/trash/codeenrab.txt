// 1) addition
    // (1.0, 2.0, -0.1) + (2.6, 3.5, 4.1) = (3.6, 5.5, 4.0)
    Vecteur3D s = v1.addition(v2);
    Vecteur3D attendu_s;
    attendu_s.set_coord(0, 3.6);
    attendu_s.set_coord(1, 5.5);
    attendu_s.set_coord(2, 4.0);

    cout << "Test addition: ";
    cout << (s.compare(attendu_s, eps) ? "OK" : "FAIL") << "  ";
    s.affiche(); cout << endl;

    // 2) addition du vecteur nul ne fait rien
    Vecteur3D s0 = v1.addition(v0);
    cout << "Test v1 + 0 = v1: ";
    cout << (s0.compare(v1, eps) ? "OK" : "FAIL") << endl;

    // 3) soustraction
    // (1.0,2.0,-0.1) - (2.6,3.5,4.1) = (-1.6,-1.5,-4.2)
    Vecteur3D d = v1.soustraction(v2);
    Vecteur3D attendu_d;
    attendu_d.set_coord(0, -1.6);
    attendu_d.set_coord(1, -1.5);
    attendu_d.set_coord(2, -4.2);

    cout << "Test soustraction: ";
    cout << (d.compare(attendu_d, eps) ? "OK" : "FAIL") << "  ";
    d.affiche(); cout << endl;

    // 4) v - v = 0
    Vecteur3D dn = v1.soustraction(v1);
    cout << "Test v1 - v1 = 0: ";
    cout << (dn.compare(v0, eps) ? "OK" : "FAIL") << endl;

    // 5) oppose
    // oppose de (1.0,2.0,-0.1) = (-1.0,-2.0,0.1)
    Vecteur3D op = v1.oppose();
    Vecteur3D attendu_op;
    attendu_op.set_coord(0, -1.0);
    attendu_op.set_coord(1, -2.0);
    attendu_op.set_coord(2, 0.1);

    cout << "Test oppose: ";
    cout << (op.compare(attendu_op, eps) ? "OK" : "FAIL") << "  ";
    op.affiche(); cout << endl;

    // 6) v + (-w) = v - w
    Vecteur3D a1 = v1.addition(v2.oppose());
    Vecteur3D a2 = v1.soustraction(v2);

    cout << "Test v1 + (-v2) = v1 - v2: ";
    cout << (a1.compare(a2, eps) ? "OK" : "FAIL") << endl;

    // 7) mult scalaire
    // 3*(1.0,2.0,-0.1) = (3.0,6.0,-0.3)
    Vecteur3D m = v1.mult(3.0);
    Vecteur3D attendu_m;
    attendu_m.set_coord(0, 3.0);
    attendu_m.set_coord(1, 6.0);
    attendu_m.set_coord(2, -0.3);

    cout << "Test mult scalaire: ";
    cout << (m.compare(attendu_m, eps) ? "OK" : "FAIL") << "  ";
    m.affiche(); cout << endl;

    // 8) produit scalaire
    // (1.0,2.0,-0.1) * (2.6,3.5,4.1) = 9.19
    double ps = v1.prod_scal(v2);
    cout << "Test prod scal = 9.19: ";
    cout << (std::abs(ps - 9.19) < eps ? "OK" : "FAIL") << "  (" << ps << ")" << endl;

    // 9) produit vectoriel
    // (1.0,2.0,-0.1) ^ (2.6,3.5,4.1) = (8.55, -4.36, -1.7)
    Vecteur3D pv = v1.prod_vect(v2);
    Vecteur3D attendu_pv;
    attendu_pv.set_coord(0, 8.55);
    attendu_pv.set_coord(1, -4.36);
    attendu_pv.set_coord(2, -1.7);

    cout << "Test prod vect: ";
    cout << (pv.compare(attendu_pv, 1e-9) ? "OK" : "FAIL") << "  ";
    pv.affiche(); cout << endl;

    // 10) norme2 v1 = 5.01
    double n1 = v1.norme2();
    cout << "Test ||v1||^2 = 5.01: ";
    cout << (std::abs(n1 - 5.01) < eps ? "OK" : "FAIL") << "  (" << n1 << ")" << endl;

    // 11) norme2 v2 = 35.82
    double n2 = v2.norme2();
    cout << "Test ||v2||^2 = 35.82: ";
    cout << (std::abs(n2 - 35.82) < eps ? "OK" : "FAIL") << "  (" << n2 << ")" << endl;








    return 0;
}