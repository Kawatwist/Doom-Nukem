#ifndef UNKNOW_PROJECT_LIST_H
# define UNKNOW_PROJECT_LIST_H

# include "unknow_project_mesh.h"

typedef struct	s_mesh_list
{
	t_mesh		*mesh;
	int			size;
	int			max_size;
}				t_mesh_list;

t_mesh_list 	create_t_mesh_list();
t_mesh_list 	*initialize_t_mesh_list();
void			t_mesh_list_push_back(t_mesh_list *dest, t_mesh to_add);
void			t_mesh_list_erase(t_mesh_list *dest, int index);
void			free_t_mesh_list(t_mesh_list dest);
void			delete_t_mesh_list(t_mesh_list *dest);
void			clean_t_mesh_list(t_mesh_list *dest);
t_mesh			t_mesh_list_at(t_mesh_list *dest, int index);
t_mesh			*t_mesh_list_get(t_mesh_list *dest, int index);

#endif
