#include "STL.hh"

Mesh loadBinarySTL(std::istream& in);
Mesh loadAsciiSTL(std::istream& in);

Mesh loadSTL(std::istream& in, bool binary) {
  if (binary) {
    return loadBinarySTL(in);
  } else {
    return loadAsciiSTL(in);
  }
}

void writeBinarySTL(std::ostream& out, Mesh& mesh);
void writeAsciiSTL(std::ostream& out, Mesh& mesh);

void writeSTL(std::ostream& out, Mesh& mesh, bool binary) {
  if (binary) {
    writeBinarySTL(out, mesh);
  } else {
    writeAsciiSTL(out, mesh);
  }
}
