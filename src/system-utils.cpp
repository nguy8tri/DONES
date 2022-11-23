#include "system-utils.hpp"
#include "system.hpp"

#include <vector>
#include <cassert>


// We will handle const temp condition later
std::vector<flux> Boundaries(System system, int position) {
    std::vector<flux> result;

    if(position - system.system->Width() > 0) {
        result.push_back({true, position - system.system->Width(), system.Dx * system.boundaries[0].h}); // up
    } else {
        result.push_back({false, position - system.system->Width(), system.k / system.Dy}); // up
    }

    if(position + system.system->Width() >= system.system->Height() * system.system->Width()) {
        result.push_back({true, position + system.system->Width(), system.Dx * system.boundaries[1].h}); // down
    } else {
        result.push_back({false, position + system.system->Width(), system.k / system.Dy}); // down
    }

    if(position % system.system->Width() == 0) {
        result.push_back({true, position - 1, system.Dy * system.boundaries[2].h}); // left
    } else {
        result.push_back({false, position - 1, system.Dy * system.k / system.Dx}); // left
    }

    if((position + 1) % system.system->Width() == 0) {
        result.push_back({true, position + 1, system.Dy * system.boundaries[3].h}); // right
    } else {
        result.push_back({false, position + 1, system.Dy * system.k / system.Dx}); // right
    }

    if(position + system.system->Width() >= system.system->Height() * system.system->Width() || position % system.system->Width() == 0) {
        result.at(0).fluxMult = result.at(0).fluxMult / 2;
        result.at(1).fluxMult = result.at(1).fluxMult / 2;
    }

    if(position % system.system->Width() == 0 || (position + 1) % system.system->Width() == 0) {
        result.at(2).fluxMult = result.at(2).fluxMult / 2;
        result.at(3).fluxMult = result.at(3).fluxMult / 2;
    }

    return result;
}

float* calculateFluxes(System system, int position, int size) {
    std::vector<flux> fluxes = Boundaries(system, position);
    float row[size];
    for(int i = 0; i < sizeof(fluxes); i++) {
        struct flux f = fluxes.at(i);
        row[position] -= f.fluxMult;
        if(!f.isBC) {
            row[f.position] = f.fluxMult;
        } else {
            row[size - 1] -= f.fluxMult * system.boundaries[i].temperature;
        }
    }
    return row;
}
