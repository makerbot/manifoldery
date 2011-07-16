#include "Mesh.hh"

bool Vertex::operator<(const Vertex& second) const {
  if (v[0] < second[0]) { return true; }
  else if (v[0] > second[0]) { return false; }
  if (v[1] < second[1]) { return true; }
  else if (v[1] > second[1]) { return false; }
  return v[2] < second[2];
}

/** Add a vertex to the collection. If an identical vertex already
 * exists in the collection, its index will be returned; otherwise
 * it will be added to the collection and the index of the newly
 * allocated vertex will be returned.
 */
int VertexCollection::addVertex(const Vertex& v) {
  int l = lookup(v);
  if (l != -1) {
    return l;
  }
  l = vertices.size();
  vertices.push_back(v);
  lookup_map[v] = l;
  return l;
}

/** Return the index of a vertex based on its coordinate, or -1
 * if no such vertex exists in the collection.
 */
int VertexCollection::lookup(const Vertex& v) const {
  std::map<Vertex,int>::const_iterator i = lookup_map.find(v);
  if (i == lookup_map.end()) {
    return -1;
  }
  return i->second;
}

void EdgeMap::addTriangleEdge(int v1, int v2, int tri) {
  intpair p(v1,v2);
  if (v2 < v1) {
    p = intpair(v2,v1);
  }
  iterator i = find(p);
  if (i == end()) {
    (*this)[p] = intpair(tri, -1);
  } else {
    if (i->second.second == -1) {
      i->second.second = tri;
      } else {
      // Report collision!
    }
  }
}

void EdgeMap::addEdgesForTriangle(const Triangle& t, int triIdx) {
  addTriangleEdge(t[0],t[1],triIdx);
  addTriangleEdge(t[1],t[2],triIdx);
  addTriangleEdge(t[2],t[0],triIdx);
}

int EdgeMap::countNonManifoldEdges() {
  int count = 0;
  for (const_iterator i = begin(); i != end(); i++) {
    if (i->second.second == -1) { count++; }
  }
  return count;
}
