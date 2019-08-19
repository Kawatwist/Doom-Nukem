/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_calcul_world_view.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 12:36:58 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/19 12:01:35 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

void	ft_calcul_world_view_matrix(t_myraster *raster)
{
	ft_set_raster_trans(0, 0, 0, raster);
	//ft_set_raster_rot_x(raster->ftheta, raster);
	ft_set_raster_rot_x(180, raster);
	//ft_set_raster_rot_y(raster->ftheta, raster);
	//ft_set_raster_rot_z(raster->ftheta * 0.5 + 180, raster);
	ft_set_raster_rot_z(0, raster);
}

void	ft_calcul_world_view(t_mytriangle *triangle, t_myraster *raster)
{
	//ROTATION Z
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_z);
	//ROTATION X
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_x);
	//TRANSLATION (offset in screen)
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_trans);
}

t_myvec		ft_calcul_normal_triangle_and_normalise(t_mytriangle triangle)
{
	t_myvec		normal;

	normal = ft_calculate_normal_of_points(triangle.vertice[0], triangle.vertice[1], triangle.vertice[2]);
	normal = ft_normalise(normal);
	return (normal);
}

int		ft_culling(t_mytriangle *triangle, t_myraster *raster)
{
	t_myvec			normal;

	normal = ft_calcul_normal_triangle_and_normalise(*triangle);
	if (ft_dot_product(normal, ft_vector_sub(triangle->vertice[0], raster->v_camera)) < 0.0)
		return (1);
	else
		return (0);
}

void	ft_calcul_shade(t_mytriangle *triangle, t_myraster *raster) // check gouraud
{
	t_myvec			normal;

	normal = ft_calcul_normal_triangle_and_normalise(*triangle);
	triangle->shade = ft_dot_product(normal, raster->light_direction);
}

void	ft_add_triangle_to_lst(t_mytriangle clipped_triangle, t_mytriangle **triangle_lst)
{
	t_mytriangle	*triangle_node;

	triangle_node = ft_triangle_node_create(clipped_triangle);
	ft_triangle_add_node(triangle_lst, triangle_node);
}

void	ft_calcul_world_and_view_matrix(t_myraster *raster)
{
	//CALCUL DE MATRIX WORLD
	ft_calcul_world_view_matrix(raster);
	//CALUL DE MATRIX VIEW
	raster->mat_camera_view = t_camera_compute_view(raster);
}

void	ft_free_lst(t_mytriangle *triangle_lst_2)
{
	t_mytriangle *current;
	while (triangle_lst_2 != NULL)
	{
		current = triangle_lst_2;
		triangle_lst_2 = triangle_lst_2->next;
		free(current);
	}
}

//surement un truck a faire ici pour le passage par adresse
void	ft_clipping_camera(t_mytriangle *triangle, t_myraster *raster, t_mytriangle **clipped_triangle)
{
	raster->nbr_of_clipped_triangle_created = 0;
	//	clipped_triangle = ft_triangle_clips_again_plan(raster->point_camera, raster->plane_camera,
	//			&(raster->nbr_of_clipped_triangle_created),
	//			clipped_triangle,
	//			triangle);
	if (triangle->vertice[0].z < 0.1 || triangle->vertice[1].z < 0.1 || triangle->vertice[2].z < 0.1)
		(raster->nbr_of_clipped_triangle_created) = 0;
	else
	{
		(*clipped_triangle) = triangle;
		(raster->nbr_of_clipped_triangle_created) = 1;
	}
}

