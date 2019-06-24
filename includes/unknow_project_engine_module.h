#ifndef UNKNOW_PROJECT_ENGINE_MODULE_H
# define UNKNOW_PROJECT_ENGINE_MODULE_H

# include "unknow_project_list.h"
# include "unknow_project_system.h"

typedef struct 	s_physic_engine
{
	t_mesh_list	*mesh_list;
	t_vector3	gravity_force;
}				t_physic_engine;

t_physic_engine	create_t_physic_engine();
t_physic_engine	*initialize_t_physic_engine();
void			free_t_physic_engine(t_physic_engine dest);
void			delete_t_physic_engine(t_physic_engine *dest);

void			t_physic_engine_draw_mesh(t_physic_engine *p_physic_engine, t_window *p_win, t_camera *p_cam);
void			t_physic_engine_add_mesh(t_physic_engine *physic_engine, t_mesh p_mesh);
t_mesh			*t_physic_engine_get_mesh(t_physic_engine *physic_engine, int index);
void			t_physic_engine_apply_velocity(t_physic_engine *physic_engine);
void			t_physic_engine_compute_check_list(t_physic_engine *physic_engine);
int				calc_max_velocity(t_mesh *mesh, t_mesh *target, t_vector3 axis);

typedef struct	s_user_engine
{
	t_mouse		*mouse;
	t_keyboard	*keyboard;
	SDL_Event	event;
}				t_user_engine;

t_user_engine	create_t_user_engine();
t_user_engine	*initialize_t_user_engine();
void			free_t_user_engine(t_user_engine dest);
void			delete_t_user_engine(t_user_engine *dest);

void			t_user_engine_handle_camera(t_user_engine *user_engine, t_camera *cam);
void			t_user_engine_handle_quit(t_user_engine *user_engine, int *play);
int				t_user_engine_poll_event(t_user_engine *engine);

#endif
