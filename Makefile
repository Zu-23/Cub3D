NAME :=		cube3D

CC :=		gcc
FLAGS :=	-Wall -Wextra -Werror
DIR :=		minilibx-linux
LIBS :=		-L$(DIR) -lmlx -lm -lX11 -lXext
LIBFT :=	42-functions/LIBFT_42/libft.a
GNL	:=		42-functions/Get_next_line_42/get_next_line.o
SRC :=		main.c
OBJ	:=		$(SRC:.c=.o)

all: $(NAME)
#dont forget making rule for the OBJ
$(NAME): $(LIBFT) $(GNL)
	@$(CC) $(FLAGS) main.c $(LIBS) $(LIBFT) $(GNL) -o $(NAME)
	@echo "build complete!"
$(LIBFT) :
	@$(MAKE) -C 42-functions/LIBFT_42 --quiet
$(GNL) :
	@$(MAKE) -C 42-functions/Get_next_line_42 --quiet
clean:
	@rm -f 

fclean: clean
	@rm -f $(NAME)

re: fclean all