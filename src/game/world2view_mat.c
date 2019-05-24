/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2view_mat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:50:53 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 12:47:00 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	world2view(t_win *wn, t_vec *ver, t_vec *f, t_vec *s, t_vec *u)
{
	t_vec	*ver_tmp;

	(ver_tmp = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc ver_tmp failed\n", wn) : 0;
	init_ver(ver_tmp, ver->x, ver->y, ver->z);
	ver->x = (s->x * 1 * ver_tmp->x) + (s->y * 0 * ver_tmp->y) + (s->z * 0 * ver_tmp->z) + (0 * -(wn->player->x) * 1);
	ver->y = (u->x * 1 * ver_tmp->x) + (u->y * 0 * ver_tmp->y) + (u->z * 0 * ver_tmp->z) + (0 * -(wn->player->y) * 1);
	ver->z = (-(f->x) * 1 * ver_tmp->x) + (-(f->y) * 0 * ver_tmp->y) + (-(f->z) * 0 * ver_tmp->z) + (0 * -(wn->player->y) * 1);
	free(ver_tmp);
}
