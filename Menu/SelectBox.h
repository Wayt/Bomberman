/*
** SelectBox.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Thu May 16 10:39:54 2013 
** Last update Thu May 16 10:39:54 2013 
*/

#ifndef __SELECTBOX__
#define __SELECTBOX__

#include <sstream>
#include <string>
#include "SubObject.h"
#include "Image.hpp"

class SelectBox : public SubObject
{
    public:
	enum e_boxtype {
	    SELECTBOX,
	    CHECKBOX
	};


	SelectBox (float, float, float, float);
	virtual ~SelectBox ();

	void initialize ();
	void update (gdl::GameClock const&, gdl::Input &);
	void draw ();

	bool moveUp ();
	bool moveDown ();
	bool moveLeft ();
	bool moveRight ();

	void addSubObject (SubObject *);
	SubObject *getSubObject();

	virtual bool select ();
	void	initpos(int, int, int, int);

	virtual SubObject *operator [] (const std::string &);

    protected:
	SubObject		*obj_;
};


#endif /*__SELECTBOX__*/
