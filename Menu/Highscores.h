/*
** Highscore.h for  in /home/masson_y/prog/tech2/cpp/Bomberman/Menu
** 
** Made by 
** Login   <masson_y@epitech.net>
** 
** Started on  Sun Jun 09 15:43:49 2013 
** Last update Sun Jun 09 15:43:49 2013 
*/

#include "SelectBox.h"
#include "InputBox.h"

class Highscores : public SelectBox
{
    public:
	Highscores (float x, float y, float z, float o);
	~Highscores();

	void initialize ();
	void update (gdl::GameClock const&, gdl::Input &);
	void draw ();
    private:
	std::list<InputText *>	inputs_;
	void addScore(const std::string &name, const std::string &score, int x, int y, int s, const gdl::Color &c);
};
