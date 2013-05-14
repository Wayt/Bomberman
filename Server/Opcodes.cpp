/*
** Opcodes.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:29:51 2013 maxime ginters
** Last update Tue May 14 17:22:46 2013 maxime ginters
*/

#include "Opcodes.h"
#include "Session.h"
#include "Client.h"
#include "Packet.hpp"

OpcodeHandler const* OpcodesMgr::GetOpcodeHandler(Opcodes code) const
{
    static OpcodeHandler opcodes[] = {
        {CMSG_LOGIN_PLAYER, STATUS_NO_AUTHED, &Session::HandleLoginPlayer, NULL},
        {SMSG_LOGIN_RESPONSE, STATUS_NO_AUTHED, NULL, &Client::HandleLoginResponse},
        {SMSG_SEND_OBJECT, STATUS_INGAME, NULL, &Client::HandleSendObject},
        {CMSG_ENTER_GAME, STATUS_AUTHED, &Session::HandleEnterGame, NULL},
        {SMSG_ADD_TO_MAP, STATUS_AUTHED, NULL, &Client::HandleAddToMap},
        {NULL_OPCODE, STATUS_NONE, NULL, NULL}
    };

    for (uint32 i = 0; opcodes[i].opcode != NULL_OPCODE; ++i)
        if (opcodes[i].opcode == code)
            return &opcodes[i];
    return NULL;
}
