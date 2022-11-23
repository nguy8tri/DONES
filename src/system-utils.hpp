#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include "system.hpp"

#include <vector>

class System;

struct BC {
    float h;
    int temperature;
};

struct flux {
    bool isBC;
    int position;
    float fluxMult;
};

std::vector<flux> Boundaries(System system, int position);

float CalculateFluxes(System system, int position, int size);
#endif