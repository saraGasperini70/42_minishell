NAME = built_ins

SRCS = builtins/echo.c builtins/cd.c builtins/export.c builtins/env/ft_print_sortedenv.c builtins/env/ft_is_validenv.c builtins/test_program.c

INCS = builtins/

OBJS = ${SRCS:.c=.o}

LIBFTDIR = ./libs/libft

LIBFT = ${LIBFTDIR}/libft.a

CC = gcc -Wextra -Wall -Werror -g

RM = rm -f

LINKS = -L${LIBFTDIR} -lft

INCLUDE = -I${LIBFTDIR} -I${INCS}

%.o:%.c
	${CC} ${INCLUDE} -c $< -o $@ ${LINKS}

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


