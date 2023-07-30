# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhaddoum <zhaddoum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 16:27:08 by zhaddoum          #+#    #+#              #
#    Updated: 2023/07/30 17:04:16 by zhaddoum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME :=		cube3D

LIBFT_SRCS = $(shell cat lib_gnl/lib/Makefile | grep "SRCS " | cut -d '=' -f 2)

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

OBJS_DIR = objs/

CC :=		gcc
CFLAGS :=	-Wall -Wextra -Werror -g
LIBS :=		-L$(DIR) -lmlx -lm -lX11 -lXext
LIBS2 :=	-lmlx -framework OpenGL -framework AppKit
LIBFT :=	lib_gnl/lib/libft.a
GNL	:=		get_next_line.o
SRC :=		parser.c main.c rendering.c raycaster.c hooks.c movements.c rendering2.c \
parser2.c parser3.c raycaster2.c get_next_line.c
OBJ	:=		$(SRC:.c=.o)

LIB_OBJ_DIR := $(addprefix lib_gnl/lib/, $(LIBFT_OBJS))
OBJ_DIR := $(addprefix objs/, $(OBJ))

all: $(NAME)

$(NAME): $(LIB_OBJ_DIR) $(OBJ_DIR) cub3d.h get_next_line.h
	$(CC) $(CFLAGS) $(OBJ_DIR) $(LIBFT) $(LIBS2) -o $(NAME)
	@echo "build complete!"

$(OBJS_DIR)%.o: %.c cub3d.h
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

lib_gnl/lib/%.o: lib_gnl/lib/%.c
	@$(MAKE) -C lib_gnl/lib --quiet

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C lib_gnl/lib fclean --quiet

fclean: clean
	@rm -rf $(NAME)

re: fclean all
	@$(MAKE) -C lib_gnl/lib --quiet