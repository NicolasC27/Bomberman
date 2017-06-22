//
// Created by kitephx on 6/17/17.
//

#include "Objects/Player.hpp"

int 				Player::getBombmax() const
{
  return settings._bombmax;
}

int 				Player::getCurrBomb() const
{
  return settings._currBomb;
}

int 				Player::getPowerbomb() const
{
  return settings._powerbomb;
}

int				Player::getPoint() const
{
  return settings._points;
}

int				Player::getMovespeed() const
{
  return settings._movespeed;
}

int 				Player::getBombType() const
{
  return settings._bombType;
}

void 				Player::setBombType(int bombType)
{
  settings._bombType = bombType;
}

void 				Player::setBombmax(int bombmax)
{
  settings._bombmax = bombmax;
}

void 				Player::setCurrBomb(int currBomb)
{
  settings._currBomb = currBomb;
}

void 				Player::setPowerbomb(int powerbomb)
{
  settings._powerbomb = powerbomb;
}

void 				Player::setMovespeed(Ogre::Real movespeed)
{
  settings._movespeed = movespeed;
}

void				Player::setPoints(int	points)
{
  settings._points = points;
}

void			Player::powerUp()
{
  int 			temp;

  if ((temp = getPowerbomb()) < 8)
    setPowerbomb(temp + 1);
}

void  			Player::maxBombUp()
{
  int 			temp;

  if ((temp = getBombmax()) < 8)
    {
      setBombmax(temp + 1);
      setCurrBomb(temp + 1);
    }
}

void    		Player::speedUp()
{
  int 			temp;

  if ((temp = getMovespeed()) < PlayerSettings::BASIC_SPEED * 2)
    setMovespeed(temp + PlayerSettings::BASIC_SPEED / 4);
}

void			Player::skullBomb()
{
  setBombType(Player::SKULLBOMB);
}

void			Player::laserBomb()
{
  setBombType(Player::LASERBOMB);
}

int			Player::getID() const
{
  return _ID;
}

