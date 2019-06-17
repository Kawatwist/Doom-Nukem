/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vector_calcul.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:17:24 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/17 13:19:55 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

t_myvec		ft_vector_add(t_myvec v1, t_myvec v2) //DONE
{
	t_myvec result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_myvec		ft_vector_sub(t_myvec v1, t_myvec v2) //DONE
{
	t_myvec result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}

t_myvec		ft_vector_multiply(t_myvec m, float k)
{
	t_myvec		result;

	result.x = m.x * k;
	result.y = m.y * k;
	result.z = m.z * k;
	return (result);
}

float	*ft_make_projection(void)   //DONE
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

float	*ft_matrix_multiply_matrix(float *m1, float *m2)  //surement DONE
{
	float	mat_multiply[5][5];
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			mat_multiply[r][c] = m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c] + m1[r][2] * m2[2][c] + m1[r][3] * m2[3][c];
	return (mat_multiply);
}

float	ft_matrix_point_at(t_myvec v_pos, t_myvec v_target, t_myvec v_up)
{
	t_myvec		new_forward;
	t_myvec		new_up;
	t_myvec		new_right;
	float		matrix[5][5];

	//CALCULATE NEW FORWARD VECTOR
	new_forward = ft_vector_sub(v_target, v_pos);
	new_forward = ft_normalise(new_forward);

	//CALCULATE NEW UP DIRECTION
	t_myvec  a  = ft_vector_multiply(new_forward, ft_dot_product(v_up, new_forward));
	new_up = ft_vector_sub(v_up, a);
	new_up = ft_normalise(new_up);

	//CALCULATE DIRECTION, EASY ITS JUST A CROSS PRODUCT
	new_right = ft_cross_product(new_up, new_forward);

	//CONSTRUCT DIMENSIONING AND TRANSLATION MATRIX
	matrix[0][0] = new_right.x;		matrix[0][1] = new_right.y;		matrix[0][2] = new_right.x;		matrix[0][3] = 0.0;
	matrix[1][0] = new_up.x;		matrix[1][1] = new_up.y;		matrix[1][2] = new_up.z;		matrix[1][3] = 0.0;
	matrix[2][0] = new_forward.x;	matrix[2][1] = new_forward.y;	matrix[2][2] = new_forward.z;   matrix[2][3] = 0.0;
	matrix[3][0] = v_pos.x;			matrix[3][1] = v_pos.y;			matrix[3][2] = v_pos.z;			matrix[3][3] = 1.1;
    return (matrix);
}

float  *ft_matrix_quick_inverse(float mu)
{
	flaot matrix[5][5];

	matrix[0][0] = mu[0][0];matrix[0][1] = mu[1][0];matrix[0][2] = mu[2][0];matrix[0][3] = 0.0f;
	matrix[1][0] = mu[0][1];matrix[1][1] = mu[1][1];matrix[1][2] = mu[2][1];matrix[1][3] = 0.0f;
	matrix[2][0] = mu[0][2];matrix[2][1] = mu[1][2];matrix[2][2] = mu[2][2];matrix[2][3] = 0.0f;

	matrix[3][0] = -(mu[3][0] * matrix[0][0] + mu[3][1] * matrix[1][0] + mu[3][2] * matrix[2][0]);
	matrix[3][1] = -(mu[3][0] * matrix[0][1] + mu[3][1] * matrix[1][1] + mu[3][2] * matrix[2][1]);
	matrix[3][2] = -(mu[3][0] * matrix[0][2] + mu[3][1] * matrix[1][2] + mu[3][2] * matrix[2][2]);
	matrix[3][3] = 1.0f;
	return (matrix);
}

float	*ft_make_identity(void)  //DONE
{
	float	mat_identity[5][5];

	mat_identity[0][0] = 1.0;
	mat_identity[0][1] = 0.0;
	mat_identity[0][2] = 0.0;
	mat_identity[0][3] = 0.0;
	mat_identity[1][0] = 0.0;
	mat_identity[1][1] = 1.0;
	mat_identity[1][2] = 0.0;
	mat_identity[1][3] = 0.0;
	mat_identity[2][0] = 0.0;
	mat_identity[2][1] = 0.0;
	mat_identity[2][2] = 1.0;
	mat_identity[2][3] = 0.0;
	mat_identity[3][0] = 0.0;
	mat_identity[3][1] = 0.0;
	mat_identity[3][2] = 0.0;
	mat_identity[3][3] = 1.0;
	return (mat_identity);
}

float	*ft_make_rotation_x(float theta)  //DONE
{
	float	mat_rotation[5][5];

	mat_rotation[0][0] = 1.0;
	mat_rotation[0][1] = 0.0;
	mat_rotation[0][2] = 0.0;
	mat_rotation[0][3] = 0.0;
	mat_rotation[1][0] = 0.0;
	mat_rotation[1][1] = cosf(ft_rad(theta));
	mat_rotation[1][2] = sinf(ft_rad(theta));
	mat_rotation[1][3] = 0.0;
	mat_rotation[2][0] = 0.0;
	mat_rotation[2][1] = -sinf(ft_rad(theta));
	mat_rotation[2][2] = cosf(ft_rad(theta));
	mat_rotation[2][3] = 0.0;
	mat_rotation[3][0] = 0.0;
	mat_rotation[3][1] = 0.0;
	mat_rotation[3][2] = 0.0;
	mat_rotation[3][3] = 1.0;
	return (mat_ratation);
}

float	*ft_make_rotation_y(float theta)  //DONE
{
	float	mat_rotation[5][5];

	mat_rotation[0][0] = cosf(ft_rad(theta));
	mat_rotation[0][1] = 0.0;
	mat_rotation[0][2] = sinf(ft_rad(theta));
	mat_rotation[0][3] = 0.0;
	mat_rotation[1][0] = 0.0;
	mat_rotation[1][1] = 1.0;
	mat_rotation[1][2] = 0.0;
	mat_rotation[1][3] = 0.0;
	mat_rotation[2][0] = -sinf(ft_rad(theta));
	mat_rotation[2][1] = 0.0;
	mat_rotation[2][2] = cosf(ft_rad(theta));
	mat_rotation[2][3] = 0.0;
	mat_rotation[3][0] = 0.0;
	mat_rotation[3][1] = 0.0;
	mat_rotation[3][2] = 0.0;
	mat_rotation[3][3] = 1.0;
	return (mat_ratation);
}

float	*ft_make_rotation_z(float theta) //DONE
{
	float	mat_rotation[5][5];

	mat_rotation[0][0] = cosf(ft_rad(theta));
	mat_rotation[0][1] = sinf(ft_rad(theta));
	mat_rotation[0][2] = 0.0;
	mat_rotation[0][3] = 0.0;
	mat_rotation[1][0] = -sinf(ft_rad(theta));
	mat_rotation[1][1] = cosf(ft_rad(theta));
	mat_rotation[1][2] = 0.0;
	mat_rotation[1][3] = 0.0;
	mat_rotation[2][0] = 0.0;
	mat_rotation[2][1] = 0.0;
	mat_rotation[2][2] = 1.0;
	mat_rotation[2][3] = 0.0;
	mat_rotation[3][0] = 0.0;
	mat_rotation[3][1] = 0.0;
	mat_rotation[3][2] = 0.0;
	mat_rotation[3][3] = 1.0;
	return (mat_ratation);
}
