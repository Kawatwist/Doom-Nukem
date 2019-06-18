/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/18 20:03:55 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_keyboard_event_check(t_win *wn, Uint8 *old, t_mychange *change)
{


	/* change->v_forward = ft_vector_multiply(change->v_look_dir, 2.0); */


	if (wn->state[SDL_SCANCODE_ESCAPE])
		change->quit = TRUE;


	if (wn->state[SDL_SCANCODE_UP] == 1 && old[SDL_SCANCODE_UP] == 0)
	{
		printf("Fleche Haut => on decrement camera y\n");
		change->v_camera.y -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_DOWN] == 1 && old[SDL_SCANCODE_DOWN] == 0)
	{
		printf("Fleche Haut => on increment camera y\n");
		change->v_camera.y += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_LEFT] == 1 && old[SDL_SCANCODE_LEFT] == 0)
	{
		printf("Fleche Gauche => on decrement camera x\n");
		change->v_camera.x -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_RIGHT] == 1 && old[SDL_SCANCODE_RIGHT] == 0)
	{
		printf("Fleche Droite => on increment camera x\n");
		change->v_camera.x += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0)
	{
		printf("A => on decremente le theta\n");
		change->theta -= 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0)
	{
		printf("D => on increment le theta\n");
		change->theta += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0)
	{
	change->v_forward = ft_vector_multiply(change->v_look_dir, 2.0);

		printf("On incremente du vecteur forward\n");
		change->v_camera = ft_vector_add(change->v_camera, change->v_forward);
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0)
	{
	change->v_forward = ft_vector_multiply(change->v_look_dir, 2.0);

		printf("On decremente du vecteur forward\n");
		change->v_camera = ft_vector_sub(change->v_forward, change->v_camera);
		change->modif = 1;
	}



