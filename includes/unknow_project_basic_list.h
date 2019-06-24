#ifndef UNKNOW_PROJECT_BASIC_LIST_H
# define UNKNOW_PROJECT_BASIC_LIST_H

# include "unknow_project_structure.h"
# include "unknow_project_geometry.h"
# include "unknow_project_vector.h"

typedef struct	s_void_list
{
	void		**data;
	int			size;
	int			max_size;
}				t_void_list;

t_void_list create_t_void_list();
t_void_list *initialize_t_void_list();
void		t_void_list_add_back(t_void_list *dest, int nb, ...);
void		t_void_list_push_back(t_void_list *dest, void *to_add);
void		free_t_void_list(t_void_list dest);
void		delete_t_void_list(t_void_list *dest);
void		clean_t_void_list(t_void_list *dest);
void		*t_void_list_at(t_void_list *dest, int index);
void		**t_void_list_get(t_void_list *dest, int index);

typedef struct	s_triangle_list
{
	t_triangle	*triangle;
	int			size;
	int			max_size;
}				t_triangle_list;

t_triangle_list create_t_triangle_list();
t_triangle_list *initialize_t_triangle_list();
void			t_triangle_list_push_back(t_triangle_list *dest, t_triangle to_add);
void			t_triangle_list_add_back(t_triangle_list *dest, t_triangle *to_add);
void			free_t_triangle_list(t_triangle_list dest);
void			delete_t_triangle_list(t_triangle_list *dest);
void			clean_t_triangle_list(t_triangle_list *dest);
t_triangle		t_triangle_list_at(t_triangle_list *dest, int index);
t_triangle		*t_triangle_list_get(t_triangle_list *dest, int index);
void			t_triangle_list_resize(t_triangle_list *dest, int new_size);

typedef struct	s_vector2_list
{
	union
	{
		t_vector2	*vector;
		float		*value;
	};
	int			size;
	int			max_size;
}				t_vector2_list;

t_vector2_list
				create_t_vector2_list();
t_vector2_list
				*initialize_t_vector2_list();
void		t_vector2_list_push_back(t_vector2_list *dest, t_vector2 to_add);
void		t_vector2_list_add_back(t_vector2_list *dest, t_vector2 *to_add);
void		free_t_vector2_list(t_vector2_list dest);
void		delete_t_vector2_list(t_vector2_list *dest);
void		clean_t_vector2_list(t_vector2_list *dest);
t_vector2	t_vector2_list_at(t_vector2_list *dest, int index);
t_vector2	*t_vector2_list_get(t_vector2_list *dest, int index);
void 		t_vector2_list_set(t_vector2_list *dest, int index, t_vector2 *vector);
float		*t_vector2_list_obtain(t_vector2_list *dest, int index);
void		t_vector2_list_resize(t_vector2_list *dest, int new_size);
void		t_vector2_list_edit(t_vector2_list *dest, int index, t_vector2 p_color);
void		t_vector2_list_set(t_vector2_list *dest, int index, t_vector2 *p_color);

typedef struct	s_vector3_list
{
	union
	{
		t_vector3
				*vector;
		float	*value;
	};
	int			size;
	int			max_size;
}				t_vector3_list;

t_vector3_list
			create_t_vector3_list();
t_vector3_list
			*initialize_t_vector3_list();
void		t_vector3_list_push_back(t_vector3_list *dest, t_vector3 to_add);
void		t_vector3_list_add_back(t_vector3_list *dest, t_vector3 *to_add);
void		free_t_vector3_list(t_vector3_list dest);
void		delete_t_vector3_list(t_vector3_list *dest);
void		clean_t_vector3_list(t_vector3_list *dest);
t_vector3	t_vector3_list_at(t_vector3_list *dest, int index);
t_vector3	*t_vector3_list_get(t_vector3_list *dest, int index);
void 		t_vector3_list_set(t_vector3_list *dest, int index, t_vector3 *vector);
float		*t_vector3_list_obtain(t_vector3_list *dest, int index);
void		t_vector3_list_edit(t_vector3_list *dest, int index, t_vector3 p_color);
void		t_vector3_list_set(t_vector3_list *dest, int index, t_vector3 *p_color);
void		t_vector3_list_resize(t_vector3_list *dest, int new_size);

typedef struct	s_vector4_list
{
	union
	{
		t_vector4
				*vector;
		float	*value;
	};
	int			size;
	int			max_size;
}				t_vector4_list;

