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
std::vector<flux> SystemND::Boundaries( int position) {
    std::vector<flux> result;

    if(position % distro->Width() == 0) {
        result.push_back({true, position - 1, Dy * boundaries[0].h}); // left
    } else {
        result.push_back({false, position - 1, Dy * k / Dx}); // left
    }

    if((position + 1) % distro->Width() == 0) {
        result.push_back({true, position + 1, Dy * boundaries[1].h}); // right
    } else {
        result.push_back({false, position + 1, Dy * k / Dx}); // right
    }

    if(position - distro->Width() < 0) {
        result.push_back({true, position - distro->Width(), Dx * boundaries[2].h}); // up
    } else {
        result.push_back({false, position - distro->Width(), Dx * k / Dy}); // up
    }

    if(position + distro->Width() >= distro->Height() * distro->Width()) {
        result.push_back({true, position + distro->Width(), Dx * boundaries[3].h}); // down
    } else {
        result.push_back({false, position + distro->Width(), Dx * k / Dy}); // down
    }

    if(N > 1) {
        if((position + 1) % distro->Width() == 0 || position % distro->Width() == 0) {
            result.at(2).fluxMult = result.at(2).fluxMult / 2;
            result.at(3).fluxMult = result.at(3).fluxMult / 2;
        }

        if(position - distro->Width() < 0 || position + distro->Width() >= distro->Height() * distro->Width()) {
            result.at(0).fluxMult = result.at(0).fluxMult / 2;
            result.at(1).fluxMult = result.at(1).fluxMult / 2;
        }
    }

    return result;
}

float* SystemND::CalculateFluxes(int position, int size, int &solution) {
    std::vector<flux> fluxes = Boundaries(position);
    float *row = (float *) malloc(sizeof(float) * size);
    for(int i = 0; i < size; i++) {
        row[i] = 0;
    }
    for(int i = 0; i < 4; i++) {
        struct flux f = fluxes.at(i);
        row[position] -= f.fluxMult;
        if(!f.isBC) {
            row[f.position] = f.fluxMult;
        } else {
            solution -= f.fluxMult * boundaries[i].temperature;
        }
    }
    return row;
}
