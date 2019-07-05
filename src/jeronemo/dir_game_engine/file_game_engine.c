/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:45:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/05 14:41:41 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>

void	ft_init_rasterization(t_mykeep *keep, t_mychange *change, t_myraster *raster)
{
	raster->mat_trans = ft_make_matrix_5_5();
	raster->mat_rot_x = ft_make_matrix_5_5();
	raster->mat_rot_y = ft_make_matrix_5_5();
	raster->mat_rot_z = ft_make_matrix_5_5();
	raster->mat_proje = ft_make_matrix_5_5();
	ft_set_pro(raster);
	raster->ftheta = 0;
	raster->theta_camera = 0;

	raster->v_camera.x = 0;
	raster->v_camera.y = 0;
	raster->v_camera.z = 0;

	raster->avancer = 0;
	raster->reculer = 0;






	keep->polygon = NULL;
	keep->vec = NULL;
	change->display = (t_mydisplay*)malloc(sizeof(t_mydisplay));
	change->old = (Uint8*)malloc(sizeof(Uint8) * 300);
	change->quit = FALSE;
	change->angle_x = 0;
	change->angle_y = 0;
	change->angle_z = 0;
	change->zoom = 1;
	change->translation_x = 0;
	change->translation_y = 0;
	change->translation_z = -10;
	change->reculer = 0;
	change->avancer = 0;
	change->modif = 1;
	change->display->triangle = 0;
	change->display->mesh = 1;
	change->display->projection = perspective;
	change->display->culling_face = 0;
	change->display->mesh_normal = 0;
	change->display->triangle_normal = 0;
	change->display->panel = 1;
	change->display->color = 0;
	change->display->shade = 0;
	change->v_look_dir.x = 0;
	change->v_look_dir.y = 0;
	change->v_look_dir.z = 0;
	change->v_camera.x = 0;
	change->v_camera.y = 0;
	change->v_camera.z = 0;
	change->theta_x = 0;
	change->theta_y = 0;
	change->theta_z = 0;
	change->mat_trans = ft_make_matrix_5_5();
}

void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	t_mychange			change;
	t_mykeep			keep;
	t_myraster			raster;
	t_mytriangle		*triangle_array;

	ft_launch_bsp_tree(s_win, wn);
	triangle_array = ft_get_triangles_array(s_win);
	int max = ft_get_nbr_of_triangle(s_win);
	SDL_Init(SDL_INIT_EVERYTHING);
	s_win->interface = GAME_ENGINE;
	ft_launch_window(s_win, s_win->interface);
	ft_init_rasterization(&keep, &change, &raster);
	/* ft_display_triangle_array(s_win, triangle_array, max); */
	while (!change.quit)
	{
		ft_input_event_check(wn, &change, &raster);
		if (change.modif == 1 || 1)
		{
		ft_clear_window(s_win);
		ft_update_raster(s_win, &raster, triangle_array, max);
		SDL_RenderPresent(s_win->renderer[s_win->interface]);
		SDL_Delay(30);
		change.modif = 0;
		}
		setkeyboard(change.old, wn->state);
	}
}
