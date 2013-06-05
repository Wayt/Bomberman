/*
** Utils.hpp for Plazza in /Storage/Epitech/Plazza
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon Apr 15 14:14:28 2013 maxime ginters
** Last update Wed Jun 05 18:48:15 2013 maxime ginters
*/

#ifndef UTILS_H_
# define UTILS_H_

#include <sstream>
#include <vector>
#include "SharedDefines.h"

template<class T>
T to(char const* buff)
{
    T val;
    std::stringstream ss;
    ss << buff;
    ss >> val;
    return val;
}

template<class T>
T to(std::string const& str)
{
    return to<T>(str.c_str());
}

void split(std::string const& s, char c, std::vector<std::string> &elems);
inline std::string &trim(std::string &s);

uint32 GetMSTime();
uint32 GetMSTimeDiffToNow(uint32 prev);
uint32 GetMSTimeDiff(uint32 prev, uint32 now);
bool FuzzyCompare(float f1, float f2);
void Mod2PI(float &angle);

#endif /* !UTILS_H_ */
