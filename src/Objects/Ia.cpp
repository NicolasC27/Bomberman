//
// Ia.cpp for Ia in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Thu Jun 15 15:29:04 2017 Jon Aristeguy
// Last update Thu Jun 15 15:29:04 2017 Jon Aristeguy
//

Ogre::Vector3	in_danger(MapManager *map, Player *ia)
{
  Ogre::Vector3	res;

  for (unsigned int i = 0; i < 11, i++)
    {

    }
  
}

Ogre::Vector3	attack_dir(MapManager *map, Player *ia, Player *target)
{
  Ogre::Vector3 dir;
  Ogre::Vector3 res(1, 1, 0);
  
  dir = target->_node->getPosition() - ia->_node->getPosition();
  if (dir.x > dir.y)
    res.y = abs(dir.y) / abs(dir.x);
  else
    res.x = abs(dir.x) / abs(dir.y);
  res.x *= (dir.x > 0) ? 1 : -1;
  res.y *= (dir.y > 0) ? 1 : -1;
  return (res);
}

AGameObject	*get_target(MapManager *map, Player *ia)
{
  AGameObject	*target;
  double	dist;
  double	distmin;
  Ogre::Vector3	playerpos;
  Ogre::Vector3	targetpos;

  distmin = 0;
  playerpos = ia->_node->getPosition();
  for(unsigned int i = 0; i < map->_character; i++)
    {
      targetpos = map->_character->_node->getPosition();
      dist = sqrt(pow(targetpos.x - playerpos.x, 2) +
		  pow(targetpos.x - playerpos.x, 2));
      if (dist < distmin && ia != map->_character)
	{
	  distmin = dist;
	  target = map->_character;
	}
    }
  return (target);
}

Ogre::Vector3	Player::Ia(MapManager *map)
{
  AGameObject	*target;
  Ogre::Vector3	dir;
  Ogre::Vector3 pos;

  pos = this->_node->getPosition();
  target = get_target(map, this);
  dir = attack_dir(map, this, target);
  if (is_blocked(map, pos))
    this->
  dir = in_danger(map, this, target, dir);
  return (dir);
}
  