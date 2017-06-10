//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_ACHARACTER_HPP
#define BOMBERMAN_ACHARACTER_HPP

#include "AGameObject.hpp"

class ACharacter : public AGameObject
{

 public:
  ACharacter(Object object);

  virtual ~ACharacter();

  void			createEntity();

  void 			move(Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt);

  std::string 		getName() const;
  State 		getState() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double		getPositionY() const;

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

};
#endif //BOMBERMAN_ACHARACTER_HPP
