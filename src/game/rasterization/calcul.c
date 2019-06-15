/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matriice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:24:28 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/15 17:44:48 by jsauron          ###   ########.fr       */
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
		ret[i] = malloc(sizeof(double) * 4);
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

t_vec        ft_cross_product(t_vec v1, t_vec v2)
{
	t_vec        result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

t_vec        ft_calculate_normal_of_points(t_vec vertex1, t_vec vertex2, t_vec vertex3)
{
	t_vec        result;
	t_vec        v1;
	t_vec        v2;

	v1.x = vertex2.x - vertex1.x;
	v1.y = vertex2.y - vertex1.y;
	v1.z = vertex2.z - vertex1.z;
	v2.x = vertex3.x - vertex1.x;
	v2.y = vertex3.y - vertex1.y;
	v2.z = vertex3.z - vertex1.z;
	result = ft_cross_product(v1, v2);
	return (result);
}

t_vec        ft_normalise(t_vec vector)
{
	float        l;

	l = sqrtf(vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z*vector.z);
	vector.x /= l;
	vector.y /= l;
	vector.z /= l;
	return (vector);
}
