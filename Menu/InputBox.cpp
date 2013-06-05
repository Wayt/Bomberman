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

InputBox::InputBox (float x, float y, float z, float o) :
    SelectBox(x, y, z, o)
{
    ret_ = false;
    value_ = 0;
    intervalH_ = 500;
    input_ = "";
    setStatus(VISIBLE);
}

InputBox::~InputBox ()
{
}

bool InputBox::select ()
{
    return true;
}

void InputBox::update (gdl::GameClock const&, gdl::Input &)
{
}

void InputBox::draw ()
{
    gdl::Text text;
    switch (status_){
	case VISIBLE:
	    SelectBox::draw();
	    text.setText(input_);
	    text.setSize(20);
	    text.setPosition(100, 50);
	    glMatrixMode(GL_MODELVIEW);
	    glPushMatrix();
	    glMatrixMode(GL_PROJECTION);
	    glPushMatrix();
	    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT   | GL_ENABLE_BIT  |
		    GL_TEXTURE_BIT      | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
	    glDisable(GL_ALPHA_TEST);
	    glDisable(GL_DEPTH_TEST);
	    glDisable(GL_LIGHTING);
	    text.draw();
	    glMatrixMode(GL_PROJECTION);
	    glPopMatrix();
	    glMatrixMode(GL_MODELVIEW);
	    glPopMatrix();
	    glPopAttrib();
	    break;
	case HIDDEN:
	    break;
	case SELECTED:
	    break;
	default:
	    break;
    }
}

void InputBox::handleKeyDown(gdl::Keys::Key key)
{
    char c;

    if (key >= gdl::Keys::A && key <= gdl::Keys::Z){
	c = key - gdl::Keys::A + 'a';
	input_.append(1, c);
    }
    if (key == gdl::Keys::Space)
	input_.append(1, ' ');
    if (key >= gdl::Keys::Num0 && key <= gdl::Keys::Num9){
	c = key - gdl::Keys::Num0 + '0';
	input_.append(1, c);
    }
    if (key == gdl::Keys::Back && input_.size() > 0)
	input_ = input_.substr(0, input_.size() - 1);

    std::cout << input_ << std::endl;


}
