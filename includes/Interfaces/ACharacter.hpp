//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_ACHARACTER_HPP
#define BOMBERMAN_ACHARACTER_HPP

#include <OIS/OIS.h>
#include <MapManager.hpp>
//#include "Controller/KeyController.hpp"
#include "AGameObject.hpp"

class ACharacter : public AGameObject
{

 public:
  enum ActionKeyCode {
    AT_UP,
    AT_DOWN,
    AT_LEFT,
    AT_RIGHT,
    AT_FIRE,
  };

  ACharacter(MapManager *map, Object object, int r);

  virtual ~ACharacter();

  virtual void	move(MapManager const &, Ogre::Vector3 const &vector, const Ogre::FrameEvent &evt) = 0;
  virtual void	action(MapManager const &, ActionKeyCode, const Ogre::FrameEvent &evt) = 0;

  void			createEntity();

  void 			update(Ogre::Real);

  std::string 		getName() const;
  State 		getState() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double		getPositionY() const;

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

  virtual const std::map<OIS::KeyCode, ActionKeyCode>	&getKeyCodeType() const = 0;


 protected:
  static int		objectId;

  std::map<OIS::KeyCode, ActionKeyCode> keyCodeType;
};

#endif //BOMBERMAN_ACHARACTER_HPP
