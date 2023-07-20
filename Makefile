NAME :=		cube3D

CC :=		gcc
FLAGS :=	-Wall -Wextra -Werror
DIR :=		minilibx-linux
LIBS :=		-L$(DIR) -lmlx -lm -lX11 -lXext
LIBS2 :=	-lmlx -framework OpenGL -framework AppKit
LIBFT :=	lib_gnl/lib/libft.a
GNL	:=		lib_gnl/gnl/get_next_line.o
SRC :=		parser.c main.c rendering.c raycaster.c hooks.c movements.c
OBJ	:=		$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(FLAGS) $(OBJ)  $(LIBFT) $(GNL) $(LIBS2) -o $(NAME)
	@echo "build complete!"

%.o: %.c cub3d.h
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT) :
	@$(MAKE) -C lib_gnl/lib --quiet
$(GNL) :
	@$(MAKE) -C lib_gnl/gnl --quiet
clean:
	@rm -f $(OBJ) $(GNL)
	@$(MAKE) -C lib_gnl/lib fclean --quiet

fclean: clean
	@rm -f $(NAME)

re: fclean all