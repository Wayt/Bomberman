/*
** PathFindingRunnable.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 22 16:17:12 2013 vincent leroy
** Last update Thu Jun 06 22:48:27 2013 vincent leroy
*/

#include <iostream>

#include "Map.h"
#include "PathFinder.h"
#include "PathFindingRunnable.h"

PathFindingRunnable::PathFindingRunnable(PathFinder* f) :
    Runnable(),
    _open(), _close(),
    _finder(f)
{
}

PathFindingRunnable::~PathFindingRunnable()
{
}

void PathFindingRunnable::operator()()
{
    while (!isStopped())
    {
        PathFinderRequest *request = _finder->takeRequest();
        if (!request)
            continue;

        if (request->callback || !request->object)
        {
            std::list<point> path;

            _open.clear();
            _close.clear();
            findPath(path, request);
            (request->object->*request->callback)(path);
        }

        if (request->map)
        {
            for (uint32 i = 0; i < request->height; ++i)
                delete[] request->map[i];
            delete[] request->map;
        }

        delete request;
    }
}

void PathFindingRunnable::findPath(std::list<point> &path, const PathFinderRequest *request)
{
    path.clear();
    if (!request->map)
        return ;

    if (request->begin == request->end)
    {
        path.push_front(request->end);
        return ;
    }

    point actu(request->begin);

    _open[actu] = noeud(request->begin);
    addCloseList(actu);
    addAdjacentBox(actu, request);

    while (actu != request->end && !_open.empty())
    {
        actu = bestNoeud(_open);
        addCloseList(actu);
        addAdjacentBox(actu, request);
    }

    if (actu == request->end)
        restaurePath(path, request);

    for (uint32 y = 0; y < request->height ; ++y)
    {
        for (uint32 x = 0; x < request->width; ++x)
        {
            if (x == request->begin.first && request->begin.second == y)
                std::cout << "B ";
            else if (x == request->end.first && request->end.second == y)
                std::cout << "E ";
            else
            {
                bool fount = false;
                for (std::list<point>::const_iterator itr = path.begin(); itr != path.end(); ++itr)
                    if ((*itr).first == x && (*itr).second == y)
                    {
                        std::cout << ". ";
                        fount = true;
                    }
                if (!fount)
                    std::cout << uint32(request->map[y][x]) << " ";
            }
        }
            std::cout << std::endl;
    }
}

float PathFindingRunnable::distance(const point &p1, const point &p2) const
{
    return (CARRE(p2.first - p1.first) + CARRE(p2.second - p1.second));
}

bool PathFindingRunnable::isInList(const point &p, const l_noeud &l) const
{
    return l.find(p) != l.end();
}

void PathFindingRunnable::addAdjacentBox(const point &n, const PathFinderRequest *request)
{
    if (n.second >= 0)
        checkForAddInList(n.first, n.second - 1, n, request);
    if (n.first >= 0)
        checkForAddInList(n.first - 1, n.second, n, request);
    if (n.first < request->width)
        checkForAddInList(n.first + 1, n.second, n, request);
    if (n.second < request->height)
        checkForAddInList(n.first, n.second + 1, n, request);
}

void PathFindingRunnable::checkForAddInList(uint32 x, uint32 y, const point &n, const PathFinderRequest *request)
{
    noeud tmp;
    point p(x, y);

    if (request->map[y][x] != 0)
        return ;

    if (!isInList(p, _close))
    {
        tmp.cout_g = _close[n].cout_g + distance(p, n);
        tmp.cout_h = distance(p, request->end);
        tmp.cout_f = tmp.cout_g + tmp.cout_h;
        tmp.parent = n;

        if (isInList(p, _open))
        {
            if (tmp.cout_f < _open[p].cout_f)
                _open[p] = tmp;
        }
        else
            _open[p] = tmp;
    }
}

void PathFindingRunnable::addCloseList(const point &p)
{
    noeud &n = _open[p];
    _close[p] = n;

    _open.erase(p);
}

point PathFindingRunnable::bestNoeud(const l_noeud &l) const
{
    float m_cout_f = l.begin()->second.cout_f;
    point m_noeud = l.begin()->first;

    for (l_noeud::const_iterator it = l.begin(); it != l.end(); ++it)
        if (it->second.cout_f < m_cout_f)
        {
            m_cout_f = it->second.cout_f;
            m_noeud = it->first;
        }

    return m_noeud;
}

void PathFindingRunnable::restaurePath(std::list<point> &path, const PathFinderRequest *request)
{
    noeud &tmp = _close[request->end];
    point n(request->end);
    point prec(tmp.parent);

    n.first *= MAP_PRECISION;
    n.second *= MAP_PRECISION;
    path.push_front(n);

    while (prec != request->begin)
    {
        n = prec;
        n.first *= MAP_PRECISION;
        n.second *= MAP_PRECISION;
        path.push_front(n);

        tmp = _close[tmp.parent];
        prec = tmp.parent;
    }
}
