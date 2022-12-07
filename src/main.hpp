#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <math.h>

#include "system.hpp"
#include "solve.hpp"

int main();

std::vector<float> translate(int N, std::vector<float> dims, float k, std::vector<float> h, std::vector<float> T);

#endif