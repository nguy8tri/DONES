#include "system-utils.hpp"
#include "system.hpp"

#include <map>
#include <cassert>

struct BC {
    float h;
    int temperature;
};

struct flux {
    bool isBC;
    int position;
    float fluxMult;
};

// We will handle const temp condition later
std::vector<struct flux> Boundaries(System sys, int position) {
    std::vector<struct flux> result;

    if(position - sys.system->Width() > 0) {
        result.push_back({true, position - sys.system->Width(), sys.Dx * sys.boundaries[0].h}); // up
    } else {
        result.push_back({false, position - sys.system->Width(), sys.k / sys.Dy}); // up
    }

    if(position + sys.system->Width() >= sys.system->Height() * sys.system->Width()) {
        result.push_back({true, position + sys.system->Width(), sys.Dx * sys.boundaries[1].h}); // down
    } else {
        result.push_back({false, position + sys.system->Width(), sys.k / sys.Dy}); // down
    }

    if(position % sys.system->Width() == 0) {
        result.push_back({true, position - 1, sys.Dy * sys.boundaries[2].h}); // left
    } else {
        result.push_back({false, position - 1, sys.Dy * sys.k / sys.Dx}); // left
    }

    if((position + 1) % sys.system->Width() == 0) {
        result.push_back({true, position + 1, sys.Dy * sys.boundaries[3].h}); // right
    } else {
        result.push_back({false, position + 1, sys.Dy * sys.k / sys.Dx}); // right
    }

    if(position + sys.system->Width() >= sys.system->Height() * sys.system->Width() || position % sys.system->Width() == 0) {
        result.at(0).fluxMult = result.at(0).fluxMult / 2;
        result.at(1).fluxMult = result.at(1).fluxMult / 2;
    }

    if(position % sys.system->Width() == 0 || (position + 1) % sys.system->Width() == 0) {
        result.at(2).fluxMult = result.at(2).fluxMult / 2;
        result.at(3).fluxMult = result.at(3).fluxMult / 2;
    }

    return result;
}

float* calculateFluxes(System system, int position, int size) {
    std::vector<struct flux> fluxes = Boundaries(system, position);
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
}
