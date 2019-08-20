/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_test_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:04:25 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/20 15:43:30 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_bsp.h> 

void			ft_display_the_polygon_list(t_mypolygon *polygon_lst)
{
	t_mypolygon		*keep;
	t_myvec			*keep_vec;
	int				i;
	int				j;

	keep = polygon_lst;
	printf("Display polygone lst\n");
	i = 0;
	while (polygon_lst != NULL)
	{
		printf("\nPolynome n=%d\n", i);
		keep_vec = polygon_lst->vertex_lst;
		j = 0;
		while (polygon_lst->vertex_lst != NULL)
		{
			printf("vertice n=%d\t", j);
			printf("x =%f\t", polygon_lst->vertex_lst->x);
			printf("y =%f\t", polygon_lst->vertex_lst->y);
			printf("u =%f\n", polygon_lst->vertex_lst->u);
			printf("v =%f\n", polygon_lst->vertex_lst->v);
			j++;
			polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
		}
		polygon_lst->vertex_lst = keep_vec;
		polygon_lst = polygon_lst->next;
		i++;
	}
	polygon_lst = keep;
}
