NAME = built_ins

SRCS =	builtins/cd_utils.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		env/ft_print_sortedenv.c \
		env/ft_env_len.c \
		env/ft_env_tostr.c \
		env/ft_is_validenv.c \
		env/ft_env_add.c \
		env/ft_get_envname.c \
		env/ft_isin_env.c \
		env/ft_sizeenv.c \
		env/ft_strenv_len.c \
		env/ft_sortenv.c \
		exec/bin.c \
		exec/builtins.c \
		exec/exec.c \
		exec/utils.c \
		test_program.c \

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


