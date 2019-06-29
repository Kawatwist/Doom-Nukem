/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vertex_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:51:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/29 18:43:56 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_calcul_rotation_scale_translation(t_mychange *change)
{
	change->result_1 = ft_rotation_x(change->angle_x, change->result_1);
	change->result_2 = ft_rotation_x(change->angle_x, change->result_2);
	if (change->display->triangle == 1)
		change->result_3 = ft_rotation_x(change->angle_x, change->result_3);

	change->result_1 = ft_rotation_y(change->angle_y, change->result_1);
	change->result_2 = ft_rotation_y(change->angle_y, change->result_2);
 	if (change->display->triangle == 1)
		change->result_3 = ft_rotation_y(change->angle_y, change->result_3);
	change->result_1 = ft_rotation_z(change->angle_z, change->result_1);
	change->result_2 = ft_rotation_z(change->angle_z, change->result_2);
	if (change->display->triangle == 1)
		change->result_3 = ft_rotation_z(change->angle_z, change->result_3);

	change->result_1 = ft_scale(change->zoom, change->result_1);
	change->result_2 = ft_scale(change->zoom, change->result_2);
	if (change->display->triangle == 1)
		change->result_3 = ft_scale(change->zoom, change->result_3);

	change->result_1 = ft_translation_x(change->translation_x, change->result_1);
	change->result_2 = ft_translation_x(change->translation_x, change->result_2);
	if (change->display->triangle == 1)
		change->result_3 = ft_translation_x(change->translation_x, change->result_3);

	change->result_1 = ft_translation_y(change->translation_y, change->result_1);
	change->result_2 = ft_translation_y(change->translation_y, change->result_2);
	if (change->display->triangle == 1)
		change->result_3 = ft_translation_y(change->translation_y, change->result_3);

	change->result_1 = ft_translation_z(change->translation_z, change->result_1);
	change->result_2 = ft_translation_z(change->translation_z, change->result_2);
	if (change->display->triangle == 1)
		change->result_3 = ft_translation_z(change->translation_z, change->result_3);
}

t_myvec		ft_scale_screen(t_myvec result)
{
	result.x += 1.0;
	result.y += 1.0;

	result.x *= 0.5 * (float)XSCREEN / 2;
	result.y *= 0.5 * (float)YSCREEN / 2;
	return (result);
}

void	ft_calcul_projection(t_mychange *change)
{
	if (change->display->projection == orthographique)
		;
	else if (change->display->projection == perspective)
	{
		/* change->result_1 = ft_perspective_projection(change->result_1, change); */
		/* change->result_2 = ft_perspective_projection(change->result_2, change); */
		if (change->display->triangle == 1)
		{
			/* change->result_3 = ft_perspective_projection(change->result_3, change); */

			if (change->display->shade == 1)
			{
				t_myvec		light_direction;
				float		shade; //variable light from 0 to 1;
				t_myvec		triangle_normal;
				t_myvec		triangle_normal_normalise;
				light_direction.x = 0.5;
				light_direction.y = 0.5;
				light_direction.z = 1.0;

				printf("\n");
				printf("\n");
				printf("\n");
				printf("the triangle first point x=%f\n", change->result_1.x);
				printf("the triangle first point y=%f\n", change->result_1.y);
				printf("the triangle first point z=%f\n", change->result_1.z);

				printf("the triangle seconde point x=%f\n", change->result_2.x);
				printf("the triangle seconde point y=%f\n", change->result_2.y);
				printf("the triangle seconde point z=%f\n", change->result_2.z);


				printf("the triangle third point x=%f\n", change->result_3.x);
				printf("the triangle third point y=%f\n", change->result_3.y);
				printf("the triangle third point z=%f\n", change->result_3.z);
				printf("\n");

				triangle_normal = ft_calculate_normal_of_points(change->result_1, change->result_2, change->result_3);
				printf("the triangle normal x=%f\n", triangle_normal.x);
				printf("the triangle normal y=%f\n", triangle_normal.y);
				printf("the triangle normal z=%f\n", triangle_normal.z);
				triangle_normal_normalise = ft_normalise(triangle_normal);
				printf("the triangle normal normalise x=%f\n", triangle_normal_normalise.x);
				printf("the triangle normal normalise y=%f\n", triangle_normal_normalise.y);
				printf("the triangle normal normalise z=%f\n", triangle_normal_normalise.z);
				light_direction = ft_normalise(light_direction);
				printf("the light direction normalise x=%f\n", light_direction.x);
				printf("the light direction normalise y=%f\n", light_direction.y);
				printf("the light direction normalise z=%f\n", light_direction.z);
				shade = ft_dot_product(triangle_normal_normalise, light_direction);


				/* 	change->result_1.shade = shade * 255; */
				/* 	change->result_2.shade = shade * 255; */
				/* 	change->result_3.shade = shade * 255; */
				/* printf("A SHADE = %f\n", shade * 255); */
				/* } */
				/* else */
				/* 	; */
		}
		change->result_1 = ft_scale_screen(change->result_1);
		change->result_2 = ft_scale_screen(change->result_2);
		change->result_3 = ft_scale_screen(change->result_3);
	}
}
}

