/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 12:43:12 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

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


	raster->light_direction = ft_create_vector(0.5, 0.0, -1.0);
	raster->light_direction = ft_normalise(raster->light_direction);

	raster->plane_camera = ft_create_vector(0.0, 0.0, 1.0);
	raster->point_camera = ft_create_vector(0.0, 0.0, 0.1);


	raster->point_up_screen = ft_create_vector(-1, -1, -1);
	raster->plane_up_screen = ft_create_vector(-1, -1, -1);


}

void		ft_update_raster(t_myraster *raster, t_mytriangle *triangle_array, int max, t_win *wn)
{
	int				i;
	t_mytriangle	triangle;
	t_mytriangle	*triangle_lst;
	t_mytriangle	*triangle_lst_2;
	t_mytriangle	*triangle_node;
	t_mytriangle	*keep;
	t_myvec			normal;
	int				j;
	int				nbr;
	t_mytriangle	*clipped_triangle;


	triangle_lst = NULL;
	triangle_lst_2 = NULL;
	clipped_triangle = NULL;
	clipped_triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle) * 3);




	//CALCUL DE MATRIX WORLD
	ft_set_raster_trans(0, 0, -30, raster);
	//ft_set_raster_rot_x(raster->ftheta, raster);
	ft_set_raster_rot_x(180, raster);
	//ft_set_raster_rot_y(raster->ftheta, raster);
	ft_set_raster_rot_z(raster->ftheta * 0.5, raster);
	//CALUL DE MATRIX VIEW
	raster->mat_camera_view = t_camera_compute_view(raster);
	////##################################################################################################
	i = 0;
	while (i < max )
	{
		triangle = triangle_array[i];

		//CALCUL WORLD VIEW
		triangle = ft_calcul_world_view(triangle, raster);




		/* //ROTATION Z */
		/* triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_z); */
		/* //ROTATION X */
		/* triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_x); */
		/* //TRANSLATION (offset in screen) */
		/* triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_trans); */
		//CULLING
		normal = ft_calculate_normal_of_points(triangle.vertice[0], triangle.vertice[1], triangle.vertice[2]);
		normal = ft_normalise(normal);
		if (ft_dot_product(normal, ft_vector_sub(triangle.vertice[0], raster->v_camera)) < 0.0)
		{
			//SHADE
			triangle.shade = ft_dot_product(normal, raster->light_direction);
			//CAM VIEW
			triangle = ft_apply_calucul(ft_matrix_multiply_vector_general, triangle, raster->mat_camera_view);
			//CLIP AGAINST CAMERA PLANE
			clipped_triangle = ft_triangle_clips_again_plan(raster->point_up_screen, raster->plane_camera, &nbr, clipped_triangle, &triangle);
			j = 0;
			while(j < nbr)
			{
				//PROJECTION
				*clipped_triangle = ft_apply_calucul(ft_matrix_multiply_vector, *clipped_triangle, raster->mat_proje);
				//SCALE
				clipped_triangle[j]= ft_scale_screen(clipped_triangle[j]);
				triangle_node = ft_triangle_node_create(clipped_triangle[j]);
				ft_triangle_add_node(&triangle_lst, triangle_node);
				j++;
			}
		}
		i++;
	}
	//ORDER TRIANGLE FROM FAR TO NEAR
	triangle_lst = ft_order_triangle_z_buffer(triangle_lst);

	//CLIP AGAINST SCREEN PLANE


	/* int		newtriangle; */
	/* newtriangle = 1; */
	/* i = 0; */
	/* t_mytriangle *head; */
	/* head = triangle_lst; */
	/* while(triangle_lst != NULL) */
	/* { */

	/* 	while (i < 4) */
	/* 	{ */
	/* 		if (i == 0) */
	/* 			nbr = ft_triangle_clips_again_plan(p_0, n_0, triangle_lst, clipped_triangle); */
	/* 		else if (i == 1) */
	/* 			nbr = ft_triangle_clips_again_plan(p_1, n_1, triangle_lst, clipped_triangle); */
	/* 		else if (i == 2) */
	/* 			nbr = ft_triangle_clips_again_plan(p_2, n_2, triangle_lst , clipped_triangle); */
	/* 		else if (i == 3) */
	/* 			nbr = ft_triangle_clips_again_plan(p_3, n_3, triangle_lst, clipped_triangle); */
	/* 		j = 0; */
	/* 		while(j < nbr) */
	/* 		{ */
	/* 			triangle_node = ft_triangle_node_create(clipped_triangle[j]); */
	/* 			ft_triangle_add_node(&triangle_lst_2, triangle_node); */
	/* 			j++; */
	/* 		} */
	/* 		i++; */
	/* 	} */
	/* 	triangle_lst = triangle_lst->next; */
	/* } */
	/* triangle_lst = head; */
	/* //Fonction de pushback des triangles */


	keep = triangle_lst;
	while(triangle_lst != NULL)
	{
		nbr = 0;
		clipped_triangle = ft_triangle_clips_again_plan(raster->point_up_screen, raster->plane_up_screen, &nbr, clipped_triangle, triangle_lst);
		printf("le nbr=%d\n", nbr);
		j = 0;
		while(j < nbr)
		{
			printf("j =%f\n", clipped_triangle->vertice[0].x);
			triangle_node = ft_triangle_node_create(clipped_triangle[j]);
			printf("le node =%f\n", triangle_node->vertice[0].x);
			ft_triangle_add_node(&triangle_lst_2, triangle_node);
			j++;
		}
		triangle_lst = triangle_lst->next;
	}
	triangle_lst = keep;

	//AFFICHAGE
	/* triangle_lst_2 = triangle_lst; */

	keep = triangle_lst_2;
	while (triangle_lst_2 != NULL)
	{
		//DRAW FILL TRIANGLE WITH SHADE/LIGHT
		ft_fill_triangle_shade((triangle_lst_2->vertice[0]), (triangle_lst_2->vertice[1]), (triangle_lst_2->vertice[2]), wn, triangle_lst_2->shade);
		//DRAW MESH
		if (triangle_lst_2->ft_color == 'r')
			SDL_SetRenderDrawColor(wn->rend, 255, 0, 0, 255);
		else if (triangle_lst_2->ft_color == 'g')
			SDL_SetRenderDrawColor(wn->rend, 0, 255, 0, 255);
		else if (triangle_lst_2->ft_color == 'b')
			SDL_SetRenderDrawColor(wn->rend, 0, 0, 255, 255);
		SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 255);
		ft_draw_triangle_base(&(triangle_lst_2->vertice[0]), &(triangle_lst_2->vertice[1]), &(triangle_lst_2->vertice[2]), wn);
		triangle_lst_2 = triangle_lst_2->next;
	}
	triangle_lst_2 = keep;
	raster->ftheta += 0;
	if (raster->ftheta == 360 * 2)
		raster->ftheta = 0;
	t_mytriangle *current;
	while (triangle_lst_2 != NULL)
	{
		current = triangle_lst_2;
		triangle_lst_2 = triangle_lst_2->next;
		free(current);
	}
	return;
}
