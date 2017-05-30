//
// Created by root on 29/05/17.
//

#ifndef BOMBERMAN_AGAMEOBJECT_HPP
#define BOMBERMAN_AGAMEOBJECT_HPP

#include <OgreVector2.h>

class AGameObject {
  enum object {
    NOTHING,
    BOMB,
    ITEM,
    BLOCK,
    CHARACTER
  };

 public:
  AGameObject(Ogre::Vector2 const &pos, object object = NOTHING);

  virtual ~AGameObject();

 private:
};

#endif //BOMBERMAN_AGAMEOBJECT_HPP
