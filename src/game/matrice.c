/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 15:10:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/22 17:01:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	trans(t_win *wn, double **mat)
{
	mat[0][3] = wn->player->rawx * XSCREEN / 360;
	mat[1][3] = wn->player->rawy;
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
	mat[1][1] += cos(ang);
	mat[1][2] += -sin(ang);
	mat[2][1] += sin(ang);
	mat[2][2] += cos(ang);
}
