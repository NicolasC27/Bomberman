//
// collision.hh for indie_studio in /home/guilbo_m/rendu/cpp/cpp_indie_studio
//
// Made by Mathis Guilbon
// Login   <guilbo_m@epitech.net>
//
// Started on  Sun Jun 11 00:30:24 2017 Mathis Guilbon
// Last update Wed Jun 14 14:24:02 2017 chalie_a
//

#ifndef BOMBERMAN_COLLISION_HPP
#define BOMBERMAN_COLLISION_HPP

#include <OgreVector2.h>
#include <vector>
#include <iostream>
#include <OgreAxisAlignedBox.h>

class Collision
{
 public:
  enum BoundingBoxType
    {
      SPHERE,
      PARALL
    };

  Collision(Collision::BoundingBoxType type);
  Collision(double r);
  Collision(Ogre::AxisAlignedBox const &, Ogre::Vector3 const &);
  ~Collision();

  Collision		&operator=(Collision const &);
  bool			operator==(Collision const &) const;
  bool			operator!=(Collision const &) const;

  Collision::BoundingBoxType	getType() const;

  Ogre::Vector2 	getOrigin() const;
  Ogre::Vector2		getV() const;
  double		getR() const;

  void			setOrigin(Ogre::Vector3 const &);

private:
  Collision(Collision const &);
  Collision();

  void     		init();

  Collision::BoundingBoxType	_type;

  Ogre::Vector3		_min;
  Ogre::Vector3		_max;
  Ogre::Vector2		_origin;
  Ogre::Vector2		_v;
  double    		_r;

  bool			StoS(Collision const &) const;
  bool			PtoP(Collision const &) const;
  bool			PtoS(Collision const &) const;

  std::vector<int>  	collideType;
  std::vector<bool (Collision::*)(Collision const &) const>	doesCollide;
};

std::ostream	&operator<<(std::ostream &, Collision const &);

#endif //BOMBERMAN_COLLISION_HPP