//####################################
	//perspective set



	/* if (wn->state[SDL_SCANCODE_Q] == 1 && old[SDL_SCANCODE_Q] == 0) */
	/* { */
	/* 	if (change->display->panel == 1) */
	/* 		change->display->panel = 0; */
	/* 	else */
	/* 		change->display->panel = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch perspective\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_E] == 1 && old[SDL_SCANCODE_E] == 0) */
	/* { */
	/* 	if (change->display->color == 1) */
	/* 		change->display->color = 0; */
	/* 	else */
	/* 		change->display->color = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch color\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_G] == 1 && old[SDL_SCANCODE_G] == 0) */
	/* { */
	/* 	if (change->display->shade == 1) */
	/* 		change->display->shade = 0; */
	/* 	else */
	/* 		change->display->shade = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch color\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_P] == 1 && old[SDL_SCANCODE_P] == 0) */
	/* { */
	/* 	if (change->display->projection == orthographique) */
	/* 		change->display->projection = perspective; */
	/* 	else */
	/* 		change->display->projection = orthographique; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch perspective\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_T] == 1 && old[SDL_SCANCODE_T] == 0) */
	/* { */
	/* 	if (change->display->triangle == 1) */
	/* 		change->display->triangle = 0; */
	/* 	else */
	/* 		change->display->triangle = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch affichage triangle\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_M] == 1 && old[SDL_SCANCODE_M] == 0) */
	/* { */
	/* 	if (change->display->mesh == 1) */
	/* 		change->display->mesh = 0; */
	/* 	else */
	/* 		change->display->mesh = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch affichage mesh\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_C] == 1 && old[SDL_SCANCODE_C] == 0) */
	/* { */
	/* 	if (change->display->culling_face == 1) */
	/* 		change->display->culling_face = 0; */
	/* 	else */
	/* 		change->display->culling_face = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch culling\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_N] == 1 && old[SDL_SCANCODE_N] == 0) */
	/* { */
	/* 	if (change->display->mesh_normal == 1) */
	/* 		change->display->mesh_normal = 0; */
	/* 	else */
	/* 		change->display->mesh_normal = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch mesh normal\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_B] == 1 && old[SDL_SCANCODE_B] == 0) */
	/* { */
	/* 	if (change->display->triangle_normal == 1) */
	/* 		change->display->triangle_normal = 0; */
	/* 	else */
	/* 		change->display->triangle_normal = 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("switch triangle normal\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_J] == 1 ) */
	/* { */
	/* 	change->angle_x += 1; */
	/* 	change->theta_x += 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("rotation sur x\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_U] == 1 ) */
	/* { */
	/* 	change->angle_x -= 1; */
	/* 	change->modif = 1; */
	/* 	/1* printf("rotation sur x\n"); *1/ */
	/* } */
	/* if (wn->state[SDL_SCANCODE_K] == 1 ) */
	/* { */
	/* 	/1* printf("rotation sur y\n"); *1/ */
	/* 	change->angle_y += 1; */
	/* 	change->theta_y += 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_I] == 1 ) */
	/* { */
	/* 	/1* printf("rotation sur y\n"); *1/ */
	/* 	change->angle_y -= 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_L] == 1 ) */
	/* { */
	/* 	/1* printf("rotation sur z\n"); *1/ */
	/* 	change->angle_z += 1; */
	/* 	change->theta_z += 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_O] == 1 ) */
	/* { */
	/* 	/1* printf("rotation sur z\n"); *1/ */
	/* 	change->angle_z -= 1; */
	/* 	change->modif = 1; */
	/* } */
	/* /1* if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0) *1/ */
	/* /1* { *1/ */
	/* /1* 	/2* printf("zoom\n"); *2/ *1/ */
	/* /1* 	change->zoom += 1; *1/ */
	/* /1* 	change->modif = 1; *1/ */
	/* /1* } *1/ */
	/* /1* if (wn->state[SDL_SCANCODE_I] == 1 && old[SDL_SCANCODE_I] == 0) *1/ */
	/* /1* { *1/ */
	/* /1* 	/2* printf("zoom\n"); *2/ *1/ */
	/* /1* 	change->zoom -= 1; *1/ */
	/* /1* 	change->modif = 1; *1/ */
	/* /1* } *1/ */
	/* if (wn->state[SDL_SCANCODE_UP] == 1 && old[SDL_SCANCODE_UP] == 0) */
	/* { */
	/* 	printf("Fleche Bas => on decrement camera y\n"); */
	/* 	change->v_camera.y -= 5; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_DOWN] == 1 && old[SDL_SCANCODE_DOWN] == 0) */
	/* { */
	/* 	printf("Fleche Haut => on increment camera y\n"); */
	/* 	/1* change->v_camera.y += 5; *1/ */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_LEFT] == 1 && old[SDL_SCANCODE_LEFT] == 0) */
	/* { */
	/* 	printf("Fleche Gauche => on decrement camera x\n"); */
	/* 	change->v_camera.x -= 5; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_RIGHT] == 1 && old[SDL_SCANCODE_RIGHT] == 0) */
	/* { */
	/* 	printf("Fleche Droite => on increment camera x\n"); */
	/* 	change->v_camera.x += 5; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0) */
	/* { */
	/* 	printf("A => on decremente le theta\n"); */
	/* 	change->translation_x -= 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0) */
	/* { */
	/* 	printf("D => on decrement le theta\n"); */
	/* 	change->translation_x += 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0) */
	/* { */
	/* 	/1* printf("Translation UP\n"); *1/ */
	/* 	change->translation_y -= 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0) */
	/* { */
	/* 	/1* printf("Translation DOWN\n"); *1/ */
	/* 	change->translation_y += 1; */
	/* 	change->modif = 1; */
	/* } */
	/* /1* if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0) *1/ */
	/* /1* { *1/ */
	/* /1* 	/2* printf("Translation LEFT\n"); *2/ *1/ */
	/* /1* 	change->translation_x -= 5; *1/ */
	/* /1* 	change->modif = 1; *1/ */
	/* /1* } *1/ */
	/* /1* if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0) *1/ */
	/* /1* { *1/ */
	/* /1* 	/2* printf("Translation RIGHT\n"); *2/ *1/ */
	/* /1* 	change->translation_x += 5; *1/ */
	/* /1* 	change->modif = 1; *1/ */
	/* /1* } *1/ */
	/* if (wn->state[SDL_SCANCODE_Z] == 1 && old[SDL_SCANCODE_Z] == 0) */
	/* { */
	/* 	/1* printf("Translation Z\n"); *1/ */
	/* 	change->translation_z += 5; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_X] == 1 && old[SDL_SCANCODE_X] == 0) */
	/* { */
	/* 	/1* printf("Translation X\n"); *1/ */
	/* 	change->translation_z -= 5; */
	/* 	change->modif = 1; */
	/* } */



}

