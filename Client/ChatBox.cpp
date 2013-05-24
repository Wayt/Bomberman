/*
** ChatBox.cpp for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 24 16:21:31 2013 maxime ginters
** Last update Fri May 24 18:42:37 2013 maxime ginters
*/

#include <iostream>
#include "ChatBox.h"

ChatBox::ChatBox() : _isInput(false), _inputStream()
{
}

void ChatBox::StartInput()
{
    if (_isInput)
        return;

    _isInput = true;
    _inputStream.str("");
}

void ChatBox::HandleInput(int key)
{
    if (!_isInput)
        return;
    if (key == 59)
    {
        std::string str = _inputStream.str();
        if (str.length() == 0)
        {
            EndInput();
            return;
        }
        str.erase(str.size() - 1);
        _inputStream.str(str);
        return;
    }
    char c = GetCharForKey(key);
    if (c != 0)
    _inputStream << c;
}

bool ChatBox::IsOpen() const
{
    return _isInput;
}

void ChatBox::EndInput()
{
    if (!_isInput)
        return;

    _isInput = false;
    if (_inputStream.str().length() == 0)
        return;
}

void ChatBox::PushMessage(std::string const& msg)
{
    _messages.push_back(msg);
    if (_messages.size() > CHAT_HISTORY_SIZE)
        _messages.pop_front();
}

std::string ChatBox::GetInputString() const
{
    return _inputStream.str();
}

char ChatBox::GetCharForKey(int32 key) const
{
    if (key >= 0 && key <= 25)
        return key + 'a';
    if (key == 57)
        return ' ';
    return 0;
}

void ChatBox::GetMessageList(std::list<std::string>& list) const
{
    list = _messages;
}
