#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "main.hpp"

namespace py = pybind11;

PYBIND11_MODULE(translate, m) {
    m.doc() = "Translation function";
    m.def("t", &translate, "Translator for interaction between frontend and backend");
}