//
// Created by kitephx on 6/17/17.
//

#include "Objects/Player.hpp"

Ogre::Real			Player::getNextFireDelay() const
{
  return settings._nextFireDelay;
}

Ogre::Real			Player::getIntervFire() const
{
  return settings._intervFire;
}

int 				Player::getBombmax() const
{
  return settings._bombmax;
}

int 				Player::getDelaybomb() const
{
  return settings._delaybomb;
}

int 				Player::getPowerbomb() const
{
  return settings._powerbomb;
}

int				Player::getPoint() const
{
  return settings._points;
}

Ogre::Real			Player::getMovespeed() const
{
  return settings._movespeed;
}

Ogre::Real			Player::getProtectDelay() const
{
  return settings._protectDelay;
}

int	                        Player::getAbility() const
{
  return settings._ability;
}

int                             Player::getMode() const
{
  return settings._mode;
}


void 				Player::setNextFireDelay(Ogre::Real nextFireDelay)
{
  settings._nextFireDelay = nextFireDelay;
}

void 				Player::setIntervFire(Ogre::Real intervFire)
{
  settings._intervFire = intervFire;
}

void 				Player::setBombmax(int bombmax)
{
  settings._bombmax = bombmax;
}

void 				Player::setDelaybomb(Ogre::Real delaybomb)
{
  settings._delaybomb = delaybomb;
}

void 				Player::setPowerbomb(int powerbomb)
{
  settings._powerbomb = powerbomb;
}

void 				Player::setMovespeed(Ogre::Real movespeed)
{
  settings._movespeed = movespeed;
}

void				Player::setAbility(int	ability)
{
  settings._ability = ability;
}

void				Player::setPoints(int	points)
{
  settings._points = points;
}

void                            Player::setMode(int  mode)
{
  settings._mode = mode;
}

void	Player::powerUp()
{
  int temp;

  if ((temp = getPowerbomb()) < 8)
    setPowerbomb(temp + 1);
}

void    Player::maxBombUp()
{
  int temp;

  if ((temp = getBombmax()) < 8)
    setBombmax(temp + 1);
}

void    Player::speedUp()
{
  int temp;

  if ((temp = getMovespeed()) < PlayerSettings::BASIC_SPEED * 2)
    setMovespeed(temp + PlayerSettings::BASIC_SPEED / 4);
}

void    Player::throwing()
{
  setAbility(1);
}

void    Player::pushing()
{
  setAbility(2);
}

void    Player::godmode()
{
  setMode(1);
}

void    Player::ghostmode()
{
  setMode(2);
}

int 	Player::getID() const
{
  return _ID;
}
