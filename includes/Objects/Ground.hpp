//
// Created by nicolas on 30/05/17.
//

#ifndef BOMBERMAN_WALL_H
#define BOMBERMAN_WALL_H

#include <OgreSceneManager.h>
#include "Interfaces/AGameObject.hpp"


class Ground : public AGameObject
{
  Ogre::MaterialPtr	mMaterial;
  Ogre::TexturePtr 	mTexture;

  State 		_state;
  std::string		_name;

 public:
  Ground(State type);
  virtual ~Ground();

  void 			CreateOwnEntity();

  void			setState(State state);

  State			getState() const;
  std::string 		getName() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double	 	getPositionY() const;


  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

 protected:
  void			createEntity();
};

#endif //BOMBERMAN_WALL_H
