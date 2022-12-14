#include "solve.hpp"
#include "system.hpp"

#include <set>
#include <malloc.h>

System* Solve(SystemND system, std::set<int> exclude) {
    Matrix* m = system.distro;
    float *b = (float *) malloc(m->Width() * m->Height() * sizeof(float));
    float *A = (float *) malloc(m->Width() * m->Width() * m->Height() * m->Height() * sizeof(float));

    for(int i = 0; i < m->Width() * m->Height(); i++) {
        for(int j = 0; j < m->Width() * m->Height(); j++) {
            A[i * m->Width() * m->Height() + j] = 0;
        }
    }

    for(int i = 0; i < m->Width() * m->Height(); i++) {
        if(exclude.find(i) == exclude.end()) {
            int solution = 0;
            float *fluxes = system.CalculateFluxes(i, m->Width() * m->Height(), solution);
            for(int j = 0; j < m->Width() * m->Height(); j++) {
                A[i * m->Width() * m->Height() + j] = fluxes[j];
            }
            b[i] = solution;
        } else {
            A[i * m->Width() * m->Height() + i] = 1;
            b[i] = m->get(i / m->Width(), i % m->Width());
        }
    }
    Matrix *eqs = new Matrix(A, m->Width() * m->Height(), m->Width() * m->Height());
    
    // Debugging
    // eqs->Display();
    
    Vector *sol = new Vector(b, m->Width() * m->Height());
    // sol->Display();
    Vector x = eqs->GaussianSolve(*sol);

    return new SystemND(new Matrix(&x, m->Height(), m->Width()), system.boundaries, system.k, system.GetDimension());
}