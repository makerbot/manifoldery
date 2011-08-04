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
    cout << argv[i] << ": ";
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
    list<Loop> loops = m.edges.getHoles();
    if (loops.size() > 0) {
      cout << loops.size() << " loops" << endl;
      list<Loop>::iterator j = loops.begin();
      while (j != loops.end()) {
	for (Loop::iterator k = j->begin(); k != j->end(); k++) {
	  cout << *k << " ";
	}
	cout << endl;
	j++;
      }
    } else {
      cout << "OK" << endl;
    }
  }
  return 0;
}
