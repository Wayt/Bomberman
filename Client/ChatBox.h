/*
** ChatBox.h for Client in /home/fest/Epitech/Bomberman/Client
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 24 16:21:18 2013 maxime ginters
** Last update Fri May 24 18:37:40 2013 maxime ginters
*/

#ifndef CHATBOX_H_
# define CHATBOX_H_

#include <string>
#include <sstream>
#include <list>
#include "Shared.h"

#define CHAT_HISTORY_SIZE 6

class ChatBox
{
public:
    ChatBox();

    void StartInput();
    void EndInput();
    bool IsOpen() const;

    void HandleInput(int c);
    void PushMessage(std::string const& msg);
    std::string GetInputString() const;
    void GetMessageList(std::list<std::string>& list) const;

private:
    bool _isInput;
    std::stringstream _inputStream;
    std::list<std::string> _messages;
    char GetCharForKey(int32 key) const;
};

#endif /* !CHATBOX_H_ */
