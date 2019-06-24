#ifndef UNKNOW_PROJECT_H
# define UNKNOW_PROJECT_H

# include "unknow_project_includes.h"
# include "unknow_project_define.h"

# include "unknow_project_basic.h"
# include "unknow_project_math.h"
# include "unknow_project_drawing.h"
# include "unknow_project_system.h"
# include "unknow_project_engine.h"
# include "unknow_project_list.h"

//			PNG reader
t_texture 	*png_load(char *path);

//			Shader - handler
GLuint		load_shaders(const char * p_vertex_file_path,
						const char * p_fragment_file_path);

//			convert
t_vector3	convert_screen_to_opengl(t_window *p_win, t_vector3 source);
t_vector2	convert_vector2_to_opengl(t_window *p_win, t_vector2 source);
t_vector3	convert_opengl_to_vector3(t_window *p_win, t_vector3 source);
t_vector2_int
			convert_vector2_to_vector2_int(t_vector2 base);
t_vector3_int
			convert_vector3_to_vector3_int(t_vector3 base);
t_vector3		convert_vector2_to_vector3(t_vector2 base);
float		degree_to_radius(float angle);
float		radius_to_degree(float radian);
t_uv 		convert_t_uv_to_texture(t_uv *source);

void		prepare_screen(t_window *win, t_camera *p_cam, t_color color);
void		render_screen(t_window *win, t_camera *p_cam);
void 		clear_buffers(t_window *win);
void		draw_pixel(t_window *p_win, int x, int y, t_color *color);

t_triangle	compose_t_triangle_from_t_mesh(t_mesh *src, int *index);
t_triangle	compose_t_triangle_from_t_vertices(t_vector3_list *src, int *index);

#endif
