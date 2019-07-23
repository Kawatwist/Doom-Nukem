/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_poly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:38:03 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/09 12:38:05 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_mypolygon 		*polygon_map(t_win *wn)
{
	t_mypolygon 	*poly;
	t_elem 			*keep;

	keep = wn->elem;
	while (keep != NULL)
	{
		poly = malloc(sizeof(t_mypolygon));
		if (keep->point != NULL)
		{
			poly->vertex_lst = malloc(sizeof(t_myvec));
			poly->vertex_lst->x = keep->point->x;
			poly->vertex_lst->y = keep->point->y;
			poly->vertex_lst->z = keep->point->z;
			keep->point = keep->point->next;
		}
		keep = keep->next;
	}
	if (wn->elem == NULL)
		poly = NULL;
	return (poly);
}

t_poly 				*poly_map(t_win *wn)
{
	t_poly 		*poly;
	t_elem 		*keep;
	int			i;

	keep = wn->elem;
	i = 0;
	while (keep != NULL)
	{
		poly = malloc(sizeof(t_poly));
		poly->nb_ver = keep->nb_pt;
		poly->ver_list = malloc(sizeof(t_vec) * poly->nb_ver);
		while (i < poly->nb_ver && keep->point != NULL)
		{
			poly->ver_list[i].x = keep->point->x;
			poly->ver_list[i].y = keep->point->y;
			poly->ver_list[i].z = keep->point->z;
			i++;
			keep->point = keep->point->next;
		}
		keep = keep->next;
	}
	if (wn->elem == NULL)
		poly = NULL;
	return (poly);
}