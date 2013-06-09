##
## Makefile
##
## Made by maxime ginters
## Login <ginter_m@epitech.eu>
##
## Started on Mon May 06 13:39:56 2013 maxime ginters
## Last update Sun Jun 09 17:03:30 2013 vincent leroy
##

include Menu/menu.mk

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I. -IShared -IClient -IServer -IGraphic -ILibrary -IServer/AI -IMenu
CXXFLAGS	+= -fopenmp
CXXFLAGS	+= -I/usr/include/lua5.1

UNAME	:= $(shell uname -a)

LDFLAGS	= -LShared -lshared -lpthread -lboost_system -lgomp
LDFLAGS	+= -lGL -lGLU -lgdl_gl -LLibrary -Wl,-rpath=Library
LDFLAGS	+= -lsfml-audio
LDFLAGS	+= -lluabind

NAME	= bomberman

SRCS	= Main.cpp Position.cpp MotionMaster.cpp MovementIdle.cpp MovementPlayer.cpp MovementPoint.cpp GameObject.cpp \
	Opcodes.cpp ModelMgr.cpp ScoreMgr.cpp \
	Server/SessionHandler.cpp Server/Map.cpp Server/MapObject.cpp Server/Player.cpp Server/Speed.cpp Server/Range.cpp Server/More.cpp Server/Teleport.cpp \
	Server/Server.cpp Server/SessionSocketAcceptor.cpp Server/Session.cpp Server/SessionSocket.cpp \
	Server/SessionSocketMgr.cpp Server/Bomb.cpp Server/Object.cpp Server/AI/ObjectAI.cpp \
	Client/Client.cpp Client/ClientSocket.cpp Client/ClientHandler.cpp Client/ClientObject.cpp \
	Client/ChatBox.cpp Client/SoundMgr.cpp \
	Graphic/GameMonitor.cpp Graphic/Camera.cpp Graphic/Vector.cpp Graphic/GraphicObject.cpp Graphic/ModelFactory.cpp \
	Server/PathFinder.cpp Server/PathFindingRunnable.cpp

SRCS	+= $(MENU_SRCS)

OBJS	= $(SRCS:.cpp=.o)

DEPS	=	Position.h MotionMaster.hpp MovementIdle.h MovementPlayer.h MovementPoint.h GameObject.h \
	Opcodes.h ModelMgr.h ScoreMgr.h \
	Server/Map.h Server/MapObject.h Server/Player.h Server/Speed.h Server/Range.h Server/More.h Server/Teleport.h \
	Server/Server.h Server/SessionSocketAcceptor.h Server/Session.h Server/SessionSocket.h \
	Server/SessionSocketMgr.h Server/Bomb.h Server/Object.h Server/AI/ObjectAI.h \
	Client/Client.h Client/ClientSocket.h Client/ClientObject.h \
	Client/ChatBox.h Client/SoundMgr.h \
	Graphic/GameMonitor.h Graphic/Camera.h Graphic/Vector.h Graphic/GraphicObject.h Graphic/ModelFactory.h \
	Server/PathFinder.h Server/PathFindingRunnable.h

MAKE	= make -C

SHARED	= Shared/

all: shared $(NAME)

shared:
	$(MAKE) $(SHARED)

