# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 20:02:58 by mbasile           #+#    #+#              #
#    Updated: 2024/03/26 13:17:32 by mbasile          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC		= gcc
CFLAGS	+= -Wall -Wextra -Werror -fcommon #impedisce la non compilazione data dalla variabile globale
RM		= rm -rf


FILES		= 	./srcs/builtins/echo_utils \
				./srcs/builtins/env/env_list \
				./srcs/builtins/env/env_search \
				./srcs/builtins/env/env_utils \
				./srcs/builtins/export_utils_0 \
				./srcs/builtins/export_utils_1 \
				./srcs/builtins/ft_cd \
				./srcs/builtins/ft_echo \
				./srcs/builtins/ft_env \
				./srcs/builtins/ft_exit \
				./srcs/builtins/ft_export \
				./srcs/builtins/ft_pwd \
				./srcs/builtins/ft_unset \
				./srcs/clean_up \
				./srcs/error \
				./srcs/exec/execute \
				./srcs/exec/execute_cmd \
				./srcs/exec/find \
				./srcs/exec/redir \
				./srcs/lexer/lexer \
				./srcs/lexer/lexer_utils \
				./srcs/lexer/list \
				./srcs/main_utils \
				./srcs/minishell \
				./srcs/parser/ast \
				./srcs/parser/parse_core \
				./srcs/parser/parse_utils \
				./srcs/parser/parser \
				./srcs/parser/redir_utils \
				./srcs/signals \
				./srcs/syntax \
				./srcs/utils/ft_atoi \
				./srcs/utils/ft_calloc \
				./srcs/utils/ft_itoa \
				./srcs/utils/ft_realloc \
				./srcs/utils/ft_split \
				./srcs/utils/get_line \
				./srcs/utils/string \
				./srcs/utils/string_utils

SRC		= $(FILES:=.c)
OBJ		= $(FILES:=.o)
HEADER		= ./includes/minishell.h
INCLUDES	= -I includes -L/usr/include -lreadline
LDFLAGS	+= -lreadline


all: $(NAME)

$(NAME):  $(OBJ) $(HEADER)
	@echo "Compiling..."
	@ $(CC) $(OBJ) $(INCLUDES) $(LDFLAGS) $(OPTS) -o $(NAME)
	@echo "Compiled"

%.o: %.c $(HEADER)
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OPTS) -c $< -o $@

norm:
	@norminette | grep "Error"

clean:
	@ $(RM) $(OBJ)
	@echo "Removing .o files"

fclean: clean
	@ $(RM) $(NAME)
	@echo "Removing $(NAME)"

re: fclean all

.PHONY: all clean fclean re  norm