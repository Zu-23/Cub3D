#include"lib_gnl/lib/libft.h"


#include<stdio.h>



int coom_counter(char *line)
{
    int i;
    int coom;
    int state;
    i = 0;
    coom = 0;
    state = 0;
    while (line[i])
    {
		if (coom == 2 && line[i] != ' ' && !ft_isdigit(line[i]))
			printf("get_ccomed");
		while (ft_isdigit(line[i]))
		{
			state = 1;
			printf("digit %c ", line[i]);
			i++;
		}
        if (line[i] == ',')
        {
            if (state)
            {
                coom++;
                state--;            
            }
			else
				printf("exit\n");
        }
		i++;
    }
	return (coom);
}

int main()
{
    char line[100] = "F 242,    232    , 210  ";
    char *r;
   if (coom_counter(line) != 2)
		printf("you have been coomed\n %d ", coom_counter(line));
	printf("line %s\n", line);
    printf("first call %s\n", ft_strtok(line, " "));
    while(1)
    {
        r = ft_strtok(NULL," ,\n");
        printf("%s\n", r);
        if (!r)
            break;
    }

}