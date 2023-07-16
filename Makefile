NAME :=		cube3D

CC :=		gcc
FLAGS :=	-Wall -Wextra -Werror -lm -g 
DIR :=		minilibx-linux
LIBFT :=	./lib_gnl/lib/libft.a
GNL	:=		./lib_gnl/gnl/get_next_line.o
SRC :=		$(wildcard *.c)
OBJ	:=		$(SRC:.c=.o)
MLX := 		mlx_repo/libmlx42.a -I./mlx_repo/glfw -L./mlx_repo/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
all: $(NAME)
#dont forget making rule for the OBJ
$(NAME): $(LIBFT) $(GNL)
	@$(CC) $(FLAGS) $(MLX) $(SRC) $(LIBFT) $(GNL) -o $(NAME)
	@echo "build complete!"
$(LIBFT) :
	@$(MAKE) -C lib_gnl/lib --quiet
$(GNL) :
	@$(MAKE) -C lib_gnl/gnl --quiet
clean:
	@rm -f 

fclean: clean
	@rm -f $(NAME)

re: fclean all