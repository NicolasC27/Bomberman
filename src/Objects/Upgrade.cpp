//
// Item.cpp for Item in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Thu Jun  1 14:46:35 2017 Jon Aristeguy
// Last update Thu Jun 15 12:58:45 2017 Jon Aristeguy
//

#include "Item.hh"

void	Player::powerup()
{
  int temp;
  
  if ((temp = player.getPower()) < 8)
    player.setPower(temp + 1);
}

void    Player::rangeup()
{
  int temp;

  if ((temp = player.getRange()) < 8)
    player.setRange(temp + 1);
  
}

void    Player::speedup()
{
  int temp;

  if ((temp = player.getSpeed()) < 8)
    player.setSpeed(temp + 1);
  
}

void    Player::throwing()
{
  player.setAbility(1);
}

void    Player::pushing()
{
  player.setAbility(2);
}

void    Player::godmode()
{
  player.setMode(1);
}

void    Player::ghostmode()
{
  player.setMode(2);
}
