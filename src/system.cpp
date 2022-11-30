#include "system.hpp"

#include <vector>
#include <cassert>
#include <map>
#include <iostream>

System::~System() {}

SystemND::~SystemND() {}

int SystemND::GetDimension() {
    return N;
}
// We will handle const temp condition later
std::vector<flux> Boundaries(SystemND system, int position) {
    std::vector<flux> result;

    if(position - system.distro->Width() < 0) {
        result.push_back({true, position - system.distro->Width(), system.Dx * system.boundaries[0].h}); // up
    } else {
        result.push_back({false, position - system.distro->Width(), system.Dx * system.k / system.Dy}); // up
    }

    if(position + system.distro->Width() >= system.distro->Height() * system.distro->Width()) {
        result.push_back({true, position + system.distro->Width(), system.Dx * system.boundaries[1].h}); // down
    } else {
        result.push_back({false, position + system.distro->Width(), system.Dx * system.k / system.Dy}); // down
    }

    if(position % system.distro->Width() == 0) {
        result.push_back({true, position - 1, system.Dy * system.boundaries[2].h}); // left
    } else {
        result.push_back({false, position - 1, system.Dy * system.k / system.Dx}); // left
    }

    if((position + 1) % system.distro->Width() == 0) {
        result.push_back({true, position + 1, system.Dy * system.boundaries[3].h}); // right
    } else {
        result.push_back({false, position + 1, system.Dy * system.k / system.Dx}); // right
    }
    if(system.GetDimension() > 1) {
        if((position + 1) % system.distro->Width() == 0 || position % system.distro->Width() == 0) {
            result.at(0).fluxMult = result.at(0).fluxMult / 2;
            result.at(1).fluxMult = result.at(1).fluxMult / 2;
        }

        if(position - system.distro->Width() < 0 || position + system.distro->Width() >= system.distro->Height() * system.distro->Width()) {
            result.at(2).fluxMult = result.at(2).fluxMult / 2;
            result.at(3).fluxMult = result.at(3).fluxMult / 2;
        }
    }

    return result;
}

float* CalculateFluxes(SystemND system, int position, int size, int &solution) {
    std::vector<flux> fluxes = Boundaries(system, position);
    float *row = (float *) malloc(sizeof(float) * size);
    for(int i = 0; i < 4; i++) {
        struct flux f = fluxes.at(i);
        row[position] -= f.fluxMult;
        if(!f.isBC) {
            row[f.position] = f.fluxMult;
        } else {
            solution -= f.fluxMult * system.boundaries[i].temperature;
        }
    }
    return row;
}
