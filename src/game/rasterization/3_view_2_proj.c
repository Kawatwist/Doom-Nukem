/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_view_2_proj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:13:10 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/15 18:12:45 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	v2p_matrice(t_win *wn)
{
	int i;

	i = -1;
	initmatrice(wn->rast->mat_3);
	wn->rast->mat_3[0][0] = atan(60 / 2);
	wn->rast->mat_3[1][1] = atan(60 / 2);
	wn->rast->mat_3[2][2] =
		-((wn->player->far + wn->player->near)
				/ (wn->player->far - wn->player->near));
	wn->rast->mat_3[2][3] =
		-((2 * wn->player->near * wn->player->far)
				/ (wn->player->far - wn->player->near));
	wn->rast->mat_3[2][0] = -1;
}

void	v2p_matrice_calcul(t_win *wn, t_poly *curr, t_vec *ver,  double **mat)
{		
	int		i;
	t_vec*	ver_tmp;

	i = 0;
	v2p_matrice(wn);

	while (i < curr->nb_ver)
	{
	(ver_tmp = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc ver_tmp failed\n", wn) : 0;
		init_ver(ver_tmp, curr->ver_tmp[curr->indices[i]].x , curr->ver_tmp[curr->indices[i]].y ,curr->ver_tmp[curr->indices[i]].z );
			ver[i].x = (ver_tmp->x * mat[0][0])
				+ (ver_tmp->y * mat[0][1])
				+ (ver_tmp->z * mat[0][2]);
			ver[i].y = (ver_tmp->y * mat[1][0])
				+ (ver_tmp->y * mat[1][1])
				+ (ver_tmp->z * mat[1][2]);
			ver[i].z = (ver_tmp->z * mat[2][0])
				+ (ver_tmp->y * mat[2][1])
				+ (ver_tmp->z * mat[2][2]);
			free(ver_tmp);
		i++;
	}
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
