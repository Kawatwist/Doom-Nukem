/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_calcul_world_view.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 12:36:58 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 13:34:10 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

void	ft_calcul_world_view_matrix(t_myraster *raster)
{
	ft_set_raster_trans(0, 0, -30, raster);
	//ft_set_raster_rot_x(raster->ftheta, raster);
	ft_set_raster_rot_x(180, raster);
	//ft_set_raster_rot_y(raster->ftheta, raster);
	ft_set_raster_rot_z(raster->ftheta * 0.5, raster);
}

t_mytriangle	ft_calcul_world_view(t_mytriangle triangle, t_myraster *raster)
{
	//ROTATION Z
	triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_z);
	//ROTATION X
	triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_x);
	//TRANSLATION (offset in screen)
	triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_trans);
	return (triangle);
}

t_myvec		ft_calcul_normal_triangle_and_normalise(t_mytriangle triangle)
{
	t_myvec		normal;

	normal = ft_calculate_normal_of_points(triangle.vertice[0], triangle.vertice[1], triangle.vertice[2]);
	normal = ft_normalise(normal);
	return (normal);
}

int		ft_culling(t_mytriangle triangle, t_myraster *raster)
{
	t_myvec			normal;

	normal = ft_calcul_normal_triangle_and_normalise(triangle);
	if (ft_dot_product(normal, ft_vector_sub(triangle.vertice[0], raster->v_camera)) < 0.0)
		return (1);
	else
		return (0);
}

float	ft_calcul_shade(t_mytriangle triangle, t_myraster *raster)
{
	t_myvec			normal;

	normal = ft_calcul_normal_triangle_and_normalise(triangle);
	triangle.shade = ft_dot_product(normal, raster->light_direction);
	return (triangle.shade);
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
