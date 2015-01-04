#ifndef DILAY_OCTREE
#define DILAY_OCTREE

#include <functional>
#include <glm/fwd.hpp>
#include <unordered_map>
#include "macro.hpp"

class AffectedFaces;
class Camera;
class Id;
class OctreeNode;
class PrimRay;
class PrimSphere;
class PrimTriangle;
class WingedEdge;
class WingedFace;
class WingedFaceIntersection;
class WingedMesh;

struct OctreeStatistics {
  typedef std::unordered_map <int, unsigned int> DepthMap;

  unsigned int numNodes;
  unsigned int numFaces;
  unsigned int numDegeneratedFaces;
  unsigned int numFreeFaceIndices;
  int          minDepth;
  int          maxDepth;
  unsigned int maxFacesPerNode;
  DepthMap     numFacesPerDepth;
  DepthMap     numNodesPerDepth;
};

class OctreeNode {
  public: 
    class Impl;

    OctreeNode            (Impl*);
    DELETE_COPYMOVEASSIGN (OctreeNode)

    int               depth      () const;
    const glm::vec3&  center     () const;
    float             width      () const;

  private:
    friend class Octree;
    Impl* impl;
};

class Octree { 
  public: 
    DECLARE_BIG4MOVE (Octree)

    void             setupRoot            (const glm::vec3&, float);
    WingedFace&      addFace              (const PrimTriangle&);
    WingedFace&      addFace              (unsigned int, WingedEdge*, const PrimTriangle&);
    WingedFace&      realignFace          (WingedFace&, const PrimTriangle&, bool* = nullptr);
    void             deleteFace           (WingedFace&);
    WingedFace*      face                 (unsigned int) const;
    void             render               (const Camera&);
    bool             intersects           (WingedMesh&, const PrimRay&, WingedFaceIntersection&);
    bool             intersects           (const WingedMesh&, const PrimSphere&, AffectedFaces&);
    void             reset                ();
    void             shrinkRoot           ();
    bool             hasRoot              () const;
    unsigned int     numFaces             () const;
    unsigned int     numDegeneratedFaces  () const;
    unsigned int     numFreeFaceIndices   () const;
    unsigned int     numIndices           () const;
    OctreeStatistics statistics           () const;
    WingedFace*      someFace             () const;
    WingedFace*      someDegeneratedFace  () const;
    glm::vec3        avgCenter            () const;

    void             forEachFace          (const std::function <void (WingedFace&)>&) const;
    void             forEachFreeFaceIndex (const std::function <void (unsigned int)>&) const;

    SAFE_REF1_CONST (WingedFace,face,unsigned int)
    SAFE_REF_CONST  (WingedFace,someFace)

  private:
    IMPLEMENTATION
};

#endif
