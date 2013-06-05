##
## Makefile
## 
## Made by maxime ginters
## Login   <ginter_m@epitech.eu>
## 
## Started on  Mon May 06 13:39:56 2013 maxime ginters
## Last update Wed May 15 16:15:04 2013 fabien casters
##

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I. -I../Library -I../Shared
CXXFLAGS	+= -ggdb3

LDFLAGS	= -lGL -lGLU -lgdl_gl -L../Library -Wl,-rpath=../Library -lSOIL

NAME	= bomberman

SRCS	= main.cpp GameMonitor.cpp Vector.cpp Camera.cpp SelectBox.cpp Menu.cpp SubMenu.cpp SubObject.cpp CheckBox.cpp ListBox.cpp InputBox.cpp

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