void	ft_init_launch_rasterization(t_mykeep *keep, t_mychange *change)
{
	keep->polygon = NULL;
	keep->vec = NULL;

	change->display = (t_mydisplay*)malloc(sizeof(t_mydisplay));
	change->old = (Uint8*)malloc(sizeof(Uint8) * 300);

	change->quit = FALSE;

	change->angle_x = 0;
	change->angle_y = 0;
	change->angle_z = 0;
	change->zoom = 1;
	change->translation_x = 0;
	change->translation_y = 0;
	change->translation_z = -10;

	change->modif = 1;

	change->display->triangle = 0;
	change->display->mesh = 1;

	change->display->projection = perspective;
	change->display->culling_face = 0;
	change->display->mesh_normal = 0;
	change->display->triangle_normal = 0;

	change->display->panel = 1;
	change->display->color = 0;
	change->display->shade = 0;

	change->v_look_dir.x = 0;
	change->v_look_dir.y = 0;
	change->v_look_dir.z = 0;

	change->v_camera.x = 0;
	change->v_camera.y = 0;
	change->v_camera.z = 0;

	change->theta_x = 0;
	change->theta_y = 0;
	change->theta_z = 0;



	change->mat_trans = ft_make_matrix_5_5();


}

float		ft_get_the_indice_vertex_x(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	x;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	x = vertex_lst->x;
	vertex_lst = keep;
	return (x);
}

float		ft_get_the_indice_vertex_y(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	y;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	y = vertex_lst->y;
	vertex_lst = keep;
	return (y);
}

float		ft_get_the_indice_vertex_z(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	z;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	z = vertex_lst->z;
	vertex_lst = keep;
	return (z);
}