int		ft_calcul_culing(t_mychange *change, t_mytriangle *triangle)
{ float			l;
	t_myvec			normal;
	t_myvec			camera;

	;
	camera.x = change->v_camera.x;
	camera.y = change->v_camera.y;
	camera.z = change->v_camera.z;
	camera.x = 0;
	camera.y = 0;
	camera.z = 0;
	normal = ft_calculate_normal_of_points(triangle->vertice[0], triangle->vertice[1], triangle->vertice[2]);
	//normalisation
	l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z*normal.z);
	normal.x /= l;
	normal.y /= l;
	normal.z /= l;
	if ((normal.x * (triangle->vertice[0].x - camera.x) +
				normal.y * (triangle->vertice[0].y - camera.y) +
				normal.z * (triangle->vertice[0].z - camera.z)) < 0.0)
		return (0);
	else
		return (1);
}

void	ft_draw_mesh(t_mywin *s_win, t_mychange *change)
{
	/* t_myputtheline		s_line;; */
	t_mycolor			color;

	color = ft_setcolor(RED);
	SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], color.rrr, color.ggg, color.bbb, 255);

	if (change->display->culling_face == 1)
	{

		{
			/* printf("helo\n"); */
			if (change->display->color == 1)
			{
				ft_order_triangle_vertice(&(change->result_1), &(change->result_2), &(change->result_3));
				/* printf("hola bb\n"); */
				if (change->display->shade == 1)
				{
					/* //on fait la lumiere par triangle */
					/* //the easiest light to perform but doesnt exist in real world */
					/* t_myvec		light_direction; */
					float		shade = 0; //variable light from 0 to 1;
					/* t_myvec		triangle_normal; */
					/* t_myvec		triangle_normal_normalise; */
					/* light_direction.x = 0.0; */
					/* light_direction.y = 0.0; */
					/* light_direction.z = -1.0; */


					printf("bb\n");
					printf("the triangle first point x=%f\n", change->result_1.x);
					printf("the triangle first point y=%f\n", change->result_1.y);
					printf("the triangle first point z=%f\n", change->result_1.z);

					printf("\n");


					printf("the triangle seconde point x=%f\n", change->result_2.x);
					printf("the triangle seconde point y=%f\n", change->result_2.y);
					printf("the triangle seconde point z=%f\n", change->result_2.z);

					printf("\n");

					printf("the triangle third point x=%f\n", change->result_3.x);
					printf("the triangle third point y=%f\n", change->result_3.y);
					printf("the triangle third point z=%f\n", change->result_3.z);

					exit(0);


					/* printf("\n"); */
					/* triangle_normal = ft_calculate_normal_of_points(change->result_1, change->result_2, change->result_3); */
					/* /1* printf("the triangle normal x=%f\n", triangle_normal.x); *1/ */
					/* /1* printf("the triangle normal y=%f\n", triangle_normal.y); *1/ */
					/* /1* printf("the triangle normal z=%f\n", triangle_normal.z); *1/ */

					/* triangle_normal_normalise = ft_normalise(triangle_normal); */
					/* printf("the triangle normal normalise x=%f\n", triangle_normal_normalise.x); */
					/* printf("the triangle normal normalise y=%f\n", triangle_normal_normalise.y); */
					/* printf("the triangle normal normalise z=%f\n", triangle_normal_normalise.z); */

					/* light_direction = ft_normalise(light_direction); */
					/* /1* printf("the light direction normalise x=%f\n", light_direction.x); *1/ */
					/* /1* printf("the light direction normalise y=%f\n", light_direction.y); *1/ */
					/* /1* printf("the light direction normalise z=%f\n", light_direction.z); *1/ */

					/* shade = ft_dot_product(triangle_normal_normalise, light_direction); */
					/* printf("the dot product result shade x=%f\n\n\n\n", shade); */

					ft_fill_triangle_shade(&(change->result_1), &(change->result_2), &(change->result_3), s_win, shade);

				}
				else
				{
					ft_fill_triangle_one_color(&(change->result_1), &(change->result_2), &(change->result_3), s_win);
				}
			}
			ft_draw_triangle_base(&(change->result_1), &(change->result_2), &(change->result_3), s_win);
		}
	}
	else
	{
		/* printf("helo\n"); */
		if (change->display->color == 1)
		{
			/* printf("hola bb\n"); */
			ft_order_triangle_vertice(&(change->result_1), &(change->result_2), &(change->result_3));
			ft_fill_triangle_one_color(&(change->result_1), &(change->result_2), &(change->result_3), s_win);
		}
		color = ft_setcolor(PINK);
		SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], color.rrr, color.ggg, color.bbb, 255);
		ft_draw_triangle_base(&(change->result_1), &(change->result_2), &(change->result_3), s_win);
	}
}




