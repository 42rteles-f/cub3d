/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:33:30 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 19:25:52 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#define HERE write(2, "here\n", 5)
#define THERE write(2, "there\n", 6)

typedef struct s_list	t_list;

struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*previous;
};

int					ft_atoi(const char *nptr);
char				*ft_itoa(int number);
int					ft_isspace(char c);
void				*ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t n, size_t xsize);
char				*ft_strchr(const char *string, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_strlen(const char *string);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
void				*trim_no_memory(char *str, char *set);
char				*substr_no_memory(char *str, int start, int end);
char				*cut_str(char *str);
char				*sttc_itoa(int number);
char				*ft_stradd(char **original, char *add);
char				*ft_strjoin(char const *s1, char const *s2);


void				*ft_memset(void *s, int c, size_t n);
char				**ft_split(char const *s, char c);

#endif