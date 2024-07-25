# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fli <fli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 17:19:02 by fli               #+#    #+#              #
#    Updated: 2024/07/25 16:01:21 by fli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= cc -pthread -g3

CFLAGS	= -Werror -Wextra -Wall

INCLUDE	=	-I ../includes/

SRC			=	philo_utils.c \
				philo_utils2.c \
				philo.c \
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

.PHONY: $(NAME) all clean fclean re
