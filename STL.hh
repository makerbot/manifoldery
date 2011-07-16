#ifndef STL_HH
#define STL_HH

#include <iostream>
#include "Mesh.hh"

class ParseException {
};

Mesh loadSTL(std::istream& in, bool binary);

void writeSTL(std::ostream& out, Mesh& mesh, bool binary);

#endif
