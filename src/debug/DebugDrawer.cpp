#include "debug/DebugDrawer.h"

template <>
DebugDrawerAI* Singleton<DebugDrawerAI>::msSingleton = 0;
DebugDrawerAI* DebugDrawerAI::getSingletonPtr(void) { return msSingleton; }

DebugDrawerAI& DebugDrawerAI::getSingleton(void) {
  assert(msSingleton);
  return (*msSingleton);
}

DebugDrawerAI::DebugDrawerAI(SceneManager* _sceneManager, float _fillAlpha)
    : sceneManager(_sceneManager),
      fillAlpha(_fillAlpha),
      manualObject_(0),
      linesIndex(0),
      trianglesIndex(0) {
  initialise();
}

DebugDrawerAI::~DebugDrawerAI() { shutdown(); }

void DebugDrawerAI::initialise() {
  manualObject_ = sceneManager->createManualObject();
  manualObjectNode = sceneManager->getRootSceneNode()->createChildSceneNode();
  manualObjectNode->attachObject(manualObject_);
  manualObject_->setDynamic(true);

  icoSphere.create(DEFAULT_ICOSPHERE_RECURSION_LEVEL);

  manualObject_->begin("debug_draw", RenderOperation::OT_LINE_LIST);
  manualObject_->position(Vector3::ZERO);
  manualObject_->colour(ColourValue::ZERO);
  manualObject_->index(0);
  manualObject_->end();
  manualObject_->begin("debug_draw", RenderOperation::OT_TRIANGLE_LIST);
  manualObject_->position(Vector3::ZERO);
  manualObject_->colour(ColourValue::ZERO);
  manualObject_->index(0);
  manualObject_->end();

  manualObject_->setBoundingBox(AxisAlignedBox::BOX_INFINITE);
  manualObjectNode->_updateBounds();

  linesIndex = trianglesIndex = 0;
  setEnabled(true);
}

void DebugDrawerAI::setIcoSphereRecursionLevel(int recursionLevel) {
  icoSphere.create(recursionLevel);
}

void DebugDrawerAI::shutdown() {
  sceneManager->destroySceneNode(manualObjectNode);
  sceneManager->destroyManualObject(manualObject_);
}