void	ft_clipping_screen(t_mytriangle *triangle_lst,
		t_myraster *raster, 
		t_mytriangle **clipped_triangle)
{
	t_mytriangle		*head;
	t_rectbox	box;

	box.x = 30;
	box.y = 30;
	box.z = 0.1;
	box.w = XSCREEN - 60;
	box.h = YSCREEN - 60;
	box.l = 999;

	(void)clipped_triangle;
	head = triangle_lst;
	while(triangle_lst != NULL)
	{
		if (!hitboxbox(triangle_lst->vertice[0], box) || !hitboxbox(triangle_lst->vertice[1], box) || !hitboxbox(triangle_lst->vertice[2], box))
			(raster->nbr_of_clipped_triangle_created) = 0;
		else
			ft_add_triangle_to_lst(*triangle_lst, &(raster->triangle_lst_2));
		//else
		//{
		//(raster->nbr_of_clipped_triangle_created) = 1;
		//(*clipped_triangle)[0] = *triangle;
		//}
		/*
		   i = 0;
		   while (i < 4)
		   {
		   raster->nbr_of_clipped_triangle_created = 0;
		   if (i == 0)
		   {
		   printf("gauche\n");
		//bord gauche
		clipped_triangle = ft_triangle_clips_again_plan(
		raster->point_left_screen,
		raster->plane_left_screen,
		&(raster->nbr_of_clipped_triangle_created),
		clipped_triangle,
		triangle_lst);
		}
		else if (i == 1)
		{
		printf("hautt\n");
		//bord du haut
		clipped_triangle = ft_triangle_clips_again_plan(
		raster->point_up_screen,
		raster->plane_up_screen,
		&(raster->nbr_of_clipped_triangle_created),
		clipped_triangle,
		triangle_lst);
		}
		else if (i == 2)
		{
		printf("droite\n");
		//bord de droite
		clipped_triangle = ft_triangle_clips_again_plan(
		raster->point_right_screen,
		raster->plane_right_screen,
		&(raster->nbr_of_clipped_triangle_created),
		clipped_triangle,
		triangle_lst);
		}
		else if (i == 3)
		{
		printf("bas\n");
		//bord du bas
		clipped_triangle = ft_triangle_clips_again_plan(
		raster->point_bottom_screen,
		raster->plane_bottom_screen,
		&(raster->nbr_of_clipped_triangle_created),
		clipped_triangle,
		triangle_lst);
		}
		*/
		//		j = -1;
		//		while(++j < raster->nbr_of_clipped_triangle_created)
		//		{
		//			ft_add_triangle_to_lst(raster->clipped_triangle[raster->j], &(raster->triangle_lst_2));
		//			i++;
		//		}
		triangle_lst = triangle_lst->next;
	}
	triangle_lst = head;
	}

	void	ft_calcul_cam_view(t_mytriangle *triangle, t_myraster *raster)
	{
		ft_apply_calucul(ft_matrix_multiply_vector_general, triangle, raster->mat_camera_view);
	}

	void	ft_calcul_projection_view(t_mytriangle *triangle, t_myraster *raster)
	{
		ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_proje);//PROJECTION
	}

	void	ft_scale_screen(t_mytriangle *triangle)
	{
		triangle->vertice[0].x += 1.0;
		triangle->vertice[1].x += 1.0;
		triangle->vertice[2].x += 1.0;

		triangle->vertice[0].y += 1.0;
		triangle->vertice[1].y += 1.0;
		triangle->vertice[2].y += 1.0;


		triangle->vertice[0].x *= 0.5 * (float)XSCREEN;
		triangle->vertice[1].x *= 0.5 * (float)XSCREEN;
		triangle->vertice[2].x *= 0.5 * (float)XSCREEN;

		triangle->vertice[0].y *= 0.5 * (float)YSCREEN;
		triangle->vertice[1].y *= 0.5 * (float)YSCREEN;
		triangle->vertice[2].y *= 0.5 * (float)YSCREEN;
	}

	void	ft_draw(t_mytriangle *triangle_lst_2, t_win *wn)
	{
		t_mytriangle	*keep;

		keep = triangle_lst_2;
		while (triangle_lst_2 != NULL)
		{
			//printf("=%f\n", triangle_lst_2->vertice[0].x);
			//DRAW FILL TRIANGLE WITH SHADE/LIGHT
			/* ft_fill_triangle_shade((*triangle_lst_2), wn, triangle_lst_2->shade); */
			//DRAW MESH
			ft_draw_triangle_base(&(triangle_lst_2->vertice[0]), &(triangle_lst_2->vertice[1]), &(triangle_lst_2->vertice[2]), wn);


	ft_draw_textured_triangle(	triangle_lst_2->vertice[0].x,
								triangle_lst_2->vertice[0].y,
								triangle_lst_2->texture[0].u,
								triangle_lst_2->texture[0].v,
								triangle_lst_2->texture[0].w,
								triangle_lst_2->vertice[1].x,
								triangle_lst_2->vertice[1].y,
								triangle_lst_2->texture[1].u,
								triangle_lst_2->texture[1].v,
								triangle_lst_2->texture[1].w,
								triangle_lst_2->vertice[2].x,
								triangle_lst_2->vertice[2].y,
								triangle_lst_2->texture[2].u,
								triangle_lst_2->texture[2].v,
								triangle_lst_2->texture[2].w,
								wn
			);


			triangle_lst_2 = triangle_lst_2->next;
		}
		triangle_lst_2 = keep;
	}

	void	ft_make_the_world_spin(int turn, t_myraster *raster)
	{
		if (turn == 1)
		{
			raster->ftheta += 1;
			if (raster->ftheta == 360 * 2)
				raster->ftheta = 0;
		}
	}
