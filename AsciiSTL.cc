#include "STL.hh"

#include <string>

using namespace std;

static void expect(std::istream& in, const string expected) {
  string got;
  in >> got;
  if (got != expected) {
    throw ParseException();
  }
  in >> std::ws;
}

static string readHeader(std::istream& in) {
  expect(in,"solid");
  string comment;
  getline(in,comment);
  in >> std::ws;
  return comment;
}

static Vertex readVertex(std::istream& in, const string expected) {
  expect(in,expected);
  Vertex v;
  in >> v[0] >> v[1] >> v[2];
  return v;
}

static Triangle readTriangle(std::istream& in, Mesh& mesh) {
  Triangle t;
  expect(in, "facet");
  t.normal() = readVertex(in,"normal");
  
  expect(in, "outer");
  expect(in, "loop");

  for (int i = 0; i < 3; i++) {
    Vertex v = readVertex(in,"vertex");
    t[i] = mesh.vertices.addVertex(v);
  }
  expect(in, "endloop");
  expect(in, "endfacet");
  return t;
}

Mesh AsciiStlFormatter::readMesh(std::istream& in) {  
  Mesh mesh;
  in.width(80);
  string comment = readHeader(in);
  cout << "STL ASCII header comment: " << comment << endl;
  mesh.comment = comment;
  try {
    while (1) {
      Triangle t = readTriangle(in,mesh);
      mesh.tris.push_back(t);
      int triIdx = mesh.tris.size();
      mesh.edges.addEdgesForTriangle(t,triIdx);
    }
  } catch (ParseException e) {
    // Okay, probably endsolid
  }
  cout << "Loaded mesh; facet count " << mesh.tris.size() << endl;
  return mesh;
}

void AsciiStlFormatter::writeMesh(std::ostream& out, const Mesh& mesh) {
  throw -1;
}
