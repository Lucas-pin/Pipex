# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 11:22:27 by lpin              #+#    #+#              #
#    Updated: 2024/08/17 21:37:37 by lpin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./src/pipex.c ./src/pipex_utils.c ./src/pipex_cmd_list.c
LIBFT = ./libft/libft.a
OBJS = $(SRCS:.c=.o)


NAME = pipex

RM = rm -f

HEADER = ./src/pipex.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT):
	@make all -C libft

.PHONY: clean fclean re

clean:
	@$(RM) $(OBJS)
	@make clean -C libft
	@echo "Pipex cleaning done."

fclean: clean
	@$(RM) $(OBJS) $(NAME)
	@make fclean -C libft
	@echo "Pipex full cleaning done."

re: fclean all
	@echo "Pipex rebuild done"
#re: Genera un rebuild del objetivo