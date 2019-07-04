/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vector_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:42:03 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/04 12:10:47 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_myvec ft_create_vector(float p_x, float p_y, float p_z)
{
	t_myvec result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;
	return (result);
}

t_myvec	ft_vector_inverse(t_myvec src)
{
	t_myvec	result;

	result.x = -1 * src.x;
	result.y = -1 * src.y;
	result.z = -1 * src.z;

	return (result);
}

t_myvec        ft_normalise(t_myvec vector)
{
   	float        l;

   	l = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
   	vector.x /= l;
   	vector.y /= l;
   	vector.z /= l;
   	return (vector);
}

t_myvec		ft_vector_sub(t_myvec v2, t_myvec v1)
{
	t_myvec result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}

t_myvec		ft_vector_add(t_myvec v1, t_myvec v2)
{
	t_myvec result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_myvec		 ft_matrix_multiply_vector(float **m, t_myvec i)
{
	t_myvec v;
	float w;

 	v.x = i.x * m[0][0] + i.y * m[1][0] + i.z * m[2][0] + m[3][0];
	v.y = i.x * m[0][1] + i.y * m[1][1] + i.z * m[2][1] + m[3][1];
	v.z = i.x * m[0][2] + i.y * m[1][2] + i.z * m[2][2] + m[3][2];
	w = i.x * m[0][3] + i.y * m[1][3] + i.z * m[2][3] + m[3][3];
	if (w != 0.0)
	{
		v.x /= w;
		v.y /= w;
		v.z /= w;

	}
	return v;
}

t_myvec	ft_matrix_multiply_vector_general(float matrix[5][5], t_myvec v)
{
	t_myvec		vertex;

	vertex.x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0] + v.w * matrix[3][0];
	vertex.y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1] + v.w * matrix[3][1];
	vertex.z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2] + v.w * matrix[3][2];
	vertex.w = v.x * matrix[0][3] + v.y * matrix[1][3] + v.z * matrix[2][3] + v.w * matrix[3][3];
	return (vertex);
}

t_myvec		ft_vector_multiply(t_myvec m, float k)
{
	t_myvec		result;

	result.x = m.x * k;
	result.y = m.y * k;
	result.z = m.z * k;
	return (result);
}
