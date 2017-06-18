//
// Created by nicolas on 07/06/17.
//

#include <Ogre.h>
#include "Interfaces/ACharacter.hpp"
#include <Ogre.h>

ACharacter::ACharacter(MapManager *map, AGameObject::Object object, int r) : AGameObject(map, object, r)
{

}

ACharacter::~ACharacter()
{

}

void	 		ACharacter::update(Ogre::Real dt)
{

}

void 			ACharacter::createEntity()
{
  _obj = SceneManager->createEntity(getName(), getMeshName());
  dynamic_cast <Ogre::Entity*>(_obj)->setMaterialName(this->getMaterialName());
  static_cast<Ogre::Entity*>(_obj)->getMesh()->_setBounds(Ogre::AxisAlignedBox(-35, 0.0, -35, 35, 100, 35));
}

std::string 		ACharacter::getName() const
{
  return "Character" + std::to_string(_id);
}

AGameObject::State 	ACharacter::getState() const
{
  return UNBREAKABLE_BLOCK;
}

std::string 		ACharacter::getMaterialName() const
{
  static int 		i = 1;

  if (i == 1)
    {
      i += 1;
      return ("mutant_M");
    }
  else
    {
      i = 0;
      return ("mutant_M_red");
    }
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
