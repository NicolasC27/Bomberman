##
## Makefile for lemipc in /home/guilbo_m/rendu/PSU/PSU_2016_lemipc
## 
## Made by Mathis Guilbon
## Login   <guilbo_m@epitech.net>
## 
## Started on  Wed Mar 29 23:47:23 2017 Mathis Guilbon
## Last update Tue Jun  6 18:33:36 2017 Jon Aristeguy
##


NAME		= test

CXX		= g++

RM		= rm -f

CXXFLAGS	= -I ./include/

SRCS		= main.cpp \
		  Entity.cpp

OBJS		= $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
