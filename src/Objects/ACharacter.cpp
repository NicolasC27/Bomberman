//
// Created by nicolas on 07/06/17.
//

#include "Interfaces/ACharacter.hpp"

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
  return "Character" + std::to_string(_id);
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

