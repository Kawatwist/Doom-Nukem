/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_matrix_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:17:48 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/29 16:05:58 by jchardin         ###   ########.fr       */
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

t_myvec		 ft_matrix_multiply_vector(float **m, t_myvec i)
{
	t_myvec v;
	float w;

	v.x = i.x * m[0][0] + i.y * m[1][0] + i.z * m[2][0] + i.w * m[3][0];
	v.y = i.x * m[0][1] + i.y * m[1][1] + i.z * m[2][1] + i.w * m[3][1];
	v.z = i.x * m[0][2] + i.y * m[1][2] + i.z * m[2][2] + i.w * m[3][2];

	w = i.x * m[0][3] + i.y * m[1][3] + i.z * m[2][3] + m[3][3];
	if (w != 0.0)
	{
		v.x /= w;
		v.y /= w;
		v.z /= w;
	}
	return v;
}
