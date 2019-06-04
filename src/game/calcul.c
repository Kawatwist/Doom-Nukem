/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matriice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:24:28 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/27 19:34:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double **mult_matrice(double **mat1, double **mat2)
{
	double	**ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(double *) * 4);
	while (++i < 4)
	ret = malloc(sizeof(double) * 4);
	ret[0][0] = (mat1[0][0] * mat2[0][0]) + (mat1[0][1] * mat2[1][0]) + (mat1[0][2] * mat2[2][0]) + (mat1[0][3] * mat2[3][0]);
	ret[0][1] = (mat1[0][0] * mat2[0][1]) + (mat1[0][1] * mat2[1][1]) + (mat1[0][2] * mat2[2][1]) + (mat1[0][3] * mat2[3][1]);
	ret[0][2] = (mat1[0][0] * mat2[0][2]) + (mat1[0][1] * mat2[1][2]) + (mat1[0][2] * mat2[2][2]) + (mat1[0][3] * mat2[3][2]);
	ret[0][3] = (mat1[0][0] * mat2[0][3]) + (mat1[0][1] * mat2[1][3]) + (mat1[0][2] * mat2[2][3]) + (mat1[0][3] * mat2[3][3]);
	ret[1][0] = (mat1[1][0] * mat2[0][0]) + (mat1[1][1] * mat2[1][0]) + (mat1[1][2] * mat2[2][0]) + (mat1[1][3] * mat2[3][0]);
	ret[1][1] = (mat1[1][0] * mat2[0][1]) + (mat1[1][1] * mat2[1][1]) + (mat1[1][2] * mat2[2][1]) + (mat1[1][3] * mat2[3][1]);
	ret[1][2] = (mat1[1][0] * mat2[0][2]) + (mat1[1][1] * mat2[1][2]) + (mat1[1][2] * mat2[2][2]) + (mat1[1][3] * mat2[3][2]);
	ret[1][3] = (mat1[1][0] * mat2[0][3]) + (mat1[1][1] * mat2[1][3]) + (mat1[1][2] * mat2[2][3]) + (mat1[1][3] * mat2[3][3]);
	ret[2][0] = (mat1[2][0] * mat2[0][0]) + (mat1[2][1] * mat2[1][0]) + (mat1[2][2] * mat2[2][0]) + (mat1[2][3] * mat2[3][0]);
	ret[2][1] = (mat1[2][0] * mat2[0][1]) + (mat1[2][1] * mat2[1][1]) + (mat1[2][2] * mat2[2][1]) + (mat1[2][3] * mat2[3][1]);
	ret[2][2] = (mat1[2][0] * mat2[0][2]) + (mat1[2][1] * mat2[1][2]) + (mat1[2][2] * mat2[2][2]) + (mat1[2][3] * mat2[3][2]);
	ret[2][3] = (mat1[2][0] * mat2[0][3]) + (mat1[2][1] * mat2[1][3]) + (mat1[2][2] * mat2[2][3]) + (mat1[2][3] * mat2[3][3]);
	ret[3][0] = (mat1[3][0] * mat2[0][0]) + (mat1[3][1] * mat2[1][0]) + (mat1[3][2] * mat2[2][0]) + (mat1[3][3] * mat2[3][0]);
	ret[3][1] = (mat1[3][0] * mat2[0][1]) + (mat1[3][1] * mat2[1][1]) + (mat1[3][2] * mat2[2][1]) + (mat1[3][3] * mat2[3][1]);
	ret[3][2] = (mat1[3][0] * mat2[0][2]) + (mat1[3][1] * mat2[1][2]) + (mat1[3][2] * mat2[2][2]) + (mat1[3][3] * mat2[3][2]);
	ret[3][3] = (mat1[3][0] * mat2[0][3]) + (mat1[3][1] * mat2[1][3]) + (mat1[3][2] * mat2[2][3]) + (mat1[3][3] * mat2[3][3]);
	return (ret);
}
