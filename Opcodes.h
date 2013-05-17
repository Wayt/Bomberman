/*
** Opcodes.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 18:39:40 2013 maxime ginters
** Last update Fri May 17 17:45:39 2013 maxime ginters
*/

#ifndef OPCODES_H_
# define OPCODES_H_

#include "Shared.h"

enum OpcodeStatus
{
    STATUS_NONE         = 0,
    STATUS_NO_AUTHED    = 1,
    STATUS_AUTHED       = 2,
    STATUS_INGAME       = 3
};

enum LoginResponses
{
    LOGIN_RESPONSE_OK                 = 0,
    LOGIN_RESPONSE_NICK_UNAVAILABLE   = 1
};

enum Opcodes
{
    NULL_OPCODE             = 0x0000,
    SMSG_TEST               = 0x0001,
    CMSG_LOGIN_PLAYER       = 0x0002,
    SMSG_LOGIN_RESPONSE     = 0x0003,
    SMSG_SEND_OBJECT        = 0x0004,
    CMSG_ENTER_GAME         = 0x0005,
    SMSG_ADD_TO_MAP         = 0x0006,
    // Movements
    CMSG_MOVE_FORWARD       = 0x0007,
    CMSG_MOVE_BACKWARD      = 0x0008,
    CMSG_MOVE_TURN_LEFT     = 0x0009,
    CMSG_MOVE_TURN_RIGHT    = 0x000A,
    SMSG_UPDATE_MOVEFLAGS   = 0x000B,
    CMSG_MOVE_STRAF_LEFT    = 0x000C,
    CMSG_MOVE_STRAF_RIGHT   = 0x000D,

    SMSG_DEL_OBJECT         = 0x000E,
};

class Packet;
class Session;
class Client;

struct OpcodeHandler
{
    Opcodes opcode;
    OpcodeStatus status;
    void (Session::*srv_handler)(Packet& recvData);
    void (Client::*cli_handler)(Packet& recvData);
};

class OpcodesMgr : public Singleton<OpcodesMgr>
{
public:
    OpcodeHandler const* GetOpcodeHandler(Opcodes code) const;
};

#define sOpcodesMgr OpcodesMgr::instance()

#endif /* !OPCODES_H_ */
