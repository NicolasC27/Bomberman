//
// Created by kitephx on 6/17/17.
//

#include "Objects/Player.hpp"

float 				Player::getNextFireDelay() const
{
  return settings->_nextFireDelay;
}

float 				Player::getIntervFire() const
{
  return settings->_intervFire;
}

int 				Player::getBombmax() const
{
  return settings->_bombmax;
}

int 				Player::getDelaybomb() const
{
  return settings->_delaybomb;
}

int 				Player::getPowerbomb() const
{
  return settings->_powerbomb;
}

float 				Player::getMovespeed() const
{
  return settings->_movespeed;
}

float 				Player::getProtectDelay() const
{
  return settings->_protectDelay;
}

void 				Player::setNextFireDelay(Ogre::Real nextFireDelay)
{
  settings->_nextFireDelay = nextFireDelay;
}

void 				Player::setIntervFire(Ogre::Real intervFire)
{
  settings->_intervFire = intervFire;
}

void 				Player::setBombmax(int bombmax)
{
  settings->_bombmax = bombmax;
}

void 				Player::setDelaybomb(Ogre::Real delaybomb)
{
  settings->_delaybomb = delaybomb;
}

void 				Player::setPowerbomb(int powerbomb)
{
  settings->_powerbomb = powerbomb;
}

void 				Player::setMovespeed(Ogre::Real movespeed)
{
  settings->_movespeed = movespeed;
}
