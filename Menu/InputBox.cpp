//
// InputBox.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Wed Jun 05 11:49:27 2013 
// Last update Wed Jun 05 11:49:27 2013 
//

#include  <GL/glut.h> 
#include "InputBox.h"
#include "MenuMonitor.h"
#include <unistd.h>
#include <sstream>

/*{ InputText */
InputText::InputText (float x, float y, float z, float o)
    : AObject(x, y, z, o)
{
    value_ = "";
}

InputText::~InputText ()
{
}

void InputText::initialize()
{
}

void InputText::initialize(const std::string &key, int x, int y, int s, const gdl::Color &c)
{
    setKey(key);
    text_.setText(">" + value_);
    text_.setSize(s);
    text_.setPosition(x, y);
    text_.setColor(c);
}

void InputText::setColor(const gdl::Color &c)
{
    text_.setColor(c);
}

void	InputText::setValue(const std::string &v)
{
    value_ = v;
    text_.setText(value_);
}

void	InputText::setValue(unsigned int v)
{
    std::stringstream ss;
    ss << v;
    value_ = ss.str();
    text_.setText(ss.str());
}

void InputText::update(gdl::GameClock const &, gdl::Input &)
{
}

void InputText::draw()
{
    text_.setText(">" + value_);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT   | GL_ENABLE_BIT  |
	    GL_TEXTURE_BIT      | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    text_.draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

void 	InputText::setKey(const std::string &key)
{
    key_ = key;
}

std::string 	InputText::getKey()
{
    return key_;
}

std::string InputText::getValue()
{
    return value_;
}

void	InputText::append(char c)
{
	value_.append(1, c);
}

void	InputText::pop()
{
    if (value_.size() > 0)
	value_ = value_.substr(0, value_.size() - 1);
}
/*}*/

InputBox::InputBox (float x, float y, float z, float o) :
    SelectBox(x, y, z, o)
{
    ret_ = false;
    mvt_ = false;
    value_ = 0;
    intervalH_ = 500;
    setStatus(VISIBLE);
    current_ = 0;
}

InputBox::~InputBox ()
{
}

bool InputBox::select ()
{
    mvt_ = SubObject::NONE;
    if (!value_){
	value_ = 1;
    }
    else {
	value_ = 0;
    }
    return true;
}

bool InputBox::moveUp ()
{
    bool ret = SelectBox::moveUp();
    mvt_ = (ret == false) ? false : true;
    return ret;
}

bool InputBox::moveDown ()
{
    bool ret = SelectBox::moveDown();
    mvt_ = (ret == false) ? false : true;
    return ret;
}

void InputBox::update (gdl::GameClock const&, gdl::Input &)
{
}

void InputBox::draw ()
{
    switch (status_){
	case VISIBLE:
	    SelectBox::draw();
	    if (!mvt_ && focus_){
		unsigned int i = 0;
		for (std::list<InputText *>::iterator it = inputs_.begin(); it != inputs_.end(); ++it){
		    if (i == current_)
			(*it)->setColor(gdl::Color(81, 81, 81, 255));
		    else
			(*it)->setColor(gdl::Color(16, 16, 16, 255));
		    (*it)->draw();
		    i++;	
		}
	    }
	    break;
	case HIDDEN:
	    break;
	case SELECTED:
	    break;
	default:
	    break;
    }
}

void	InputBox::setValue(const std::string &key, unsigned int v)
{
    for (std::list<InputText *>::iterator it = inputs_.begin(); it != inputs_.end(); ++it){
	if ((*it)->getKey() == key)
	    (*it)->setValue(v);
	}
}

void	InputBox::addInput(const std::string &key, int x, int y, int s, const gdl::Color &c, InputBox::keyType type)
{
    InputText *t = new InputText(_pos.x, _pos.y, _pos.z, _rot.x);
    t->initialize(key, x, y, s, c);
    inputs_.push_back(t);
    keytype_ = type;
}

void InputBox::handleKeyDown(gdl::Keys::Key key)
{
    std::list<InputText *>::iterator it = inputs_.begin();
    std::advance(it, current_);
    char c;

    if (!*it)
	return;

    if (key >= gdl::Keys::A && key <= gdl::Keys::Z){
	c = key - gdl::Keys::A + 'a';
	(*it)->append(c);
    }
    else if (key == gdl::Keys::Space)
	(*it)->append(' ');
    else if (key >= gdl::Keys::Num0 && key <= gdl::Keys::Num9){
	c = key - gdl::Keys::Num0 + '0';
	(*it)->append(c);
    }
    else if (key == gdl::Keys::Back)
	(*it)->pop();

    else if (key == gdl::Keys::Tab){
	current_++;
	if (current_ >= inputs_.size())
	    current_ = 0;
    }
    else if (key != gdl::Keys::Up && key != gdl::Keys::Down 
	    && key != gdl::Keys::LShift && key != gdl::Keys::RShift)
	(*it)->append('.');
}
std::string InputBox::getInput (const std::string &key)
{
    for (std::list<InputText *>::iterator it = inputs_.begin(); it != inputs_.end(); ++it)
	if ((*it)->getKey() == key)
	    return ((*it)->getValue());
    return "";
}
