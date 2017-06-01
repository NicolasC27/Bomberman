//
// collision.cpp for indie_studio in /home/guilbo_m/rendu/cpp/cpp_indie_studio
// 
// Made by Mathis Guilbon
// Login   <guilbo_m@epitech.net>
// 
// Started on  Wed May 31 13:32:38 2017 Mathis Guilbon
// Last update Thu Jun  1 19:32:33 2017 Mathis Guilbon
//

#include "collision.hh"

void		Collision::init()
{
  this->collideType.push_back(SPHERE + SPHERE);
  this->collideType.push_back(PARALL + PARALL);
  this->collideType.push_back(PARALL + SPHERE);
  this->doesCollide.push_back(&Collision::StoS);
  this->doesCollide.push_back(&Collision::PtoP);
  this->doesCollide.push_back(&Collision::PtoS);
}

Collision::Collision(Ogre::Vector2 v)
  : _type(PARALL), _v(v), _origin(0, 0)
{
  this->init();
}

Collision::Collision(double r)
  : _type(SPHERE), _r(r), _origin(0, 0)
{
  this->init();
}

Collision::~Collision()
{

}

Collision		&Collision::operator=(Collision const &with)
{
  this->_type = with.getType();
  if (this->_type == PARALL)
    this->_v = with.getV();
  else
    this->_r = with.getR();
  this->_origin = with.getOrigin();
}

bool			Collision::operator==(Collision const &with)
{
  unsigned int		i;

  for (i = 0; i < this->collideType.size(); ++i)
    {
      if (this->collideType[i] == this->_type + with.getType())
	break;
    }
  std::cout << "op n°" << i << std::endl;
  if (i < this->collideType.size())
    return ((this->*(this->doesCollide[i]))(with));
  // type inconnue ou non géré ?
  return (false);
}

BoundingBoxType		Collision::getType() const
{
  return (this->_type);
}

Ogre::Vector2		Collision::getV() const
{
  return (this->_v);
}

double			Collision::getR() const
{
  return (this->_r);
}

Ogre::Vector2		Collision::getOrigin() const
{
  return (this->_origin);
}

void			Collision::setOrigin(Ogre::Vector2 const v)
{
  this->_origin = v;
}

bool			Collision::StoS(Collision const &with) const
{
  Ogre::Vector2		withO(with.getOrigin());
  double		r = with.getR();
  int			d;
  
  d = (this->_origin.x - withO.x) * (this->_origin.x - withO.x);
  d += (this->_origin.y - withO.y) * (this->_origin.y - withO.y);
  if (d > (this->_r + r) * (this->_r + r))
    return (false);
  return (true);
}

bool			Collision::PtoP(Collision const &with) const
{
  Ogre::Vector2		withO(with.getOrigin());
  Ogre::Vector2		withV(with.getV());

  if ((withO.x >= this->_origin.x + this->_v.x) ||
      (withO.x + withV.x <= this->_origin.x) ||
      (withO.y >= this->_origin.y + this->_v.y) ||
      (withO.y + withV.y <= this->_origin.y))
    return (false);
  return (true);
}

bool			Collision::PtoS(Collision const &with) const
{
  Ogre::Vector2		sO;
  double		sR;
  Ogre::Vector2		pO;
  Ogre::Vector2		pV;
  Ogre::Vector2		near;
  double		d;
  
  if (this->_type == SPHERE)
    {
      sO = this->getOrigin();
      sR = this->getR();
      pO = with.getOrigin();
      pV = with.getV();
    }
  else
    {
      sO = with.getOrigin();
      sR = with.getR();
      pO = this->getOrigin();
      pV = this->getV();
    }
  near.x = fabs(pO.x - sO.x) > fabs(pO.x + pV.x - sO.x) ? pO.x + pV.x : pO.x;
  near.y = fabs(pO.y - sO.y) > fabs(pO.y + pV.y - sO.y) ? pO.y + pV.y : pO.y;
  d = (sO.x - near.x) * (sO.x - near.x) + (sO.y - near.y) * (sO.y - near.y);
  if (d > sR * sR)
    return (false);
  return (true);
}
