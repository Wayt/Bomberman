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
	    CHECKBOX,
	    INPUTBOX
	};


	SelectBox (float, float, float, float);
	virtual ~SelectBox ();

	virtual void initialize ();
	virtual void update (gdl::GameClock const&, gdl::Input &);
	virtual void draw ();

	virtual bool moveUp ();
	virtual bool moveDown ();
	bool moveLeft ();
	bool moveRight ();
	virtual void handleKeyDown(gdl::Keys::Key key);
	void setFocus(bool);

	void addSubObject (SubObject *);
	SubObject *getSubObject();

	virtual bool select ();
	void	initpos(int, int, int, int);

	virtual SubObject *operator [] (const std::string &);

    protected:
	SubObject		*obj_;
	bool			focus_;
};


#endif /*__SELECTBOX__*/
