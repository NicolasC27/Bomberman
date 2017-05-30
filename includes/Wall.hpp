//
// Created by nicolas on 30/05/17.
//

#ifndef BOMBERMAN_WALL_H
#define BOMBERMAN_WALL_H

#include "AGameObject.hpp"

class Wall : public AGameObject
{
 public:

  Wall(State type);
  virtual ~Wall();

 private:
  State 	_state;

 public:
  void	setState(State state);
  State	getState() const;

};
#endif //BOMBERMAN_WALL_H
