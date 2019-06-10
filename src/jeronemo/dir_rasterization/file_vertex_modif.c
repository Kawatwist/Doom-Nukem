/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vertex_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:51:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/10 10:57:24 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

t_myvec	ft_rotation_y(float angle, t_myvec vertex);
t_myvec	ft_rotation_z(float angle, t_myvec vertex);
t_myvec	ft_matrix_multiply(float matrix[5][5], t_myvec vertex);
float	ft_rad(float angle)
t_myvec	ft_translation_x(float value, t_myvec vertex)
t_myvec	ft_translation_y(float value, t_myvec vertex)
t_myvec	ft_translation_z(float value, t_myvec vertex)
t_myvec	ft_scale(float zoom, t_myvec vertex)


float	ft_rad(float angle)
{
	float	result;

	result = angle * (M_PI / 180.0);
	return (result);
}

t_myvec	ft_translation_x(float value, t_myvec vertex)
{
	t_myvec		result;

	printf("translation x\n");
	result.x = vertex.x + value;
	result.y = vertex.y;
	result.z = vertex.z;
	return (result);
}

t_myvec	ft_translation_y(float value, t_myvec vertex)
{
	t_myvec		result;

	printf("translation y\n");
	result.x = vertex.x;
	result.y = vertex.y + value;
	result.z = vertex.z;
	return (result);
}

t_myvec	ft_translation_z(float value, t_myvec vertex)
{
	t_myvec		result;

	printf("translation z\n");
	result.x = vertex.x;
	result.y = vertex.y;
	result.z = vertex.z + value;
	return (result);

}

t_myvec	ft_scale(float zoom, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	matrix[1][1] = zoom;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = zoom;
	matrix[2][3] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = zoom;
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}

t_myvec	ft_rotation_x(float angle, t_myvec vertex)
{
	printf("rotation x\n");
	float		matrix[5][5];
	t_myvec		result;

	angle = ft_rad(angle);
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
	matrix[2][3] = sin(angle);
	matrix[3][1] = 0;
	matrix[3][2] = -sin(angle);
	matrix[3][3] = cos(angle);
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}

t_myvec	ft_matrix_multiply(float matrix[5][5], t_myvec vertex)
{
	t_myvec		result;

	result.x = (matrix[1][1] * vertex.x) + (matrix[1][2] * vertex.y) + (matrix[1][3] * vertex.z);
	result.y = (matrix[2][1] * vertex.x) + (matrix[2][2] * vertex.y) + (matrix[2][3] * vertex.z);
	result.z = (matrix[3][1] * vertex.x) + (matrix[3][2] * vertex.y) + (matrix[3][3] * vertex.z);
	return (result);
}

t_myvec	ft_rotation_z(float angle, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	angle = ft_rad(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = sin(angle);
	matrix[1][3] = 0;
	matrix[2][1] = -sin(angle);
	matrix[2][2] = cos(angle);
	matrix[2][3] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}

t_myvec	ft_rotation_y(float angle, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	angle = ft_rad(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = 0;
	matrix[1][3] = -sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;
	matrix[3][1] = sin(angle);
	matrix[3][2] = 0;
	matrix[3][3] = cos(angle);
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}
