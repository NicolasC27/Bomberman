//
// Created by root on 29/05/17.
//

#ifndef BOMBERMAN_AGAMEOBJECT_HPP
#define BOMBERMAN_AGAMEOBJECT_HPP


#include <OgreSceneManager.h>
#include <OgreVector2.h>
#include <OgreMovableObject.h>
#include <OgreEntity.h>
#include <OgreNode.h>
#include <OgreSceneNode.h>
#include "Collision.hpp"

class AGameObject {

 public:
  enum Object {
    NOTHING,
    WALL,
    BLOCK,
    BOMB,
    ITEM,
    CHARACTER
  };

  enum State {
    BREAKABLE,
    UNBREAKABLE
  };

  AGameObject(AGameObject::Object object);
  AGameObject(AGameObject::Object object, double r);
  virtual ~AGameObject();

 private:
  Object 		_type;

 public:
  void			setNode(Ogre::SceneNode *node);
  void 			setPosition(int x, int y, int z);

  void 			AttachObject();

  Object 		getType() const;
  Ogre::MovableObject 	*getObj() const;

  void 			setType(Object type);
  void 			setObj(Ogre::MovableObject *obj);
  void 			setSceneManager(Ogre::SceneManager *SceneManager);

 protected:

  Ogre::Real		_moveSpeed;
  static int		objectId;
  int			_id;

  Ogre::MovableObject	*_obj;
  Ogre::SceneManager 	*SceneManager;
  Ogre::SceneNode	*_node;

  Collision		*_collision;

 public:
  virtual void		createEntity() = 0;

  virtual std::string 	getName() const = 0;
  virtual State 	getState() const = 0;
  virtual std::string	getMaterialName() const = 0;
  virtual Ogre::Vector3 getScale() const = 0;
  virtual double	getPositionY() const = 0;

  virtual Ogre::SceneManager::PrefabType	getMeshPrefab() const = 0;
  virtual std::string				getMeshName() const = 0;

  virtual void					update(Ogre::Real) = 0;
};

#endif //BOMBERMAN_AGAMEOBJECT_HPP
