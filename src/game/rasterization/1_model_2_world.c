/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_model_2_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:54:04 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/11 15:36:25 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	scale(double **mat)
{
	mat[0][0] = SCALEX; //scale = distance entre player et objet
	mat[1][1] = SCALEY;
	mat[2][2] = SCALEZ;
}

void	trans(t_win *wn, double **mat)
{
	mat[0][3] = wn->player->x;
	mat[1][3] = wn->player->y;
	mat[2][3] = wn->player->z;
}

void	rotatez(double ang, double **mat)
{
	ang *= M_PI / 180;
	mat[0][0] += cos(ang);
	mat[0][1] += sin(ang);
	mat[1][0] += -sin(ang);
	mat[1][1] += cos(ang);
}

void	rotatey(double ang, double **mat)
{
	ang *= M_PI / 180;
	mat[0][0] += cos(ang);
	mat[0][2] += sin(ang);
	mat[2][0] += -sin(ang);
	mat[2][2] += cos(ang);
}

void	rotatex(double ang, double **mat)
{
	ang *= M_PI / 180;
	mat	[1][1] += cos(ang);
	mat[1][2] += -sin(ang);
	mat[2][1] += sin(ang);
	mat[2][2] += cos(ang);
}

void	m2w_matrice(t_win *wn, t_poly *curr, double **mat, t_vec *ver)
{
	int		i;

	(void)wn;
	i = 0;
	while (i < curr->nb_ver)
	{
		ver[i].x = (curr->ver_tmp[curr->indices[i]].x * mat[0][0])
			+ (curr->ver_tmp[curr->indices[i]].y * mat[0][1])
			+ (curr->ver_tmp[curr->indices[i]].z * mat[0][2])
			+ mat[0][3];
		ver[i].y = (curr->ver_tmp[curr->indices[i]].y * mat[1][0])
			+ (curr->ver_tmp[curr->indices[i]].y * mat[1][1])
			+ (curr->ver_tmp[curr->indices[i]].z * mat[1][2])
			+ mat[1][3];
		ver[i].z = (curr->ver_tmp[curr->indices[i]].z * mat[2][0])
			+ (curr->ver_tmp[curr->indices[i]].y * mat[2][1])
			+ (curr->ver_tmp[curr->indices[i]].z * mat[2][2])
			+ mat[2][3];
		i++;
	}
}
