NAME = built_ins

SRCS =	builtins/cd_utils.c builtins/cd.c builtins/echo.c builtins/export.c builtins/pwd.c builtins/env/ft_print_sortedenv.c builtins/env/ft_is_validenv.c builtins/env/ft_env_add.c builtins/env/ft_get_envname.c builtins/env/ft_isin_env.c builtins/test_program.c

INCS = builtins/

OBJS = ${SRCS:.c=.o}

LIBFTDIR = libs/libft

LIBFT = libs/libft/libft.a

CC = gcc -Wextra -Wall -Werror -g

RM = rm -f

LINKS = -L${LIBFTDIR} -lft

INCLUDE = -I${LIBFTDIR} -I${INCS}

%.o:%.c
	${CC} -c $< -o $@

all: ${LIBFT} ${NAME}

${NAME}: ${OBJS}
	${CC} ${LIBFT} ${OBJS} -o ${NAME} ${LINKS}

${LIBFT}:
	@make -C ${LIBFTDIR}

clean:
	@${RM} ${OBJS}
	@make fclean -C ${LIBFTDIR}

fclean: clean
	@${RM} ${NAME} ${OBJS}
	@make fclean -C ${LIBFTDIR}

re: fclean all

.PHONY: all clean fclean re


