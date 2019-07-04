/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/04 16:21:59 by jchardin         ###   ########.fr       */
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


void	ft_swap(t_mytriangle *triangle_lst)
{
	t_mytriangle	*swap;
	swap = NULL;
	swap = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	swap->shade = triangle_lst->shade;
	swap->vertice[0].x = triangle_lst->vertice[0].x;
	swap->vertice[0].y = triangle_lst->vertice[0].y;
	swap->vertice[0].z = triangle_lst->vertice[0].z;
	swap->vertice[1].x = triangle_lst->vertice[1].x;
	swap->vertice[1].y = triangle_lst->vertice[1].y;
	swap->vertice[1].z = triangle_lst->vertice[1].z;
	swap->vertice[2].x = triangle_lst->vertice[2].x;
	swap->vertice[2].y = triangle_lst->vertice[2].y;
	swap->vertice[2].z = triangle_lst->vertice[2].z;

	triangle_lst->shade = triangle_lst->next->shade;
	triangle_lst->vertice[0].x = triangle_lst->next->vertice[0].x;
	triangle_lst->vertice[0].y = triangle_lst->next->vertice[0].y;
	triangle_lst->vertice[0].z = triangle_lst->next->vertice[0].z;
	triangle_lst->vertice[1].x = triangle_lst->next->vertice[1].x;
	triangle_lst->vertice[1].y = triangle_lst->next->vertice[1].y;
	triangle_lst->vertice[1].z = triangle_lst->next->vertice[1].z;
	triangle_lst->vertice[2].x = triangle_lst->next->vertice[2].x;
	triangle_lst->vertice[2].y = triangle_lst->next->vertice[2].y;
	triangle_lst->vertice[2].z = triangle_lst->next->vertice[2].z;

	triangle_lst->next->shade = swap->shade;
	triangle_lst->next->vertice[0].x = swap->vertice[0].x;
	triangle_lst->next->vertice[0].y = swap->vertice[0].y;
	triangle_lst->next->vertice[0].z = swap->vertice[0].z;
	triangle_lst->next->vertice[1].x = swap->vertice[1].x;
	triangle_lst->next->vertice[1].y = swap->vertice[1].y;
	triangle_lst->next->vertice[1].z = swap->vertice[1].z;
	triangle_lst->next->vertice[2].x = swap->vertice[2].x;
	triangle_lst->next->vertice[2].y = swap->vertice[2].y;
	triangle_lst->next->vertice[2].z = swap->vertice[2].z;
}

void	ft_order_triangle_z_buffer(t_mytriangle *triangle_lst)
{
	float			z1;
	float			z2;
	t_mytriangle	*keep;

	keep = triangle_lst;
	while (triangle_lst->next != NULL)
	{
		z1 = (triangle_lst->vertice[0].z + triangle_lst->vertice[1].z + triangle_lst->vertice[2].z) / 3;
		z2 = (triangle_lst->next->vertice[0].z + triangle_lst->next->vertice[1].z + triangle_lst->next->vertice[2].z) / 3;
		if (z1 < z2)
		{
			ft_swap(triangle_lst);
			triangle_lst = keep;
		}
		triangle_lst = triangle_lst->next;
	}
	triangle_lst = keep;
}

void		ft_update_raster(t_mywin *s_win, t_myraster *raster, t_mytriangle *triangle_array, int max)
{
	int				i;
	t_myvec			light_direction;
	t_mytriangle	triangle;
	t_mytriangle	*triangle_lst;
	t_mytriangle	*triangle_node;
	t_mytriangle	*keep;
	t_myvec			normal;

	triangle_lst = NULL;
	light_direction.x = 0.5;
	light_direction.y = 0.0;
	light_direction.z = -1.0;
	light_direction = ft_normalise(light_direction);
	//CALCUL DE MATRIX WORLD
	ft_set_raster_trans(0, 0, 30, raster);
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
			//PROJECTION
			triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_proje, triangle.vertice[0]);
			triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_proje, triangle.vertice[1]);
			triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_proje, triangle.vertice[2]);
			//SCALE
			triangle.vertice[0] = ft_scale_screen(triangle.vertice[0]);
			triangle.vertice[1] = ft_scale_screen(triangle.vertice[1]);
			triangle.vertice[2] = ft_scale_screen(triangle.vertice[2]);
			triangle_node = ft_triangle_node_create(triangle);
			ft_triangle_add_node(&triangle_lst, triangle_node);
		}
		i++;
	}
	//ORDER TRIANGLE FROM FAR TO NEAR
	ft_order_triangle_z_buffer(triangle_lst);
	keep = triangle_lst;
	while (triangle_lst != NULL)
	{
		//DRAW FILL TRIANGLE WITH SHADE/LIGHT
		ft_fill_triangle_shade((triangle_lst->vertice[0]), (triangle_lst->vertice[1]), (triangle_lst->vertice[2]), s_win, triangle_lst->shade);
		//DRAW MESH
		SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 255, 0, 0, 255);
		ft_draw_triangle_base(&(triangle_lst->vertice[0]), &(triangle_lst->vertice[1]), &(triangle_lst->vertice[2]), s_win);
		triangle_lst = triangle_lst->next;
	}
	triangle_lst = keep;
	raster->ftheta += 1;
	if (raster->ftheta == 360 * 2)
		raster->ftheta = 0;
	//free list
	return;
}
