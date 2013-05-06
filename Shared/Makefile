##
## Makefile
## 
## Made by maxime ginters
## Login   <ginter_m@epitech.eu>
## 
## Started on  Mon May 06 13:35:36 2013 maxime ginters
## Last update Mon May 06 14:03:14 2013 maxime ginters
##

CXX	= g++

RM	= rm -f

AR	= ar rc
RAN	= ranlib

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I.

NAME	= libshared.a

SRCS	= ConditionalVariable.cpp \
		  Mutex.cpp \
		  Runnable.cpp \
		  ScopLock.cpp \
		  Utils.cpp \
		  Log.cpp

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS) $(LDFLAGS)
	$(RAN) $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

