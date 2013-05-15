/*
** Cube.h for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:13 2013 vincent leroy
** Last update Wed May 15 15:23:15 2013 fabien casters
*/

#ifndef CUBE_H_
# define CUBE_H_

#include "AObject.h"

class Cube : public AObject
{
public:
    Cube(float, float, float, float);

    void initialize();
    void update(gdl::GameClock const&, gdl::Input &);
    void draw();

private:
};

#endif /* !CUBE_H_ */
