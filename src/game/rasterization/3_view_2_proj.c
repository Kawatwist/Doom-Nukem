/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_view_2_proj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:13:10 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/11 16:38:59 by jsauron          ###   ########.fr       */
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
	int i;

	i = 0;
	v2p_matrice(wn);
	//	mat = mult_matrice(mat, wn->rast->mat_proj);
	while (i < curr->nb_ver)
	{
		ver[i].x = (curr->ver_tmp[curr->indices[i]].x * mat[0][0])
			+ (curr->ver_tmp[curr->indices[i]].y * mat[0][1])
			+ (curr->ver_tmp[curr->indices[i]].z * mat[0][2]);
		ver[i].y = (curr->ver_tmp[curr->indices[i]].y * mat[1][0])
			+ (curr->ver_tmp[curr->indices[i]].y * mat[1][1])
			+ (curr->ver_tmp[curr->indices[i]].z * mat[1][2]);
		ver[i].z = (curr->ver_tmp[curr->indices[i]].z * mat[2][0])
			+ (curr->ver_tmp[curr->indices[i]].y * mat[2][1])
			+ (curr->ver_tmp[curr->indices[i]].z * mat[2][2]);
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
