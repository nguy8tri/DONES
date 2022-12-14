#ifndef SYSTEM_H
#define SYSTEM_H

#include "matrix.hpp"

#include <vector>

struct BC {
    float h;
    int temperature;
};

struct flux {
    bool isBC;
    int position;
    float fluxMult;
};

class System {
public:
    ~System();
    System();
    System(BC *boundary, float k) : boundaries(boundary) , k(k) {};
    System(Matrix* sys, BC *boundary, float k) : distro(sys) , boundaries(boundary) , k(k) {};
    Matrix* distro;
    BC* boundaries;
    float k;
    float Dx;
    float Dy;
};

class SystemND : public System {
public:
    ~SystemND();
    SystemND();
    SystemND(BC *boundary, float k) : System(boundary, k) {};
    SystemND(Matrix* sys, BC *boundary, float k, int n) : System(sys, boundary, k) {
        N = n;
    }
    int GetDimension();
    float* CalculateFluxes(int position, int size, int &solution);
private:
    std::vector<flux> Boundaries(int position);
    float getFlux(int position, int dir);
    void halfFlux(int position, std::vector<flux> &fluxes);
    int N;
};

/*
class SystemT : public System {
public:
    ~SystemT();
    SystemT();
    SystemT(BC* BC, float Dt, float k) : System(BC, k) {
        dt = Dt;
    }
    SystemT(Matrix* sys, BC* BC, float Dt, float k) : System(sys, BC, k) {
        dt = Dt;
    }
    float dt;
};

class SystemNDT : public System {
    
};
*/


#endif