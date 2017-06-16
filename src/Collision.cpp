//
// collision.cpp for indie_studio in /home/guilbo_m/rendu/cpp/cpp_indie_studio
//
// Made by Mathis Guilbon
// Login   <guilbo_m@epitech.net>
//
// Started on  Wed May 31 13:32:38 2017 Mathis Guilbon
// Last update Wed Jun 14 14:23:44 2017 chalie_a
//

#include "Collision.hpp"

std::ostream	&operator<<(std::ostream &os, Collision const &coll)
{
  std::cout << "origin(" << coll.getOrigin().x << "," << coll.getOrigin().y << ") ";
  if (coll.getType() == Collision::SPHERE)
    std::cout << "type(SPHERE) radius(" << coll.getR() << ")";
  else
    std::cout << "type(PARALL) size(" << coll.getV().x << "," << coll.getV().y << ")";
  std::cout << std::endl;
  return (os);
}

Collision::Collision(Ogre::AxisAlignedBox const &box, Ogre::Vector3 const &pos)
  : _type(Collision::PARALL), _min(box.getMinimum()), _max(box.getMaximum()), _v(0, 0), _origin(0, 0)
{
  this->_v = Ogre::Vector2(_max.x - _min.x, _max.z - _min.z);
  this->_origin = Ogre::Vector2(_min.x + pos.x, _min.z + pos.z);
  this->init();
}

Collision::Collision(double r)
  : _type(Collision::SPHERE), _r(r), _origin(0, 0)
{
  this->init();
}

void		Collision::init()
{
  this->collideType.push_back(Collision::SPHERE + Collision::SPHERE);
  this->collideType.push_back(Collision::PARALL + Collision::PARALL);
  this->collideType.push_back(Collision::PARALL + Collision::SPHERE);
  this->doesCollide.push_back(&Collision::StoS);
  this->doesCollide.push_back(&Collision::PtoP);
  this->doesCollide.push_back(&Collision::PtoS);
}

Collision::~Collision()
{

}

Collision		&Collision::operator=(Collision const &with)
{
  this->_type = with.getType();

  if (this->_type == Collision::PARALL)
    this->_v = with.getV();
  else
    this->_r = with.getR();

  this->_origin = with.getOrigin();
}

bool			Collision::operator==(Collision const &with) const
{
  unsigned int 		i;

  for (i = 0; i < this->collideType.size(); ++i)
    {
      if (this->collideType[i] == this->_type + with.getType())
	break;
    }
  std::cout << *this << with << std::endl;
  if (i < this->collideType.size())
    return ((this->*this->doesCollide[i])(with));
  // type inconnue ou non géré ?
  return (false);
}

bool			Collision::operator!=(Collision const &with) const
{
  return (!(*this == with));
}

Collision::BoundingBoxType	Collision::getType() const
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

void			Collision::setOrigin(Ogre::Vector3 const &v)
{
  this->_origin = Ogre::Vector2(v.x + _min.x, v.z + _min.z);
}

bool			Collision::StoS(Collision const &with) const
{
  Ogre::Vector2 	withO(with.getOrigin());
  double		r = with.getR();
  int			d;

  d = (this->_origin.x - withO.x) * (this->_origin.x - withO.x);
  d += (this->_origin.y - withO.y) * (this->_origin.y - withO.y);

  if (d > (this->_r + r) * (this->_r + r))
    return (false);
  else
    return (true);
}

bool			Collision::PtoP(Collision const &with) const
{
  Ogre::Vector2 	withO(with.getOrigin());
  Ogre::Vector2 	withV(with.getV());

  return (((withO.x >= this->_origin.x + this->_v.x) ||
	   (withO.x + withV.x <= this->_origin.x) ||
	   (withO.y >= this->_origin.y + this->_v.y) ||
	   (withO.y + withV.y <= this->_origin.y)) ? false : true);
}

bool			Collision::PtoS(Collision const &with) const
{
  Ogre::Vector2		near;
  Ogre::Vector2    	sO;
  Ogre::Vector2		pO;
  Ogre::Vector2		pV;
  double		sR;
  double		d;

  if (this->_type == Collision::SPHERE)
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
  // Cercle center inside of rectangle
  /*if (Ogre::Vector2(pO.x, sO.x))

  if ((pO.x <= sO.x && sO.x <= pO.x + pV.x) &&
      (pO.y <= sO.y && sO.y <= pO.y + pV.y))
    return (false);*/
  near.x = fabs(pO.x - sO.x) > fabs(pO.x + pV.x - sO.x) ? pO.x + pV.x : pO.x;
  near.y = fabs(pO.y - sO.y) > fabs(pO.y + pV.y - sO.y) ? pO.y + pV.y : pO.y;
  d = (sO.x - near.x) * (sO.x - near.x) + (sO.y - near.y) * (sO.y - near.y);
  std::cout << "point le plus proche (" << near.x << "," << near.y << ") " <<
    "distance-to-center: " << d <<
    " r²: " << sR * sR << std::endl << std::endl;
  return ((d > sR * sR) ? false : true);
}
