##
## Makefile
## 
## Made by maxime ginters
## Login   <ginter_m@epitech.eu>
## 
## Started on  Mon May 06 13:39:56 2013 maxime ginters
## Last update Mon Jun 03 19:05:49 2013 maxime ginters
##

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I. -IShared -IClient -IServer -IGraphic -ILibrary -IServer/AI
CXXFLAGS	+= -fopenmp
CXXFLAGS	+= -ggdb3
CXXFLAGS	+= -I/usr/include/lua5.1

UNAME	:= $(shell uname -a)

LDFLAGS	= -LShared -lshared -lpthread -lboost_system -lgomp
LDFLAGS	+= -lGL -lGLU -lgdl_gl -LLibrary -Wl,-rpath=Library
LDFLAGS	+= -llua
LDFLAGS	+= -llua5.1
LDFLAGS	+= -lluabind
LDFLAGS	+= -lSOIL

NAME	= bomberman

SRCS	= Main.cpp Position.cpp MotionMaster.cpp MovementIdle.cpp MovementPlayer.cpp MovementPoint.cpp GameObject.cpp \
		  Opcodes.cpp ModelMgr.cpp ScoreMgr.cpp \
		  Server/SessionHandler.cpp Server/Map.cpp Server/MapObject.cpp Server/Player.cpp \
		  Server/Server.cpp Server/SessionSocketAcceptor.cpp Server/Session.cpp Server/SessionSocket.cpp \
		  Server/SessionSocketMgr.cpp Server/Bomb.cpp Server/Object.cpp Server/AI/ObjectAI.cpp \
		  Client/Client.cpp Client/ClientSocket.cpp Client/ClientHandler.cpp Client/ClientObject.cpp \
		  Client/ChatBox.cpp \
		  Graphic/GameMonitor.cpp Graphic/Camera.cpp Graphic/Vector.cpp Graphic/GraphicObject.cpp Graphic/ModelFactory.cpp \
		  Server/PathFinder.cpp Server/PathFindingRunnable.cpp

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

