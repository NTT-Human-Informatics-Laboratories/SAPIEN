#pragma once
#include "id_generator.h"
#include <PxPhysicsAPI.h>
#include <string>
#include <vector>

namespace sapien {
using namespace physx;

namespace Renderer {
class IPxrRigidbody;
};

class SScene;

class SActorBase {
protected:
  std::string mName = "";
  physx_id_t mId = 0;
  SScene *mParentScene = nullptr;
  std::vector<Renderer::IPxrRigidbody *> mRenderBodies;
  std::vector<Renderer::IPxrRigidbody *> mCollisionBodies;

  uint32_t mCol1 = 0;
  uint32_t mCol2 = 0;
  uint32_t mCol3 = 0;

  uint32_t mRenderMode = 0;

public:
  void setRenderMode(uint32_t mode);
  uint32_t getRenderMode();

  inline std::string getName() { return mName; };
  inline void setName(const std::string &name) { mName = name; }
  inline physx_id_t getId() { return mId; }
  inline SScene *getScene() { return mParentScene; }

  PxTransform getPose();
  inline uint32_t getCollisionGroup1() { return mCol1; }
  inline uint32_t getCollisionGroup2() { return mCol2; }
  inline uint32_t getCollisionGroup3() { return mCol3; }

  // render
  std::vector<Renderer::IPxrRigidbody *> getRenderBodies();
  std::vector<Renderer::IPxrRigidbody *> getCollisionBodies();
  void updateRender(PxTransform const &pose);

  virtual PxRigidActor *getPxActor() = 0;
  virtual ~SActorBase() = default;

protected:
  SActorBase(physx_id_t id, SScene *scene, std::vector<Renderer::IPxrRigidbody *> renderBodies,
             std::vector<Renderer::IPxrRigidbody *> collisoinBodies);
};

class SActorDynamicBase : public SActorBase {

public:
  PxVec3 getVel();
  PxVec3 getAngularVel();
  PxReal getMass();
  PxVec3 getInertia();
  PxTransform getCMassLocalPose();

  PxRigidBody *getPxActor() override = 0;
  virtual void addForceAtPoint(PxVec3 const &force, PxVec3 const &pos);

protected:
  using SActorBase::SActorBase;
};

} // namespace sapien