/*
** InputBox.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Wed Jun 05 11:50:23 2013 
** Last update Wed Jun 05 11:50:23 2013 
*/


#ifndef __INPUTBOX__
#define __INPUTBOX__

#include <iostream>
#include <sstream>
#include "SelectBox.h"
#include "Text.hpp"

class InputText: public AObject
{
    public:
	InputText (float, float, float, float);
	~InputText ();
	void 		setColor(const gdl::Color &c);
	std::string 	getValue();
	void		setValue(const std::string &);
	void 		setKey(const std::string &key);
	std::string 	getKey();
	void		append(char);
	void		pop();

	void 		initialize(const std::string &key, int x, int y, int s, const gdl::Color &c);
	void 		initialize();
	void 		update(gdl::GameClock const &, gdl::Input &);
	void 		draw();

    private:
	std::string 	key_;
	std::string 	value_;
	gdl::Text 	text_;

};

class InputBox : public SelectBox
{
    public:
	InputBox (float, float, float, float);
	~InputBox ();

	virtual void draw ();
	virtual void update (gdl::GameClock const&clock, gdl::Input &input);

	virtual bool select ();
	void handleKeyDown(gdl::Keys::Key);

	virtual bool moveUp();
	virtual bool moveDown();

	void	addInput(const std::string &key, int x, int y, int size, const gdl::Color &c);
	std::string getInput (const std::string &);

    private:
	std::list<InputText *>	inputs_;
	unsigned int		current_;
	bool			mvt_;
};

#endif
