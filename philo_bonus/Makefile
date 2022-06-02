# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 09:27:51 by rgatnaou          #+#    #+#              #
#    Updated: 2022/06/01 10:59:26 by rgatnaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = 	parsing.c		\
		philosophers.c	\
		utils.c			\
		creat.c			\
		state.c

CC = cc

FLAGS = -Wall -Wextra -Werror -g

HEADER = philosophers.h

OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :	fclean all
