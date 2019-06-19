/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_view_2_proj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:13:10 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/19 15:44:13 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	matrice_projection(t_win *wn)
{
	int i;

	i = -1;
	initmatrice(wn->rast->proj);
	wn->rast->proj[0][0] = 1.0 / (tan(degres_to_radius(wn->rast->fov / 2.0)));
	wn->rast->proj[1][1] = 1.0 / (tan(degres_to_radius(wn->rast->fov / 2.0)));
	wn->rast->proj[2][2] = -(wn->player->far
				/ (wn->player->far - wn->player->near));
	wn->rast->proj[2][3] = -1.0;
	wn->rast->proj[3][2] =
		-(2.0 * wn->player->near * wn->player->far)
				/ (wn->player->far - wn->player->near);
}

void	get_near_n_far(t_win *wn, double z)
{
	if (z > wn->player->far && (wn->player->far == wn->player->near))
	{
		wn->player->far = z;
		wn->player->near = z;
	}
	else if (z > wn->player->far)
		wn->player->far = z;
	else if (z < wn->player->near)
		wn->player->near = z;
}
