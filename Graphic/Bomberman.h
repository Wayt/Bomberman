/*
** Bomberman.h for bomberman in /home/vaga/Projects/tek2/bomberman
** 
** Made by fabien casters
** Login   <fabien.casters@epitech.eu>
** 
** Started on  Mon May 06 18:45:32 2013 fabien casters
** Last update Mon May 06 18:52:10 2013 fabien casters
*/

#ifndef BOMBERMAN_H_
# define BOMBERMAN_H_

#include "Game.hpp"

class Bomberman : public gdl::Game
{
public:
    void initialize(void);
    void update(void);
    void draw(void);
    void unload(void);
};

#endif
