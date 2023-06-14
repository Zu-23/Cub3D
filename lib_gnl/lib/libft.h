#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
#include "stdio.h"

typedef struct s_list
{
	void    *content;
	struct s_list   *next;
}   t_list;

char	    *ft_strtok(char *str, char *delim);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strcpy(char *dest, const char *src);
int         ft_isalpha(int c);
int         ft_isdigit(int c);
int         ft_isalnum(int c);
int         ft_isascii(int c);
int         ft_isprint(int c);
int         ft_tolower(int c);
int         ft_toupper(int c);
char        *ft_strchr(const char *str, int c);
size_t      ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t      ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t      ft_strlen(const char *str);
int         ft_strncmp(const char *s1, const char *s2, size_t n);
char        *ft_strnstr(const char *str, const char *to_find, size_t n);
void        *ft_memset(void *s, int c, size_t n);
void        *ft_memmove(void *dest, const void *src, size_t n);
void        *ft_memchr(const void *s, int c, size_t n);
void        *ft_memcpy(void *dest, const void *src, size_t n);
int         ft_memcmp(const void *s1, const void *s2, size_t n);
void        ft_bzero(void *s, size_t n);
char        *ft_strrchr(const char *s, int c);
int         ft_atoi(const char *str);
void        *ft_calloc(size_t count, size_t size);
char        *ft_strdup(const char *s1);
char        *ft_substr(char const *s, unsigned int start, size_t len);
char        *ft_strjoin(char const *s1, char const *s2);
char        *ft_strtrim(char const *s1, char const *set);
char        **ft_split(char const *str, char c);
void        ft_putchar_fd(char cara, int file_d);
void        ft_putstr_fd(char *str, int file_d);
void        ft_putnbr_fd(int nb, int file_d);
void        ft_putendl_fd(char *str, int file_d);
char        *ft_itoa(int n);
char        *ft_strrev(char *str);
char        *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void        ft_striteri(char *s, void (*f) (unsigned int, char *));

void    ft_lstadd_back(t_list **lst, t_list *new);
void    ft_lstadd_front(t_list **lst, t_list *new);
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    ft_lstdelone(t_list *lst, void (*del)(void *));
t_list  *ft_lstlast(t_list *lst);
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list  *ft_lstnew(void *content);
int     ft_lstsize(t_list *lst);
void    ft_lstiter(t_list *lst, void (*f)(void *));

#endif

