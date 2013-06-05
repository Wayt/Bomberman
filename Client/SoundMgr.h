/*
** SoundMgr.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed Jun 05 15:03:13 2013 maxime ginters
** Last update Wed Jun 05 16:13:04 2013 maxime ginters
*/

#ifndef SOUNDMGR_H_
# define SOUNDMGR_H_

#include <SFML/Audio.hpp>
#include <map>
#include "Shared.h"

enum Sounds
{
    SOUND_NONE              = 0,
    SOUND_BOMB_PLANTED      = 1,
    SOUND_ENEMY_DOWN        = 2,
    SOUND_GOGOGO            = 3,
    SOUND_BOUM              = 4,
};

class SoundMgr : public Singleton<SoundMgr>
{
public:
    SoundMgr();
    ~SoundMgr();

    void PlaySound(Sounds s);

private:
    sf::SoundBuffer const* GetBuffer(Sounds s) const;
    void Cleanup();

    std::map<Sounds, sf::Sound*> _soundsMap;
    std::map<Sounds, sf::SoundBuffer*> _buffersMap;
};

#define sSoundMgr SoundMgr::instance()

#endif /* !SOUNDMGR_H_ */
