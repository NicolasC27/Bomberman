//
// Created by root on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include <OgreVector2.h>
#include "AGameObject.hpp"
#include <OgreException.h>

#define ERR_MAPSIZE 	"Size map too big"
#define NOT_FOUND   	"File not found"
#define FOLDER_MAP	"media/map"

class Map {

 public:
  Map(std::string const &filename = "media/map/map1");

  virtual ~Map();

  void generate();

 private:
  std::map<Ogre::Vector2, AGameObject *> 	_objects;
  const std::string 				_filename;
  int					_size;
 public:
  void setSize(int size);
};

#endif //CPP_INDIE_STUDIO_MAP_HPP
