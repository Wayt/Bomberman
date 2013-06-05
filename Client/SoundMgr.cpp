/*
** SoundMgr.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Wed Jun 05 15:03:13 2013 maxime ginters
** Last update Wed Jun 05 16:24:24 2013 maxime ginters
*/

#include <iostream>
#include "SoundMgr.h"

SoundMgr::SoundMgr() :
    _soundsMap(), _buffersMap()
{
    struct
    {
        Sounds s;
        const char* file;
    } soundFile[] = {
        {SOUND_BOMB_PLANTED, "Sounds/bomb.ogg"},
        {SOUND_ENEMY_DOWN, "Sounds/enemy.ogg"},
        {SOUND_GOGOGO, "Sounds/gogogo.ogg"},
        {SOUND_BOUM, "Sounds/boum.ogg"},
        {SOUND_NONE, NULL}
    };

    for (uint32 i = 0; soundFile[i].s != SOUND_NONE; ++i)
    {
        sf::SoundBuffer* buff = new sf::SoundBuffer();
        if (buff->LoadFromFile(soundFile[i].file))
            _buffersMap[soundFile[i].s] = buff;
        else
        {
            sLog->error("Fail to load sound : %s", soundFile[i].file);
            delete buff;
        }
    }
}

SoundMgr::~SoundMgr()
{
    for (std::map<Sounds, sf::Sound*>::iterator itr = _soundsMap.begin(); itr != _soundsMap.end(); ++itr)
        delete itr->second;

    for (std::map<Sounds, sf::SoundBuffer*>::iterator itr = _buffersMap.begin(); itr != _buffersMap.end(); ++itr)
        delete itr->second;
}

void SoundMgr::PlaySound(Sounds s)
{
    Cleanup();

    sf::SoundBuffer const* buffer = GetBuffer(s);
    if (!buffer)
    {
        sLog->error("Error: No buffer for sound %d", uint32(s));
        return;
    }



    std::map<Sounds, sf::Sound*>::iterator itr = _soundsMap.find(s);
    if (itr != _soundsMap.end())
        if (itr->second->GetStatus() == sf::Sound::Playing)
        {
            itr->second->Stop();
            Cleanup();
        }

    sf::Sound* sound = new sf::Sound();
    sound->SetBuffer(*buffer);
    _soundsMap[s] = sound;
    sound->Play();
}

sf::SoundBuffer const* SoundMgr::GetBuffer(Sounds s) const
{
    std::map<Sounds, sf::SoundBuffer*>::const_iterator itr = _buffersMap.find(s);
    if (itr == _buffersMap.end())
        return NULL;
    return itr->second;
}

void SoundMgr::Cleanup()
{
    for (std::map<Sounds, sf::Sound*>::iterator itr = _soundsMap.begin(); itr != _soundsMap.end();)
    {
        if (itr->second->GetStatus() == sf::Sound::Stopped)
        {
            delete itr->second;
            _soundsMap.erase(itr++);
        }
        else
            ++itr;
    }
}

