#ifndef CONTROLLERS_H
# define CONTROLLERS_H

# include <cub3d.h>

typedef struct s_matrix	t_matrix;

typedef struct	s_collect {
	void	**array;
	int		size;
	int		index;
	void	(*add)(t_collect *, void *);
	void	(*clear)(t_collect *);
	void	(*destroy)(t_collect *);
} t_collect;

struct s_matrix {
	t_object	*(*element)(int, int);
	void		(*forEach)(void (*)());
	t_matrix	*(*create)(char **);
	void		(*destroy)(void);
};


typedef struct s_lister {
    void    	(*add)();
    void    	(*forEach)();
    void    	(*destroy)(void);
	t_list		*(*find)(int);
    void    	(*delete)(void *);
} t_lister;

t_collect			*new_collection(void);
void				collection_add(t_collect *sequence, void *element);
void				collection_clear(t_collect *sequence);
void				collection_destroy(t_collect *sequence);

t_lister			*list(void *list);


#endif