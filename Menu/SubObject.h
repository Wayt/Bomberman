/*
** SubObject.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Tue May 28 16:55:58 2013 
** Last update Tue May 28 16:55:58 2013 
*/

#ifndef __SUBOBJECT__
#define __SUBOBJECT__

#include <sstream>
#include <string>
#include "AObject.h"
#include "Image.hpp"

class SubObject : public AObject
{
    public:
	enum e_movement { 	
	    NONE,
	    UP, 
	    DOWN,
	    RIGHT,
	    LEFT,
	    SRIGHT,
	    SLEFT
	};

	enum e_status {
	    VISIBLE,
	    HIDDEN,
	    SELECTED,
	    BACK
	};

	SubObject (float, float, float, float);
	~SubObject ();

	virtual void initialize () = 0;
	virtual void update (gdl::GameClock const&, gdl::Input &) = 0;
	virtual void draw () = 0;

	void setId (int);
	int getId ();

	void setKey (const std::string &);
	std::string &getKey ();

	void setValue (int);
	int value ();

	void setRet (bool ret);
	bool getRet ();

	void setStatus(e_status);
	e_status getStatus();

	virtual bool select () = 0;
	e_movement 	getMvt();

	void setTexture (const std::string &s);
	void setTexture (const std::string &img1, const std::string &img2);

	//scroll & movements

	void 		setMovableH();
	bool 		isMovableH();
	void 		setIntervalV(int);
	void 		setIntervalH(int);

	//get elem
	virtual SubObject *operator [] (const std::string &) = 0;

    protected:
	Vector 			oldpos_;
	e_status		status_;
	int			id_;
	std::string		key_;
	int			value_;
	bool			ret_;

	e_movement 		mvt_;
	int			intervalV_;
	int			intervalH_;
	bool			h_;

	gdl::Image 		texture_;
	std::string		img1_;
	std::string		img2_;
};

#endif /*__SUBOBJECT__*/
