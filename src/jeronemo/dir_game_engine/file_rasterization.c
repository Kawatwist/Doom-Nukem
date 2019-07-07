/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/07 14:16:28 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_mytriangle	*ft_triangle_node_create(t_mytriangle tri)
{
	t_mytriangle	*triangle;

	triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	triangle = memcpy(triangle, &tri, sizeof(t_mytriangle));
	triangle->next = NULL;
	return (triangle);
}

void			ft_triangle_add_node(t_mytriangle **lst, t_mytriangle *node)
{
	if (*lst == NULL)
	{
		*lst = node;
	}
	else
	{
		node->next = *lst;
		*lst = node;
	}
}


t_mytriangle	*ft_get_before(t_mytriangle *head, t_mytriangle *node)
{
	t_mytriangle	*before;
	t_mytriangle	*keep;

	keep = head;

	before = NULL;
	if (head == node)
		return (NULL);

	while(head != node)
	{
		before = head;
		head = head->next;
	}
	head = keep;
	return (before);
}

void	ft_swap_node_with_the_next(t_mytriangle *head, t_mytriangle *node2)
{
	t_mytriangle	*before_node_2;
	t_mytriangle	*node1;

	node1 = node2->next;
	before_node_2 = ft_get_before(head, node2);
	node2->next = node2->next->next;
	if (before_node_2 != NULL)
	{
		before_node_2->next = node1;
	}
	else
	{
		head = node1;
	}
	node1->next = node2;
	printf("swapping\n\n");
}


/* void	ft_swap(t_mytriangle *triangle_lst) */
/* { */
/* 	/1* t_mytriangle	*swap; *1/ */
/* int				i; */

/* i = 0; */
/* swap = NULL; */
/* swap = (t_mytriangle*)malloc(sizeof(t_mytriangle)); */
/* swap->shade = triangle_lst->shade; */
/* while (i++ < 3) */
/* { */
/* 	swap->vertice[i].x = triangle_lst->vertice[i].x; */
/* 	swap->vertice[i].y = triangle_lst->vertice[i].y; */
/* 	swap->vertice[i].z = triangle_lst->vertice[i].z; */
/* } */
/* triangle_lst->shade = triangle_lst->next->shade; */
/* triangle_lst->vertice[0].x = triangle_lst->next->vertice[0].x; */
/* triangle_lst->vertice[0].y = triangle_lst->next->vertice[0].y; */
/* triangle_lst->vertice[0].z = triangle_lst->next->vertice[0].z; */
/* triangle_lst->vertice[1].x = triangle_lst->next->vertice[1].x; */
/* triangle_lst->vertice[1].y = triangle_lst->next->vertice[1].y; */
/* triangle_lst->vertice[1].z = triangle_lst->next->vertice[1].z; */
/* triangle_lst->vertice[2].x = triangle_lst->next->vertice[2].x; */
/* triangle_lst->vertice[2].y = triangle_lst->next->vertice[2].y; */
/* triangle_lst->vertice[2].z = triangle_lst->next->vertice[2].z; */

/* triangle_lst->next->shade = swap->shade; */
/* triangle_lst->next->vertice[0].x = swap->vertice[0].x; */
/* triangle_lst->next->vertice[0].y = swap->vertice[0].y; */
/* triangle_lst->next->vertice[0].z = swap->vertice[0].z; */
/* triangle_lst->next->vertice[1].x = swap->vertice[1].x; */
/* triangle_lst->next->vertice[1].y = swap->vertice[1].y; */
/* triangle_lst->next->vertice[1].z = swap->vertice[1].z; */
/* triangle_lst->next->vertice[2].x = swap->vertice[2].x; */
/* triangle_lst->next->vertice[2].y = swap->vertice[2].y; */
/* triangle_lst->next->vertice[2].z = swap->vertice[2].z; */
/* } */

void	ft_order_triangle_z_buffer(t_mytriangle *triangle_lst)
{
	float			z1;
	float			z2;
	t_mytriangle	*keep;

	if (triangle_lst == NULL)
		return;
	keep = triangle_lst;
	while (triangle_lst->next != NULL)
	{
		z1 = (triangle_lst->vertice[0].z + triangle_lst->vertice[1].z + triangle_lst->vertice[2].z) / 3;
		z2 = (triangle_lst->next->vertice[0].z + triangle_lst->next->vertice[1].z + triangle_lst->next->vertice[2].z) / 3;
		if (z1 < z2)  ///jai inverser
		{
			ft_swap_node_with_the_next(keep, triangle_lst);
			triangle_lst = keep;
		}
		triangle_lst = triangle_lst->next;
		if (triangle_lst == NULL)
			break;
	}
	triangle_lst = keep;
}

