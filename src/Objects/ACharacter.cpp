//
// Created by nicolas on 07/06/17.
//

#include "Interfaces/ACharacter.hpp"
#include <OGRE/OgreEntity.h>


ACharacter::ACharacter(AGameObject::Object object, int r) : AGameObject(object, r)
{

}


ACharacter::~ACharacter()
{

}

void ACharacter::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshName());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());

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

  return Ogre::Vector3(0.8, 0.8, 0.8);
}

double ACharacter::getPositionY() const
{
  return (-50);
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

  Ogre::Real mMoveSpeed  = 400;
  Ogre::Vector3 translateVector = 	vector;

  Collision *test;

  test = new Collision((Ogre::Vector2(100, 100)));

  test->setOrigin(Ogre::Vector2(100, 100));
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);

  _node->translate(translateVector);
  //Rotate the object to the moving direction

  _collision->setOrigin(Ogre::Vector2(_node->getPosition().x, _node->getPosition().z));
  if (_collision == test)
    std::cout << "COLLISION" << std::endl;
  if (translateVector != Ogre::Vector3::ZERO)
    {

      Ogre::Vector3 src = _node->getOrientation() * Ogre::Vector3::UNIT_Z;
      Ogre::Vector3 mDirection = vector;
      mDirection.normalise();

      if ((1.0f + src.dotProduct(mDirection)) < 0.0001f)
	{
	  _node->yaw(Ogre::Degree(180));
	} else
	{
	  Ogre::Quaternion quat = src.getRotationTo(mDirection);
	  _node->rotate(quat);

	} // else
    }
  mAnimationState->addTime(evt.timeSinceLastFrame * 1.5);
  std::cout << "x : " << _node->getPosition().x << "z: " << _node->getPosition().z << std::endl;

}
