#ifndef STL_HH
#define STL_HH

#include "Formatter.hh"

class AsciiStlFormatter : public Formatter {
public:
  Mesh readMesh(std::istream& in);
  void writeMesh(std::ostream& out, const Mesh& mesh);
};

class BinaryStlFormatter : public Formatter {
public:
  Mesh readMesh(std::istream& in);
  void writeMesh(std::ostream& out, const Mesh& mesh);
};

#endif // STL_HH
