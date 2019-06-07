/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process_polygon.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:50:04 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/02 11:20:26 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_bsp.h"

t_myvec		ft_calculate_polygon_normal(t_mypolygon *polygon_node)
{
	t_myvec		normal;
	t_myvec		v1, v2, v3;

	v1.x = polygon_node->vertex_lst->x;
	v1.y = polygon_node->vertex_lst->y;
	v1.z = polygon_node->vertex_lst->z;
	v2.x = polygon_node->vertex_lst->next->x;
	v2.y = polygon_node->vertex_lst->next->y;
	v2.z = polygon_node->vertex_lst->next->z;
	v3.x = polygon_node->vertex_lst->next->next->x;
	v3.y = polygon_node->vertex_lst->next->next->y;
	v3.z = polygon_node->vertex_lst->next->next->z;
	normal = ft_calculate_normal_of_points(v1, v2, v3);
	return (normal);
}

int			ft_calculate_number_of_vertex(t_mypolygon *polygon_lst)
{
	t_myvec			*keep_vec;
	int				nbr_vertex;

	keep_vec = polygon_lst->vertex_lst;
	nbr_vertex = 0;
	while (polygon_lst->vertex_lst != NULL)
	{
		polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
		nbr_vertex++;
	}
	polygon_lst->vertex_lst = keep_vec;
	return (nbr_vertex);
}

int			ft_calculate_number_of_indices(t_mypolygon *polygon_node)
{
	int		number_of_indices;

	number_of_indices = (polygon_node->number_of_vertex - 2) * 3;
	return (number_of_indices);
}

int			*ft_calculate_indices_tab(t_mypolygon *polygon_node)
{
	int		i;
	int		*indices;
	int		v0, v1, v2;

	i = 0;
	indices = (int*)malloc(sizeof(int) * polygon_node->number_of_indices);
	while (i < polygon_node->number_of_indices / 3)
	{
		if (i == 0)
		{
			v0 = 0;
			v1 = 1;
			v2 = 2;
		}
		else
		{
			v1 = v2;
			v2++;
		}
		indices[i * 3] = v0;
		indices[(i * 3) + 1] = v1;
		indices[(i * 3) + 2] = v2;
		i++;
	}
	return (indices);
}


void		ft_process_polygon(t_mypolygon *polygon_lst)
{
	t_mypolygon		*keep;
	int				i, j;

	printf("\n==>Process polygone lst<==");
	keep = polygon_lst;
	i = 0;
	while (polygon_lst != NULL)
	{
		printf("\npolygone n=%d\n", i);
		polygon_lst->normal = ft_calculate_polygon_normal(polygon_lst);
		printf("the normal result =%f =%f =%f\n",	polygon_lst->vertex_lst->x, polygon_lst->vertex_lst->y, polygon_lst->vertex_lst->z);
		polygon_lst->number_of_vertex = ft_calculate_number_of_vertex(polygon_lst);
		printf("Number of vertex =%d\n", polygon_lst->number_of_vertex);
		polygon_lst->number_of_indices = ft_calculate_number_of_indices(polygon_lst);
		printf("Number of indices =%d\n", polygon_lst->number_of_indices);
		polygon_lst->indices = ft_calculate_indices_tab(polygon_lst);
		j = 0;
		printf("Les indices : ");
		while (j < polygon_lst->number_of_indices)
		{
			printf("%d  ", polygon_lst->indices[j]);
			j++;
		}
		printf("\n");
		polygon_lst = polygon_lst->next;
		i++;
	}
	polygon_lst = keep;
}
