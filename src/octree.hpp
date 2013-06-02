#ifndef DILAY_OCTREE
#define DILAY_OCTREE

#include "fwd-winged.hpp"
#include "fwd-glm.hpp"

class Triangle;
class OctreeNode;
class OctreeFaceIterator;
class ConstOctreeFaceIterator;
class OctreeNodeIterator;
class ConstOctreeNodeIterator;
class Ray;
class FaceIntersection;

/** Internal template for iterators over all faces of an octree */
template <class,class,class,class> struct OctreeFaceIteratorTemplate;

/** Internal template for iterators over all nodes of an octree */
template <class,class,class> struct OctreeNodeIteratorTemplate;

/** Internal template for iterators over all faces of a node */
template <class,class> struct OctreeNodeFaceIteratorTemplate;

/** Octree node interface */
class OctreeNode {
  public: 
    class Impl;

          OctreeNode               (Impl*);
          OctreeNode               (const OctreeNode&) = delete;
    const OctreeNode& operator=    (const OctreeNode&) = delete;

    void              deleteFace   (LinkedFace);
    void              intersectRay (const WingedMesh&, const Ray&, FaceIntersection&);
    unsigned int      numFaces     () const;
    int               depth        () const;
    const glm::vec3&  center       () const;
    float             width        () const;

  private:
    Impl* impl;
};

/** Octree main class */
class Octree { 
  public: 
    class Impl; 
    
          Octree            ();
          Octree            (const Octree&) = delete;
    const Octree& operator= (const Octree&) = delete;
         ~Octree            ();

    LinkedFace  insertFace   (const WingedFace&, const Triangle&);
    void        render       ();
    void        intersectRay (const WingedMesh&, const Ray&, FaceIntersection&);
    void        reset        ();
    void        reset        (const glm::vec3&, float);

    OctreeFaceIterator      faceIterator ();
    ConstOctreeFaceIterator faceIterator () const;
    OctreeNodeIterator      nodeIterator ();
    ConstOctreeNodeIterator nodeIterator () const;

  private:
    Impl* impl;
};

/** Internal classes for iterators over all faces of a node */
using OctreeNodeFaceIterator = OctreeNodeFaceIteratorTemplate 
                               <OctreeNode::Impl, LinkedFace>;

using ConstOctreeNodeFaceIterator = OctreeNodeFaceIteratorTemplate 
                                    <const OctreeNode::Impl, ConstLinkedFace>;

/** Iterator over all faces of an octree */
class OctreeFaceIterator {
  public: OctreeFaceIterator            (Octree::Impl&);
          OctreeFaceIterator            (const OctreeFaceIterator&);
    const OctreeFaceIterator& operator= (const OctreeFaceIterator&);
         ~OctreeFaceIterator            ();

    bool         hasFace            () const;
    LinkedFace   face               () const;
    void         next               ();
    int          depth              () const;

  private:
    using Impl = OctreeFaceIteratorTemplate < Octree::Impl, OctreeNode::Impl
                                            , OctreeNodeFaceIterator, LinkedFace>;
    Impl* impl;
};

/** Constant iterator over all faces of an octree */
class ConstOctreeFaceIterator {
  public: ConstOctreeFaceIterator            (const Octree::Impl&);
          ConstOctreeFaceIterator            (const ConstOctreeFaceIterator&);
    const ConstOctreeFaceIterator& operator= (const ConstOctreeFaceIterator&);
         ~ConstOctreeFaceIterator            ();
     
    bool            hasFace            () const;
    ConstLinkedFace face               () const;
    void            next               ();
    int             depth              () const;

  private:
    using Impl = OctreeFaceIteratorTemplate < const Octree::Impl, const OctreeNode::Impl
                                            , ConstOctreeNodeFaceIterator
                                            , ConstLinkedFace>;
    Impl* impl;
};

/** Iterator over all nodes of an octree */
class OctreeNodeIterator {
  public: OctreeNodeIterator            (Octree::Impl&);
          OctreeNodeIterator            (const OctreeNodeIterator&);
    const OctreeNodeIterator& operator= (const OctreeNodeIterator&);
         ~OctreeNodeIterator            ();

    bool         hasNode () const;
    OctreeNode&  node    () const;
    void         next    ();

  private:
    using Impl = OctreeNodeIteratorTemplate < Octree::Impl, OctreeNode
                                            , OctreeNode::Impl >;
    Impl* impl;
};

/** Constant iterator over all nodes of an octree */
class ConstOctreeNodeIterator {
  public: ConstOctreeNodeIterator            (const Octree::Impl&);
          ConstOctreeNodeIterator            (const ConstOctreeNodeIterator&);
    const ConstOctreeNodeIterator& operator= (const ConstOctreeNodeIterator&);
         ~ConstOctreeNodeIterator            ();

    bool              hasNode () const;
    const OctreeNode& node    () const;
    void              next    ();

  private:
    using Impl = OctreeNodeIteratorTemplate < const Octree::Impl, const OctreeNode
                                            , const OctreeNode::Impl >;
    Impl* impl;
};

#endif
