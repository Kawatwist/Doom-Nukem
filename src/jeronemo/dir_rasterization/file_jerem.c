/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_jerem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:52:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/04 13:42:27 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>


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
