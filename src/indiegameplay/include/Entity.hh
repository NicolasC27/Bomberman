//
// Entity.hh for Entity in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Fri May 19 11:31:25 2017 Jon Aristeguy
// Last update Tue Jun  6 18:25:35 2017 Jon Aristeguy
//

#ifndef _ENTITY_HH_
# define _ENTITY_HH_

#include <vector>

class Item;

class	Direction
{
public:
  double	x;
  double	y;
  double	z;

  Direction();
  Direction(double x, double y, double z);
  ~Direction();
};

class	Collision
{
  double	x;
  double	y;
  double	z;
  std::vector<double> value;
  bool	mode;
public:
  Collision();
  Collision(double x, double y, double radius);
  Collision(double x, double y, double width, double length);
  ~Collision();
  Collision	&operator=(Collision const &);
  bool		operator==(Collision const &) const;
  
};

class	Entity
{

  Collision	collision;

public:
  Entity(double x, double y, double radius);
  Entity(double x, double y, double width, double length);
  Entity(const Collision &collision);
  virtual ~Entity() = 0;
  bool		move(const Direction &dir);
  virtual void	die();
};

class	Bomb : public Entity
{
  int		timer;
  double	speed;
  Direction	dir;

  Bomb(double x, double y);
  ~Bomb();
  void		explosion();
};

class	Player : public	Entity
{
  int		ability;
  int		power;
  int		range;
  int		speed;
  int		mode;
  int		timer;
  Direction	dir;
public:
  Player(double x, double y);
  ~Player();
  int		getAbility() const;
  int		getPower() const;
  int		getRange() const;
  int		getSpeed() const;
  int		getMode() const;
  void		setAbility(int);
  void          setPower(int);
  void          setRange(int);
  void          setSpeed(int);
  void          setMode(int);
  
  
  void		getItem(Item item);
  void		useAbility();
  void		die();
};

class	Item : public Entity
{
public:
  Item(double x, double y);
  ~Item();
  virtual void	use(Player & player);
  void		die();
};

class	Block : public Entity
{
  Block(double x, double y);
  ~Block();
  void	die();
};

# endif /* _ENTITY_HH_ */
