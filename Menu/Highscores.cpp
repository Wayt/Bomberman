//
// Highscores.cpp for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
// 
// Made by 
// Login   <masson_y@epitech.net>
// 
// Started on  Sun Jun 09 15:43:42 2013 
// Last update Sun Jun 09 15:43:42 2013 
//

#include "Highscores.h"
#include "Shared.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

struct sort_by_score {
    bool operator()(const std::pair<std::string,unsigned int> &p1, const std::pair<std::string,unsigned int> &p2) {
        return p1.second > p2.second;
    }
};


Highscores::Highscores (float x, float y, float z, float o) :
    SelectBox(x, y, z, o)
{
    std::vector<std::pair<std::string, unsigned int> > scores;
    std::string line;
    std::ifstream infile("score.sc");

    while (std::getline(infile, line))
    {
	std::vector<std::string> score;
	split(line, ',', score);
	if (score.size() == 5)
	    scores.push_back( std::make_pair(score[0],to<int>(score[2])));
    }
    std::sort(scores.begin(), scores.end(), sort_by_score());
    int i = 0;
    for (std::vector<std::pair<std::string, unsigned int> >::iterator it = scores.begin(); it != scores.end() && i < 10; ++it){
	std::stringstream ss;
	ss << (*it).second;
	addScore((*it).first, ss.str(), x + 375, _pos.y + 180 + 40 * i, 30, gdl::Color(81, 81, 81, 255) );
	i++;
    }
}

Highscores::~Highscores()
{
}

void Highscores::initialize ()
{
}

void Highscores::update (gdl::GameClock const&, gdl::Input &)
{
}

void Highscores::draw ()
{
    SelectBox::draw();
    if (focus_)
	for (std::list<InputText *>::iterator it = inputs_.begin(); it != inputs_.end();
	       	++it)
	    (*it)->draw();
}

void	Highscores::addScore(const std::string &name, const std::string &score, int x, int y, int s, const gdl::Color &c)
{
    InputText *in = new InputText(_pos.x, _pos.y, _pos.z, _rot.x);
    in->initialize(name, x, y, s, c);
    in->setValue(name);
    inputs_.push_back(in);
    InputText *is = new InputText(_pos.x, _pos.y, _pos.z, _rot.x);
    is->initialize(score, x + 245, y, s, c);
    is->setValue(score);
    inputs_.push_back(is);
}
