/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:36:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/04 14:44:30 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# define BUFF_SIZE 4096
# define MAX_INT64 (9223372036854775807LL)

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *s1, void const *s2, size_t n);
void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void			*ft_memchr(void const *s, int c, size_t n);
void			*ft_memalloc(size_t n);
void			ft_memdel(void **ap);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			*ft_memmove(void *s1, void const *s2, size_t n);
void			ft_lstdel(t_list**alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *n);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_deltab(char **tab);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isalnum(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_atoi(char const *str);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_occur(char const *s, char c);
int				ft_countwords(char const *s);
int				ft_sqrt(int nb);
int				ft_isblank(char *str);
int				ft_strlenu(char *str);
char			*ft_strdup(char const *s);
char			*ft_strcpy(char *dest, char const *src);
char			*ft_strncpy(char *dest, char const *src, unsigned int n);
char			*ft_strcat(char *dest, char const *src);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int start, int c);
char			*ft_strncat(char *dest, char const *src, size_t n);
char			*ft_itoa(int c);
char			*ft_strstr(char const *s1, char const *s2);
char			*ft_strnstr(char const *s1, char const *s2, size_t e);
char			*ft_strnew(size_t n);
char			*ft_strmap(char const *s1, char (*f)(char));
char			*ft_strmapi(char const *s1, char (*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			**ft_strsplit(char const *s, char c);
char			*ft_strtrim(char const *s);
char			*ft_fill(char *s, char c);
char			*ft_realloc(char *str, int size);
char			*ft_strndup(const char *s, size_t n);
size_t			ft_strlcat(char *dest, char const *src, size_t n);
size_t			ft_strlen(char const *s);
t_list			*ft_lstnew(void const *content, size_t content_size);
size_t			ft_strchri(const char *s, int c);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				get_next_line(const int fd, char **line);
char			*ft_strlower(char *str);
char			*ft_strupper(char *str);
char			*ft_strnncpy(char *dest, char const *src,
	unsigned int i, unsigned int n);
const char		*ft_conststrjoin(char const *s1, char const *s2);
char			*ft_strjoinnf(char const *s1, char const *s2);

#endif
