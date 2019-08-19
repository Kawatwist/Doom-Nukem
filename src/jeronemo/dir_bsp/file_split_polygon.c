/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_split_polygon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:20:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/19 23:17:20 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h> 


int			ft_get_intersect(t_myvec *line_start,
							t_myvec *line_end,
							t_myvec *vertex,
							t_myvec *normal,
							t_myvec *intersection,
							float *percentage)
{
	t_myvec		direction;
	t_myvec		L1;
	float		line_length;
	float		dist_from_plane;

	direction.x = line_end->x - line_start->x;
	direction.y = line_end->y - line_start->y;
	direction.z = line_end->z - line_start->z;

	line_length = ft_dot_product(direction, normal);

	if (fabsf(line_length) < 0.0001)
		return 0;

	L1.x = vertex->x - line_start->x;
	L1.y = vertex->y - line_start->y;
	L1.z = vertex->z - line_start->z;

	dist_from_plane = ft_dot_product(L1, normal);
	percentage = dist_from_plane / line_length;

	if (percentage<0.0f)
			return (0);
	else if (percentage > 1.0f)
			return (0);

	intersection->x = line_start->x + direction.x * (percentage);
	intersection->y = line_start->y + direction.y * (percentage);
	intersection->z = line_start->z + direction.z * (percentage);
	return (1);
}



void		ft_split_polygon(t_mypolygon *poly, t_mypolygon *plane, t_mypolygon *front_split, t_mypolygon *back_split)
{
	t_myvec		front_list[20];
	t_myvec		back_list[20];
	t_myvec		first_vertex;
	t_myvec		plane_normal;
	t_myvec		intersect_point;
	t_myvec		point_on_plane;
	t_myvec		point_a;
	t_myvec		point_b;
	int			front_counter = 0;
	int			back_counter = 0;
	int			i = 0;
	int			current_vertex;
	float		percent;


	point_on_plane = plane->vertex_lst[0]t;  //un point fesant partis du polygon splitter
	first_vertex = poly->vertex_lst[0];
	int result;
	result = ft_classify_point(first_vertex, plane);
	if (result == FRONT)
		front_list[front_counter++] = first_vertex;
	else if (result == BACK)
		back_list[back_counter++] = first_vertex;
	else if (result == ON_PLANE)
	{
		front_list[front_counter++] = first_vertex;
		back_list[back_counter++] = first_vertex;
	}
	////////////////////////////////////
	i = 1;
	while (i < poly->number_of_vertex + 1)
	{
		////on boucle le dernier point avec le premier
		if (i == poly->number_of_vertex)
			current_vertex = 0;
		else
			current_vertex = i;

		point_a = poly->vertex_list[i - 1];  ///////a changer
		point_b = poly->vertex_list[current_vertex]; ///// a changer

		result = ft_classify_point(point_b, plane);

		if (result == ON_PLANE) //// on ajoute au deux list
		{
				front_list[front_counter++] = poly->vertex_list[current_vertex];
				back_list[back_counter++] = poly->vertex_list[current_vertex];
		}
		else
		{
			if (ft_get_intersect(point_a, point_b, point_on_plane, plane_normal, intersect_point, percent))
			{

				/////si il y intersection if a edge get intersect
			}
			else
			{
				///// si il il n'y a pas d'intersection
				if (result == FRONT && current_vertex != 0)
					front_list[front_counter++] = poly->vertex_list[current_vertex]; ///// a changer
				if (result == BACK && curent_vertex != 0)
					back_list[back_counter++] = poly->vertex_list[current_vertex]; ///// a changer
			}
		}
		i++;
	}

	/////////////////we process les deux vouveau polygones
	//normal
	//nombre de vertex
	//nombre d'indices
	//tableau d'indices
}



