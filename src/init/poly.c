/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:15:13 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/21 16:28:51 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_ver(t_vec	*vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void		init_poly(t_win **wn)
{
	(*wn)->poly = malloc(sizeof(t_poly));
	(*wn)->poly->ver_list = (t_vec *)malloc(sizeof(t_vec) * 4);
	init_ver(&((*wn)->poly->ver_list[0]), 100, 100, 100);
	init_ver(&((*wn)->poly->ver_list[1]), 120, 120, 100);
	init_ver(&((*wn)->poly->ver_list[2]), 120, 160, 100);
	init_ver(&((*wn)->poly->ver_list[3]), 100, 140, 100);
	(*wn)->poly->indices = malloc(sizeof(int) * 6);
	(*wn)->poly->indices[0] = 0;
	(*wn)->poly->indices[1] = 1;
	(*wn)->poly->indices[2] = 2;
	(*wn)->poly->indices[3] = 0;
	(*wn)->poly->indices[4] = 2;
	(*wn)->poly->indices[5] = 3;
	(*wn)->poly->nb_indices = 6;
	(*wn)->poly->nb_ver = 6;
	(*wn)->poly->next = NULL;
}
