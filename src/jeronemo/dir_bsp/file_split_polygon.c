/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_split_polygon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:20:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/30 16:22:15 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_bsp.h"


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

	//[...]

	return (0);
}



void		ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split)
{
	t_myvec		front_list[20];
	t_myvec		back_list[20];
	t_myvec		*first_vertex;
	t_myvec		plane_normal;
	t_myvec		intersect_point;
	t_myvec		*point_on_plane;
	t_myvec		point_a;
	t_myvec		point_b;
	int			front_counter = 0;
	int			back_counter = 0;
	int			i;
	int			current_vertex;
	float		percent;


	point_on_plane = plane->vertex_lst;  //un point fesant partis du polygon splitter
	first_vertex = poly->vertex_lst;

	int result;
	result = ft_classify_point(*first_vertex, plane);
	if (result == FRONT)
	{
		front_list[front_counter] = *first_vertex;
		front_counter++;
	}
	else if (result == BACK)
	{
		back_list[back_counter] = *first_vertex;
		back_counter++;
	}
	else if (result == ON_PLANE)
	{
		front_list[front_counter] = *first_vertex;
		front_counter++;
		back_list[back_counter] = *first_vertex;
		back_counter++;
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
			front_list[front_counter] = *first_vertex;
			front_counter++;
			back_list[back_counter] = *first_vertex;
			back_counter++;
		}
		else
		{
			if (ft_get_intersect())
			{
				/////si il y intersection if a edge get intersect
			}
			else
			{
				///// si il il n'y a pas d'intersection
				if (result == FRONT && current_vertex != 0)
				{
					front_list[front_counter] = poly->vertex_list[current_vertex]; ///// a changer
					front_counter++;
				}
				if (result == BACK && curent_vertex != 0)
				{
					back_list[front_counter] = poly->vertex_list[current_vertex]; ///// a changer
					back_counter++;
				}
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



