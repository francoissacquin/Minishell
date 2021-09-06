/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:53:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/02 18:47:00 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_element
{
	int			nb;
	void		*next;
	void		*previous;
}				t_element;

typedef struct s_list
{
	t_element	*first;
	int			lenght;
}				t_list;

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		ft_strlcat(char *dest, char *src, unsigned int size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_is_in_set(char c, char const *charset);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *src);
void	*ft_malloc(void *data, int size);
void	addelement(t_list *l, int nb);
void	addelementend(t_list *l, int nb);
void	delelement(t_list *l);
void	delelementend(t_list *l);
void	listdisplay(t_list *l);
void	listdisplayreverse(t_list *l);
void	destroylist(t_list *l);
int		listlen(t_list *l);
int		mediane2(t_list *tosort, int size);
int		*chainedtoarr(t_list *tosort, int size);
int		ft_strcmp(char *s1, char *s2);


/*
** bonus
*/

/*
** t_list	*ft_lstnew(void *content);
*/
#endif
