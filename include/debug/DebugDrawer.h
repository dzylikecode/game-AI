#pragma once
#include <raylib.h>

#include <map>
#include <vector>

#include "utils/IcoSphere.h"

constexpr auto DEFAULT_ICOSPHERE_RECURSION_LEVEL = 1;

class DebugDrawer {
 public:
  static DebugDrawer& getInstance() {
    static DebugDrawer instance;
    return instance;
  }

 public:
  void build(){};
  void clear(){};

 private:
  DebugDrawer() {}
  DebugDrawer(DebugDrawer const&) = delete;
  void operator=(DebugDrawer const&) = delete;
};

// class DebugDrawer : public Ogre::Singleton<DebugDrawer> {
//  public:
//   DebugDrawer(Ogre::SceneManager *_sceneManager, float _fillAlpha);
//   ~DebugDrawer();

//   static DebugDrawer &getSingleton(void);
//   static DebugDrawer *getSingletonPtr(void);

//   void build();

//   void setIcoSphereRecursionLevel(int recursionLevel);

//   void drawLine(const Ogre::Vector3 &start, const Ogre::Vector3 &end,
//                 const Ogre::ColourValue &colour);
//   void drawCircle(const Ogre::Vector3 &centre, float radius, int
//   segmentsCount,
//                   const Ogre::ColourValue &colour, bool isFilled = false);
//   void drawCylinder(const Ogre::Vector3 &centre, float radius,
//                     int segmentsCount, float height,
//                     const Ogre::ColourValue &colour, bool isFilled = false);
//   void drawTriangle(const Ogre::Vector3 *vertices,
//                     const Ogre::ColourValue &colour, bool isFilled = false);
//   void drawQuad(const Ogre::Vector3 *vertices, const Ogre::ColourValue
//   &colour,
//                 bool isFilled = false);
//   void drawCuboid(const Ogre::Vector3 *vertices,
//                   const Ogre::ColourValue &colour, bool isFilled = false);
//   void drawSphere(const Ogre::Vector3 &centre, float radius,
//                   const Ogre::ColourValue &colour, bool isFilled = false);
//   void drawTetrahedron(const Ogre::Vector3 &centre, float scale,
//                        const Ogre::ColourValue &colour, bool isFilled =
//                        false);

//   bool getEnabled() { return isEnabled; }
//   void setEnabled(bool _isEnabled) { isEnabled = _isEnabled; }
//   void switchEnabled() { isEnabled = !isEnabled; }

//   void clear();

//  private:
//   Ogre::SceneManager *sceneManager;
//   Ogre::ManualObject *manualObject_;
//   Ogre::SceneNode *manualObjectNode;
//   float fillAlpha;
//   IcoSphere icoSphere;

//   bool isEnabled;

//   std::vector<VertexPair> lineVertices;
//   std::vector<int> lineIndices;

//   std::vector<VertexPair> triangleVertices;
//   std::vector<int> triangleIndices;

//   int linesIndex, trianglesIndex;

//   void initialise();
//   void shutdown();

//   void buildLine(const Ogre::Vector3 &start, const Ogre::Vector3 &end,
//                  const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildQuad(const Ogre::Vector3 *vertices, const Ogre::ColourValue
//   &colour,
//                  float alpha = 1.0f);
//   void buildFilledQuad(const Ogre::Vector3 *vertices,
//                        const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildTriangle(const Ogre::Vector3 *vertices,
//                      const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildFilledTriangle(const Ogre::Vector3 *vertices,
//                            const Ogre::ColourValue &colour, float alpha
//                            = 1.0f);
//   void buildCuboid(const Ogre::Vector3 *vertices,
//                    const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildFilledCuboid(const Ogre::Vector3 *vertices,
//                          const Ogre::ColourValue &colour, float alpha
//                          = 1.0f);

//   void buildCircle(const Ogre::Vector3 &centre, float radius, int
//   segmentsCount,
//                    const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildFilledCircle(const Ogre::Vector3 &centre, float radius,
//                          int segmentsCount, const Ogre::ColourValue &colour,
//                          float alpha = 1.0f);

//   void buildCylinder(const Ogre::Vector3 &centre, float radius,
//                      int segmentsCount, float height,
//                      const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildFilledCylinder(const Ogre::Vector3 &centre, float radius,
//                            int segmentsCount, float height,
//                            const Ogre::ColourValue &colour, float alpha
//                            = 1.0f);

//   void buildTetrahedron(const Ogre::Vector3 &centre, float scale,
//                         const Ogre::ColourValue &colour, float alpha = 1.0f);
//   void buildFilledTetrahedron(const Ogre::Vector3 &centre, float scale,
//                               const Ogre::ColourValue &colour,
//                               float alpha = 1.0f);

//   int addLineVertex(const Ogre::Vector3 &vertex,
//                     const Ogre::ColourValue &colour);
//   void addLineIndices(const int index1, const int index2);

//   int addTriangleVertex(const Ogre::Vector3 &vertex,
//                         const Ogre::ColourValue &colour);
//   void addTriangleIndices(int index1, int index2, int index3);

//   void addQuadIndices(int index1, int index2, int index3, int index4);
// };
