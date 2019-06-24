#ifndef UNKNOW_PROJECT_GEOMETRY_H
# define UNKNOW_PROJECT_GEOMETRY_H

# include "unknow_project_vector.h"

typedef struct	s_triangle
{
	t_vector3	a;
	t_vector3	b;
	t_vector3	c;
}				t_triangle;

t_triangle		create_t_triangle(t_vector3 p_a, t_vector3 p_b, t_vector3 p_c);
t_triangle		*initialize_t_triangle(t_vector3 p_a, t_vector3 p_b, t_vector3 p_c);
void 			sort_t_triangle_points(t_triangle *p_triangle);
void			print_t_triangle(t_triangle p_triangle, char *triangle_name);
t_triangle		t_triangle_add_vector3(t_triangle triangle, t_vector3 to_add);
t_triangle		mult_triangle_by_vector3(t_triangle triangle, t_vector3 to_add);
void			t_triangle_get_min_max_value(t_triangle *triangle, t_vector3 *min, t_vector3 *max);
int				t_triangle_equal(t_triangle a, t_triangle b);
int				t_triangle_is_bigger(t_triangle a, t_triangle b);

typedef struct	s_line
{
	t_vector3	a;
	t_vector3	b;
}				t_line;

t_line			create_t_line(t_vector3 p_a, t_vector3 p_b);
t_line			*initialize_t_line(t_vector3 p_a, t_vector3 p_b);

#endif
