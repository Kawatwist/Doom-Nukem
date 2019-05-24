/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:15:13 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/22 16:58:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_ver(t_vec	*vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void		init_rast(t_win **wn)
{
	int i;

	i = 0;
	((*wn)->rast = malloc(sizeof(t_rast))) == NULL ? stop_exec("malloc struct rast failed\n", *wn) : 0;
	((*wn)->rast->mat = (double **)malloc(sizeof(double *) * 4)) == NULL ? stop_exec("malloc rast->mat failed\n", *wn) : 0;
	while (i < 4)	
		((*wn)->rast->mat[i++] = (double *)malloc(sizeof(double) * 4)) == NULL ? stop_exec("malloc rast->mat[] failed\n", *wn) : 0;
	((*wn)->rast->f = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->f failed\n", *wn) : 0;
	((*wn)->rast->s = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->s failed\n", *wn) : 0;
	((*wn)->rast->u = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->u failed\n", *wn) : 0;
	initmatrice((*wn)->rast->mat);	
	init_ver((*wn)->rast->f, 0, 0, 0);
	init_ver((*wn)->rast->s, 0, 0, 0);
	init_ver((*wn)->rast->u, 0, 0, 0);
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
	(*wn)->poly->ver_tmp = NULL;
}
