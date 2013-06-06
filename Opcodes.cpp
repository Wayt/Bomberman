/*
** Opcodes.cpp for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Fri May 10 15:29:51 2013 maxime ginters
** Last update Thu Jun 06 12:43:50 2013 maxime ginters
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
        {CMSG_MOVE_STRAF_LEFT, STATUS_INGAME, &Session::HandleMovement, NULL},
        {CMSG_MOVE_STRAF_RIGHT, STATUS_INGAME, &Session::HandleMovement, NULL},
        {SMSG_UPDATE_MOVEFLAGS, STATUS_INGAME, NULL, &Client::HandleUpdateMoveflags},
        {SMSG_DEL_OBJECT, STATUS_INGAME, NULL, &Client::HandleDeleteObject},
        {SMSG_FORCE_POSITION, STATUS_INGAME, NULL, &Client::HandleForcePosition},
        {CMSG_DROP_BOMB, STATUS_INGAME, &Session::HandleDropBomb, NULL},
        {CMSG_SEND_GLOBALTEXT, STATUS_INGAME, &Session::HandleGlobalChatText, NULL},
        {SMSG_SEND_GLOBALTEXT, STATUS_INGAME, NULL, &Client::HandleGlobalChatText},
        {SMSG_GRID_CHANGE_NOTIFY, STATUS_INGAME, NULL, &Client::HandleGridChange},
        {SMSG_SEND_SCORE, STATUS_INGAME, NULL, &Client::HandleSendScore},
        {SMSG_TELEPORT, STATUS_INGAME, NULL, &Client::HandleTeleport},
        {SMSG_PLAYER_KILLED, STATUS_INGAME, NULL, &Client::HandlePlayerKilled},
        {SMSG_PLAYER_RESPAWN, STATUS_INGAME, NULL, &Client::HandlePlayerRespawn},
        {SMSG_SEND_GAMETIMER, STATUS_INGAME, NULL, &Client::HandleSendGameTimer},
        {SMSG_GAME_FINISH, STATUS_INGAME, NULL, &Client::HandleGameFinish},
        {CMSG_SAVE_MAP, STATUS_INGAME, &Session::HandleSaveMap, NULL},
        {SMSG_MAP_SAVED, STATUS_INGAME, NULL, &Client::HandleMapSaved},
        {SMSG_UPDATE_SPEED, STATUS_INGAME, NULL, &Client::HandleUpdateSpeed},
        {SMSG_BOMB_BOUMED, STATUS_INGAME, NULL, &Client::HandleBombBoumed},
        {SMSG_PLAYER_JOIN, STATUS_INGAME, NULL, &Client::HandlePlayerJoin},
        {SMSG_PLAYER_LEAVE, STATUS_INGAME, NULL, &Client::HandlePlayerLeave},
        {NULL_OPCODE, STATUS_NONE, NULL, NULL}
    };

    for (uint32 i = 0; opcodes[i].opcode != NULL_OPCODE; ++i)
        if (opcodes[i].opcode == code)
            return &opcodes[i];
    return NULL;
}
