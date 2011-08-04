#ifndef FORMATTER_HH
#define FORMATTER_HH

#include "Mesh.hh"
#include <iostream>

class Formatter {
public:
  virtual Mesh readMesh(std::istream& in) =0;
  virtual void writeMesh(std::ostream& out, const Mesh& mesh) =0;
};

class ParseException {
};

#endif // FORMATTER_HH
