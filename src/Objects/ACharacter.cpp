//
// Created by nicolas on 07/06/17.
//

#include "Interfaces/ACharacter.hpp"
#include <OGRE/OgreEntity.h>


ACharacter::ACharacter(AGameObject::Object object) : AGameObject(object)
{

}


ACharacter::~ACharacter()
{

}

void ACharacter::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshName());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
  _node->pitch(Ogre::Degree(90));
}

std::string ACharacter::getName() const
{
  return "Mutant";
}

AGameObject::State ACharacter::getState() const
{
  return UNBREAKABLE;
}

std::string ACharacter::getMaterialName() const
{
  return ("mutant_M");
}

Ogre::Vector3 ACharacter::getScale() const
{

  return Ogre::Vector3(1, 1, 1);
}

double ACharacter::getPositionY() const
{
  return 0;
}

Ogre::SceneManager::PrefabType ACharacter::getMeshPrefab() const
{
  return Ogre::SceneManager::PT_CUBE;
}

std::string ACharacter::getMeshName() const
{
  return "MutantMesh.mesh";
}

void ACharacter::move(Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt)
{

  static Ogre::AnimationState *mAnimationState;

  mAnimationState = dynamic_cast<Ogre::Entity*>(_obj)->getAnimationState("my_animation");
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);

  Ogre::Real mMoveSpeed  =400;
  Ogre::Vector3 translateVector = evt.timeSinceLastFrame * mMoveSpeed * vector;

  mAnimationState->addTime(evt.timeSinceLastFrame * 1.5);
  _node->translate(translateVector);
}
