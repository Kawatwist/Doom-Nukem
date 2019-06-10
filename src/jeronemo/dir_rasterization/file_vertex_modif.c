/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vertex_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:51:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/10 12:40:05 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_draw_change(t_mywin *s_win, t_mychange *change)
{
	t_myputtheline		s_line;

	change->result_1 = ft_rotation_x(change->angle_x, change->result_1);
	change->result_2 = ft_rotation_x(change->angle_x, change->result_2);
	change->result_1 = ft_rotation_y(change->angle_y, change->result_1);
	change->result_2 = ft_rotation_y(change->angle_y, change->result_2);
	change->result_1 = ft_rotation_z(change->angle_z, change->result_1);
	change->result_2 = ft_rotation_z(change->angle_z, change->result_2);
	change->result_1 = ft_translation_x(change->translation_x, change->result_1);
	change->result_2 = ft_translation_x(change->translation_x, change->result_2);
	change->result_1 = ft_translation_y(change->translation_y, change->result_1);
	change->result_2 = ft_translation_y(change->translation_y, change->result_2);
	change->result_1 = ft_translation_z(change->translation_z, change->result_1);
	change->result_2 = ft_translation_z(change->translation_z, change->result_2);
	change->result_1 = ft_scale(change->zoom, change->result_1);
	change->result_2 = ft_scale(change->zoom, change->result_2);
	s_line.un.a = change->result_1.x;
	s_line.un.b = change->result_1.y;
	s_line.deux.a = change->result_2.x;
	s_line.deux.b = change->result_2.y;
	ft_draw_line(s_win, &s_line);
}

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