$(NAME): $(OBJS) $(DEPS)
	@echo "Debut de la phase de linkage"
	@if [[ -f "/etc/redhat-release" || -f "/etc/redhat_version" ]] ; then \
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS) -llua; \
	elif [[ -f "/etc/debian_release" || -f "/etc/debian_version" ]] ; then \
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS) -llua5.1; \
	elif [[ -f "/etc/arch-release" ]] ; then \
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS) -llua5.1 -lSOIL; \
	fi
	@echo "Linkage terminee"
	@echo "________________________▓▓▓"
	@echo "_______________________▓▓▓▒▒▒▓"
	@echo "____________________▓▓▒▒▒▒▒▒▒▓______▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"
	@echo "__________________▓▓▒▒▓▓▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"
	@echo "________________▓▓▒▒▒▓▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓_______▓▓▓▓▓▓▓"
	@echo "_______________▓▓▒▒▒▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓_______▓▓▓▓▓"
	@echo "_____________▓▓▒▒▒▒▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓______▓▓"
	@echo "____________▓▓▒▒▒▒▓▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓"
	@echo "___________▓▓▒▒▒▒▓▒▒▒▒▒▒▒▒▒▓░░░░░░▓▓▓▓▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓"
	@echo "__________▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▓░░░░░░░░░▓▓▓▓▒▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓"
	@echo "__________▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▓▓░░░░░░░░░▓▓▓▓▓▒▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓"
	@echo "__________▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▓░░░░░░░░░░▓▓▓▓▓▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓"
	@echo "__________▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▓░░░░░▒░░░░░▓▓▓▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓"
	@echo "_________▓▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓░░░▒░░░░░▓▓▓▓▓▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓"
	@echo "________▓▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░░▒░░░░░░▓▓▓▓▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓"
	@echo "_______▓▒▒▓▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░▒▒░░░░░░▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▓"
	@echo "______▓▒▒▒▓▒▒▒▒▒▄▒▒▒█▄▀▀▀▀▀▄▄▒▒▒▒▒▒▓▒▒▒░░░░░░░▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓_▓▒▓"
	@echo "_____▓▒▒▒▒▓▒▒▒▒▒▀▄▄▀____________▀▄▒▒▒▒▓▒▒▒░░▓░░░░░▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▓_▓▒▓"
	@echo "____▓▒▒▒▒▓▒▒▒▒▄▒▄▀_________________█▒▒▒▓▓▒▒░▓▒▓░░░░░▓▓▓▒▒▒▒▒▒▒▒▒▒▒▓__▓▒▓"
	@echo "____▓▒▒▒▓▓▒▒▒▒▒██__________▓▓▓▓▓▓▓▓▒▒▒▓▓▒▒▓▒▒▓░░░░░▓▓▓▒▒▒▒▒▒▒▒▒▒▓___▓▒▓"
	@echo "___▓▒▒▒▓▓▓▒▒▒▒▒█_________▓▓▓▓▓▓▓▓▓▓▒▒▒▓▓▒▓▒▒▒▓░░░░░▓▓▓▒▒▒▒▒▒▒▒▒▒▓___▓▒▓"
	@echo "__▓▒▒▓▓▓▓▓▒▒▒▒▒________▓▓▓▓▓_______█▒▒▒▒▓▒▓▒▒▒▒▓░░░░░▓▓▓▒▒▒▒▒▒▒▒▒▓_____▓"
	@echo "__▓▒▓▓▓▓▓▓▒▒▒▒▒_______▓▓▓▓▓_______▄█▒▒▒▒▒▓▒▒▒▒▒▓░░░░░▓▓▓▒▒▒▒▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▒▒▒▒▒______▓▓▓▓▓______▄███▒▒▒▒▒▒▒▒▒▒▒▓░░░░░░▓▓▒▒▒▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▒▒▒▒▒______▓▓▓▓██▄▄▄████▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓░░░░░▓▓▒▒▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▓▒▒▒▒▒_____▓▓▓▓████___██▒▒▒▒▒▒▒▒▒▓▓▓____▓░░░░░▓▓▒▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒____▓▓▓▓████▄▄██▒▒▒▒▒▒▒▒▓▓▓____██▓░░░░░░▓▒▒▒▒▒▒▓"
	@echo "_▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒____▓▓▓▓███████▒▒▒▒▒▒▒▒▓▓▓__▄███__▓▓░░░░░▓▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒___▓▓▓▓█████▒▒▒▒▒▒▒▒▒▓▓_█▀▀██______▓▓░░░░▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▓▒▓▒▒▒▒▒▒▒__▓▓▓▓▓███▒▒▒▒▒▒▒▒▒▒▓▓█▄▄█___________▓▓▓░▒▒▒▒▒▓"
	@echo "__▓▓▓▓▓▓▓▓▓▒▒▓▒▒▒▒▒▒▒▒▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▓▒▒▓███_________________▓▓▓▒▒▒▒▓"
	@echo "___▓▓▓▓▓▓▓▓▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒██_______________________▓▓▓▒▓"
	@echo "____▓▓▓▓▓▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓__________________________▓▓"
	@echo "____▓▓▓▓▓▓▓▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▓"
	@echo "_____▓▓▓▓▓▓▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒░▓▓▓▒▒▒▒▒▒▒▒▒▒▓"
	@echo "______▓▓▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▒▒▒▒▒▒▒░░▓▓▓▓▓▒▒▒▒▓▓▓"
	@echo "_______▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▒▒▒▒░░░▓▓▓▓"
	@echo "_________▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓░▓▓▒▒▒░░░▓"
	@echo "__________▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓░░▓▓▓▓▒▒▓▓"
	@echo "____________▓▒▒▒▒▒▒▒▒▒▒▒▓░░░▒▒▓▓▓▒▓▓"
	@echo "____________▓▒▒▒▒▒▒▒▒▒▒▓░░░▒▒▓▒▒▒▓▓▓"
	@echo "_____________▓▒▒▒▒▒▒▒▒▓░░░▒▒▒▓▒▒▒▓▓▓▓"
	@echo "_____________▓▒▒▒▒▒▒▒▓░░▒▒▒▒▓▒▒▒▓▓▓▓"
	@echo "_____________▓▒▒▒▒▒▒▓░░▒▒▒▒▓▒▒▒▓▓▓▓▓"
	@echo "______________▓▒▒▒▒▓░░▒▒▒▓▓▒▒▒▓▓▓▓▓▓"
	@echo "______________▓▒▒▒▓░░▒▒▒▓▓▒▒▒▓▓▓▓▓▓"
	@echo "_______________▓▒▓░░▒▒▒▓▒▒▒▓▓▓▓▓▓▓"
	@echo "________________▓▓░▒▒▓_▓▒▒▒▓▓▓▓▓▓"
	@echo "________________▓░░▒▓_▓▒▒▒▓▓▓▓▓▓"
	@echo "_________________▓░▒▓_▓▒▒▓▓▓▓▓▓"
	@echo "__________________▓▒▓_▓▒▓▓▓▓▓"
	@echo "___________________▓▓_▓▓▓▓▓▓"
	@echo "_______________________▓▓▓▓▓"
	@echo "________________________▓▓▓"
	@echo "________________________▓▓"

clean:
	$(MAKE) $(SHARED) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
