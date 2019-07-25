/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_poly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:38:03 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/24 18:00:49 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "header_bsp.h"

t_myvec 		*create_vec_node(t_point *point)
{
	t_myvec		*vec;

	vec = malloc(sizeof(t_myvec));
	vec->x = point->x;
	vec->y = point->y;
	vec->z = point->z;
	return (vec);
}

t_mypolygon	 	*polygon_map(t_win *wn)
{
	t_mypolygon 	*poly;
	t_mypolygon 	*gon;
	t_point			*point;
	t_elem 			*keep;
	t_myvec 		*ver;
	t_myvec			*tex;

	keep = wn->elem;
	gon	= NULL;
	tex = NULL;
	while (keep != NULL)
	{
		point = keep->point;
		if (point != NULL)
			point = point->next;
		while (point != NULL)
		{
			ver = create_vec_node(point);
			ft_add_vertex(&tex, ver);
			if (point->next != NULL)
				point = point->next->next;
			else
				break;
		}
		poly = ft_create_polygon_node(tex);
		ft_add_polygon(&gon, poly);
		keep = keep->next;
	}
	if (wn->elem == NULL)
		gon = NULL;
	return (gon);
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
