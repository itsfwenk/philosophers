# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fli <fli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 17:19:02 by fli               #+#    #+#              #
#    Updated: 2024/08/06 14:55:04 by fli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= cc -pthread -g3

CFLAGS	= -Werror -Wextra -Wall

INCLUDE	=	-I philo_bonus.h

SRC			=	create_sem.c \
				dessert.c \
				mother.c \
				philo_utils.c \
				philo_utils2.c \
				philo.c \
				routine_utils.c \
				routine.c \

OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
