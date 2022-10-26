#ifndef SYSTEM_H
#define SYSTEM_H

#include "system-utils.hpp"

#include <vector>

class System {
public:
    virtual ~System();
    System();
    System(BC* BC) : boundaries(BC) {};
    System(float* sys, BC* BC) : system(sys) , boundaries(BC) {};
    struct flux GetFluxes();
    float* system;
    BC* boundaries;
};


class SystemT : public System {
public:
    ~SystemT();
    SystemT();
    SystemT(BC* BC, float Dt) {
        boundaries = BC;
        dt = Dt;
    }
    SystemT(float* sys, BC* BC, float Dt) {
        system = sys;
        boundaries = BC;
        dt = Dt;
    }
    float dt;
};


class SystemND : public System {
    ~SystemND();
    SystemND();
    SystemND(BC* BC) {
        boundaries = BC;
    } 
    SystemND(float* sys, BC* BC) {
        system = sys;
        boundaries = BC;
    } 
};

class SystemNDT : public System {
    
};


#endif