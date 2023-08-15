#include "utils/IcoSphere.h"

#include <cmath>

IcoSphere::IcoSphere() : index(0) {}

IcoSphere::~IcoSphere() {}

void IcoSphere::create(int recursionLevel) {
  vertices.clear();
  lineIndices.clear();
  triangleIndices.clear();
  faces.clear();
  middlePointIndexCache.clear();
  index = 0;

  float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

  addVertex(Vector3{-1.0f, t, 0.0f});
  addVertex(Vector3{1.0f, t, 0.0f});
  addVertex(Vector3{-1.0f, -t, 0.0f});
  addVertex(Vector3{1.0f, -t, 0.0f});

  addVertex(Vector3{0.0f, -1.0f, t});
  addVertex(Vector3{0.0f, 1.0f, t});
  addVertex(Vector3{0.0f, -1.0f, -t});
  addVertex(Vector3{0.0f, 1.0f, -t});

  addVertex(Vector3{t, 0.0f, -1.0f});
  addVertex(Vector3{t, 0.0f, 1.0f});
  addVertex(Vector3{-t, 0.0f, -1.0f});
  addVertex(Vector3{-t, 0.0f, 1.0f});

  addFace(0, 11, 5);
  addFace(0, 5, 1);
  addFace(0, 1, 7);
  addFace(0, 7, 10);
  addFace(0, 10, 11);

  addFace(1, 5, 9);
  addFace(5, 11, 4);
  addFace(11, 10, 2);
  addFace(10, 7, 6);
  addFace(7, 1, 8);

  addFace(3, 9, 4);
  addFace(3, 4, 2);
  addFace(3, 2, 6);
  addFace(3, 6, 8);
  addFace(3, 8, 9);

  addFace(4, 9, 5);
  addFace(2, 4, 11);
  addFace(6, 2, 10);
  addFace(8, 6, 7);
  addFace(9, 8, 1);

  addLineIndices(1, 0);
  addLineIndices(1, 5);
  addLineIndices(1, 7);
  addLineIndices(1, 8);
  addLineIndices(1, 9);

  addLineIndices(2, 3);
  addLineIndices(2, 4);
  addLineIndices(2, 6);
  addLineIndices(2, 10);
  addLineIndices(2, 11);

  addLineIndices(0, 5);
  addLineIndices(5, 9);
  addLineIndices(9, 8);
  addLineIndices(8, 7);
  addLineIndices(7, 0);

  addLineIndices(10, 11);
  addLineIndices(11, 4);
  addLineIndices(4, 3);
  addLineIndices(3, 6);
  addLineIndices(6, 10);

  addLineIndices(0, 11);
  addLineIndices(11, 5);
  addLineIndices(5, 4);
  addLineIndices(4, 9);
  addLineIndices(9, 3);
  addLineIndices(3, 8);
  addLineIndices(8, 6);
  addLineIndices(6, 7);
  addLineIndices(7, 10);
  addLineIndices(10, 0);

  for (int i = 0; i < recursionLevel; i++) {
    std::vector<TriangleIndices> faces2;

    for (std::vector<TriangleIndices>::iterator j = faces.begin();
         j != faces.end(); j++) {
      TriangleIndices f = *j;
      int a = getMiddlePoint(f.v1, f.v2);
      int b = getMiddlePoint(f.v2, f.v3);
      int c = getMiddlePoint(f.v3, f.v1);

      removeLineIndices(f.v1, f.v2);
      removeLineIndices(f.v2, f.v3);
      removeLineIndices(f.v3, f.v1);

      faces2.push_back(TriangleIndices(f.v1, a, c));
      faces2.push_back(TriangleIndices(f.v2, b, a));
      faces2.push_back(TriangleIndices(f.v3, c, b));
      faces2.push_back(TriangleIndices(a, b, c));

      addTriangleLines(f.v1, a, c);
      addTriangleLines(f.v2, b, a);
      addTriangleLines(f.v3, c, b);
    }

    faces = faces2;
  }
}

void IcoSphere::addLineIndices(const int index0, const int index1) {
  lineIndices.push_back(LineIndices(index0, index1));
}

void IcoSphere::removeLineIndices(int index0, int index1) {
  std::vector<LineIndices>::iterator result = std::find(
      lineIndices.begin(), lineIndices.end(), LineIndices(index0, index1));

  if (result != lineIndices.end()) lineIndices.erase(result);
}

void IcoSphere::addTriangleLines(int index0, int index1, int index2) {
  addLineIndices(index0, index1);
  addLineIndices(index1, index2);
  addLineIndices(index2, index0);
}

int IcoSphere::addVertex(const Vector3 &vertex) {
  vertices.push_back(vertex.normalisedCopy());
  return index++;
}

/**
 * @brief memoization
 *
 * @param index0
 * @param index1
 * @return int
 */
int IcoSphere::getMiddlePoint(int index0, int index1) {
  auto key = std::make_pair(std::min(index0, index1), std::max(index0, index1));

  if (middlePointIndexCache.find(key) != middlePointIndexCache.end())
    return middlePointIndexCache[key];

  auto point1 = vertices[index0];
  auto point2 = vertices[index1];
  auto middle =
      Vector3{(point1.x + point2.x) / 2.0f, (point1.y + point2.y) / 2.0f,
              (point1.z + point2.z) / 2.0f};

  auto index = addVertex(middle);
  middlePointIndexCache[key] = index;
  return index;
}

void IcoSphere::addFace(int index0, int index1, int index2) {
  faces.push_back(TriangleIndices(index0, index1, index2));
}

void IcoSphere::addToLineIndices(int baseIndex, std::vector<int> *target) {
  for (std::vector<LineIndices>::iterator i = lineIndices.begin();
       i != lineIndices.end(); i++) {
    target->push_back(baseIndex + (*i).v1);
    target->push_back(baseIndex + (*i).v2);
  }
}

void IcoSphere::addToTriangleIndices(int baseIndex, std::vector<int> *target) {
  for (std::vector<TriangleIndices>::iterator i = faces.begin();
       i != faces.end(); i++) {
    target->push_back(baseIndex + (*i).v1);
    target->push_back(baseIndex + (*i).v2);
    target->push_back(baseIndex + (*i).v3);
  }
}

int IcoSphere::addToVertices(std::vector<VertexPair> *target,
                             const Vector3 &position, const ColourValue &colour,
                             float scale) {
  // tranlate first then scale, res = transform * scale * vertices
  Matrix4 transform = Matrix4::IDENTITY;
  transform.setTrans(position);
  transform.setScale(Vector3(scale, scale, scale));

  for (size_t i = 0; i < vertices.size(); i++)
    target->push_back(VertexPair(transform * vertices[i], colour));

  return static_cast<int>(vertices.size());
}