void	ft_draw_change(t_mywin *s_win, t_mychange *change)
{
	//INIT mat_rot_z  and   mat_rot_x  and mat_trans
	change->mat_rot_z = ft_make_rotation_z(change->theta * 0.5);
	change->mat_rot_x = ft_make_rotation_x(change->theta);
	change->mat_trans = ft_make_translation(0.0, 0.0, 10.0);

	//CALCULATE mat_world
	change->mat_world = ft_make_identity();
	change->mat_world = ft_matrix_multiply_matrix(change->mat_rot_z, change->mat_rot_x);
	change->mat_world = ft_matrix_multiply_matrix(change->mat_world, change->mat_trans);

	//init v_up  DONE
	change->v_up.x = 0;
	change->v_up.y = 1;
	change->v_up.z = 0;
	//init v_target
	change->v_target.x = 0;
	change->v_target.y = 0;
	change->v_target.z = 1;

	float	f_y_aw = 0.0;
	change->mat_camera_rot = ft_make_matrix_5_5();
	change->mat_camera_rot = ft_make_rotation_y(f_y_aw);
	change->v_look_dir = ft_matrix_multiply_vector(change->mat_camera_rot, change->v_target);
	//CALUCLATE v_target
	change->v_target = ft_vector_add(change->v_camera, change->v_look_dir);

	//CALCULATE mat_camera
	change->mat_camera = ft_matrix_point_at(change->v_camera, change->v_target, change->v_up);

	//CALCULATE mat_view (inverse de la matrice mat camera)
	change->mat_view = ft_matrix_quick_inverse(change->mat_camera);

	/* change->result_1 = ft_matrix_multiply_vector(change->mat_world, change->result_1); */
	/* change->result_2 = ft_matrix_multiply_vector(change->mat_world, change->result_2); */
	/* change->result_3 = ft_matrix_multiply_vector(change->mat_world, change->result_3); */

	/* change->result_1 = ft_matrix_multiply_vector(change->mat_view, change->result_1); */
	/* change->result_2 = ft_matrix_multiply_vector(change->mat_view, change->result_2); */
	/* change->result_3 = ft_matrix_multiply_vector(change->mat_view, change->result_3); */

	/* ft_calcul_rotation_scale_translation(change); */
	change->result_1 = ft_perspective_projection(change->result_1);
	change->result_2 = ft_perspective_projection(change->result_2);
	change->result_3 = ft_perspective_projection(change->result_3);
	ft_calcul_projection(change);

	/* if (change->display->triangle)		//afichage des triangles */
	/* 	ft_draw_triangle(s_win, change); */
	if (change->display->mesh)			//afichage des mesh
		ft_draw_mesh(s_win, change);
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


	/* matrix[1][1] = 1.0 / tan(ft_rad(teta / 2.0) ); */


	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[1][4] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0/ tan(ft_rad(teta) / 2.0);


	/* matrix[2][2] = 1.0/ tan(ft_rad(teta / 2.0)); */


	matrix[2][3] = 0.0;
	matrix[2][4] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = z_far / (z_far - z_near);



	/* matrix[3][3] = -z_far / (z_far - z_near); */
	matrix[3][4] = 1.0;
	/* matrix[3][4] = -1.0; */
	matrix[4][1] = 0.0;
	matrix[4][2] = 0.0;
	matrix[4][3] = (-z_far * z_near)  / (z_far - z_near)  ;
	/* matrix[4][3] = (-2 * z_far * z_near)  / (z_far - z_near)  ; */
	matrix[4][4] = 0.0;
	result = ft_matrix_multiply_four(matrix, vertex);

	//scale
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

