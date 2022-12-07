#include <iostream>
#include <pybind11/pybind11.h>

void meep() {
    std::cout << "HI";
}

PYBIND11_MODULE(firstModule, l) {
    l.def("meep", &meep, "Prints out something");
}