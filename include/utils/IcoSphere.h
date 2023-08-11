#pragma once
#include <raylib.h>

#include <map>
#include <vector>
using VertexPair = std::pair<Vector3, Color>;

/**
 * @brief The prefix "Ico" in the IcoSphere class name stands for
 * "icosahedron", which is a polyhedron with 20 equilateral triangles as
 * faces. An icosphere is a sphere that is constructed by recursively
 * subdividing the faces of an icosahedron.
 *
 */
class IcoSphere {
 public:
  struct TriangleIndices {
    int v1, v2, v3;

    TriangleIndices(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) {}

    bool operator<(const TriangleIndices &o) const {
      return v1 < o.v1 && v2 < o.v2 && v3 < o.v3;
    }
  };

  struct LineIndices {
    int v1, v2;

    LineIndices(int _v1, int _v2) : v1(_v1), v2(_v2) {}

    bool operator==(const LineIndices &o) const {
      return (v1 == o.v1 && v2 == o.v2) || (v1 == o.v2 && v2 == o.v1);
    }
  };

  IcoSphere();
  ~IcoSphere();

  void create(int recursionLevel);
  void addToLineIndices(int baseIndex, std::vector<int> *target);
  int addToVertices(std::vector<VertexPair> *target, const Vector3 &position,
                    const Color &colour, float scale);
  void addToTriangleIndices(int baseIndex, std::vector<int> *target);

 private:
  int addVertex(const Vector3 &vertex);
  void addLineIndices(int index0, int index1);
  void addTriangleLines(int index0, int index1, int index2);
  int getMiddlePoint(int index0, int index1);
  void addFace(int index0, int index1, int index2);

  void removeLineIndices(int index0, int index1);

  std::vector<Vector3> vertices;
  std::vector<LineIndices> lineIndices;
  std::vector<int> triangleIndices;
  std::vector<TriangleIndices> faces;
  using cacheKey = std::pair<int, int>;
  std::map<cacheKey, int> middlePointIndexCache;
  int index;
};
