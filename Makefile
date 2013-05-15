##
## Makefile
## 
## Made by maxime ginters
## Login   <ginter_m@epitech.eu>
## 
## Started on  Mon May 06 13:39:56 2013 maxime ginters
## Last update Wed May 15 18:22:06 2013 fabien casters
##

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I. -IShared -IClient -IServer -IGraphic -ILibrary
CXXFLAGS	+= -fopenmp
#CXXFLAGS	+= -ggdb3

UNAME	:= $(shell uname -a)

LDFLAGS	= -LShared -lshared -lpthread -lboost_system -lgomp
LDFLAGS	+= -lGL -lGLU -lgdl_gl -LLibrary -Wl,-rpath=Library

ifneq (, $(findstring ARCH, $(UNAME)))
    LDFLAGS	+= -lSOIL
endif

NAME	= bomberman

SRCS	= Main.cpp Position.cpp MotionMaster.cpp MovementIdle.cpp MovementPlayer.cpp \
		  Opcodes.cpp \
		  Server/SessionHandler.cpp Server/Map.cpp Server/MapObject.cpp Server/Player.cpp \
		  Server/Server.cpp Server/SessionSocketAcceptor.cpp Server/Session.cpp Server/SessionSocket.cpp Server/SessionSocketMgr.cpp \
		  Client/Client.cpp Client/ClientSocket.cpp Client/ClientHandler.cpp Client/ClientObject.cpp \
		  Graphic/GameMonitor.cpp Graphic/Camera.cpp Graphic/Vector.cpp Graphic/Model.cpp

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

