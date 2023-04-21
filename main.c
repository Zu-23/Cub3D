#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include "42-functions/LIBFT_42/libft.h"

int main()
{
	char str[] = "N   O  ./texture.xpm                         test";
    char *token = ft_strtok(str, " ");
    while (token) {
        printf("%s\n", token);
        token = ft_strtok(NULL, " ");
    }
}

/*
1- Parser
	a-	
*/