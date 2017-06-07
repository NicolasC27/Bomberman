//
// Leveldata.hh for LevelData in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Fri May 19 13:17:34 2017 Jon Aristeguy
// Last update Thu Jun  1 17:20:45 2017 Jon Aristeguy
//

#ifndef _LEVELDATA_HH_
# define _LEVELDATA_HH_

# include "Entity.hh"

class	Leveldata
{
  int	size;
  int	height;
  int	width;
  int	nbplayers;
  
  std::string	map;
  std::list<Player> players;
  std::list<Entity> entitys;
  Leveldata(std::string map, int height, int width);
  ~Leveldata();
  bool	addEntity(int id, int x, int y);
};

# endif /* _LEVELDATA_HH_ */
