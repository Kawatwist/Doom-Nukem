/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:45:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 12:59:09 by jchardin         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */ # include <header_game_engine.h>
t_mypolygon		*ft_read_the_polygon_file(void);

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

void	ft_launch_rasterization(t_win *wn)
{
	t_myraster			raster;
	t_mytriangle		*triangle_array;
	t_mypolygon			*polygon_lst;
	int					max;

	polygon_lst = NULL;
	polygon_lst = ft_read_the_polygon_file();
	ft_launch_bsp_tree(polygon_lst);
	triangle_array = ft_get_triangles_array(polygon_lst);
	max = ft_get_nbr_of_triangle(polygon_lst);
	ft_init_rasterization(wn, &raster);
	/* ft_display_triangle_array(s_win, triangle_array, max); */
	while (!raster.quit)
	{
		ft_input_event_check(wn, &raster);
		if (raster.modif == 1 && !raster.quit)
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
