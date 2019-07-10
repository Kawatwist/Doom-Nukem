/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 16:50:39 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_myraster	*ft_init_rasterization(t_win *wn, t_myraster *raster)
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


	raster->light_direction = ft_create_vector(0.5, 0.0, -1.0);
	raster->light_direction = ft_normalise(raster->light_direction);

	raster->plane_camera = ft_create_vector(0.0, 0.0, 1.0);
	raster->point_camera = ft_create_vector(0.0, 0.0, 0.1);


	raster->point_up_screen = ft_create_vector(-1, -1, -1);
	raster->plane_up_screen = ft_create_vector(-1, -1, -1);

	raster->i = 0;   //attention limit le nombre de triangle

	return (raster);
}

t_myraster	*ft_update_raster(t_myraster *raster, t_mytriangle *triangle_array, int max, t_win *wn)
{
	/* int				j; */
	t_mytriangle    triangle;
	t_mytriangle	*triangle_lst;
	t_mytriangle	*triangle_lst_2;
	t_mytriangle	*clipped_triangle;

	triangle_lst = NULL;
	triangle_lst_2 = NULL;
	clipped_triangle = NULL;
	clipped_triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle) * 3);
	ft_calcul_world_and_view_matrix(raster);
	raster->i = -1;
	while (++(raster->i) < max )
	{
		triangle = triangle_array[raster->i];
		ft_calcul_world_view(&triangle, raster);
		if (ft_culling(&triangle, raster) == 1)
		{
			ft_calcul_shade(&triangle, raster);
			ft_calcul_cam_view(&triangle, raster);
			ft_clipping_camera(&triangle, raster, &clipped_triangle);
			raster->j = -1;
			while(++(raster->j) < raster->nbr_of_clipped_triangle_created)
			{
				ft_calcul_projection_view(&(clipped_triangle[raster->j]), raster);
				ft_scale_screen(&(clipped_triangle[raster->j]));
				ft_add_triangle_to_lst(clipped_triangle[raster->j], &triangle_lst);
			}
		}
	}
	ft_order_triangle_z_buffer(&triangle_lst);
	ft_clipping_screen();
	triangle_lst_2 = triangle_lst;
	ft_draw(triangle_lst_2, wn);
	raster->ftheta += 0;
	if (raster->ftheta == 360 * 2)
		raster->ftheta = 0;
	ft_free_lst(triangle_lst_2);
	return (raster);
}
