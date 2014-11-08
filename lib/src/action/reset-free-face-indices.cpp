#include "action/reset-free-face-indices.hpp"
#include "action/unit/on.hpp"
#include "octree.hpp"
#include "partial-action/modify-winged-mesh.hpp"
#include "winged/face.hpp"
#include "winged/mesh.hpp"

struct ActionResetFreeFaceIndices::Impl {
  ActionUnitOn <WingedMesh> actions;

  void runUndo (WingedMesh& mesh) { this->actions.undo (mesh); }
  void runRedo (WingedMesh& mesh) { this->actions.redo (mesh); }

  void run (WingedMesh& mesh) {
    if (mesh.numFaces () > 0) {
      unsigned int nonFreeFaceIndex = mesh.octree ().someFaceRef ().index ();
      mesh.forEachFreeFaceIndex ([&] (unsigned int index) {
        this->actions.add <PAModifyWMesh> ()
                     .setIndex (mesh, index + 0, mesh.index (nonFreeFaceIndex + 0));
        this->actions.add <PAModifyWMesh> ()
                     .setIndex (mesh, index + 1, mesh.index (nonFreeFaceIndex + 1));
        this->actions.add <PAModifyWMesh> ()
                     .setIndex (mesh, index + 2, mesh.index (nonFreeFaceIndex + 2));
      });
    }
  }
};

DELEGATE_BIG3 (ActionResetFreeFaceIndices)
DELEGATE1 (void, ActionResetFreeFaceIndices, run, WingedMesh&)
DELEGATE1 (void, ActionResetFreeFaceIndices, runUndo, WingedMesh&)
DELEGATE1 (void, ActionResetFreeFaceIndices, runRedo, WingedMesh&)
