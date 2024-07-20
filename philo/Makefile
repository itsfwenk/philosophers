# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fli <fli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 17:19:02 by fli               #+#    #+#              #
#    Updated: 2024/07/20 17:26:20 by fli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= cc -pthread

CFLAGS	= -Werror -Wextra -Wall

INCLUDE	=	-I ./includes/*

SRC_PATH	=	src/
SRC			=	philo.c \
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJ			=	$(SRC:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
