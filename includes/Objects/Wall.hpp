//
// Created by nicolas on 30/05/17.
//

#ifndef BOMBERMAN_GROUND_H
#define BOMBERMAN_GROUND_H

#include <OgreSceneManager.h>
#include "Interfaces/AGameObject.hpp"

class Wall : public AGameObject
{
 public:
  Wall(MapManager *map, State type);
  virtual ~Wall();

  void			setState(State state);

  State			getState() const;
  std::string 		getName() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double	 	getPositionY() const;

  void			setPositionY(int positionY);

  void			update(Ogre::Real);
  virtual void		destroy();

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

 protected:
  void			createEntity();

 private:
  Ogre::Real		_moveSpeed;
  int			_positionY;
  State 		_state;
  std::string		_name;
};

#endif //BOMBERMAN_GROUND_H
