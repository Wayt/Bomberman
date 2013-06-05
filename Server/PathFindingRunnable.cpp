/*
** PathFindingRunnable.cpp for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 22 16:17:12 2013 vincent leroy
** Last update Wed Jun 05 11:42:13 2013 vincent leroy
*/

#include "PathFinder.h"
#include "PathFindingRunnable.h"

PathFindingRunnable::PathFindingRunnable() :
    Runnable(),
    _open(), _close()
{
}

PathFindingRunnable::~PathFindingRunnable()
{
}

void PathFindingRunnable::operator()()
{
    while (!isStopped())
    {
        PathFinderRequest *request = sPathFinder->takeRequest();
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
    noeud tmp;

    for (int32 i = n.first - 1; i <= n.first + 1; ++i)
    {
        if (i < 0 || (uint32)i >= request->width)
            continue;
        for (int32 j = n.second - 1; i <= n.second + 1; ++j)
        {
            if (j < 0 || (uint32)j >= request->height || (i == n.first && j == n.second) || request->map[i][j] != 0)
                continue;

            point p(i, j);

            if (!isInList(p, _close) || tmp.cout_f < _open[p].cout_f)
                _open[p] = tmp;
        }
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

    path.push_front(n);

    while (prec != request->begin)
    {
        n = prec;
        path.push_front(n);

        tmp = _close[tmp.parent];
        prec = tmp.parent;
    }
}
