/*
** Opcodes.h for Server in /home/fest/Epitech/Bomberman/Server
**
** Made by maxime ginters
** Login  <ginter_m@epitech.eu>
**
** Started on  Mon May 06 18:39:40 2013 maxime ginters
** Last update Fri May 10 15:40:38 2013 maxime ginters
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

enum Opcodes
{
    NULL_OPCODE         = 0x0000,
    SMSG_TEST           = 0x0001,
    CMSG_PLAYER_NAME    = 0x0002,
};

class Packet;
class Session;

struct OpcodeHandler
{
    Opcodes opcode;
    OpcodeStatus status;
    void (Session::*handler)(Packet& recvData);
};

class OpcodesMgr : public Singleton<OpcodesMgr>
{
public:
    OpcodeHandler const* GetOpcodeHandler(Opcodes code) const;
};

#define sOpcodesMgr OpcodesMgr::instance()

#endif /* !OPCODES_H_ */
