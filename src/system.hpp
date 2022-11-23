#ifndef SYSTEM_H
#define SYSTEM_H

#include "system-utils.hpp"
#include "matrix.hpp"

#include <vector>

class System {
public:
    virtual ~System();
    System();
    System(BC* BC, float k) : boundaries(BC) , k(k) {};
    System(Matrix* sys, BC* BC, float k) : system(sys) , boundaries(BC) , k(k) {};
    Matrix* system;
    BC* boundaries;
    float k;
    float Dx;
    float Dy;
};

class SystemND : public System {
    ~SystemND();
    SystemND();
    SystemND(BC* BC, float k) : System(BC, k) {};
    SystemND(Matrix* sys, BC* BC, float k) : System(sys, BC, k) {
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