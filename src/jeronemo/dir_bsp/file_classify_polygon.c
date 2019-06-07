/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_classify_polygon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:37:38 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/30 11:38:34 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_bsp.h"

int			ft_classify_point(t_myvec point, t_mypolygon *plane)
{
	float		result;
	t_myvec		direction;

	direction = ft_vector_from_two_points(*plane->vertex_lst, point);//pas sur de l'etoile
	result = ft_dot_product(direction, plane->normal);
	if (result < - 0.001)
		return (FRONT);
	else if (result > 0.001)
		return (BACK);
	else
		return (ON_PLANE);
}

int			ft_classify_polygon(t_mypolygon *plane, t_mypolygon *polygon_node)
{
	int			front;
	int			back;
	int			on_plane;
	int			result;
	t_myvec		*keep;

	result = 0;
	front = 0;
	back = 0;
	on_plane = 0;
	keep = polygon_node->vertex_lst;
	while (polygon_node->vertex_lst != NULL)
	{
		result = ft_classify_point(*polygon_node->vertex_lst, plane);//pas sur de l'etoile
		if (result == FRONT)
			front++;
		else if (result == BACK)
			back++;
		else
		{
			on_plane++;
			front++;
			back++;
		}
		polygon_node->vertex_lst = polygon_node->vertex_lst->next;
	}
	polygon_node->vertex_lst = keep;
	if (on_plane == polygon_node->number_of_vertex)
		return (ON_PLANE);
	else if (front  == polygon_node->number_of_vertex)
		return (FRONT);
	else if (back == polygon_node->number_of_vertex)
		return (BACK);
	else
		return (SPANNING);
}
