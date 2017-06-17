//
// Created by kitephx on 6/17/17.
//

#ifndef BOMBERMAN_PLAYERINFO_HPP
#define BOMBERMAN_PLAYERINFO_HPP

struct PlayerSettings
{
  Ogre::Real	_nextFireDelay;
  Ogre::Real	_intervFire;
  Ogre::Real	_delaybomb;
  Ogre::Real 	_movespeed;
  Ogre::Real 	_protectDelay;

  int		_bombmax;
  int		_powerbomb;

  const float DEFAULT_PROTECTION_DELAY = 1;
};

#endif //BOMBERMAN_PLAYERINFO_HPP
