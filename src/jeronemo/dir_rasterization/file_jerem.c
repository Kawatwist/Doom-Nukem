/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_jerem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:52:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/04 13:19:32 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>


float			dot_t_vector3(t_myvec a, t_myvec b) //Produit scalaire / dot product
{
	float		result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}


t_myvec		cross_t_vector3(t_myvec a, t_myvec b) //Produit vectoriel / cross product
{
	t_myvec	result;

	result = ft_create_vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
								a.x * b.y - a.y * b.x);
	return (result);
}

t_myvec	mult_vector3_by_vector3(t_myvec a,t_myvec b)
{
	t_myvec	result;

	result = ft_create_vector(a.x * b.x, a.y * b.y, a.z * b.z);
	return (result);
}

t_myvec mult_vector3_by_matrix(t_myvec vertex, float **m)
{
	float		result[3];

	result[0] = m[0][0] * vertex.x + m[1][0] * vertex.y + m[2][0] * vertex.z + m[3][0];
	result[1] = m[0][1] * vertex.x + m[1][1] * vertex.y + m[2][1] * vertex.z + m[3][1];
	result[2] = m[0][2] * vertex.x + m[1][2] * vertex.y + m[2][2] * vertex.z + m[3][2];
	return (ft_create_vector(result[0], result[1], result[2]));
}

void		t_camera_look_at(t_camera *cam) // calcul de l'angle de vue de la camera (forward, right, up)
{
	t_myvec zaxis = ft_normalise(ft_create_vector(cos(ft_rad(cam->pitch)) * sin(ft_rad(cam->yaw)),
						sin(ft_rad(cam->pitch)),
						cos(ft_rad(cam->pitch)) * cos(ft_rad(cam->yaw))));


	t_myvec xaxis = ft_normalise(ft_create_vector(sin(ft_rad(cam->yaw) - 3.14f / 2.0f),
						0,
						cos(ft_rad(cam->yaw) - 3.14f / 2.0f)));
	t_myvec yaxis = ft_normalise(cross_t_vector3(xaxis, zaxis));

	cam->forward = zaxis;
	cam->right = xaxis;
	cam->up = ft_vector_inverse(yaxis);
}

void		t_camera_change_view(t_camera *cam, float delta_pitch, float delta_yaw)
{
	(void)delta_pitch;
	cam->pitch = 0;
	cam->yaw += delta_yaw;
	t_camera_look_at(cam);
}


t_myvec	apply_t_camera(t_myvec *src, float **mat) // applique la position de la camera
{
	t_myvec	result; // x -> coord a l'ecran en x de ce point / y -> coord a l'ecran en y de ce point / z -> distance reelle entre ce point et l'oeil de la camera
	float		delta;

	result.x = src->x * mat[0][0] + src->y * mat[1][0] + src->z * mat[2][0] + mat[3][0];
	result.y = src->x * mat[0][1] + src->y * mat[1][1] + src->z * mat[2][1] + mat[3][1];
	result.z = src->x * mat[0][2] + src->y * mat[1][2] + src->z * mat[2][2] + mat[3][2];
	delta = src->x * mat[0][3] + src->y * mat[1][3] + src->z * mat[2][3] + mat[3][3];
	if (delta != 0)
	{
		result.x /= delta;
		result.y /= delta;
		result.z /= -delta;
	}
	return (result);
}

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
	inv_forward = mult_vector3_by_vector3(cam->forward, ft_create_vector(-1, -1, -1));

	result[0][0] = cam->right.x;
	result[1][0] = cam->right.y;
	result[2][0] = cam->right.z;
	result[3][0] = - (dot_t_vector3(cam->right, cam->pos));

	result[0][1] = cam->up.x;
	result[1][1] = cam->up.y;
	result[2][1] = cam->up.z;
	result[3][1] = - (dot_t_vector3(cam->up, cam->pos));

	result[0][2] = inv_forward.x;
	result[1][2] = inv_forward.y;
	result[2][2] = inv_forward.z;
	result[3][2] = - (dot_t_vector3(inv_forward, cam->pos));
	return (result);
}

/* void		compute_t_camera(t_camera *cam) */
/* { */
/* 	cam->view = t_camera_compute_view(cam); */
/* 	cam->projection = compute_projection_matrix(cam); */
/* } */






