/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_maths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:37:01 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/30 13:42:27 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_bsp.h"

float		ft_dot_product(t_myvec v1, t_myvec v2)
{
	float		result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}

t_myvec		ft_cross_product(t_myvec v1, t_myvec v2)
{
	t_myvec		result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

t_myvec		ft_calculate_normal_of_points(t_myvec vertex1, t_myvec vertex2, t_myvec vertex3)
{
	t_myvec		result;
	t_myvec		v1;
	t_myvec		v2;

	v1.x = vertex2.x - vertex1.x;
	v1.y = vertex2.y - vertex1.y;
	v1.z = vertex2.z - vertex1.z;
	v2.x = vertex3.x - vertex1.x;
	v2.y = vertex3.y - vertex1.y;
	v2.z = vertex3.z - vertex1.z;
	result = ft_cross_product(v1, v2);
	return (result);
}

t_myvec		ft_vector_from_two_points(t_myvec v2, t_myvec v1)
{
	t_myvec			result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}

int		ft_abs(int number)
{
	//prevoir le int min
	if (number < 0)
		number *= -1;
	return (number);
}
