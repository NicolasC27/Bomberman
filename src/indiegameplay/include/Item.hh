//
// Item.hh for Item in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Thu Jun  1 11:45:58 2017 Jon Aristeguy
// Last update Thu Jun  1 17:20:42 2017 Jon Aristeguy
//

#ifndef _ITEM_HH_
#  define _ITEM_HH_

#include "Entity.hh"

class   Powerup : public Item
{
public:
  Powerup(double x, double y);
  void  use(Player & player);
};

class   Rangeup : public Item
{
public:
  Rangeup(double x, double y);
  void  use(Player & player);
};

class   Speedup : public Item
{
public:
  Speedup(double x, double y);
  void  use(Player & player);
};

class   Throwing : public Item
{
public:
  Throwing(double x, double y);
  void  use(Player & player);
};

class   Pushing : public Item
{
public:
  Pushing(double x, double y);
  void  use(Player & player);
};

class   Godmode : public Item
{
public:
  Godmode(double x, double y);
  void  use(Player & player);
};

class   Ghostmode : public Item
{
public:
  Ghostmode(double x, double y);
  void  use(Player & player);
};


#endif /* _ITEM_HH_ *µ
