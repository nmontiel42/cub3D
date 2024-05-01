NAME	= cub3D
LIBMLX	= ./MLX42
LIBFT	= ./libft


HEADERS	= -I ./includes -I ${LIBMLX}/include -I ${LIBFT}
LIBGL	= -lglfw -L"/Users/nmontiel/.brew/opt/glfw/lib"
LIBS	= ${LIBGL} ${LIBMLX}/libmlx42.a ${LIBFT}/libft.a
SRCS	= main.c \
			map.c \
			utils.c \
			check_map.c \
			error.c

OBJS	= ${SRCS:.c=.o}

all: libft libmlx ${NAME}

libft:
	@${MAKE} -C ${LIBFT}

libmlx:
	@${MAKE} -C ${LIBMLX}

%.o: %.c
	@${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}: ${OBJS}
	@${CC} ${DFLAGS} ${OBJS} ${LIBS} ${HEADERS} -o ${NAME}

clean:
	@rm -f ${OBJS}
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${LIBMLX} clean

fclean: clean
	@rm -f ${NAME}
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${LIBMLX} fclean
	
re: clean all

norma: 
	norminette ${SRCS}

.PHONY: all, clean, fclean, re, libmlx, libft