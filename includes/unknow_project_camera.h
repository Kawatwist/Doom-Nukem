#ifndef UNKNOW_PROJECT_CAMERA_H
# define UNKNOW_PROJECT_CAMERA_H

// #include "unknow_project_vector.h"
#include "unknow_project_window.h"
#include "unknow_project_math.h"
#include "unknow_project_system.h"
#include "unknow_project_geometry.h"

typedef struct	s_camera
{
	t_matrix	model;
	t_matrix	view;
	t_matrix	projection;

	t_matrix	mvp;
	t_vector3	clipping_list[6];
	t_vector3	clipping_list_uv[6];
	t_triangle_list
				triangle_color_list;
	t_color_list
				color_list;

	t_triangle_list
				triangle_texture_list;
	t_uv_list	uv_list;
	t_color_list
				darkness_list;

	t_vector3	pos;
	float		pitch; // l'angle pour l'axis y
	float		yaw; // l'angle pour l'axis x
	float		speed;
	float		running;
	float		slowing;

	t_vector3	forward;
	t_vector3	right;
	t_vector3	up;

	t_vector3	sun_direction;

	float		fov;
	float		near;
	float		far;
}				t_camera;

t_camera	create_t_camera(t_vector3 p_pos, float p_fov, t_vector2 p_dist);
t_camera	*initialize_t_camera(t_vector3 p_pos, float p_fov, t_vector2 p_dist);
void		free_t_cam(t_camera dest);
void		delete_t_cam(t_camera *dest);
t_matrix	compute_projection_matrix(t_camera *p_cam);
void		compute_t_camera(t_camera *cam);
void		t_camera_change_fov(t_camera *cam, float delta);
t_vector3	apply_t_camera(t_vector3 *src, t_matrix *mvp);
t_matrix	t_camera_compute_view(t_camera *cam);
void		t_camera_look_at_point(t_camera *cam, t_vector3 target);
void		t_camera_look_at(t_camera *cam);
void		t_camera_change_view(t_camera *cam, float delta_yaw, float delta_pitch);
void		handle_t_camera_mouvement_by_key(t_camera *cam, t_keyboard *p_keyboard);
void		handle_t_camera_view_by_mouse(t_camera *cam, t_mouse *p_mouse);
int			clip_triangle_to_plane(t_camera *p_camera, t_vector3 *p_points, t_vector3 *p_points_uv);
void		draw_triangle_from_camera_on_screen(t_window *p_win, t_camera *p_cam);
void 		t_camera_calc_depth(t_window *p_win, t_camera *p_cam);
void		draw_depth_from_camera_on_screen(t_window *p_win, t_camera *p_cam);

#endif
