# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 16:57:06 by euyi              #+#    #+#              #
#    Updated: 2023/03/05 15:30:28 by euyi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_containers

SRC		=	tests/vectorMain.cpp	tests/mapMain.cpp	\
			tests/stackMain.cpp	main.cpp

OBJ			=	$(SRC:.cpp=.o)

CXX			=	c++

CXXFLAGS	=	#-Wall -Werror -Wextra	#-std=c++98

all:		$(NAME)

vector:
			$(CXX) -D_VECTOR_ $(CXXFLAGS) $(SRC) -o $(NAME)

map:
			$(CXX) -D_MAP_ $(CXXFLAGS) $(SRC) -o $(NAME)

stack:
			$(CXX) -D_STACK_ $(CXXFLAGS) $(SRC) -o $(NAME)

$(NAME):	$(OBJ)
			$(CXX)	$(CXXFLAGS) $(OBJ)	-o $(NAME)

clean:		
			/bin/rm -f $(OBJ)
				
fclean:		clean
			/bin/rm -f $(NAME)
			clear

re:			fclean	all

.PHONY:		all	clean	fclean	re
