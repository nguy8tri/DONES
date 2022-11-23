#ifndef SYSTEM_H
#define SYSTEM_H

#include "system-utils.hpp"
#include "matrix.hpp"

#include <vector>

struct BC;


class System {
public:
    ~System();
    System();
    System(BC *boundary, float k) : boundaries(boundary) , k(k) {};
    System(Matrix* sys, BC *boundary, float k) : system(sys) , boundaries(boundary) , k(k) {};
    Matrix* system;
    BC* boundaries;
    float k;
    float Dx;
    float Dy;
};

class SystemND : public System {
    ~SystemND();
    SystemND();
    SystemND(BC *boundary, float k) : System(boundary, k) {};
    SystemND(Matrix* sys, BC *boundary, float k) : System(sys, boundary, k) {
        N = sys->Height();
    }

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