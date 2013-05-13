##
## Makefile
## 
## Made by maxime ginters
## Login   <ginter_m@epitech.eu>
## 
## Started on  Mon May 06 13:39:56 2013 maxime ginters
## Last update Mon May 13 16:55:46 2013 maxime ginters
##

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I. -I../Shared
#CXXFLAGS	+= -ggdb3

LDFLAGS	= -L../Shared -lshared -lpthread -lboost_system

NAME	= bomberman

SRCS	= Main.cpp Server.cpp SessionSocketAcceptor.cpp Session.cpp SessionSocket.cpp SessionSocketMgr.cpp \
		  Opcodes.cpp SessionHandler.cpp \
		  Client.cpp ClientSocket.cpp ClientHandler.cpp

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

