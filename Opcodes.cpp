/*
** Opcodes.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:29:51 2013 maxime ginters
** Last update Fri May 17 16:21:19 2013 maxime ginters
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
        {CMSG_MOVE_FORWARD, STATUS_INGAME, &Session::HandleMovement, NULL},
        {CMSG_MOVE_BACKWARD, STATUS_INGAME, &Session::HandleMovement, NULL},
        {CMSG_MOVE_TURN_LEFT, STATUS_INGAME, &Session::HandleMovement, NULL},
        {CMSG_MOVE_TURN_RIGHT, STATUS_INGAME, &Session::HandleMovement, NULL},
        {SMSG_UPDATE_MOVEFLAGS, STATUS_INGAME, NULL, &Client::HandleUpdateMoveflags},
        {SMSG_DEL_OBJECT, STATUS_INGAME, NULL, &Client::HandleDeleteObject},
        {NULL_OPCODE, STATUS_NONE, NULL, NULL}
    };

    for (uint32 i = 0; opcodes[i].opcode != NULL_OPCODE; ++i)
        if (opcodes[i].opcode == code)
            return &opcodes[i];
    return NULL;
}
