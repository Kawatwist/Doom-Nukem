/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vector_calcul.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:17:24 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/16 15:57:22 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

t_myvec		ft_vector_add(t_myvec v1, t_myvec v2)
{
	t_myvec result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_myvec		ft_vector_sub(t_myvec v1, t_myvec v2)
{
	t_myvec result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}

float	*ft_make_projection()
{
	float		mat_projection[5][5];
	t_myvec		result;

	float	height;
	float	width;
	float	teta;
	float	z_far;
	float	z_near;
	(void)change;

	height = YSCREEN;
	width = XSCREEN;
	teta = 90.0;
	z_far = 1000.0;
	z_near = 0.1;

	mat_projection[1][1] = (height / width) * (1.0 / (tan(ft_rad(teta) / 2.0)));
	mat_projection[1][2] = 0.0;
	mat_projection[1][3] = 0.0;
	mat_projection[1][4] = 0.0;
	mat_projection[2][1] = 0.0;
	mat_projection[2][2] = 1.0/ tan(ft_rad(teta) / 2.0);
	mat_projection[2][3] = 0.0;
	mat_projection[2][4] = 0.0;
	mat_projection[3][1] = 0.0;
	mat_projection[3][2] = 0.0;
	mat_projection[3][3] = z_far / (z_far - z_near);
	mat_projection[3][4] = 1.0;
	mat_projection[4][1] = 0.0;
	mat_projection[4][2] = 0.0;
	mat_projection[4][3] = (-z_far * z_near)  / (z_far - z_near)  ;
	mat_projection[4][4] = 0.0;
	return(mat_projection);
}

float	*ft_matrix_multiply_matrix(float *m1, float *m2)
{
	float	mat_multiply[5][5];
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			mat_multiply[r][c] = m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c] + m1[r][2] * m2[2][c] + m1[r][3] * m2[3][c];
	return (mat_multiply);
}

ft_matrix_point_at()
{

}

ft_invert_matrix_point_at()
{

}

float	*ft_make_identity()
{
	float	mat_identity[5][5];

	mat_identity[0][0] = 0.0;
	mat_identity[0][1] = 0.0;
	mat_identity[0][2] = 0.0;
	mat_identity[0][3] = 0.0;
	mat_identity[1][0] = 0.0;
	mat_identity[1][1] = 0.0;
	mat_identity[1][2] = 0.0;
	mat_identity[1][3] = 0.0;
	mat_identity[2][0] = 0.0;
	mat_identity[2][1] = 0.0;
	mat_identity[2][2] = 0.0;
	mat_identity[2][3] = 0.0;
	mat_identity[3][0] = 0.0;
	mat_identity[3][1] = 0.0;
	mat_identity[3][2] = 0.0;
	mat_identity[3][3] = 0.0;
	return (mat_identity);
}

float	*ft_make_rotation_x(float theta)
{
	float	mat_rotation[5][5];

	mat_rotation[0][0] = 0.0;
	mat_rotation[0][1] = 0.0;
	mat_rotation[0][2] = 0.0;
	mat_rotation[0][3] = 0.0;
	mat_rotation[1][0] = 0.0;
	mat_rotation[1][1] = 0.0;
	mat_rotation[1][2] = 0.0;
	mat_rotation[1][3] = 0.0;
	mat_rotation[2][0] = 0.0;
	mat_rotation[2][1] = 0.0;
	mat_rotation[2][2] = 0.0;
	mat_rotation[2][3] = 0.0;
	mat_rotation[3][0] = 0.0;
	mat_rotation[3][1] = 0.0;
	mat_rotation[3][2] = 0.0;
	mat_rotation[3][3] = 0.0;
	return (mat_ratation);
}

float	*ft_make_rotation_y(float theta)
{
	float	mat_rotation[5][5];

	mat_rotation[0][0] = 0.0;
	mat_rotation[0][1] = 0.0;
	mat_rotation[0][2] = 0.0;
	mat_rotation[0][3] = 0.0;
	mat_rotation[1][0] = 0.0;
	mat_rotation[1][1] = 0.0;
	mat_rotation[1][2] = 0.0;
	mat_rotation[1][3] = 0.0;
	mat_rotation[2][0] = 0.0;
	mat_rotation[2][1] = 0.0;
	mat_rotation[2][2] = 0.0;
	mat_rotation[2][3] = 0.0;
	mat_rotation[3][0] = 0.0;
	mat_rotation[3][1] = 0.0;
	mat_rotation[3][2] = 0.0;
	mat_rotation[3][3] = 0.0;
	return (mat_ratation);
}

float	*ft_make_rotation_z(float theta)
{
	float	mat_rotation[5][5];

	mat_rotation[0][0] = 0.0;
	mat_rotation[0][1] = 0.0;
	mat_rotation[0][2] = 0.0;
	mat_rotation[0][3] = 0.0;
	mat_rotation[1][0] = 0.0;
	mat_rotation[1][1] = 0.0;
	mat_rotation[1][2] = 0.0;
	mat_rotation[1][3] = 0.0;
	mat_rotation[2][0] = 0.0;
	mat_rotation[2][1] = 0.0;
	mat_rotation[2][2] = 0.0;
	mat_rotation[2][3] = 0.0;
	mat_rotation[3][0] = 0.0;
	mat_rotation[3][1] = 0.0;
	mat_rotation[3][2] = 0.0;
	mat_rotation[3][3] = 0.0;
	return (mat_ratation);
}
