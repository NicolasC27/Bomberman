//
// Created by root on 29/05/17.
//

#ifndef BOMBERMAN_AGAMEOBJECT_HPP
#define BOMBERMAN_AGAMEOBJECT_HPP

#include <OgreVector2.h>

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

  virtual State getState() const = 0;
};

#endif //BOMBERMAN_AGAMEOBJECT_HPP
