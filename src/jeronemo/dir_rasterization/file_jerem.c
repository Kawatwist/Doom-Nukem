/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_jerem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:52:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/24 21:06:13 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <jeronemo.h>

t_matrix	create_t_matrix()
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (j != i)
				result.value[i][j] = 0.0f;
			else
				result.value[i][j] = 1.0f;
			j++;
		}
		i++;
	}

	return (result);
}

float			dot_t_vector3(t_vector3 a, t_vector3 b) //Produit scalaire / dot product
{
	float		result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

t_vector3 create_t_vector3(float p_x, float p_y, float p_z)
{
	t_vector3 result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;

	return (result);
}

t_vector3		cross_t_vector3(t_vector3 a, t_vector3 b) //Produit vectoriel / cross product
{
	t_vector3	result;

	result = create_t_vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
								a.x * b.y - a.y * b.x);
	return (result);
}

t_vector3	mult_vector3_by_vector3(t_vector3 a,t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x * b.x, a.y * b.y, a.z * b.z);

	return (result);
}

t_vector3 mult_vector3_by_matrix(t_vector3 vertex, t_matrix m)
{
	float		result[3];

	result[0] = m.value[0][0] * vertex.x + m.value[1][0] * vertex.y + m.value[2][0] * vertex.z + m.value[3][0];

	result[1] = m.value[0][1] * vertex.x + m.value[1][1] * vertex.y + m.value[2][1] * vertex.z + m.value[3][1];

	result[2] = m.value[0][2] * vertex.x + m.value[1][2] * vertex.y + m.value[2][2] * vertex.z + m.value[3][2];

	return (create_t_vector3(result[0], result[1], result[2]));
}


float			degree_to_radius(float angle)
{
	return ((float)(((float)angle) * M_PI / (float)180));
}

t_vector3	inv_t_vector3(t_vector3 src)
{
	t_vector3	result;

	result.x = -1 * src.x;
	result.y = -1 * src.y;
	result.z = -1 * src.z;

	return (result);
}

t_vector3		normalize_t_vector3(t_vector3 v) // ramene la longueur du vecteur a 1
{
	float		length_of_v;

	length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (create_t_vector3(v.x / length_of_v, v.y
							/ length_of_v, v.z / length_of_v));
}



void		t_camera_look_at(t_camera *cam) // calcul de l'angle de vue de la camera (forward, right, up)
{
	t_vector3 zaxis = normalize_t_vector3(create_t_vector3(cos(degree_to_radius(cam->pitch)) * sin(degree_to_radius(cam->yaw)),
						sin(degree_to_radius(cam->pitch)),
						cos(degree_to_radius(cam->pitch)) * cos(degree_to_radius(cam->yaw))));


	t_vector3 xaxis = normalize_t_vector3(create_t_vector3(sin(degree_to_radius(cam->yaw) - 3.14f / 2.0f),
						0,
						cos(degree_to_radius(cam->yaw) - 3.14f / 2.0f)));
	t_vector3 yaxis = normalize_t_vector3(cross_t_vector3(xaxis, zaxis));

	cam->forward = zaxis;
	cam->right = xaxis;
	cam->up = inv_t_vector3(yaxis);
}

void		t_camera_change_view(t_camera *cam, float delta_pitch, float delta_yaw)
{
	(void)delta_pitch;
	cam->pitch = 0;
	cam->yaw += delta_yaw;
	t_camera_look_at(cam);
}


void		handle_t_camera_view_by_mouse(t_camera *cam) // calcul du mouvement de l'angle de la camera a la souris
{
	float delta_pitch;
	float delta_yaw;


	delta_pitch = 0;
	delta_yaw = 0;
	t_camera_change_view(cam, delta_yaw, delta_pitch);
}


void		t_engine_handle_camera(t_engine *p_engine)
{
	t_user_engine_handle_camera(p_engine->user_engine, p_engine->cam);
}


void			t_user_engine_handle_camera(t_user_engine *user_engine, t_camera *cam)
{

	(void)user_engine;


	handle_t_camera_view_by_mouse(cam); // calcul du mouvement de l'angle de la camera a la souris

	//handle_t_camera_mouvement_by_key(cam, keyboard); // deplacement cameras

	compute_t_camera(cam);
}

t_vector3	apply_t_camera(t_vector3 *src, t_matrix *mat) // applique la position de la camera
{
	t_vector3	result; // x -> coord a l'ecran en x de ce point / y -> coord a l'ecran en y de ce point / z -> distance reelle entre ce point et l'oeil de la camera
	float		delta;

	result.x = src->x * mat->value[0][0] + src->y * mat->value[1][0] + src->z * mat->value[2][0] + mat->value[3][0];
	result.y = src->x * mat->value[0][1] + src->y * mat->value[1][1] + src->z * mat->value[2][1] + mat->value[3][1];
	result.z = src->x * mat->value[0][2] + src->y * mat->value[1][2] + src->z * mat->value[2][2] + mat->value[3][2];
	delta = src->x * mat->value[0][3] + src->y * mat->value[1][3] + src->z * mat->value[2][3] + mat->value[3][3];
	if (delta != 0)
	{
		result.x /= delta;
		result.y /= delta;
		result.z /= -delta;
	}
	return (result);
}




t_matrix	create_t_matrix_empty()
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.value[i][j] = 0.0f;
			j++;
		}
		i++;
	}

	return (result);
}

t_matrix	compute_projection_matrix(t_camera *p_cam) //calcul de la matrice de projection
{
	t_matrix	result;
	float		n;
	float		r;
	float		f;
	float		t;




	result = create_t_matrix_empty();
	n = p_cam->near;
	r = 1.0 / (tan(degree_to_radius(p_cam->fov / 2.0)));
	f = p_cam->far;
	t = 1.0 / (tan(degree_to_radius(p_cam->fov / 2.0))) / (4.0 / 3.0); // changer le (4/3) en (16/9) va changer le ratio de l'ecran, changeant l'apparence des cubes a l'ecran
	result.value[0][0] = t;
	result.value[1][1] = r;
	result.value[2][2] = -(f) / (f - n);
	result.value[2][3] = -1.0;
	result.value[3][2] = -(2.0 * f * n) / (f - n);
	return (result);
}

t_matrix	t_camera_compute_view(t_camera *cam) //calcul de la matrice de vue
{
	t_matrix	result;
	t_vector3	inv_forward;

	result = create_t_matrix();

	inv_forward = mult_vector3_by_vector3(cam->forward, create_t_vector3(-1, -1, -1));

	result.value[0][0] = cam->right.x;
	result.value[1][0] = cam->right.y;
	result.value[2][0] = cam->right.z;
	result.value[3][0] = - (dot_t_vector3(cam->right, cam->pos));

	result.value[0][1] = cam->up.x;
	result.value[1][1] = cam->up.y;
	result.value[2][1] = cam->up.z;
	result.value[3][1] = - (dot_t_vector3(cam->up, cam->pos));

	result.value[0][2] = inv_forward.x;
	result.value[1][2] = inv_forward.y;
	result.value[2][2] = inv_forward.z;
	result.value[3][2] = - (dot_t_vector3(inv_forward, cam->pos));

	return (result);
}

void		compute_t_camera(t_camera *cam)
{
	cam->view = t_camera_compute_view(cam);
	cam->projection = compute_projection_matrix(cam);
}






