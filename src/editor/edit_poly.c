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

// t_mypolygon 		*polygon_map(t_win *wn)
// {
// 	t_mypolygon 	*poly;

// 	while (wn->elem != NULL)
// 	{
// 		poly = malloc(sizeof(t_mypolygon));
// 		while (wn->elem->point != NULL)
// 		{
// 			poly->vertex_lst = wn->elem->point;
// 			wn->elem->point = wn->elem->point->next;
// 		}
// 		wn->elem = wn->elem->next;
// 	}
// 	if (wn->elem == NULL)
// 		poly = NULL;
// 	return (poly);
// }

t_poly 				*poly_map(t_win *wn)
{
	t_poly 		*poly;
	int			i;

	i = 0;
	while (wn->elem != NULL)
	{
		poly = malloc(sizeof(t_poly));
		poly->nb_ver = wn->elem->nb_pt;
		poly->ver_list = malloc(sizeof(t_vec) * poly->nb_ver);
		while (i < poly->nb_ver && wn->elem->point != NULL)
		{
			poly->ver_list[i].x = wn->elem->point->x;
			poly->ver_list[i].y = wn->elem->point->y;
			poly->ver_list[i].z = wn->elem->point->z;
			i++;
			wn->elem->point = wn->elem->point->next;
		}
		wn->elem = wn->elem->next;
	}
	if (wn->elem == NULL)
		poly = NULL;
	return (poly);
}