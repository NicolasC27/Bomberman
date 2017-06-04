//
// Created by root on 29/05/17.
//

#ifndef BOMBERMAN_AGAMEOBJECT_HPP
#define BOMBERMAN_AGAMEOBJECT_HPP

#include <OgreVector2.h>
#include <OgreMovableObject.h>

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

  AGameObject();
  AGameObject(Object object = NOTHING);
  virtual ~AGameObject();

 private:
  Object 		_type;

 public:
  Object 		getType() const;
  void 			setType(Object type);

  virtual State 	getState() const = 0;
  virtual std::string 	getName() const = 0;

  virtual void		createEntity() = 0;
  void		setNode(Ogre::SceneNode *node);
  void 		setPosition(int x, int y, int z);
  void 		AttachObject();
  void setObj(Ogre::MovableObject *obj);

 protected:

  /**
   * Last object id
   */
  static int 	objectId;
  int		_id;

  Ogre::MovableObject	*_obj;
 public:
  Ogre::MovableObject *getObj() const;

 protected:
  Ogre::SceneManager 	*SceneManager;
  Ogre::SceneNode	*_node;
 public:
  void setSceneManager(Ogre::SceneManager *SceneManager);
};

#endif //BOMBERMAN_AGAMEOBJECT_HPP
