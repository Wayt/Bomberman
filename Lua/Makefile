##
## Makefile
## 
## Made by Aymeric Girault
## Login   <giraul_b@epitech.eu>
## 
## Started on  Mon May 13 14:24:27 2013 Aymeric Girault
## Last update Mon May 13 15:06:42 2013 Aymeric Girault
##

SRC		= main.cpp

NAME		= a.out

CXXFLAGS 	= -Wall -Wextra -W -Werror

LDFLAGS		= -llua

OBJ		= $(SRC:.cpp=.o)

RM		= rm -f

CXX		= g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