void DebugDrawerAI::buildLine(const Vector3& start, const Vector3& end,
                              const ColourValue& colour, float alpha) {
  const int i =
      addLineVertex(start, ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(end, ColourValue(colour.r, colour.g, colour.b, alpha));

  addLineIndices(i, i + 1);
}

void DebugDrawerAI::buildQuad(const Vector3* vertices,
                              const ColourValue& colour, float alpha) {
  int index = addLineVertex(vertices[0],
                            ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(vertices[1], ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(vertices[2], ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(vertices[3], ColourValue(colour.r, colour.g, colour.b, alpha));

  for (int i = 0; i < 4; ++i) {
    addLineIndices(index + i, index + ((i + 1) % 4));
  }
}

void DebugDrawerAI::buildCircle(const Vector3& centre, float radius,
                                int segmentsCount, const ColourValue& colour,
                                float alpha) {
  int index = linesIndex;
  float increment = 2 * Math::PI / segmentsCount;
  float angle = 0.0f;

  for (int i = 0; i < segmentsCount; i++) {
    addLineVertex(Vector3(centre.x + radius * Math::Cos(angle), centre.y,
                          centre.z + radius * Math::Sin(angle)),
                  ColourValue(colour.r, colour.g, colour.b, alpha));
    angle += increment;
  }

  for (int i = 0; i < segmentsCount; i++)
    addLineIndices(index + i, i + 1 < segmentsCount ? index + i + 1 : index);
}

void DebugDrawerAI::buildFilledCircle(const Vector3& centre, float radius,
                                      int segmentsCount,
                                      const ColourValue& colour, float alpha) {
  int index = trianglesIndex;
  float increment = 2 * Math::PI / segmentsCount;
  float angle = 0.0f;

  for (int i = 0; i < segmentsCount; i++) {
    addTriangleVertex(Vector3(centre.x + radius * Math::Cos(angle), centre.y,
                              centre.z + radius * Math::Sin(angle)),
                      ColourValue(colour.r, colour.g, colour.b, alpha));
    angle += increment;
  }

  addTriangleVertex(centre, ColourValue(colour.r, colour.g, colour.b, alpha));

  for (int i = 0; i < segmentsCount; i++)
    addTriangleIndices(i + 1 < segmentsCount ? index + i + 1 : index, index + i,
                       index + segmentsCount);
}

void DebugDrawerAI::buildCylinder(const Vector3& centre, float radius,
                                  int segmentsCount, float height,
                                  const ColourValue& colour, float alpha) {
  int index = linesIndex;
  float increment = 2 * Math::PI / segmentsCount;
  float angle = 0.0f;

  // Top circle
  for (int i = 0; i < segmentsCount; i++) {
    addLineVertex(
        Vector3(centre.x + radius * Math::Cos(angle), centre.y + height / 2,
                centre.z + radius * Math::Sin(angle)),
        ColourValue(colour.r, colour.g, colour.b, alpha));
    angle += increment;
  }

  angle = 0.0f;

  // Bottom circle
  for (int i = 0; i < segmentsCount; i++) {
    addLineVertex(
        Vector3(centre.x + radius * Math::Cos(angle), centre.y - height / 2,
                centre.z + radius * Math::Sin(angle)),
        ColourValue(colour.r, colour.g, colour.b, alpha));
    angle += increment;
  }

  for (int i = 0; i < segmentsCount; i++) {
    addLineIndices(index + i, i + 1 < segmentsCount ? index + i + 1 : index);
    addLineIndices(segmentsCount + index + i,
                   i + 1 < segmentsCount ? segmentsCount + index + i + 1
                                         : segmentsCount + index);
    addLineIndices(index + i, segmentsCount + index + i);
  }
}

void DebugDrawerAI::buildFilledCylinder(const Vector3& centre, float radius,
                                        int segmentsCount, float height,
                                        const ColourValue& colour,
                                        float alpha) {
  int index = trianglesIndex;
  float increment = 2 * Math::PI / segmentsCount;
  float angle = 0.0f;

  // Top circle
  for (int i = 0; i < segmentsCount; i++) {
    addTriangleVertex(
        Vector3(centre.x + radius * Math::Cos(angle), centre.y + height / 2,
                centre.z + radius * Math::Sin(angle)),
        ColourValue(colour.r, colour.g, colour.b, alpha));
    angle += increment;
  }

  addTriangleVertex(Vector3(centre.x, centre.y + height / 2, centre.z),
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  angle = 0.0f;

  // Bottom circle
  for (int i = 0; i < segmentsCount; i++) {
    addTriangleVertex(
        Vector3(centre.x + radius * Math::Cos(angle), centre.y - height / 2,
                centre.z + radius * Math::Sin(angle)),
        ColourValue(colour.r, colour.g, colour.b, alpha));
    angle += increment;
  }

  addTriangleVertex(Vector3(centre.x, centre.y - height / 2, centre.z),
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  for (int i = 0; i < segmentsCount; i++) {
    addTriangleIndices(i + 1 < segmentsCount ? index + i + 1 : index, index + i,
                       index + segmentsCount);

    addTriangleIndices(i + 1 < segmentsCount
                           ? (segmentsCount + 1) + index + i + 1
                           : (segmentsCount + 1) + index,
                       (segmentsCount + 1) + index + segmentsCount,
                       (segmentsCount + 1) + index + i);

    addQuadIndices(index + i, i + 1 < segmentsCount ? index + i + 1 : index,
                   i + 1 < segmentsCount ? (segmentsCount + 1) + index + i + 1
                                         : (segmentsCount + 1) + index,
                   (segmentsCount + 1) + index + i);
  }
}

void DebugDrawerAI::buildCuboid(const Vector3* vertices,
                                const ColourValue& colour, float alpha) {
  int index = addLineVertex(vertices[0],
                            ColourValue(colour.r, colour.g, colour.b, alpha));
  for (int i = 1; i < 8; ++i)
    addLineVertex(vertices[i],
                  ColourValue(colour.r, colour.g, colour.b, alpha));

  for (int i = 0; i < 4; ++i) addLineIndices(index + i, index + ((i + 1) % 4));
  for (int i = 4; i < 8; ++i)
    addLineIndices(index + i, i == 7 ? index + 4 : index + i + 1);
  addLineIndices(index + 1, index + 5);
  addLineIndices(index + 2, index + 4);
  addLineIndices(index, index + 6);
  addLineIndices(index + 3, index + 7);
}

void DebugDrawerAI::buildFilledCuboid(const Vector3* vertices,
                                      const ColourValue& colour, float alpha) {
  const int index = addTriangleVertex(
      vertices[0], ColourValue(colour.r, colour.g, colour.b, alpha));

  for (int i = 1; i < 8; ++i) {
    addTriangleVertex(vertices[i],
                      ColourValue(colour.r, colour.g, colour.b, alpha));
  }

  addQuadIndices(index, index + 1, index + 2, index + 3);
  addQuadIndices(index + 4, index + 5, index + 6, index + 7);

  addQuadIndices(index + 1, index + 5, index + 4, index + 2);
  addQuadIndices(index, index + 3, index + 7, index + 6);

  addQuadIndices(index + 1, index, index + 6, index + 5);
  addQuadIndices(index + 4, index + 7, index + 3, index + 2);
}

void DebugDrawerAI::buildFilledQuad(const Vector3* vertices,
                                    const ColourValue& colour, float alpha) {
  const int index = addTriangleVertex(
      vertices[0], ColourValue(colour.r, colour.g, colour.b, alpha));

  addTriangleVertex(vertices[1],
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  addTriangleVertex(vertices[2],
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  addTriangleVertex(vertices[3],
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  addQuadIndices(index, index + 1, index + 2, index + 3);
}

void DebugDrawerAI::buildTriangle(const Vector3* vertices,
                                  const ColourValue& colour, float alpha) {
  int index = addLineVertex(vertices[0],
                            ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(vertices[1], ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(vertices[2], ColourValue(colour.r, colour.g, colour.b, alpha));

  for (int i = 0; i < 3; ++i) addLineIndices(index + i, index + ((i + 1) % 3));
}

void DebugDrawerAI::buildFilledTriangle(const Vector3* vertices,
                                        const ColourValue& colour,
                                        float alpha) {
  int index = addTriangleVertex(
      vertices[0], ColourValue(colour.r, colour.g, colour.b, alpha));
  addTriangleVertex(vertices[1],
                    ColourValue(colour.r, colour.g, colour.b, alpha));
  addTriangleVertex(vertices[2],
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  addTriangleIndices(index, index + 1, index + 2);
}

void DebugDrawerAI::buildTetrahedron(const Vector3& centre, float scale,
                                     const ColourValue& colour, float alpha) {
  int index = linesIndex;

  // Distance from the centre
  float bottomDistance = scale * 0.2f;
  float topDistance = scale * 0.62f;
  float frontDistance = scale * 0.289f;
  float backDistance = scale * 0.577f;
  float leftRightDistance = scale * 0.5f;

  addLineVertex(Vector3(centre.x, centre.y + topDistance, centre.z),
                ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(
      Vector3(centre.x, centre.y - bottomDistance, centre.z + frontDistance),
      ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(Vector3(centre.x + leftRightDistance, centre.y - bottomDistance,
                        centre.z - backDistance),
                ColourValue(colour.r, colour.g, colour.b, alpha));
  addLineVertex(Vector3(centre.x - leftRightDistance, centre.y - bottomDistance,
                        centre.z - backDistance),
                ColourValue(colour.r, colour.g, colour.b, alpha));

  addLineIndices(index, index + 1);
  addLineIndices(index, index + 2);
  addLineIndices(index, index + 3);

  addLineIndices(index + 1, index + 2);
  addLineIndices(index + 2, index + 3);
  addLineIndices(index + 3, index + 1);
}

void DebugDrawerAI::buildFilledTetrahedron(const Vector3& centre, float scale,
                                           const ColourValue& colour,
                                           float alpha) {
  int index = trianglesIndex;

  // Distance from the centre
  float bottomDistance = scale * 0.2f;
  float topDistance = scale * 0.62f;
  float frontDistance = scale * 0.289f;
  float backDistance = scale * 0.577f;
  float leftRightDistance = scale * 0.5f;

  addTriangleVertex(Vector3(centre.x, centre.y + topDistance, centre.z),
                    ColourValue(colour.r, colour.g, colour.b, alpha));
  addTriangleVertex(
      Vector3(centre.x, centre.y - bottomDistance, centre.z + frontDistance),
      ColourValue(colour.r, colour.g, colour.b, alpha));
  addTriangleVertex(Vector3(centre.x + leftRightDistance,
                            centre.y - bottomDistance, centre.z - backDistance),
                    ColourValue(colour.r, colour.g, colour.b, alpha));
  addTriangleVertex(Vector3(centre.x - leftRightDistance,
                            centre.y - bottomDistance, centre.z - backDistance),
                    ColourValue(colour.r, colour.g, colour.b, alpha));

  addTriangleIndices(index, index + 1, index + 2);
  addTriangleIndices(index, index + 2, index + 3);
  addTriangleIndices(index, index + 3, index + 1);

  addTriangleIndices(index + 1, index + 3, index + 2);
}

void DebugDrawerAI::drawLine(const Vector3& start, const Vector3& end,
                             const ColourValue& colour) {
  buildLine(start, end, colour);
}

void DebugDrawerAI::drawCircle(const Vector3& centre, float radius,
                               int segmentsCount, const ColourValue& colour,
                               bool isFilled) {
  buildCircle(centre, radius, segmentsCount, colour);
  if (isFilled)
    buildFilledCircle(centre, radius, segmentsCount, colour, fillAlpha);
}

void DebugDrawerAI::drawCylinder(const Vector3& centre, float radius,
                                 int segmentsCount, float height,
                                 const ColourValue& colour, bool isFilled) {
  buildCylinder(centre, radius, segmentsCount, height, colour);
  if (isFilled)
    buildFilledCylinder(centre, radius, segmentsCount, height, colour,
                        fillAlpha);
}

void DebugDrawerAI::drawQuad(const Vector3* vertices, const ColourValue& colour,
                             bool isFilled) {
  buildQuad(vertices, colour);
  if (isFilled) buildFilledQuad(vertices, colour, fillAlpha);
}

void DebugDrawerAI::drawTriangle(const Vector3* vertices,
                                 const ColourValue& colour, bool isFilled) {
  buildTriangle(vertices, colour);
  if (isFilled) buildFilledTriangle(vertices, colour, fillAlpha);
}

void DebugDrawerAI::drawCuboid(const Vector3* vertices,
                               const ColourValue& colour, bool isFilled) {
  buildCuboid(vertices, colour);
  if (isFilled) buildFilledCuboid(vertices, colour, fillAlpha);
}

void DebugDrawerAI::drawSphere(const Vector3& centre, float radius,
                               const ColourValue& colour, bool isFilled) {
  int baseIndex = linesIndex;
  linesIndex += icoSphere.addToVertices(&lineVertices, centre, colour, radius);
  icoSphere.addToLineIndices(baseIndex, &lineIndices);

  if (isFilled) {
    baseIndex = trianglesIndex;
    trianglesIndex += icoSphere.addToVertices(
        &triangleVertices, centre,
        ColourValue(colour.r, colour.g, colour.b, fillAlpha), radius);
    icoSphere.addToTriangleIndices(baseIndex, &triangleIndices);
  }
}

void DebugDrawerAI::drawTetrahedron(const Vector3& centre, float scale,
                                    const ColourValue& colour, bool isFilled) {
  buildTetrahedron(centre, scale, colour);
  if (isFilled) buildFilledTetrahedron(centre, scale, colour, fillAlpha);
}

void DebugDrawerAI::build() {
  manualObject_->beginUpdate(0);
  if (lineVertices.size() > 0 && isEnabled) {
    manualObject_->estimateVertexCount(
        static_cast<uint32>(lineVertices.size()));
    manualObject_->estimateIndexCount(static_cast<uint32>(lineIndices.size()));

    for (std::vector<VertexPair>::iterator i = lineVertices.begin();
         i != lineVertices.end(); ++i) {
      manualObject_->position(i->first);
      manualObject_->colour(i->second);
    }

    for (std::vector<int>::iterator i = lineIndices.begin();
         i != lineIndices.end(); ++i) {
      manualObject_->index(*i);
    }
  } else {
    manualObject_->position(Vector3::ZERO);
    manualObject_->colour(ColourValue::ZERO);
    manualObject_->index(0);
  }
  manualObject_->end();

  manualObject_->beginUpdate(1);
  if (triangleVertices.size() > 0 && isEnabled) {
    manualObject_->estimateVertexCount(
        static_cast<uint32>(triangleVertices.size()));
    manualObject_->estimateIndexCount(
        static_cast<uint32>(triangleIndices.size()));
    for (std::vector<VertexPair>::iterator i = triangleVertices.begin();
         i != triangleVertices.end(); ++i) {
      manualObject_->position(i->first);
      manualObject_->colour(i->second.r, i->second.g, i->second.b, fillAlpha);
    }

    for (std::vector<int>::iterator i = triangleIndices.begin();
         i != triangleIndices.end(); ++i) {
      manualObject_->index(*i);
    }
  } else {
    manualObject_->position(Vector3::ZERO);
    manualObject_->colour(ColourValue::ZERO);
    manualObject_->index(0);
  }
  manualObject_->end();

  manualObjectNode->_updateBounds();
}

void DebugDrawerAI::clear() {
  lineVertices.clear();
  triangleVertices.clear();
  lineIndices.clear();
  triangleIndices.clear();
  linesIndex = 0;
  trianglesIndex = 0;
}

int DebugDrawerAI::addLineVertex(const Vector3& vertex,
                                 const ColourValue& colour) {
  lineVertices.push_back(VertexPair(vertex, colour));
  return linesIndex++;
}

void DebugDrawerAI::addLineIndices(int index1, int index2) {
  lineIndices.push_back(index1);
  lineIndices.push_back(index2);
}

int DebugDrawerAI::addTriangleVertex(const Vector3& vertex,
                                     const ColourValue& colour) {
  triangleVertices.push_back(VertexPair(vertex, colour));
  return trianglesIndex++;
}

void DebugDrawerAI::addTriangleIndices(int index1, int index2, int index3) {
  triangleIndices.push_back(index1);
  triangleIndices.push_back(index2);
  triangleIndices.push_back(index3);
}

void DebugDrawerAI::addQuadIndices(int index1, int index2, int index3,
                                   int index4) {
  triangleIndices.push_back(index1);
  triangleIndices.push_back(index2);
  triangleIndices.push_back(index3);

  triangleIndices.push_back(index1);
  triangleIndices.push_back(index3);
  triangleIndices.push_back(index4);
}