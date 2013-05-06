/*
** Log.h for Plazza in /Storage/Epitech/Plazza
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue Apr 16 15:10:46 2013 maxime ginters
** Last update Mon May 06 13:58:25 2013 maxime ginters
*/

#ifndef LOG_H_
# define LOG_H_

#include <fstream>
#include "Mutex.h"
#include "Singleton.hpp"

#define LOG_FILE "output.log"
#define ERROR_FILE "error.log"
#define DEBUG_FILE "debug.log"

class Log : public Singleton<Log>
{
public:
    Log();
    ~Log();

    bool initialize();

    void out(const char* str, ...);
    void error(const char* str, ...);
    void debug(const char* str, ...);

private:
    std::ofstream _stream;
    Mutex _streamMutex;

    std::ofstream _error;
    Mutex _errorMutex;

    std::ofstream _debug;
    Mutex _debugMutex;
};

#define sLog Log::instance()

#endif /* !LOG_H_ */
