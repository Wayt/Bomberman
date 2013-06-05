/*
** ScoreMgr.cpp for Bomberman in /home/fest/Epitech/Bomberman
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon Jun 03 17:58:56 2013 maxime ginters
** Last update Wed Jun 05 18:36:57 2013 maxime ginters
*/

#include "GameObject.h"
#include "ScoreMgr.h"

ScoreMgr::ScoreMgr()
{}

void ScoreMgr::AddPlayer(GameObject* obj)
{
    Score* sc = new Score();
    sc->name = obj->GetName();
    sc->died = 0;
    sc->killed = 0;
    sc->bomb = 0;
    sc->wall = 0;
    _scores.insert(std::pair<uint64, Score*>(obj->GetGUID(), sc));
}

void ScoreMgr::AddPlayer(uint64 guid, Score* sc)
{
    _scores.insert(std::pair<uint64, Score*>(guid, sc));
}


Score const* ScoreMgr::GetScore(uint64 guid) const
{
    std::map<uint64, Score*>::const_iterator itr = _scores.find(guid);
    if (itr == _scores.end())
        return NULL;
    return itr->second;
}

Score* ScoreMgr::GetScore(uint64 guid)
{
    std::map<uint64, Score*>::iterator itr = _scores.find(guid);
    if (itr == _scores.end())
        return NULL;
    return itr->second;
}

std::map<uint64, Score*>::const_iterator ScoreMgr::ScoreBegin() const
{
    return _scores.begin();
}

std::map<uint64, Score*>::const_iterator ScoreMgr::ScoreEnd() const
{
    return _scores.end();
}

void ScoreMgr::WriteScores(Packet& data, uint64 guid) const
{
    if (guid > 0)
    {
        if (Score const* sc = GetScore(guid))
        {
            data << uint32(1);
            data << uint64(guid);
            data << sc->name;
            data << uint32(sc->died);
            data << uint32(sc->killed);
            data << uint32(sc->bomb);
            data << uint32(sc->wall);
        }
        else
            data << uint32(0);
    }
    else
    {
        data << uint32(_scores.size());
        std::map<uint64, Score*>::const_iterator itr = _scores.begin();
        for (; itr != _scores.end(); ++itr)
        {
            data << uint64(itr->first);
            data << itr->second->name;
            data << uint32(itr->second->died);
            data << uint32(itr->second->killed);
            data << uint32(itr->second->bomb);
            data << uint32(itr->second->wall);
        }
    }
}

void ScoreMgr::ReadScores(Packet& data)
{
    uint32 count;
    data >> count;
    for (; count > 0; --count)
    {
        uint64 guid;
        data >> guid;
        Score* sc = GetScore(guid);
        if (!sc)
        {
            sc = new Score();
            _scores[guid] = sc;
        }

        data >> sc->name;
        data >> sc->died;
        data >> sc->killed;
        data >> sc->bomb;
        data >> sc->wall;
    }
}
