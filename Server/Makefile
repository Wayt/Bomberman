##
## Makefile
## 
## Made by maxime ginters
## Login   <ginter_m@epitech.eu>
## 
## Started on  Mon May 06 13:39:56 2013 maxime ginters
## Last update Wed May 15 13:46:37 2013 maxime ginters
##

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I. -I../Shared
CXXFLAGS	+= -fopenmp
#CXXFLAGS	+= -ggdb3

LDFLAGS	= -L../Shared -lshared -lpthread -lboost_system -lgomp

NAME	= bomberman

SRCS	= Main.cpp Server.cpp SessionSocketAcceptor.cpp Session.cpp SessionSocket.cpp SessionSocketMgr.cpp \
		  Opcodes.cpp SessionHandler.cpp Map.cpp MapObject.cpp Player.cpp \
		  Client.cpp ClientSocket.cpp ClientHandler.cpp \
		  Position.cpp MotionMaster.cpp MovementIdle.cpp MovementPlayer.cpp

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

