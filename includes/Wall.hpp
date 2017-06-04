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
  std::string	_name;

 public:
  void		setState(State state);
  State		getState() const;
  std::string 	getName() const;

 protected:
  void		createEntity();
};
#endif //BOMBERMAN_WALL_H