void		ft_update_raster(t_mywin *s_win, t_myraster *raster, t_mytriangle *triangle_array, int max, t_win *wn)
{
	int				i;
	t_myvec			light_direction;
	t_mytriangle	triangle;
	t_mytriangle	*triangle_lst;
	t_mytriangle	*triangle_lst_2;
	t_mytriangle	*triangle_node;
	t_mytriangle	*keep;
	t_myvec			normal;
	int				j;
	int				nbr;
	t_myvec			point;
	t_mytriangle	*clipped_triangle = NULL;



	clipped_triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle) * 3);
	t_myvec plane_norm;
	triangle_lst = NULL;
	triangle_lst_2 = NULL;
	light_direction.x = 0.5;
	light_direction.y = 0.0;
	light_direction.z = -1.0;
	light_direction = ft_normalise(light_direction);
	//CALCUL DE MATRIX WORLD
	ft_set_raster_trans(0, 0, 0, raster);
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
		//ROTATION Z
		triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle.vertice[0]);
		triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle.vertice[1]);
		triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle.vertice[2]);
		//ROTATION X
		triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle.vertice[0]);
		triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle.vertice[1]);
		triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle.vertice[2]);
		//TRANSLATION (offset in screen)
		triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_trans, triangle.vertice[0]);
		triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_trans, triangle.vertice[1]);
		triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_trans, triangle.vertice[2]);
		//CULLING
		normal = ft_calculate_normal_of_points(triangle.vertice[0], triangle.vertice[1], triangle.vertice[2]);
		normal = ft_normalise(normal);
		if (ft_dot_product(normal, ft_vector_sub(triangle.vertice[0], raster->v_camera)) < 0.0)
		{
			//SHADE
			triangle.shade = ft_dot_product(normal, light_direction);
			//CAM VIEW
			triangle.vertice[0] = ft_matrix_multiply_vector_general(raster->mat_camera_view, triangle.vertice[0]);
			triangle.vertice[1] = ft_matrix_multiply_vector_general(raster->mat_camera_view, triangle.vertice[1]);
			triangle.vertice[2] = ft_matrix_multiply_vector_general(raster->mat_camera_view, triangle.vertice[2]);

			//CLIP AGAINST CAMERA PLANE
			point.x = 0.0;
			point.y = 0.0;
			point.z = 0.1;

			plane_norm.x = 0.0;
			plane_norm.y = 0.0;
			plane_norm.z = 1.0;
			nbr = ft_triangle_clips_again_plan(point, plane_norm, clipped_triangle, &triangle, s_win);
			j = 0;
			while(j < nbr)
			{
				//PROJECTION
				clipped_triangle[j].vertice[0] = ft_matrix_multiply_vector(raster->mat_proje, clipped_triangle[j].vertice[0]);
				clipped_triangle[j].vertice[1] = ft_matrix_multiply_vector(raster->mat_proje, clipped_triangle[j].vertice[1]);
				clipped_triangle[j].vertice[2] = ft_matrix_multiply_vector(raster->mat_proje, clipped_triangle[j].vertice[2]);
				//SCALE
				clipped_triangle[j].vertice[0] = ft_scale_screen(clipped_triangle[j].vertice[0]);
				clipped_triangle[j].vertice[1] = ft_scale_screen(clipped_triangle[j].vertice[1]);
				clipped_triangle[j].vertice[2] = ft_scale_screen(clipped_triangle[j].vertice[2]);
				triangle_node = ft_triangle_node_create(clipped_triangle[j]);
				ft_triangle_add_node(&triangle_lst, triangle_node);
				j++;
			}
		}
		i++;
	}
	//ORDER TRIANGLE FROM FAR TO NEAR
	ft_order_triangle_z_buffer(triangle_lst);

	//Clip triangle against all four screen edges

	//1er argument => PLANE
	t_myvec p_0;
	t_myvec p_1;
	t_myvec p_2;
	t_myvec p_3;

	p_0.x = 0.0f;
	p_0.y = 0.0f;
	p_0.z = 0.0f;

	p_1.x = 0.0f;
	p_1.y = wn->yscreen - 1;
	p_1.z = 0.0f;

	p_2 = p_0;

	p_3.x = wn->xscreen - 1;
	p_3.y = 0.0f;
	p_3.z = 0.0f;

	//2eme argument => NORMAL
	t_myvec n_0;
	t_myvec n_1;
	t_myvec n_2;
	t_myvec n_3;

	n_0.x = 0.0f;
	n_0.y = 1.0f;
	n_0.z = 0.0f;

	n_1.x = 0.0f;
	n_1.y = -1.0f;
	n_1.z = 0.0f;

	n_2.x = 1.0f;
	n_2.y = 0.0f;
	n_2.z = 0.0f;

	n_3.x = -1.0f;
	n_3.y = 0.0f;
	n_3.z = 0.0f;

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
	/* 			nbr = ft_triangle_clips_again_plan(p_0, n_0, triangle_lst, clipped_triangle, s_win); */
	/* 		else if (i == 1) */
	/* 			nbr = ft_triangle_clips_again_plan(p_1, n_1, triangle_lst, clipped_triangle, s_win); */
	/* 		else if (i == 2) */
	/* 			nbr = ft_triangle_clips_again_plan(p_2, n_2, triangle_lst , clipped_triangle, s_win); */
	/* 		else if (i == 3) */
	/* 			nbr = ft_triangle_clips_again_plan(p_3, n_3, triangle_lst, clipped_triangle, s_win); */
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


	//AFFICHAGE
	triangle_lst_2 = triangle_lst;
	keep = triangle_lst_2;
	while (triangle_lst_2 != NULL)
	{
		//DRAW FILL TRIANGLE WITH SHADE/LIGHT
		ft_fill_triangle_shade((triangle_lst_2->vertice[0]), (triangle_lst_2->vertice[1]), (triangle_lst_2->vertice[2]), s_win, triangle_lst_2->shade);
		//DRAW MESH
		if (triangle_lst_2->ft_color == 'r')
			SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 255, 0, 0, 255);
		else if (triangle_lst_2->ft_color == 'g')
			SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 255, 0, 255);
		else if (triangle_lst_2->ft_color == 'b')
			SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 0, 255, 255);
		ft_draw_triangle_base(&(triangle_lst_2->vertice[0]), &(triangle_lst_2->vertice[1]), &(triangle_lst_2->vertice[2]), s_win);
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
