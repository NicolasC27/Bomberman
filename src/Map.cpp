//
// Created by root on 29/05/17.
//

#include "Map.hpp"
#include <iostream>
#include <fstream>

Map::Map(std::string const &filename) : _filename(filename)
{

}

Map::~Map()
{

}

void Map::generate()
{
  std::ifstream infile(_filename);
  std::string line;
  int size;

  if (!(infile.good()))
    throw Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			  NOT_FOUND, FOLDER_MAP);
  std::getline(infile, line);
  setSize(std::stoi(line));
  if (_size > 40)
    throw Ogre::Exception(Ogre::Exception::ERR_INVALID_STATE,
			  ERR_MAPSIZE, _filename);
  while (std::getline(infile, line))
    {
	
    }
}

void Map::setSize(int size)
{
  _size = size;
}