t_vector4_list
			create_t_vector4_list();
t_vector4_list
			*initialize_t_vector4_list();
void		t_vector4_list_push_back(t_vector4_list *dest, t_vector4 to_add);
void		t_vector4_list_add_back(t_vector4_list *dest, t_vector4 *to_add);
void		free_t_vector4_list(t_vector4_list dest);
void		delete_t_vector4_list(t_vector4_list *dest);
void		clean_t_vector4_list(t_vector4_list *dest);
t_vector4	t_vector4_list_at(t_vector4_list *dest, int index);
t_vector4	*t_vector4_list_get(t_vector4_list *dest, int index);
void 		t_vector4_list_set(t_vector4_list *dest, int index, t_vector4 *vector);
float		*t_vector4_list_obtain(t_vector4_list *dest, int index);
void		t_vector4_list_edit(t_vector4_list *dest, int index, t_vector4 p_color);
void		t_vector4_list_set(t_vector4_list *dest, int index, t_vector4 *p_color);
void		t_vector4_list_resize(t_vector4_list *dest, int new_size);

typedef struct	s_vector2_int_list
{
	union
	{
		t_vector2_int
				*vector;
		int		*value;
	};
	int			size;
	int			max_size;
}				t_vector2_int_list;

t_vector2_int_list
				create_t_vector2_int_list();
t_vector2_int_list
				*initialize_t_vector2_int_list();
void		t_vector2_int_list_push_back(t_vector2_int_list *dest, t_vector2_int to_add);
void		t_vector2_int_list_add_back(t_vector2_int_list *dest, t_vector2_int *to_add);
void		free_t_vector2_int_list(t_vector2_int_list dest);
void		delete_t_vector2_int_list(t_vector2_int_list *dest);
void		clean_t_vector2_int_list(t_vector2_int_list *dest);
t_vector2_int
			t_vector2_int_list_at(t_vector2_int_list *dest, int index);
t_vector2_int
			*t_vector2_int_list_get(t_vector2_int_list *dest, int index);
void 		t_vector2_int_list_set(t_vector2_int_list *dest, int index, t_vector2_int *vector);
int			*t_vector2_int_list_obtain(t_vector2_int_list *dest, int index);
void		t_vector2_int_list_resize(t_vector2_int_list *dest, int new_size);
void		t_vector2_int_list_edit(t_vector2_int_list *dest, int index, t_vector2_int p_color);
void		t_vector2_int_list_set(t_vector2_int_list *dest, int index, t_vector2_int *p_color);

typedef struct	s_vector3_int_list
{
	union
	{
		t_vector3_int
				*vector;
		int		*value;
	};
	int			size;
	int			max_size;
}				t_vector3_int_list;

t_vector3_int_list
			create_t_vector3_int_list();
t_vector3_int_list
			*initialize_t_vector3_int_list();
void		t_vector3_int_list_push_back(t_vector3_int_list *dest, t_vector3_int to_add);
void		t_vector3_int_list_add_back(t_vector3_int_list *dest, t_vector3_int *to_add);
void		free_t_vector3_int_list(t_vector3_int_list dest);
void		delete_t_vector3_int_list(t_vector3_int_list *dest);
void		clean_t_vector3_int_list(t_vector3_int_list *dest);
t_vector3_int
			t_vector3_int_list_at(t_vector3_int_list *dest, int index);
t_vector3_int
			*t_vector3_int_list_get(t_vector3_int_list *dest, int index);
void 		t_vector3_int_list_set(t_vector3_int_list *dest, int index, t_vector3_int *vector);
int			*t_vector3_int_list_obtain(t_vector3_int_list *dest, int index);
void		t_vector3_int_list_resize(t_vector3_int_list *dest, int new_size);
void		t_vector3_int_list_edit(t_vector3_int_list *dest, int index, t_vector3_int p_color);
void		t_vector3_int_list_set(t_vector3_int_list *dest, int index, t_vector3_int *p_color);

typedef struct	s_vector4_int_list
{
	union
	{
		t_vector4_int
				*vector;
		int		*value;
	};
	int			size;
	int			max_size;
}				t_vector4_int_list;

t_vector4_int_list
			create_t_vector4_int_list();
t_vector4_int_list
			*initialize_t_vector4_int_list();
