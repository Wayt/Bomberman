/*
** main.cpp for Lua in /home/giraul_b/work/epitech/projects/Bomberman/Lua
**
** Made by Aymeric Girault
** Login  <giraul_b@epitech.eu>
**
** Started on  Mon May 13 13:59:52 2013 Aymeric Girault
** Last update Mon May 13 16:59:37 2013 Aymeric Girault
*/

#include <iostream>
#include <string>


/*
 * utiliser un extern "C" pour le cpp
 */
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

/*
 * cette fonction est visible depuis lua
 * grace a la fonction lua_register
 */
int fn_visible(lua_State* luaVM)
{
  /*
   * valeur de retour
   */
  lua_pushstring(luaVM, "helloworld");
  /*
   * nb de valeur en retour
   */
  return (1);
}

int	  main()
{
  lua_State* luaVM;
  std::string str;

  /*
   * on open la VM lua
   */
  luaVM = luaL_newstate();
  if (luaVM == NULL)
  {
    std::cout << "Probleme initialisation" << std::endl;
    return (-1);
  }
  /*
   * chargement des libs lua
   */
  luaL_openlibs(luaVM);

  /*
   * fn_visible peut etre appelee
   */
  lua_register(luaVM, "HostVisible", fn_visible);

  /*
   * execution du fichier lua suivant
   */
  luaL_dofile(luaVM, "./test.lua");

  /*
   * on open... on close
   */
  lua_close(luaVM);
  return (0);
}
