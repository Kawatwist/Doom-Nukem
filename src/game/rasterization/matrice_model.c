/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_model.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:06:28 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/19 15:40:29 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	scale(double **mat)
{
	mat[0][0] = SCALEX; //scale = distanc	e entre player et objet
	mat[1][1] = SCALEY;
	mat[2][2] = SCALEZ;
}

void	trans(t_win *wn, double **mat)
{
	mat[0][3] += wn->player->x;
	mat[1][3] += wn->player->y;
	mat[2][3] += wn->player->z;
}

void	rot_z(double ang, double **mat)
{
	ang *= M_PI / 180;
	mat[0][0] += cos(ang);
	mat[0][1] += sin(ang);
	mat[1][0] += -sin(ang);
	mat[1][1] += cos(ang);
}

void	rot_y(double ang, double **mat)
{
	ang *= M_PI / 180;
	mat[0][0] += cos(ang);
	mat[0][2] += -sin(ang);
	mat[2][0] += sin(ang);
	mat[2][2] += cos(ang);
}

void	rot_x(double ang, double **mat)
{
	ang *= M_PI / 180;
	mat[1][1] += cos(ang);
	mat[2][1] += -sin(ang);
	mat[1][2] += sin(ang);
	mat[2][2] += cos(ang);
}

void	matrice_model(t_win *wn, double **model)
{
		rot_z(wn->player->rawz, model);
		rot_y(wn->player->rawy, model);
		rot_x(wn->player->rawx, model);
		trans(wn, wn->rast->model);
}
