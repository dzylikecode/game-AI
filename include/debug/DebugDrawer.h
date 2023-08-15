#pragma once

#include <map>
#include <vector>

#include "utils/IcoSphere.h"

constexpr auto DEFAULT_ICOSPHERE_RECURSION_LEVEL = 1;

class DebugDrawerAI : public Singleton<DebugDrawerAI> {
 public:
  DebugDrawerAI(SceneManager *_sceneManager, float _fillAlpha);
  ~DebugDrawerAI();

  static DebugDrawerAI &getSingleton(void);
  static DebugDrawerAI *getSingletonPtr(void);

  void build();

  void setIcoSphereRecursionLevel(int recursionLevel);

  void drawLine(const Vector3 &start, const Vector3 &end,
                const ColourValue &colour);
  void drawCircle(const Vector3 &centre, float radius, int segmentsCount,
                  const ColourValue &colour, bool isFilled = false);
  void drawCylinder(const Vector3 &centre, float radius, int segmentsCount,
                    float height, const ColourValue &colour,
                    bool isFilled = false);
  void drawTriangle(const Vector3 *vertices, const ColourValue &colour,
                    bool isFilled = false);
  void drawQuad(const Vector3 *vertices, const ColourValue &colour,
                bool isFilled = false);
  void drawCuboid(const Vector3 *vertices, const ColourValue &colour,
                  bool isFilled = false);
  void drawSphere(const Vector3 &centre, float radius,
                  const ColourValue &colour, bool isFilled = false);
  void drawTetrahedron(const Vector3 &centre, float scale,
                       const ColourValue &colour, bool isFilled = false);

  bool getEnabled() { return isEnabled; }
  void setEnabled(bool _isEnabled) { isEnabled = _isEnabled; }
  void switchEnabled() { isEnabled = !isEnabled; }

  void clear();

 private:
  SceneManager *sceneManager;
  ManualObject *manualObject_;
  SceneNode *manualObjectNode;
  float fillAlpha;
  IcoSphere icoSphere;

  bool isEnabled;

  std::vector<VertexPair> lineVertices;
  std::vector<int> lineIndices;

  std::vector<VertexPair> triangleVertices;
  std::vector<int> triangleIndices;

  int linesIndex, trianglesIndex;

  void initialise();
  void shutdown();

  void buildLine(const Vector3 &start, const Vector3 &end,
                 const ColourValue &colour, float alpha = 1.0f);
  void buildQuad(const Vector3 *vertices, const ColourValue &colour,
                 float alpha = 1.0f);
  void buildFilledQuad(const Vector3 *vertices, const ColourValue &colour,
                       float alpha = 1.0f);
  void buildTriangle(const Vector3 *vertices, const ColourValue &colour,
                     float alpha = 1.0f);
  void buildFilledTriangle(const Vector3 *vertices, const ColourValue &colour,
                           float alpha = 1.0f);
  void buildCuboid(const Vector3 *vertices, const ColourValue &colour,
                   float alpha = 1.0f);
  void buildFilledCuboid(const Vector3 *vertices, const ColourValue &colour,
                         float alpha = 1.0f);

  void buildCircle(const Vector3 &centre, float radius, int segmentsCount,
                   const ColourValue &colour, float alpha = 1.0f);
  void buildFilledCircle(const Vector3 &centre, float radius, int segmentsCount,
                         const ColourValue &colour, float alpha = 1.0f);

  void buildCylinder(const Vector3 &centre, float radius, int segmentsCount,
                     float height, const ColourValue &colour,
                     float alpha = 1.0f);
  void buildFilledCylinder(const Vector3 &centre, float radius,
                           int segmentsCount, float height,
                           const ColourValue &colour, float alpha = 1.0f);

  void buildTetrahedron(const Vector3 &centre, float scale,
                        const ColourValue &colour, float alpha = 1.0f);
  void buildFilledTetrahedron(const Vector3 &centre, float scale,
                              const ColourValue &colour, float alpha = 1.0f);

  int addLineVertex(const Vector3 &vertex, const ColourValue &colour);
  void addLineIndices(const int index1, const int index2);

  int addTriangleVertex(const Vector3 &vertex, const ColourValue &colour);
  void addTriangleIndices(int index1, int index2, int index3);

  void addQuadIndices(int index1, int index2, int index3, int index4);
};
