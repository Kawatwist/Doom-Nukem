/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/11 14:46:53 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_myraster	*ft_init_rasterization(t_win *wn, t_myraster *raster)
{
	raster->triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	raster->clipped_triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle) * 3);
	SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2);
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
	raster->v_camera = ft_create_vector(0.0, 0.0, 0.0);
	raster->avancer = 0;
	raster->reculer = 0;
	raster->translate_left = 0;
	raster->translate_right = 0;
	raster->modif = 1;
	raster->old = (Uint8*)malloc(sizeof(Uint8) * 300);
	raster->quit = 0;
	raster->light_direction = ft_create_vector(0.5, 0.0, -1.0);
	raster->light_direction = ft_normalise(raster->light_direction);

/* case 0:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]); break; */
/* 					case 1:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, (float)ScreenHeight() - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break; */
/* 					case 2:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break; */
/* 					case 3:	nTrisToAdd = Triangle_ClipAgainstPlane({ (float)ScreenWidth() - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break; */
/* 	//camera */
	raster->plane_camera = ft_create_vector(0.0, 0.0, 1.0);
	raster->point_camera = ft_create_vector(0.0, 0.0, 0.1);

	//haut
	raster->point_up_screen = ft_create_vector(-1, -1, -1);
	raster->plane_up_screen = ft_create_vector(-1, -1, -1);


	//gauche
	raster->point_left_screen = ft_create_vector(-1, -1, -1);
	raster->plane_left_screen = ft_create_vector(-1, -1, -1);


	//droit
	raster->point_right_screen = ft_create_vector(-1, -1, -1);
	raster->plane_right_screen = ft_create_vector(-1, -1, -1);


	//bas
	raster->point_bottom_screen = ft_create_vector(-1, -1, -1);
	raster->plane_bottom_screen = ft_create_vector(-1, -1, -1);



	raster->i = 0;   //attention limit le nombre de triangle
	raster->nbr_of_triangle = wn->rasterizer->max; //de meme
	return (raster);
}

void		ft_init_update_raster(t_myraster *raster)
{
	raster->triangle_lst = NULL;
	raster->triangle_lst_2 = NULL;
	ft_make_the_world_spin(0, raster);
	ft_calcul_world_and_view_matrix(raster);
	raster->i = -1;
}

void		ft_update_raster(t_myraster *raster, t_mytriangle *triangle_array, t_win *wn)
{
	ft_init_update_raster(raster);
	while (++(raster->i) < raster->nbr_of_triangle)
	{
		*(raster->triangle) = triangle_array[raster->i];
		ft_calcul_world_view(raster->triangle, raster);
		if (ft_culling(raster->triangle, raster) == 1)
		{
			ft_calcul_shade(raster->triangle, raster);
			ft_calcul_cam_view(raster->triangle, raster);
			ft_clipping_camera(raster->triangle, raster, &(raster->clipped_triangle));
			raster->j = -1;
			while (++(raster->j) < raster->nbr_of_clipped_triangle_created)
			{
				ft_calcul_projection_view(&(raster->clipped_triangle[raster->j]), raster);
				ft_scale_screen(&(raster->clipped_triangle[raster->j]));
				ft_add_triangle_to_lst(raster->clipped_triangle[raster->j], &(raster->triangle_lst));
			}
		}
	}
	ft_order_triangle_z_buffer(&(raster->triangle_lst));
	ft_clipping_screen(
			raster->triangle_lst,
			raster,
			&(raster->clipped_triangle));
	raster->triangle_lst_2 = raster->triangle_lst;
	ft_draw(raster->triangle_lst_2, wn);
	ft_free_lst(raster->triangle_lst_2);
}
