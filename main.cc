#include "STL.hh"

#include <iostream>
#include <fstream>

using namespace std;

void usage() {
  cout <<
    "Usage: manifoldery FILENAME [FILENAME ...]" << endl <<
    endl <<
    "Each file given on the command line will be loaded, parsed, " << endl <<
    "and evaluated for non-manifold edges." << endl;
}

int main(int argc, char** argv) {
  if (argc <= 1) { usage(); return -1; }

  for (int i = 1; i < argc; i++) {
    cout << "Evaluating " << argv[i] << "..." << endl;
    Mesh m;
    try {
      AsciiStlFormatter format;
      ifstream f(argv[i]);
      m = format.readMesh(f);
    } catch (ParseException e) {
      BinaryStlFormatter format;
      ifstream f(argv[i]);
      m = format.readMesh(f);
    }
    // Scan mesh for holes
    cout << "Mesh loaded. Non-manifold edge count: " << m.edges.countNonManifoldEdges() << endl;
  }
  return 0;
}
