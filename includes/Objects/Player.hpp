//
// Created by nicolas on 07/06/17.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "Interfaces/ACharacter.hpp"

class Player : public ACharacter
{

 public:
  Player(Object object);

  virtual ~Player();
};
#endif //BOMBERMAN_PLAYER_HPP
