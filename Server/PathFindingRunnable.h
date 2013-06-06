/*
** PathFindingRunnable.h for Server in /home/leroy_v/github/Bomberman/Server
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed May 22 16:17:15 2013 vincent leroy
** Last update Thu Jun 06 15:38:50 2013 maxime ginters
*/

#ifndef PATHFINGINGRUNNABLE_H_
# define PATHFINGINGRUNNABLE_H_

#include <list>
#include <map>

#include "Shared.h"

class MovementPoint;

#define CARRE(x) ((x) * (x))

class AMovement;

typedef std::pair<float, float> point;

struct PathFinderRequest
{
    uint8 **map;
    uint32 width;
    uint32 height;
    point begin;
    point end;
    MovementPoint *object;
    void (MovementPoint::*callback)(const std::list<point>&);
};

class PathFindingRunnable : public Runnable
{
public:
    PathFindingRunnable();
    virtual ~PathFindingRunnable();

    void operator()();

private:
    struct noeud
    {
        noeud() :
            cout_g(0.f), cout_h(0.f), cout_f(0.f), parent()
        {}
        noeud(const point &p) :
            cout_g(0.f), cout_h(0.f), cout_f(0.f), parent(p)
        {}

        float cout_g;
        float cout_h;
        float cout_f;

        point parent;
    };
    typedef std::map<point, noeud> l_noeud;

    l_noeud _open;
    l_noeud _close;

    void findPath(std::list<point> &path, const PathFinderRequest *request);
    float distance(const point &p1, const point &p2) const;
    bool isInList(const point &p, const l_noeud &l) const;
    void addAdjacentBox(const point &n, const PathFinderRequest *request);
    void addCloseList(const point &p);
    point bestNoeud(const l_noeud &l) const;
    void restaurePath(std::list<point> &path, const PathFinderRequest *request);
};

#endif /* !PATHFINGINGRUNNABLE_H_ */
