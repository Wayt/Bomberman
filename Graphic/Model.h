/*
** Model.h for Graphic in /home/leroy_v/github/Bomberman/Graphic
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 15 13:32:13 2013 vincent leroy
** Last update Wed May 15 18:35:35 2013 fabien casters
*/

#ifndef MODEL_H_
# define MODEL_H_

class ClientObject;

class Model
{
public:
    Model(ClientObject const *);

    void draw();
private:
    ClientObject const *_object;
};

#endif /* !MODEL_H_ */
