# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 14:29:03 by ncolin            #+#    #+#              #
#    Updated: 2021/04/25 16:20:30 by ncolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	TICK = \342\234\224
	RE = \342\231\272
	TRASH = \360\237\227\221
else
	TICK = \xE2\x9C\x94
	RE = \xE2\x99\xBA
	TRASH = \xF0\x9F\x97\x91
endif

SRC_PATH = srcs

SRC_NAME =	philo_three.c		\
			utils.c			\
			print.c			\
			memory.c		\
			input.c			\
			init.c			\
			actions.c		\
			
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include -pthread -O2

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:%.c=%.o)

default:
	@make -s all

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $^ -o $@
	@echo "\033[32;1m\rPhilo_three compiled ${TICK}          \033[0m"

.SILENT:clean

clean:
	@rm -rf $(OBJ) philo_one.dSYM
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[32;1m\rDirectory cleaned ${TRASH}          \033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32;1m\rDirectory fully cleaned ${TRASH} ${TRASH} ${TRASH}          \033[0m"

re: 
	@echo "\033[32;1m\rPhilo_three recompiling ${RE}          \033[0m"
	@make -s fclean 
	@make -s all

bonus: all

.PHONY: all clean fclean re