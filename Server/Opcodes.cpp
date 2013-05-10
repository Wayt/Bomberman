/*
** Opcodes.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:29:51 2013 maxime ginters
** Last update Fri May 10 15:41:27 2013 maxime ginters
*/

#include "Opcodes.h"
#include "Session.h"
#include "Packet.hpp"

OpcodeHandler const* OpcodesMgr::GetOpcodeHandler(Opcodes code) const
{
    static OpcodeHandler opcodes[] = {
        {CMSG_PLAYER_NAME, STATUS_NO_AUTHED, &Session::HandlePlayerName},
        {NULL_OPCODE, STATUS_NONE, NULL}
    };

    for (uint32 i = 0; opcodes[i].opcode != NULL_OPCODE; ++i)
        if (opcodes[i].opcode == code)
            return &opcodes[i];
    return NULL;
}
