/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:45:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 14:53:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>
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

void	turn_rast(t_win *wn)
{
	/* ft_display_triangle_array(s_win, triangle_array, max); */
	ft_input_event_check(wn, (t_myraster *)wn->rasterizer->tmp);
	if (((t_myraster *)wn->rasterizer->tmp)->modif == 1 && !((t_myraster *)wn->rasterizer->tmp)->quit)
	{
//		ft_clear_window(wn);
		ft_update_raster((t_myraster *)wn->rasterizer->tmp, wn->rasterizer->tmp2, wn->rasterizer->max, wn);
		((t_myraster *)wn->rasterizer->tmp)->modif = 0;
	}
}

void	ft_launch_rasterization(t_win *wn)
{
	wn->rasterizer->tmp3 = NULL;
	wn->rasterizer->tmp3 = ft_read_the_polygon_file();
	ft_launch_bsp_tree(wn->rasterizer->tmp3);
	wn->rasterizer->tmp2 = ft_get_triangles_array(wn->rasterizer->tmp3);
	wn->rasterizer->max = ft_get_nbr_of_triangle(wn->rasterizer->tmp3);
	wn->rasterizer->tmp = malloc(sizeof(t_myraster));
	ft_init_rasterization(wn, (t_myraster*)(wn->rasterizer->tmp));
	/* ft_display_triangle_array(s_win, triangle_array, max); */
}
