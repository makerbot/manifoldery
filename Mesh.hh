#ifndef MESH_HH
#define MESH_HH

#include <vector>
#include <map>

/**
 * A Vertex is a point in 3-space.
 */
class Vertex {
private:
  double v[3];
public:
  Vertex() {}
  double& operator[](int idx) { return v[idx]; }
  const double& operator[](int idx) const { return v[idx]; }
  bool operator<(const Vertex& second) const;
};

/**
 * A VertexCollection is a collection of unique vertices. Identical
 * vertices inserted into the collection will result in only one
 * vertex being created in the collection.
 *
 * We have some interesting design constraints here: we're more concerned
 * with fast insertion time, and not so much with array lookup...
 */
class VertexCollection {
private:
  std::map<Vertex,int> lookup_map;
  std::vector<Vertex> vertices;
public:
  VertexCollection() {}
  /** Add a vertex to the collection. If an identical vertex already
   * exists in the collection, its index will be returned; otherwise
   * it will be added to the collection and the index of the newly
   * allocated vertex will be returned.
   */
  int addVertex(const Vertex& v);
  /** Return the index of a vertex based on its coordinate, or -1
   * if no such vertex exists in the collection.
   */
  int lookup(const Vertex& v) const;
  const Vertex& operator[](int idx) { return vertices[idx]; }
};


/**
 * A triangle is a set of three indices into a collection of points.
 */
class Triangle {
private:
  int v[3];
public:
  Triangle() {}
  int& operator[](int idx) { return v[idx]; }
  const int& operator[](int idx) const { return v[idx]; }
};

typedef std::pair<int,int> intpair;

/**
 * An edge map maps edges onto their associated triangles.
 * This map is built during the manifold check. It can be
 * used to decompose the source mesh into seperate meshes,
 * to discover holes, and (during the build) find pathological
 * cases, like self-tangent meshes.
 */
class EdgeMap : public std::map<intpair,intpair> {
public:
  void addTriangleEdge(int v1, int v2, int tri);
  void addEdgesForTriangle(const Triangle& t, int triIdx);

  int countNonManifoldEdges();
};

class Mesh {
public:
  VertexCollection vertices;
  std::vector<Triangle> tris;
  EdgeMap edges;
public:
  /**
   * Instantiate a new empty triangle mesh. A newly instantiated mesh
   * does not contain any triangles.
   */
  Mesh() {}
};

#endif // MESH_HH
