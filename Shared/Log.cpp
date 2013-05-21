/*
** Log.cpp for Plazza in /Storage/Epitech/Plazza
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Tue Apr 16 15:10:46 2013 maxime ginters
** Last update Tue May 21 18:56:23 2013 maxime ginters
*/

#include <ctime>
#include <iostream>
#include <stdarg.h>
#include "Log.h"

Log::Log() : _stream()
{}

Log::~Log()
{
    if (_stream.is_open())
        _stream.close();
    if (_error.is_open())
        _error.close();
    if (_debug.is_open())
        _debug.close();
}

bool Log::initialize()
{
    try
    {
        _stream.open(LOG_FILE, std::ios_base::out | std::ios_base::trunc);
        _error.open(ERROR_FILE, std::ios_base::out | std::ios_base::trunc);
        _debug.open(DEBUG_FILE, std::ios_base::out | std::ios_base::trunc);
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void Log::out(const char* str, ...)
{
    char buff[4096];
    va_list ap;
    time_t tm;

    va_start(ap, str);
    vsnprintf(buff, 4096, str, ap);
    va_end(ap);

    _streamMutex.lock();
    time(&tm);
    std::string st = ctime(&tm);
    st[st.length() - 1] = ' ';
    _stream << st << ": " << buff << std::endl;
    std::cout << "OUT : " << buff << std::endl;
    _streamMutex.unlock();
}

void Log::error(const char* str, ...)
{
    char buff[4096];
    va_list ap;
    time_t tm;

    va_start(ap, str);
    vsnprintf(buff, 4096, str, ap);
    va_end(ap);

    _errorMutex.lock();
    time(&tm);
    std::string st = ctime(&tm);
    st[st.length() - 1] = 0;
    _error << st << ": " << buff << std::endl;
    std::cerr << "ERR : " << buff << std::endl;
    _errorMutex.unlock();
}

void Log::debug(const char* str, ...)
{
    char buff[4096];
    va_list ap;
    time_t tm;

    va_start(ap, str);
    vsnprintf(buff, 4096, str, ap);
    va_end(ap);

    _debugMutex.lock();
    time(&tm);
    std::string st = ctime(&tm);
    st[st.length() - 1] = 0;
    _debug << st << ": " << buff << std::endl;
    std::cout << "DEBUG : " << buff << std::endl;
    _debugMutex.unlock();
}

void Log::print(const char* str)
{
    std::cout << str << std::endl;
}
