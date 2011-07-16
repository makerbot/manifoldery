#include "STL.hh"

#include <iostream>
#include <stdint.h>
#include <endian.h>

using namespace std;

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

// Oh, I could be all magical C++ guru and extend istream to support
// these the way I want. The only issue there is that I'd be contributing
// to the massive, intercontinental clusterfuck that is iostreams.

int readUInt32(std::istream& in) {
  uint32_t tmp;
  in.read((istream::char_type*)&tmp,4);
  return le32toh(tmp);
}

float readFloat(std::istream& in) {
  uint32_t tmp;
  in.read((istream::char_type*)&tmp,4);
  tmp = le32toh(tmp);
  return *(float*)(&tmp);
}

Vertex readVertex(std::istream& in) {
  Vertex v;
  v[0] = readFloat(in);
  v[1] = readFloat(in);
  v[2] = readFloat(in);
  return v;
}

Mesh loadBinarySTL(std::istream& in) {
  Mesh mesh;
  istream::char_type comment[81];
  istream::char_type padding[2];
  in.read(comment,80);
  comment[80] = '\0';
  cout << "STL header comment: " << comment << endl;
  uint32_t facets = readUInt32(in);
  cout << "Facet count: " << facets << endl;
  for (int f = 0; f < facets; f++) {
    // TODO: check that file is long enough! We can't have this
    // block.
    // Read normal and discard (for now)
    Vertex normal = readVertex(in);
    Vertex v[3];
    Triangle t;
    for (int i =0; i < 3; i++) {
      v[i] = readVertex(in);
      t[i] = mesh.vertices.addVertex(v[i]);
    }
    // Read padding
    in.read(padding,2);
    mesh.tris.push_back(t);
    int triIdx = mesh.tris.size();
    mesh.edges.addEdgesForTriangle(t,triIdx);
  }
  return mesh;
}

void writeBinarySTL(std::ostream& out, Mesh& mesh) {
  throw -1;
}


Mesh loadAsciiSTL(std::istream& in) {
  
  throw ParseException();
}

void writeAsciiSTL(std::ostream& out, Mesh& mesh) {
  throw -1;
}