void		t_vector4_int_list_push_back(t_vector4_int_list *dest, t_vector4_int to_add);
void		t_vector4_int_list_add_back(t_vector4_int_list *dest, t_vector4_int *to_add);
void		free_t_vector4_int_list(t_vector4_int_list dest);
void		delete_t_vector4_int_list(t_vector4_int_list *dest);
void		clean_t_vector4_int_list(t_vector4_int_list *dest);
t_vector4_int
			t_vector4_int_list_at(t_vector4_int_list *dest, int index);
t_vector4_int
			*t_vector4_int_list_get(t_vector4_int_list *dest, int index);
void 		t_vector4_int_list_set(t_vector4_int_list *dest, int index, t_vector4_int *vector);
int			*t_vector4_int_list_obtain(t_vector4_int_list *dest, int index);
void		t_vector4_int_list_resize(t_vector4_int_list *dest, int new_size);
void		t_vector4_int_list_edit(t_vector4_int_list *dest, int index, t_vector4_int p_color);

typedef struct	s_color_list
{
	union
	{
		t_color	*color;
		float	*value;
	};
	int			size;
	int			max_size;
}				t_color_list;

t_color_list
				create_t_color_list();
t_color_list
				*initialize_t_color_list();
void			t_color_list_push_back(t_color_list *dest, t_color to_add);
void			t_color_list_add_back(t_color_list *dest, t_color *to_add);
void			free_t_color_list(t_color_list dest);
void			delete_t_color_list(t_color_list *dest);
void			clean_t_color_list(t_color_list *dest);
t_color			t_color_list_at(t_color_list *dest, int index);
t_color			*t_color_list_get(t_color_list *dest, int index);
void 			t_color_list_set(t_color_list *dest, int index, t_color *color);
float			*t_color_list_obtain(t_color_list *dest, int index);
void			t_color_list_resize(t_color_list *dest, int new_size);
void			t_color_list_edit(t_color_list *dest, int index, t_color p_color);
void			t_color_list_set(t_color_list *dest, int index, t_color *p_color);

typedef struct	s_uv_list
{
	t_uv		*uvs;
	int			size;
	int			max_size;
}				t_uv_list;

t_uv_list		create_t_uv_list();
t_uv_list		*initialize_t_uv_list();
void			t_uv_list_push_back(t_uv_list *dest, t_uv to_add);
void			t_uv_list_add_back(t_uv_list *dest, t_uv *to_add);
t_uv			*t_uv_list_get(t_uv_list *dest, int index);
void			clean_t_uv_list(t_uv_list *dest);

typedef struct	s_face_list
{
	t_face		*face;
	int			size;
	int			max_size;
}				t_face_list;

t_face_list		create_t_face_list(); //creer sans malloc
t_face_list		*initialize_t_face_list(); //creer avec malloc
void			t_face_list_push_back(t_face_list *dest, t_face to_add); // ajoute une t_face a la liste, a la fin, en la brut
void			t_face_list_add_back(t_face_list *dest, t_face *to_add); // ajoute une t_face a la liste, a la fin, en la copiant
void			free_t_face_list(t_face_list dest); //libere le contenu d'un t_face_list sans free le t_face_list
void			delete_t_face_list(t_face_list *dest); //libere le contenu d'un t_face_list en liberant le t_face_list
void			clean_t_face_list(t_face_list *dest); //supprime le contenu d'un t_face_list
t_face			t_face_list_at(t_face_list *dest, int index); //renvoi une copie de l'element situe a la position [index] de la liste
t_face			*t_face_list_get(t_face_list *dest, int index); //renvoi l'adresse de l'element situe a la position [index] de la liste

typedef struct	s_texture_list
{
	t_texture	*texture;
	int			size;
	int			max_size;
}				t_texture_list;

t_texture_list 	create_t_texture_list();
t_texture_list 	*initialize_t_texture_list();
void			t_texture_list_push_back(t_texture_list *dest, t_texture to_add);
void			t_texture_list_add_back(t_texture_list *dest, t_texture *to_add);
void			free_t_texture_list(t_texture_list dest);
void			delete_t_texture_list(t_texture_list *dest);
void			clean_t_texture_list(t_texture_list *dest);
t_texture		t_texture_list_at(t_texture_list *dest, int index);
t_texture		*t_texture_list_get(t_texture_list *dest, int index);

#endif
