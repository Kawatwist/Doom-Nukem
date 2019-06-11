/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vertex_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:51:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/11 17:40:50 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_draw_change(t_mywin *s_win, t_mychange *change)
{
	t_myputtheline		s_line;;

	change->result_1 = ft_rotation_x(change->angle_x, change->result_1);
	change->result_2 = ft_rotation_x(change->angle_x, change->result_2);
		if (change->triangle == 1)
			change->result_3 = ft_rotation_x(change->angle_x, change->result_3);

	change->result_1 = ft_rotation_y(change->angle_y, change->result_1);
	change->result_2 = ft_rotation_y(change->angle_y, change->result_2);
	if (change->triangle == 1)
		change->result_3 = ft_rotation_y(change->angle_y, change->result_3);

	change->result_1 = ft_rotation_z(change->angle_z, change->result_1);
	change->result_2 = ft_rotation_z(change->angle_z, change->result_2);
	if (change->triangle == 1)
		change->result_3 = ft_rotation_z(change->angle_z, change->result_3);

	change->result_1 = ft_scale(change->zoom, change->result_1);
	change->result_2 = ft_scale(change->zoom, change->result_2);
	if (change->triangle == 1)
		change->result_3 = ft_scale(change->zoom, change->result_3);

	change->result_1 = ft_translation_x(change->translation_x, change->result_1);
	change->result_2 = ft_translation_x(change->translation_x, change->result_2);
	if (change->triangle == 1)
		change->result_3 = ft_translation_x(change->translation_x, change->result_3);

	change->result_1 = ft_translation_y(change->translation_y, change->result_1);
	change->result_2 = ft_translation_y(change->translation_y, change->result_2);
	if (change->triangle == 1)
	{
		change->result_3 = ft_translation_y(change->translation_y, change->result_3);
		printf("AAAAAAAAAAAAAAAAA\n");
	}

	change->result_1 = ft_translation_z(change->translation_z, change->result_1);
	change->result_2 = ft_translation_z(change->translation_z, change->result_2);
	if (change->triangle == 1)
		change->result_3 = ft_translation_z(change->translation_z, change->result_3);


	t_myvec		normal;
	t_myvec		camera;

	camera.x = 0;
	camera.y = 0;
	camera.z = 0;


	normal = ft_cross_product(change->result_2, change->result_1);


	float l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z*normal.z);
	normal.x /= l;
	normal.y /= l;
	normal.z /= l;


	if (	(normal.x * (change->result_1.x - camera.x) +
			 	normal.y * (change->result_1.y - camera.y) +
			 	normal.z * (change->result_1.z - camera.z)) < 0.0 || 1  )
	{
		if (change->projection == 1)
		{
			s_line.un.a = change->result_1.x;
			s_line.un.b = change->result_1.y;
			s_line.deux.a = change->result_2.x;
			s_line.deux.b = change->result_2.y;
			ft_draw_line(s_win, &s_line);
		}
		else if (change->projection == 0)
		{
			change->result_1 = ft_perspective_projection(change->result_1);
			change->result_2 = ft_perspective_projection(change->result_2);
			if (change->triangle == 1)
				change->result_3 = ft_perspective_projection(change->result_3);


			s_line.un.a = change->result_1.x;
			s_line.un.b = change->result_1.y;
			s_line.deux.a = change->result_2.x;
			s_line.deux.b = change->result_2.y;
			ft_draw_line(s_win, &s_line);


			if (change->triangle == 1)
			{
				s_line.un.a = change->result_2.x;
				s_line.un.b = change->result_2.y;
				s_line.deux.a = change->result_3.x;
				s_line.deux.b = change->result_3.y;
				ft_draw_line(s_win, &s_line);


				s_line.un.a = change->result_3.x;
				s_line.un.b = change->result_3.y;
				s_line.deux.a = change->result_1.x;
				s_line.deux.b = change->result_1.y;
				ft_draw_line(s_win, &s_line);
			}

		}
		SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
	}
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

	/* printf("translation x\n"); */
	result.x = vertex.x + value;
	result.y = vertex.y;
	result.z = vertex.z;
	return (result);
}

t_myvec	ft_translation_y(float value, t_myvec vertex)
{
	t_myvec		result;

	/* printf("translation y\n"); */
	result.x = vertex.x;
	result.y = vertex.y + value;
	result.z = vertex.z;
	return (result);
}

t_myvec	ft_translation_z(float value, t_myvec vertex)
{
	t_myvec		result;

	/* printf("translation z\n"); */
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
	/* printf("rotation x\n"); */
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


t_myvec	ft_matrix_multiply_four(float matrix[5][5], t_myvec vertex)
{
	t_myvec		result;
	float		x;
	float		y;
	float		z;
	float		zz;

	x = (matrix[1][1] * vertex.x) + (matrix[2][1] * vertex.y) + (matrix[3][1] * vertex.z) + (matrix[4][1] * 1);
	y = (matrix[1][2] * vertex.x) + (matrix[2][2] * vertex.y) + (matrix[3][2] * vertex.z) + (matrix[4][2] * 1);
	z = (matrix[1][3] * vertex.x) + (matrix[2][3] * vertex.y) + (matrix[3][3] * vertex.z) + (matrix[4][3] * 1);
	zz= (matrix[1][4] * vertex.x) + (matrix[2][4] * vertex.y) + (matrix[3][4] * vertex.z) + (matrix[4][4] * 1);
	if (zz != 0)
		;
	else
		zz = 1;

	result.x = x / zz;
	result.y = y / zz;
	result.z = z / zz;
	return (result);
}

t_myvec	ft_perspective_projection(t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	float	height;
	float	width;
	float	teta;
	float	z_far;
	float	z_near;

	height = YSCREEN;
	width = XSCREEN;
	teta = 90.0;
	z_far = 1000.0;
	z_near = 0.1;

	matrix[1][1] = (height / width) * (1.0 / (tan(ft_rad(teta) / 2.0)));
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[1][4] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0/ tan(ft_rad(teta) / 2.0);
	matrix[2][3] = 0.0;
	matrix[2][4] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = z_far / (z_far - z_near);
	matrix[3][4] = 1.0;
	matrix[4][1] = 0.0;
	matrix[4][2] = 0.0;
	matrix[4][3] = (-z_far * z_near)  / (z_far - z_near)  ;
	matrix[4][4] = 0.0;
	result = ft_matrix_multiply_four(matrix, vertex);

	//scale
	result.x += 1.0;
	result.y += 1.0;

	result.x *= 0.5 * (float)XSCREEN;
	result.y *= 0.5 * (float)YSCREEN;
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

