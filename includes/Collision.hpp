//
// collision.hh for indie_studio in /home/guilbo_m/rendu/cpp/cpp_indie_studio
//
// Made by Mathis Guilbon
// Login   <guilbo_m@epitech.net>
//
// Started on  Sun Jun 11 00:30:24 2017 Mathis Guilbon
// Last update Sun Jun 11 00:44:38 2017 Mathis Guilbon
//

#ifndef BOMBERMAN_COLLISION_HPP
#define BOMBERMAN_COLLISION_HPP

#include <OgreVector2.h>
#include <vector>

class Collision
{
  enum BoundingBoxType
  {
    SPHERE,
    PARALL
  };

 public:
  Collision(BoundingBoxType type);
  Collision(double r);
  Collision(Ogre::Vector2);
  ~Collision();

  Collision		&operator=(Collision const &);
  bool			operator==(Collision const &);

  BoundingBoxType	getType() const;

  Ogre::Vector2 	getOrigin() const;
  Ogre::Vector2		getV() const;
  double		getR() const;

  void			setOrigin(Ogre::Vector2 const &);

 private:
  Collision(Collision const &);
  Collision();

  void     		init();
  bool			StoS(Collision const &) const;
  bool			PtoP(Collision const &) const;
  bool			PtoS(Collision const &) const;

  BoundingBoxType	_type;

  Ogre::Vector2		_origin;
  Ogre::Vector2		_v;
  double    		_r;

  std::vector<int>  	collideType;
  std::vector<bool (Collision::*)(Collision const &) const>	doesCollide;
};

#endif //BOMBERMAN_COLLISION_HPP
