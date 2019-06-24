#ifndef UNKNOW_PROJECT_WINDOW_H
# define UNKNOW_PROJECT_WINDOW_H

# include "unknow_project_includes.h"
# include "unknow_project_define.h"
# include "unknow_project_basic_list.h"

typedef struct		s_window
{
	SDL_DisplayMode	current; //ecran actuel de travail
	SDL_Window		*window; //la fenetre

	int				size_x; //taille en x de la fenetre
	int				size_y; // taille en y de la fenetre
	GLuint 			vertex_array; //adresse de la grosse boite des tube de peinture
	SDL_GLContext	context; //la toile du peintre

	GLuint			vertex_buffer; //le pot de peinture vertex
	GLuint			vertex_fixed_buffer; //le pot de peinture vertex
	GLuint			color_buffer; //le pot de peinture color
	GLuint			color_fixed_buffer; //le pot de peinture color
	GLuint			texture_buffer; //le pot de peinture texture
	GLuint			alpha_buffer; //le pot de peinture alpha

	GLuint			program_color; //le livre qui explique la couleur
	GLuint			program_texture; //le livre qui explique la texture

	t_vector3		*vertex_data;
	t_color			*color_data;
	float			*depth_buffer;

	pthread_t		threads[NB_THREAD_MAX]; //pointeur pour le multithreading
	t_void_list		data[NB_THREAD_MAX]; //liste qui donne au thread les element dont il a besoin

}					t_window;

//			fps_handler
void		check_frame();

//			window_handler
void		start_sdl();
t_window	*initialize_t_window(char *name, int size_x, int size_y);
int 		is_point_in_screen(t_window *p_win, t_vector3 p_point);
int			is_t_triangle_in_screen(t_window *p_win, t_triangle *p_triangle);

#endif
