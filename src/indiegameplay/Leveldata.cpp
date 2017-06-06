//
// Leveldata.cpp for Leveldata in /home/ariste_j/Projet/indiegameplay
// 
// Made by Jon Aristeguy
// Login   <ariste_j@epitech.net>
// 
// Started on  Fri May 19 13:30:20 2017 Jon Aristeguy
// Last update Wed May 24 16:34:57 2017 Jon Aristeguy
//

# include "Leveldata.hh"

Leveldata::Leveldata(std::string map, int height, int width)
{
  for (unsigned int i = 0; i < map.size(); i++)
    {
      if (map[i] != '0' && map[i] != '1')
	{
	  this->addEntity(map[i] - 48, i % width, i / width);
	  map[i] = '0';
	}
    }
  this->width = width;
  this->height = height;
  this->map = map;
  this->size = map.size();
}

bool	Leveldata::addEntity(int id, int x, int y)
{
  if (id == 3)
    this->players.push_back(new Player(x, y));
  if (id == 2)
    this->entitys.push_back(new Block(x, y));
}
