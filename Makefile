# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 18:34:29 by jihi              #+#    #+#              #
#    Updated: 2026/02/18 18:17:59 by jihi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	src/main.c						\
			src/utils.c						\
			src/setup.c						\
			src/time.c						\
			src/stop.c						\
			src/print_safe.c				\
			src/routine.c					\
			src/threads.c					\
			src/forks.c						\
			src/eat.c						\
			
OBJ_DIR	=	obj
OBJ		=	$(SRC:src/%.c=$(OBJ_DIR)/%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -I include
HEADERS	=	-Iincludes
RM		=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
