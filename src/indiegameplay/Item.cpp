//
// Item.cpp for Item in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Thu Jun  1 14:46:35 2017 Jon Aristeguy
// Last update Thu Jun  1 16:57:44 2017 Jon Aristeguy
//

#include "Item.hh"

Powerup::Powerup(int x, int y) : Item(x, y)
{
}

Rangeup::Rangeup(int x, int y) : Item(x, y)
{
}

Speedup::Speedup(int x, int y) : Item(x, y)
{
}

Throwing::Throwing(int x, int y) : Item(x, y)
{
}

Pushing::Pushing(int x, int y) : Item(x, y)
{
}

Godmode::Godmode(int x, int y) : Item(x, y)
{
}

Ghostmode::Ghostmode(int x, int y) : Item(x, y)
{
}

void	Powerup::use(Player & player)
{
  int temp;
  
  if ((temp = player.getPower()) < 8)
    player.setPower(temp + 1);
}

void    Rangeup::use(Player & player)
{
  int temp;

  if ((temp = player.getRange()) < 8)
    player.setRange(temp + 1);
  
}

void    Speedup::use(Player & player)
{
  int temp;

  if ((temp = player.getSpeed()) < 8)
    player.setSpeed(temp + 1);
  
}

void    Throwing::use(Player & player)
{
  player.setAbility(1);
}

void    Pushing::use(Player & player)
{
  player.setAbility(2);
}

void    Godmode::use(Player & player)
{
  player.setMode(1);
}

void    Ghostmode::use(Player & player)
{
  player.setMode(2);
}

Item	*create_powerup(int x, int y)
{
  return (new Powerup(x, y));
}

Item    *create_rangeup(int x, int y)
{
  return (new Powerup(x, y));
}

Item    *create_speedup(int x, int y)
{
  return (new Powerup(x, y));
}

Item    *create_throwing(int x, int y)
{
  return (new Powerup(x, y));
}

Item    *create_pushing(int x, int y)
{
  return (new Powerup(x, y));
}

Item    *create_godmode(int x, int y)
{
  return (new Powerup(x, y));
}

Item    *create_ghostmode(int x, int y)
{
  return (new Powerup(x, y));
}

