/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:45:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 22:02:40 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>

void	ft_init_rasterization(t_win *wn, t_myraster *raster)
{
	SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2) ;
	raster->mat_trans = ft_make_matrix_5_5();
	raster->mat_rot_x = ft_make_matrix_5_5();
	raster->mat_rot_y = ft_make_matrix_5_5();
	raster->mat_rot_z = ft_make_matrix_5_5();
	raster->mat_proje = ft_make_matrix_5_5();
	ft_set_pro(raster);
	raster->ftheta = 0;
	raster->theta_camera = 0;
	raster->pitch = 0;
	raster->leave_mouse = 0;
	raster->v_camera.x = 0;
	raster->v_camera.y = 0;
	raster->v_camera.z = 0;
	raster->avancer = 0;
	raster->reculer = 0;
	raster->translate_left = 0;
	raster->translate_right = 0;
	raster->modif = 1;
	raster->old = (Uint8*)malloc(sizeof(Uint8) * 300);
	raster->quit = 0;
}

void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	t_myraster			raster;
	t_mytriangle		*triangle_array;
	t_mypolygon			*polygon_lst;

	polygon_lst = NULL;
	ft_launch_bsp_tree(s_win, polygon_lst);
	//s_win->polygon_lst = polygon_lst;
	triangle_array = ft_get_triangles_array(s_win);
	int max = ft_get_nbr_of_triangle(s_win->polygon_lst);
	ft_init_rasterization(wn, &raster);
	/* ft_display_triangle_array(s_win, triangle_array, max); */
	while (!raster.quit)
	{
		ft_input_event_check(wn, &raster, s_win);
		if (raster.modif == 1)
		{
			ft_clear_window(wn);
			ft_update_raster(&raster, triangle_array, max, wn);
			SDL_RenderPresent(wn->rend);
			SDL_Delay(30);
			raster.modif = 0;
		}
		setkeyboard(raster.old, wn->state);
	}
}
