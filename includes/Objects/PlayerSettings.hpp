//
// Created by kitephx on 6/17/17.
//

#ifndef BOMBERMAN_PLAYERINFO_HPP
#define BOMBERMAN_PLAYERINFO_HPP

#include "Item.hpp"

struct PlayerSettings
{
  int		_movespeed;
  int		_bombmax;
  int 		_currBomb;
  int		_powerbomb;
  int 		_points;
  int 		_bombType;

  const float DEFAULT_PROTECTION_DELAY = 1;
  static const int   BASIC_SPEED = 400;
};

#endif //BOMBERMAN_PLAYERINFO_HPP
