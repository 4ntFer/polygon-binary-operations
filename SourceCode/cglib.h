#pragma once

#include "Polygon.h"

int left(float p[], float q[], float r[]);
float areaPoligono(Point* vertices[], int len);

int* encontraArestasQueIntersectam(Poligono* g1, Poligono* g2);


Poligono* clipping(Poligono* g1, Poligono* g2);
Poligono* exclusion(Poligono* g1, Poligono* g2);
Poligono** unionn(Poligono* g1, Poligono* g2);
Poligono* nott(Poligono* g1);