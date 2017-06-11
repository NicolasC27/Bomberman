//
// Entity.cpp for entity in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Fri May 19 12:10:55 2017 Jon Aristeguy
// Last update Tue Jun  6 18:39:46 2017 Jon Aristeguy
//

#include "Entity.hh"

Direction::Direction()
{
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Direction::Direction(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Direction::~Direction(){}

Collision::Collision()
{
  this->x = 0;
  this->y = 0;
  this->z = 0;
  this->value.push_back(0);
  this->mode = 0;
}

Collision::Collision(double x, double y, double radius)
{
  this->x = x;
  this->y = y;
  this->z = 0;
  this->value.push_back(radius);
  this->mode = 0;
}

Collision::Collision(double x, double y, double width, double length)
{
  this->x = x;
  this->y = y;
  this->z = 0;
  this->value.push_back(width);
  this->value.push_back(length);
  this->mode = 1;
}

Collision::~Collision(){}

Collision &Collision::operator=(Collision const & other)
{
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->mode = other.mode;
  this->value.clear();
  for (unsigned int i = 0; i < other.value.size(); i++)
    this->value.push_back(other.value[i]);
  return (*this);
}

bool	Collision::operator==(Collision const & other) const
{
  //calcul de collision
  return (false);
}

Entity::Entity(const Collision &collision)
{
  this->collision = collision;
}

Entity::Entity(double x, double y, double radius)
{
  this->collision = Collision(x, y, radius);
}

Entity::Entity(double x, double y, double width, double length)
{
  this->collision= Collision(x, y, width, length);
}

Entity::~Entity(){}

void	Entity::die(){}

bool	Entity::move(const Direction &dir)
{
  //mouvement
  (void)dir;
  return (true);
}

Bomb::Bomb(double x, double y) : Entity(x, y, 0.5)
{
}

Bomb::~Bomb(){}

void	Bomb::explosion()
{
  //explosion
}

Player::Player(double x, double y) : Entity(x, y, 0.75)
{
  this->ability = 0;
  this->power = 1;
  this->range = 1;
  this->speed = 2;
  this->mode = 0;
  this->timer = 0;
  this->dir = Direction(0, 1, 0);
}

Player::~Player(){}

void	Player::die()
{
}

int	Player::getAbility() const
{
  return (this->ability);
}

int	Player::getPower() const
{
  return (this->ability);
}

int	Player::getRange() const
{
  return (this->ability);
}

int	Player::getSpeed() const
{
  return (this->ability);
}

int	Player::getMode() const
{
  return (this->ability);
}

void	Player::setAbility(int ability)
{
  this->ability = ability;
}

void    Player::setPower(int power)
{
  this->power = power;
}

void    Player::setRange(int range)
{
  this->range = range;
}

void    Player::setSpeed(int speed)
{
  this->speed = speed;
}

void	Player::setMode(int mode)
{
  this->mode = mode;
}
