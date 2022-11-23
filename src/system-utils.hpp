#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <map>

struct BC;

struct flux;

std::map<int, float> Boundaries(System sys, int position, BC* BC);

float CalculateFluxes(System system, int r, int c, int dir);
#endif