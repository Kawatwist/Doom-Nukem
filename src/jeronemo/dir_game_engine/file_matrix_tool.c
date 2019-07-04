/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_matrix_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:17:48 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/04 13:45:05 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>

float	**compute_projection_matrix(t_camera *p_cam) //calcul de la matrice de projection
{
	float	**result;
	float		n;
	float		r;
	float		f;
	float		t;

	result = ft_make_matrix_5_5();
	n = p_cam->near;
	r = 1.0 / (tan(ft_rad(p_cam->fov / 2.0)));
	f = p_cam->far;
	t = 1.0 / (tan(ft_rad(p_cam->fov / 2.0))) / (4.0 / 3.0); // changer le (4/3) en (16/9) va changer le ratio de l'ecran, changeant l'apparence des cubes a l'ecran
	result[0][0] = t;
	result[1][1] = r;
	result[2][2] = -(f) / (f - n);
	result[2][3] = -1.0;
	result[3][2] = -(2.0 * f * n) / (f - n);
	return (result);
}

float	**t_camera_compute_view(t_camera *cam) //calcul de la matrice de vue
{
	float	**result;
	t_myvec	inv_forward;

	result = ft_make_matrix_5_5();
	inv_forward = ft_vector_multiply_vector(cam->forward, ft_create_vector(-1, -1, -1));

	result[0][0] = cam->right.x;
	result[1][0] = cam->right.y;
	result[2][0] = cam->right.z;
	result[3][0] = - (ft_dot_product(cam->right, cam->pos));

	result[0][1] = cam->up.x;
	result[1][1] = cam->up.y;
	result[2][1] = cam->up.z;
	result[3][1] = - (ft_dot_product(cam->up, cam->pos));

	result[0][2] = inv_forward.x;
	result[1][2] = inv_forward.y;
	result[2][2] = inv_forward.z;
	result[3][2] = - (ft_dot_product(inv_forward, cam->pos));
	return (result);
}

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

float	**ft_make_identity(void)
{
	float	**mat_identity;

	mat_identity = ft_make_matrix_5_5();
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

float	**ft_make_rotation_y(float theta)  //DONE
{
	float	**mat_rotation;

	mat_rotation = ft_make_matrix_5_5();
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
	return (mat_rotation);
}

float	**ft_matrix_point_at(t_myvec v_pos, t_myvec v_target, t_myvec v_up)
{
	t_myvec		new_forward;
	t_myvec		new_up;
	t_myvec		new_right;
	float		**matrix;

	matrix = ft_make_matrix_5_5();
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

float  **ft_matrix_quick_inverse(float **mu)
{
	float **matrix;

	matrix = ft_make_matrix_5_5();
	matrix[0][0] = mu[0][0];matrix[0][1] = mu[1][0];matrix[0][2] = mu[2][0];matrix[0][3] = 0.0f;
	matrix[1][0] = mu[0][1];matrix[1][1] = mu[1][1];matrix[1][2] = mu[2][1];matrix[1][3] = 0.0f;
	matrix[2][0] = mu[0][2];matrix[2][1] = mu[1][2];matrix[2][2] = mu[2][2];matrix[2][3] = 0.0f;

	matrix[3][0] = -(mu[3][0] * matrix[0][0] + mu[3][1] * matrix[1][0] + mu[3][2] * matrix[2][0]);
	matrix[3][1] = -(mu[3][0] * matrix[0][1] + mu[3][1] * matrix[1][1] + mu[3][2] * matrix[2][1]);
	matrix[3][2] = -(mu[3][0] * matrix[0][2] + mu[3][1] * matrix[1][2] + mu[3][2] * matrix[2][2]);
	matrix[3][3] = 1.0f;
	return (matrix);
}
