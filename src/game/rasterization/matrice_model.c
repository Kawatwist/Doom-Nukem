/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_model.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:06:28 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/19 17:34:12 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*void	scale(double **mat)
{
	malloc_mat(wn, mat);
	mat[0][0] = SCALEX; //scale = distance entre player et objet
	mat[1][1] = SCALEY;
	mat[2][2] = SCALEZ;
}
*/
void	trans(t_win *wn, double **mat)
{
	malloc_mat(wn, mat);
	mat[0][3] = wn->player->x;
	mat[1][3] = wn->player->y;
	mat[2][3] = wn->player->z;
}

void	rot_z(t_win *wn, double ang, double **mat)
{
	ang *= M_PI / 180;
	malloc_mat(wn, mat);
	mat[0][0] = cos(ang);
	mat[0][1] = sin(ang);
	mat[1][0] = -sin(ang);
	mat[1][1] = cos(ang);
}

void	rot_y(t_win *wn, double ang, double **mat)
{
	ang *= M_PI / 180;
	malloc_mat(wn, mat);
	mat[0][0] = cos(ang);
	mat[0][2] = -sin(ang);
	mat[2][0] = sin(ang);
	mat[2][2] = cos(ang);
}

void	rot_x(t_win *wn, double ang, double **mat)
{
	ang *= M_PI / 180;
	malloc_mat(wn, mat);
	mat[1][1] = cos(ang);
	mat[2][1] = -sin(ang);
	mat[1][2] = sin(ang);
	mat[2][2] = cos(ang);
}

void	matrice_model(t_win *wn, double **model)
{
		rot_z(wn, wn->player->rawz, wn->rast->rot_z);
		rot_y(wn, wn->player->rawy, wn->rast->rot_y);
		rot_x(wn, wn->player->rawx, wn->rast->rot_x);
		trans(wn, wn->rast->trans);
		model = mult_matrice(wn->rast->trans, wn->rast->rot_x);
		model = mult_matrice(model, wn->rast->rot_y);
		model = mult_matrice(model, wn->rast->rot_z);
		free(wn->rast->trans);
		free(wn->rast->rot_x);
		free(wn->rast->rot_y);
		free(wn->rast->rot_z);
}
