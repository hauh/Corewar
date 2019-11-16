/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:54:28 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 17:53:02 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
** --- memory ---
*/
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dst, void const *src, size_t n);
void			*ft_memccpy(void *dst, void const *src, int c, size_t n);
void			*ft_memmove(void *d, void const *s, size_t n);
void			*ft_memchr(void const *s, int c, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
/*
** --- chars ---
*/
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isblank(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_itoa(int n);
/*
** --- one string ---
*/
size_t			ft_strlen(char const *s);
char			*ft_strdup(char const *s);
char			*ft_strndup(char const *s, size_t n);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int c);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s);
char			*ft_strtrimc(char const *s, char c);
char			**ft_strsplit(char const *s, char c);
int				ft_atoi(char const *s);
double			ft_atof(const char *s);
char			*ft_strsub(char const *s, unsigned int start, size_t n);
char			*ft_strcapitalize(char *s);
/*
** --- two strings ---
*/
char			*ft_strcpy(char *dst, char const *src);
char			*ft_strncpy(char *dst, char const *src, size_t n);
size_t			ft_strlcpy(char *dst, char const *src, size_t n);
char			*ft_strcat(char *dst, char const *src);
char			*ft_strncat(char *dst, char const *src, size_t n);
size_t			ft_strlcat(char *dst, char const *src, size_t n);
char			*ft_strstr(char const *haystack, char const *needle);
char			*ft_strnstr(char const *haystack, char const *needle, size_t n);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
/*
** --- write ---
*/
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
/*
** --- lists ---
*/
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

#endif
