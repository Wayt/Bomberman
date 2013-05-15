/*
** Bomberman.h for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:32 2013 fabien casters
** Last update Wed May 15 13:40:08 2013 vincent leroy
*/

#ifndef BOMBERMAN_H_
# define BOMBERMAN_H_

#include "Camera.h"
#include "Cube.h"
#include "Game.hpp"

class Bomberman : public gdl::Game
{
public:
    Bomberman();

    void initialize(void);
    void update(void);
    void draw(void);
    void unload(void);

private:
    Camera _cam;
    Cube _cube;
};

#endif