void		ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep, t_mytriangle *triangle_array)
{
	printf("helloa\n");
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);

	int					nbr_triangle;
	t_mytriangle		triangle;
	int					j;
	int					i;

	change->theta_y = 90.0;

	change->mat_rot_x = ft_make_rotation_x(change->theta_x);
	change->mat_rot_y = ft_make_rotation_y(change->theta_y);
	change->mat_rot_z = ft_make_rotation_z(change->theta_z);
	change->mat_trans = ft_make_translation(change->translation_x, change->translation_y, change->translation_z);
	change->mat_perspectiv = ft_make_perspectiv();


	//########Make mat view
	change->v_up.x = 0.0;
	change->v_up.y = 1.0;
	change->v_up.z = 0.0;


	change->v_target.x = 0.0;
	change->v_target.y = 0.0;
	change->v_target.z = 1.0;

	change->mat_camera_rot = ft_make_rotation_y(change->theta);
	change->v_look_dir = ft_matrix_multiply_vector(change->mat_camera_rot, change->v_target);

	printf("le vecteur look dir x=%f, y=%f, z=%f\n", change->v_look_dir.x, change->v_look_dir.y, change->v_look_dir.z);

	printf("le vecteur camera x=%f, y=%f, z=%f\n", change->v_camera.x, change->v_camera.y, change->v_camera.z);

	change->v_target = ft_vector_add(change->v_camera, change->v_look_dir);

	printf("le vecteur v_target x=%f, y=%f, z=%f\n", change->v_target.x, change->v_target.y, change->v_target.z);
	/* return; */

	change->mat_camera = ft_matrix_point_at(change->v_camera, change->v_target, change->v_up);
	change->mat_view = ft_matrix_quick_inverse(change->mat_camera);



	nbr_triangle = ft_get_nbr_of_triangle(s_win);
	i = 0;
	while (i < nbr_triangle)
	{
		triangle = triangle_array[i];
		printf("\n\n\n########################################################################\n");
		printf("\nLE TRIANGLE DE BASE\n");
		j = -1;
		while (++j < 3)
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);

		printf("\nON APLLIQUE LES ROTATION et TRANSATION\n");
		j = -1;
		while (++j < 3)
		{
			triangle.vertice[j] = ft_matrix_multiply_vector(change->mat_rot_x, triangle.vertice[j]);  
			triangle.vertice[j] = ft_matrix_multiply_vector(change->mat_rot_y, triangle.vertice[j]);  
			triangle.vertice[j] = ft_matrix_multiply_vector(change->mat_rot_z, triangle.vertice[j]);  
			triangle.vertice[j] = ft_matrix_multiply_vector(change->mat_trans, triangle.vertice[j]);  
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
		}




		printf("\nOn applique mat view\n");

		j = -1;
		while (++j < 3)
		{
			triangle.vertice[j] = ft_matrix_multiply_vector(change->mat_view, triangle.vertice[j]);  
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
		}


		printf("\nON APLLIQUE la PERSPECTIV\n");
		/* j = -1; */
		/* while (++j < 3) */
		/* { */
		/* 	printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z); */
		/* } */
		j = -1;
		while (++j < 3)
		{
			triangle.vertice[j] = ft_perspective_projection(triangle.vertice[j]);
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
		}

		printf("\nON APLLIQUE la SCALE SCREEN\n");
		j = -1;
		while (++j < 3)
		{
			triangle.vertice[j] = ft_scale_screen(triangle.vertice[j]);  
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
		}


		/* printf("\nON trie\n"); */
		/* ft_order_triangle_vertice(&(triangle.vertice[0]), &(triangle.vertice[1]), &(triangle.vertice[2])); */
		/* j = -1; */
		/* while (++j < 3) */
		/* { */
		/* 	printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z); */
		/* } */

		printf("\nON affiche\n");
		SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 0, 0, 255);
		ft_draw_triangle_base(&(triangle.vertice[0]), &(triangle.vertice[1]), &(triangle.vertice[2]), s_win);
		j = -1;
		while (++j < 3)
		{
			printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
		}

		/* exit(0); */
		/* return; */
		i++;
	}
	/* exit(0); */
	return;




	t_mypolygon *polygon;

	change->modif = 0;
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);

	polygon = s_win->polygon_lst;
	keep->polygon = polygon;
	/* printf("\n\n\n\n\nAPLY\n"); */
	while (polygon != NULL)
	{
		/* printf("\nNEW POLYGON\n"); */
		if (change->display->triangle == 0)
		{
			keep->vec = polygon->vertex_lst;
 			/* printf("le AAAA = %d\n", polygon->number_of_vertex); */
			while (polygon->vertex_lst->next != NULL)
			{
				change->result_1.x = polygon->vertex_lst->x;
				change->result_1.y = polygon->vertex_lst->y;
				change->result_1.z = polygon->vertex_lst->z;
				change->result_2.x = polygon->vertex_lst->next->x;
				change->result_2.y = polygon->vertex_lst->next->y;
				change->result_2.z = polygon->vertex_lst->next->z;
				SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
				ft_draw_change(s_win, change);
				polygon->vertex_lst = polygon->vertex_lst->next;
			}
			//bouclage dernier et premier
			change->result_1.x = polygon->vertex_lst->x;
			change->result_1.y = polygon->vertex_lst->y;
			change->result_1.z = polygon->vertex_lst->z;
			polygon->vertex_lst = keep->vec;
			change->result_2.x = polygon->vertex_lst->x;
			change->result_2.y = polygon->vertex_lst->y;
			change->result_2.z = polygon->vertex_lst->z;
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
			ft_draw_change(s_win, change);
		}
		else if (change->display->triangle == 1)
		{
			int i = 0;
			while (i < polygon->number_of_indices - 2)
			{
				change->result_1.x = ft_get_the_indice_vertex_x(polygon->indices[i] ,polygon->vertex_lst);
				change->result_1.y = ft_get_the_indice_vertex_y(polygon->indices[i], polygon->vertex_lst);
				change->result_1.z = ft_get_the_indice_vertex_z(polygon->indices[i], polygon->vertex_lst);

				change->result_2.x = ft_get_the_indice_vertex_x(polygon->indices[i + 1], polygon->vertex_lst);
				change->result_2.y = ft_get_the_indice_vertex_y(polygon->indices[i + 1], polygon->vertex_lst);
				change->result_2.z = ft_get_the_indice_vertex_z(polygon->indices[i + 1], polygon->vertex_lst);

				change->result_3.x = ft_get_the_indice_vertex_x(polygon->indices[i + 2], polygon->vertex_lst);
				change->result_3.y = ft_get_the_indice_vertex_y(polygon->indices[i + 2], polygon->vertex_lst);
				change->result_3.z = ft_get_the_indice_vertex_z(polygon->indices[i + 2], polygon->vertex_lst);


				/* printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa\n"); */

				/* 	printf("the triangle first point x=%f\n", change->result_1.x); */
				/* 	printf("the triangle first point y=%f\n", change->result_1.y); */
				/* 	printf("the triangle first point z=%f\n", change->result_1.z); */

				/* 	printf("\n"); */


				/* 	printf("the triangle seconde point x=%f\n", change->result_2.x); */
				/* 	printf("the triangle seconde point y=%f\n", change->result_2.y); */
				/* 	printf("the triangle seconde point z=%f\n", change->result_2.z); */

				/* 	printf("\n"); */

				/* 	printf("the triangle third point x=%f\n", change->result_3.x); */
				/* 	printf("the triangle third point y=%f\n", change->result_3.y); */
				/* 	printf("the triangle third point z=%f\n", change->result_3.z); */


				/* 	printf("\n"); */

				SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
				ft_draw_change(s_win, change);
				i = i + 3;
			}
		}
		polygon = polygon->next;
	}
	polygon = keep->polygon;
}


void	ft_order_triangle_vertice(t_myvec *v1, t_myvec *v2, t_myvec *v3);

void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	t_mychange			change;
	t_mykeep			keep;


	SDL_Init(SDL_INIT_EVERYTHING);
	s_win->current_window = J_EDITOR;
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);

	ft_init_launch_rasterization(&keep, &change);
	ft_launch_bsp_tree(s_win, wn);

	t_mytriangle	*triangle_array;
	triangle_array = ft_get_triangles_array(s_win);
	ft_display_triangle_array(s_win, triangle_array);

	while (!change.quit)
	{
		SDL_PollEvent(&(wn->ev));
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		wn->input->oldmouse = wn->input->mouse;
		wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
		ft_keyboard_event_check(wn , change.old, &change);
		ft_mouse_event_check(wn, &change);
		if (change.modif == 1)
		{
			ft_apply_modif(s_win, &change, &keep, triangle_array);
			if (change.display->panel == 1)
				ft_display_panel(s_win, &change);
			change.modif = 0;
			SDL_RenderPresent(s_win->renderer[J_EDITOR]);
		}
		SDL_Delay(1);
		setkeyboard(change.old, wn->state);
	}
}




