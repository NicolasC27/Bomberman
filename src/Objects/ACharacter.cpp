//
// Created by nicolas on 07/06/17.
//

#include "Interfaces/ACharacter.hpp"
#include <Ogre.h>

ACharacter::ACharacter(AGameObject::Object object, int r) : AGameObject(object, r)
{
}

ACharacter::~ACharacter()
{

}

void	 		ACharacter::update()
{

}

void 			ACharacter::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshName());
  static_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
  static_cast<Ogre::Entity*>(_obj)->getMesh()->_setBounds(Ogre::AxisAlignedBox(-125.152 * 0.3, -0.594098, -34.2034, 149.101 * 0.3, 185.54, 36.3049));
  //static_cast<Ogre::Entity*>(_obj)->getMesh()->_setBounds(Ogre::AxisAlignedBox(-125.152 * 0.35, 0.0, -34.2034 * 0.35, 149.101 * 0.35, 100, 36.3049 * 0.35));
}

std::string 		ACharacter::getName() const
{
  return "Character" + std::to_string(_id);
}

AGameObject::State 	ACharacter::getState() const
{
  return UNBREAKABLE;
}

std::string 		ACharacter::getMaterialName() const
{
  return ("mutant_M");
}

Ogre::Vector3	 	ACharacter::getScale() const
{

  return Ogre::Vector3(0.7, 0.7, 0.7);
}

double 			ACharacter::getPositionY() const
{
  return (-50);
}

std::string		ACharacter::getMeshName() const
{
  return "MutantMesh.mesh";
}

Ogre::SceneManager::PrefabType	ACharacter::getMeshPrefab() const
{
  return Ogre::SceneManager::PT_CUBE;
}
