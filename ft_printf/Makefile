NAME			= libftprintf.a

SRCS			= parser_spec.c ft_printf.c char.c nums.c

OBJ_DIR			= obj/

OBJS			= $(addprefix ${OBJ_DIR}, ${SRCS:.c=.o})

OBJS_D			= $(addprefix ${OBJ_DIR}, ${SRCS:.c=.d})

PHEADER			= ft_printf.h

LIBFT			= ./libft/libft.a

CC				= gcc

FLAGS			= -Wall -Werror -Wextra -O2 -MMD

${OBJ_DIR}%.o:	%.c
				${CC} ${FLAGS} -c $< -o $@

all:			${OBJ_DIR} ${NAME}

${LIBFT}:		FORCE
				@${MAKE} -C ./libft all

${OBJ_DIR}:
				@mkdir -p ${OBJ_DIR}

${NAME}:		${OBJS} ${LIBFT} ${PHEADER} 
				cp libft/libft.a ${NAME}
				ar -rcs ${NAME} ${OBJS}

FORCE:			;

bonus:			all

clean:
				@${MAKE} -C ./libft clean
				@rm -rf ${OBJ_DIR}
				@echo "Clean: Done."

fclean:			clean
				@${MAKE} -C ./libft fclean
				@rm -f ${NAME}
				@echo "Fclean: Done."

re:				fclean all

.PHONY:			 all clean fclean re bonus

-include		${OBJS_D}
