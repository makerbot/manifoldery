#include "STL.hh"

#include <iostream>
#include <stdint.h>

#ifdef ON_DARWIN
#if !defined(le32toh) || !defined(htole32)
  #if BYTE_ORDER == LITTLE_ENDIAN
    #define le32toh(x) (x)
    #define htole32(x) bswap_32(x)
  #else
    #define le32toh(x) bswap_32(x)
    #define htole32(x) (x)
  #endif
#endif
 #if defined(HAVE_COREFOUNDATION_COREFOUNDATION_H)
    #include <CoreFoundation/CoreFoundation.h>
    #define htole32(x) CFSwapInt32HostToLittle(x)
    #define le32toh(x) CFSwapInt32LittleToHost(x)
 #endif
#else
  #if defined(ON_LINUX) 
    #include <endian.h>
  #endif /*ON_LINUX*/
#endif


using namespace std;


// Oh, I could be all magical C++ guru and extend istream to support
// these the way I want. The only issue there is that I'd be contributing
// to the massive, intercontinental clusterfuck that is iostreams.

static int readUInt32(std::istream& in) {
  uint32_t tmp;
  in.read((istream::char_type*)&tmp,4);
  return le32toh(tmp);
}

static float readFloat(std::istream& in) {
  uint32_t tmp;
  in.read((istream::char_type*)&tmp,4);
  tmp = le32toh(tmp);
  return *(float*)(&tmp);
}

static Vertex readVertex(std::istream& in) {
  Vertex v;
  v[0] = readFloat(in);
  v[1] = readFloat(in);
  v[2] = readFloat(in);
  return v;
}

Mesh BinaryStlFormatter::readMesh(std::istream& in) {
  Mesh mesh;
  istream::char_type comment[81];
  istream::char_type padding[2];
  in.read(comment,80);
  comment[80] = '\0';
  //cout << "STL header comment: " << comment << endl;
  mesh.comment = comment;
  uint32_t facets = readUInt32(in);
  //cout << "Facet count: " << facets << endl;
  for (int f = 0; f < facets && !in.eof(); f++) {
    // TODO: check that file is long enough! We can't have this
    // block.
    // Read normal
    Triangle t;
    t.normal() = readVertex(in);
    Vertex v[3];
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
  if (in.fail()) {
    cerr << "Error reading file; file possibly corrupted or misunderstood." <<
      endl;
    throw ParseException();
  }
  return mesh;
}

void BinaryStlFormatter::writeMesh(std::ostream& out, const Mesh& mesh) {
  throw -1;
}
