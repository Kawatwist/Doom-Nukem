/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_matrix_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:17:48 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/03 15:32:42 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>

float	ft_rad(float angle)
{
	float	result;

	result = angle * (M_PI / 180.0);
	return (result);
}

t_myvec		ft_scale_screen(t_myvec result)
{
	result.x += 1.0;
	result.y += 1.0;

	result.x *= 0.5 * (float)XSCREEN;
	result.y *= 0.5 * (float)YSCREEN;
	return (result);
}

float	**ft_make_matrix_5_5(void)
{
	float	**matrix;
	int		i;
	int		j;

	i = 0;
	matrix = (float**)malloc(sizeof(float*) * 5);
	while(i < 5)
	{
		matrix[i] = (float*)malloc(sizeof(float) * 5);
		i++;
	}
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (matrix);
}

void	ft_set_raster_trans(float x, float y, float z, t_myraster *raster)
{
	raster->mat_trans[0][0] = 1.0;
	raster->mat_trans[1][1] = 1.0;
	raster->mat_trans[2][2] = 1.0;
	raster->mat_trans[3][0] = x;
	raster->mat_trans[3][1] = y;
	raster->mat_trans[3][2] = z;
	raster->mat_trans[3][3] = 1.0;
}

void	ft_set_raster_rot_x(float theta, t_myraster *raster)
{
	raster->mat_rot_x[0][0] = 1.0;
	raster->mat_rot_x[1][1] = cosf(ft_rad(theta));
	raster->mat_rot_x[1][2] = sinf(ft_rad(theta));
	raster->mat_rot_x[2][1] = -sinf(ft_rad(theta));
	raster->mat_rot_x[2][2] = cosf(ft_rad(theta));
	raster->mat_rot_x[3][3] = 1.0;
}

void	ft_set_raster_rot_y(float theta, t_myraster *raster)
{
	raster->mat_rot_y[0][0] = cosf(ft_rad(theta));
	raster->mat_rot_y[0][2] = sinf(ft_rad(theta));
	raster->mat_rot_y[1][1] = 1.0;
	raster->mat_rot_y[2][0] = -sinf(ft_rad(theta));
	raster->mat_rot_y[2][2] = cosf(ft_rad(theta));
	raster->mat_rot_y[3][3] = 1.0;
}

void	ft_set_raster_rot_z(float theta, t_myraster *raster)
{
	raster->mat_rot_z[0][0] = cosf(ft_rad(theta));
	raster->mat_rot_z[0][1] = sinf(ft_rad(theta));
	raster->mat_rot_z[1][0] = -sinf(ft_rad(theta));
	raster->mat_rot_z[1][1] = cosf(ft_rad(theta));
	raster->mat_rot_z[2][2] = 1.0;
	raster->mat_rot_z[3][3] = 1.0;
}

void	ft_set_pro(t_myraster *raster)
{
	float	height;
	float	width;
	float	fov;
	float	z_far;
	float	z_near;
	float	screen_ratio;
	float	fov_rad;

	height = YSCREEN;
	width = XSCREEN;
	fov = 90.0;
	z_far = 1000.0;
	z_near = 0.1;
	screen_ratio = height / width;
	fov_rad = 1.0 / tanf(ft_rad(fov / 2));

	raster->mat_proje[0][0] = screen_ratio / fov_rad;
	raster->mat_proje[1][1] = fov_rad;
	raster->mat_proje[2][2] = z_far / (z_far - z_near);
	raster->mat_proje[3][2] = (-z_far * z_near)  / (z_far - z_near)  ;
	raster->mat_proje[3][3] = 0.0;
	raster->mat_proje[2][3] = 1.0;
}

float	**ft_matrix_multiply_matrix(float **m1, float **m2)  //surement DONE
{
	float	**mat_multiply;

	mat_multiply = ft_make_matrix_5_5();
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			mat_multiply[r][c] = m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c] + m1[r][2] * m2[2][c] + m1[r][3] * m2[3][c];
	return (mat_multiply);
}

/* mat4x4 Matrix_MakeIdentity() */
/* { */
/* 	mat4x4 matrix; */
/* 	matrix.m[0][0] = 1.0f; */
/* 	matrix.m[1][1] = 1.0f; */
/* 	matrix.m[2][2] = 1.0f; */
/* 	matrix.m[3][3] = 1.0f; */
/* 	return matrix; */
/* } */

