#ifndef UNKNOW_PROJECT_MESH_H
# define UNKNOW_PROJECT_MESH_H

# include "unknow_project_basic_list.h"
# include "unknow_project_camera.h"
# include "unknow_project_window.h"

typedef struct	s_mesh
{
	t_vector3	pos;
	t_vector3	center;
	int			is_visible;
	float		bubble_radius;

	t_vector3	angle;
	t_vector3	forward;
	t_vector3	right;
	t_vector3	up;

	t_vector3	velocity; // express in Ud / f in 3 axis
	float		kinetic;

	t_texture	*texture;
	t_color		color;

	t_vector3_list *check_list; // utils for gravity
	t_triangle_list	*triangle_check_list; //utils for gravity
	int			connected;

	t_vector3_list
				*vertices;
	t_vector3_list
				*uvs;
	t_vector3_list
				*normales;
	t_face_list	*faces;
}				t_mesh;

t_mesh		create_t_mesh(t_vector3 pos);
t_mesh		read_obj_file(char *path, t_vector3 pos, t_vector3 size, float gravity);
t_mesh		*initialize_t_mesh(t_vector3 pos);
void		free_t_mesh();
void		delete_t_mesh();
void		t_mesh_add_point(t_mesh *dest, t_vector3 new_point);
void		t_mesh_add_uv(t_mesh *dest, t_vector3 new_uv);
void		t_mesh_add_face(t_mesh *dest, t_face new_face);
void 		t_mesh_set_texture(t_mesh *dest, t_texture *p_texture);
void 		t_mesh_set_color(t_mesh *dest, t_color p_color);
void		t_mesh_compute_normals(t_mesh *mesh);
void		t_mesh_compute_bubble_box(t_mesh *mesh);

void		t_mesh_apply_velocity(t_mesh *dest);
void		t_mesh_add_velocity(t_mesh *dest, t_vector3 delta_velocity);
void		t_mesh_set_velocity(t_mesh *dest, t_vector3 new_velocity);
void		t_mesh_activate_gravity(t_mesh *dest, float gravity);

t_mesh		create_primitive_cube(t_vector3 coord, t_vector3 size, t_texture *texture, float gravity);
t_mesh		create_primitive_plane(t_vector3 pos, t_vector3 size, t_texture *texture, float gravity);
t_mesh		create_primitive_vertical_plane(t_vector3 pos, t_vector3 size, t_texture *p_texture, float gravity);

void 		draw_t_mesh(t_window *p_win, t_camera *p_cam, t_mesh *mesh);
void		t_mesh_rotate(t_mesh *mesh, t_vector3 delta_angle);
void		t_mesh_rotate_around_point(t_mesh *mesh, t_vector3 delta_angle, t_vector3 center);
void		t_mesh_look_at(t_mesh *mesh);
void		t_mesh_translate(t_mesh *dest, t_vector3 delta);

void		t_mesh_set_visibility(t_mesh *dest, int new_state);
void		t_mesh_compute_check_list(t_mesh *dest);

#endif
