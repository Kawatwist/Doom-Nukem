#ifndef UNKNOW_PROJECT_STRUCTURE_H
# define UNKNOW_PROJECT_STRUCTURE_H

# include "unknow_project_geometry.h"

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
	float		a;
}				t_color;

t_color		create_t_color(float p_r, float p_g, float p_b, float p_a);
t_color		*initialize_t_color(float p_r, float p_g, float p_b, float p_a);
t_color 	create_t_color_from_int(int p_r, int p_g, int p_b, int p_a);
t_color 	*initialize_t_color_from_int(int p_r, int p_g, int p_b, int p_a);
t_color		fuze_t_color(t_color src1, t_color src2);
t_color		merge_t_color(t_color src1, t_color delta);
void 		print_t_color(t_color p_color, char *str);

typedef struct	s_surface
{
	GLuint  	w;           /* largeur */
    GLuint  	h;          /* hauteur */

    GLenum  	format;          /* RVB, RVBA, Luminance, Luminance Alpha */
    GLint   	internalFormat;  /* composantes d'un texel */

    GLubyte 	*pixels;         /* données de l'image */
}				t_surface;

typedef struct	s_texture
{
	t_surface	*surface;
	GLuint		id;
}				t_texture;

t_color			get_pixel_color(t_texture *texture, int x, int y);

typedef struct	s_uv
{
	t_texture	*image;
	t_triangle	uv;
}				t_uv;

t_uv		create_t_uv(t_triangle p_triangle, t_texture *p_image);
t_uv		*initialize_t_uv(t_triangle p_triangle, t_texture *p_image);
void		print_t_uv(t_uv uv, char *texture_name);

typedef struct	s_face
{
	int			index_vertices[3];
	int			index_uvs[3];
	t_vector3	normale;
}				t_face;

t_face 			create_t_face();
t_face 			*initialize_t_face();
void 			set_t_face_vertices(t_face *face, int a, int b, int c);
void 			set_t_face_uvs(t_face *face, int a, int b, int c);

#endif
