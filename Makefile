# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ali <ali@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 12:56:58 by ali               #+#    #+#              #
#    Updated: 2022/09/07 16:14:37 by ali              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g
NAME = tests
FT = ft
STL = stl
SRC_FT = ft.cpp
SRC_STL = stl.cpp
SRC_MAIN = main.cpp
OBJ_FT = $(SRC_FT:.cpp=.o)
OBJ_STL = $(SRC_STL:.cpp=.o)
OBJ_MAIN = $(SRC_MAIN:.cpp=.o)
OBJS = $(OBJ_FT) $(OBJ_STL) $(OBJ_MAIN)
RESULTS = resultFT resultSTL
BIN = $(NAME) $(FT) $(STL)
INC = vector.hpp stack.hpp map.hpp utils.hpp reverse_iterator.hpp vectorIterator.hpp mapIterator.hpp
RM = rm -f

all:		$(NAME)

%.o:		%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

$(FT):		$(OBJ_FT) $(INC)
			$(CC) $(CFLAGS) -o $(FT) $(OBJ_FT)
			
$(STL):		$(OBJ_STL)
			$(CC) $(CFLAGS) -o $(STL) $(OBJ_STL)

$(NAME):	$(OBJ_MAIN) $(FT) $(STL)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAIN)

clean:
			$(RM) $(OBJS) $(RESULTS)

fclean:		clean
			$(RM) $(BIN)

re:			fclean all


