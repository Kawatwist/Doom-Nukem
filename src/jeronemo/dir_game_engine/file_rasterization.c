/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/03 15:03:05 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_mytriangle	*ft_triangle_node_create(t_mytriangle tri)
{
	t_mytriangle	*triangle;

	triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	triangle = memcpy(triangle, &tri, sizeof(t_mytriangle));
	triangle->next = NULL;
	return (triangle);
}

void			ft_triangle_add_node(t_mytriangle **lst, t_mytriangle *node)
{
	if (*lst == NULL)
	{
		*lst = node;
	}
	else
	{
		node->next = *lst;
		*lst = node;
	}
}


void	ft_swap(t_mytriangle *triangle_lst)
{
	t_mytriangle	*swap;
	swap = NULL;
	swap = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	swap->shade = triangle_lst->shade;
	swap->vertice[0].x = triangle_lst->vertice[0].x;
	swap->vertice[0].y = triangle_lst->vertice[0].y;
	swap->vertice[0].z = triangle_lst->vertice[0].z;
	swap->vertice[1].x = triangle_lst->vertice[1].x;
	swap->vertice[1].y = triangle_lst->vertice[1].y;
	swap->vertice[1].z = triangle_lst->vertice[1].z;
	swap->vertice[2].x = triangle_lst->vertice[2].x;
	swap->vertice[2].y = triangle_lst->vertice[2].y;
	swap->vertice[2].z = triangle_lst->vertice[2].z;

	triangle_lst->shade = triangle_lst->next->shade;
	triangle_lst->vertice[0].x = triangle_lst->next->vertice[0].x;
	triangle_lst->vertice[0].y = triangle_lst->next->vertice[0].y;
	triangle_lst->vertice[0].z = triangle_lst->next->vertice[0].z;
	triangle_lst->vertice[1].x = triangle_lst->next->vertice[1].x;
	triangle_lst->vertice[1].y = triangle_lst->next->vertice[1].y;
	triangle_lst->vertice[1].z = triangle_lst->next->vertice[1].z;
	triangle_lst->vertice[2].x = triangle_lst->next->vertice[2].x;
	triangle_lst->vertice[2].y = triangle_lst->next->vertice[2].y;
	triangle_lst->vertice[2].z = triangle_lst->next->vertice[2].z;

	triangle_lst->next->shade = swap->shade;
	triangle_lst->next->vertice[0].x = swap->vertice[0].x;
	triangle_lst->next->vertice[0].y = swap->vertice[0].y;
	triangle_lst->next->vertice[0].z = swap->vertice[0].z;
	triangle_lst->next->vertice[1].x = swap->vertice[1].x;
	triangle_lst->next->vertice[1].y = swap->vertice[1].y;
	triangle_lst->next->vertice[1].z = swap->vertice[1].z;
	triangle_lst->next->vertice[2].x = swap->vertice[2].x;
	triangle_lst->next->vertice[2].y = swap->vertice[2].y;
	triangle_lst->next->vertice[2].z = swap->vertice[2].z;
}

void	ft_order_triangle_z_buffer(t_mytriangle *triangle_lst)
{
	float			z1;
	float			z2;
	t_mytriangle	*keep;

	keep = triangle_lst;
	while (triangle_lst->next != NULL)
	{
		z1 = (triangle_lst->vertice[0].z + triangle_lst->vertice[1].z + triangle_lst->vertice[2].z) / 3;
		z2 = (triangle_lst->next->vertice[0].z + triangle_lst->next->vertice[1].z + triangle_lst->next->vertice[2].z) / 3;
		if (z1 < z2)
		{
			ft_swap(triangle_lst);
			triangle_lst = keep;
		}
		triangle_lst = triangle_lst->next;
	}
	triangle_lst = keep;
}

void		ft_update_raster(t_mywin *s_win, t_myraster *raster, t_mytriangle *triangle_array, int max)
{
	int				i;
	t_myvec			light_direction;
	t_mytriangle	triangle;
	t_mytriangle	*triangle_lst;
	t_mytriangle	*triangle_node;
	t_mytriangle	*keep;

	triangle_lst = NULL;
	light_direction.x = 0.5;
	light_direction.y = 0.0;
	light_direction.z = -1.0;
	light_direction = ft_normalise(light_direction);
	raster->v_camera.x = 0;
	raster->v_camera.y = 0;
	raster->v_camera.z = 0;
	t_myvec		normal;
	ft_set_raster_trans(0, 0, 30, raster);
	//ft_set_raster_rot_x(raster->ftheta, raster);
	ft_set_raster_rot_x(180, raster);
	//ft_set_raster_rot_y(raster->ftheta, raster);
	ft_set_raster_rot_z(raster->ftheta * 0.5, raster);

	////##################################################################################################
	i = 0;
	while (i < max )
	{
		triangle = triangle_array[i];
		//ROTATION Z
		triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle.vertice[0]);
		triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle.vertice[1]);
		triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle.vertice[2]);
		//ROTATION X
		triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle.vertice[0]);
		triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle.vertice[1]);
		triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle.vertice[2]);
		//TRANSLATION (offset in screen)
		triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_trans, triangle.vertice[0]);
		triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_trans, triangle.vertice[1]);
		triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_trans, triangle.vertice[2]);
		//CULLING
		normal = ft_calculate_normal_of_points(triangle.vertice[0], triangle.vertice[1], triangle.vertice[2]);
		normal = ft_normalise(normal);
		if (ft_dot_product(normal, ft_vector_sub(triangle.vertice[0], raster->v_camera)) < 0.0)
		{
			triangle.shade = ft_dot_product(normal, light_direction);
			//PROJECTION
			triangle.vertice[0] = ft_matrix_multiply_vector(raster->mat_proje, triangle.vertice[0]);
			triangle.vertice[1] = ft_matrix_multiply_vector(raster->mat_proje, triangle.vertice[1]);
			triangle.vertice[2] = ft_matrix_multiply_vector(raster->mat_proje, triangle.vertice[2]);
			//SCALE
			triangle.vertice[0] = ft_scale_screen(triangle.vertice[0]);
			triangle.vertice[1] = ft_scale_screen(triangle.vertice[1]);
			triangle.vertice[2] = ft_scale_screen(triangle.vertice[2]);
			triangle_node = ft_triangle_node_create(triangle);
			ft_triangle_add_node(&triangle_lst, triangle_node);
		}
		i++;
	}
	//ORDER TRIANGLE FROM FAR TO NEAR
	ft_order_triangle_z_buffer(triangle_lst);
	keep = triangle_lst;
	while (triangle_lst != NULL)
	{
		//DRAW FILL TRIANGLE + SHADE/LIGHT
		ft_fill_triangle_shade((triangle_lst->vertice[0]), (triangle_lst->vertice[1]), (triangle_lst->vertice[2]), s_win, triangle_lst->shade);
		//DRAW MESH
		SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 255, 0, 0, 255);
		ft_draw_triangle_base(&(triangle_lst->vertice[0]), &(triangle_lst->vertice[1]), &(triangle_lst->vertice[2]), s_win);
		triangle_lst = triangle_lst->next;
	}
	triangle_lst = keep;
	raster->ftheta += 0;
	if (raster->ftheta == 360 * 2)
		raster->ftheta = 0;
	//free list
	return;
}

/*
   void		ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep, t_mytriangle *triangle_array)
   {
   int					nbr_triangle;
   t_mytriangle		triangle;
   int					j;
   int					i;

   SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 0, 0, 255);
   SDL_RenderClear(s_win->renderer[s_win->interface]);

   t_camera cam;

   cam.pos.x = 0.0;
   cam.pos.y = 0.0;
   cam.pos.z = 0.0;

   cam.pos.x = change->v_camera.x;
   cam.pos.y = change->v_camera.y;
   cam.pos.z = change->v_camera.z;

   printf("=%f =%f =%f", cam.pos.x, cam.pos.y, cam.pos.z);


   cam.pitch = 3;
   cam.yaw = change->theta;

   t_vector3 zaxis = normalize_t_vector3(create_t_vector3(cos(degree_to_radius(cam.pitch)) * sin(degree_to_radius(cam.yaw)),
   sin(degree_to_radius(cam.pitch)),
   cos(degree_to_radius(cam.pitch)) * cos(degree_to_radius(cam.yaw))));


   t_vector3 xaxis = normalize_t_vector3(create_t_vector3(sin(degree_to_radius(cam.yaw) - 3.14f / 2.0f),
   0,
   cos(degree_to_radius(cam.yaw) - 3.14f / 2.0f)));


   t_vector3 yaxis = normalize_t_vector3(cross_t_vector3(xaxis, zaxis));


//this is the look at vector   (rotation de la camera)
cam.forward = zaxis;
cam.right = xaxis;
cam.up = inv_t_vector3(yaxis);


if (change->avancer == 1)
{
cam.forward = normalize_t_vector3(cam.forward);
cam.pos = substract_vector3_to_vector3(cam.pos, cam.forward);

printf("AAAAAAAAAAAAAAAAAAAAAAAAAaaa\n\n\n\n");

change->avancer = 0;
}
if (change->reculer == 1)
{

cam.forward = normalize_t_vector3(cam.forward);
cam.pos = add_vector3_to_vector3(cam.pos, cam.forward);

printf("AAAAAAAAAAAAAAAAAAAAAAAAAaaa\n\n\n\n");

change->reculer = 0;
}



//this is the matrix view
cam.view = t_camera_compute_view(&cam);
//this is the matrix projection


cam.near = 0.1;
cam.far = 50.0;
cam.fov = 70;

cam.projection = compute_projection_matrix(&cam);
t_vector3 vertice[3];

nbr_triangle = ft_get_nbr_of_triangle(s_win);
i = 0;
printf("BOUCLE\n");


printf("\n\n");
printf("la matrice = %f ", cam.view.value[0][0]);
printf("la matrice = %f ", cam.view.value[1][0]);
printf("la matrice = %f ", cam.view.value[2][0]);
printf("la matrice = %f \n", cam.view.value[3][0]);

printf("la matrice = %f ", cam.view.value[0][1]);
printf("la matrice = %f ", cam.view.value[1][1]);
printf("la matrice = %f ", cam.view.value[2][1]);
printf("la matrice = %f \n", cam.view.value[3][1]);

printf("la matrice = %f ", cam.view.value[0][2]);
printf("la matrice = %f ", cam.view.value[1][2]);
printf("la matrice = %f ", cam.view.value[2][2]);
printf("la matrice = %f \n", cam.view.value[3][2]);
printf("\n\n");



change->mat_trans = ft_make_translation(0, 0, -15);
while (i < nbr_triangle)
{
	printf("A i =%d\n", i);


	triangle = triangle_array[i];

	j = -1;
	while (++j < 3)
		triangle.vertice[j] = ft_matrix_multiply_vector(change->mat_trans, triangle.vertice[j]);



	if (ft_calcul_culing(change, &triangle))
	{
		vertice[0].x = triangle.vertice[0].x;
		vertice[0].y = triangle.vertice[0].y;
		vertice[0].z = triangle.vertice[0].z;

		vertice[1].x = triangle.vertice[1].x;
		vertice[1].y = triangle.vertice[1].y;
		vertice[1].z = triangle.vertice[1].z;

		vertice[2].x = triangle.vertice[2].x;
		vertice[2].y = triangle.vertice[2].y;
		vertice[2].z = triangle.vertice[2].z;

		j = -1;
		while (++j < 3)
			vertice[j] = mult_vector3_by_matrix(vertice[j], cam.view);


		int			number_of_clipped_triangle;
		t_myvec		point;
		t_myvec		plan_N;
		t_mytriangle	clipped_triangle[2];

		point.x = 0.0;
		point.y = 0.0;
		point.z = 5.1;
		plan_N.x = 0.0;
		plan_N.y = 0.0;
		plan_N.z = 1.0;

		plan_N = ft_normalise(plan_N);

		triangle.vertice[0].x = vertice[0].x;
		triangle.vertice[0].y = vertice[0].y;
		triangle.vertice[0].z = vertice[0].z;

		triangle.vertice[1].x =vertice[1].x;
		triangle.vertice[1].y =vertice[1].y;
		triangle.vertice[1].z =vertice[1].z;

		triangle.vertice[2].x = vertice[2].x;
		triangle.vertice[2].y = vertice[2].y;
		triangle.vertice[2].z = vertice[2].z;
		//on clipped sur sur le plan de la camera
		number_of_clipped_triangle = ft_triangle_clips_again_plan(point, plan_N, &(clipped_triangle[0]), &(triangle), s_win);


		int k = 0;
		while (k < number_of_clipped_triangle)
		{
			printf("###################################################\n");
			vertice[0].x = clipped_triangle[k].vertice[0].x;
			vertice[0].y = clipped_triangle[k].vertice[0].y;
			vertice[0].z = clipped_triangle[k].vertice[0].z;

			vertice[1].x = clipped_triangle[k].vertice[1].x;
			vertice[1].y = clipped_triangle[k].vertice[1].y;
			vertice[1].z = clipped_triangle[k].vertice[1].z;

			vertice[2].x = clipped_triangle[k].vertice[2].x;
			vertice[2].y = clipped_triangle[k].vertice[2].y;
			vertice[2].z = clipped_triangle[k].vertice[2].z;
			j = -1;
			while (++j < 3)
				vertice[j] = apply_t_camera(&(vertice[j]), &(cam.projection)); // applique la position de la camera

			triangle.vertice[0].x = vertice[0].x;
			triangle.vertice[0].y = vertice[0].y;
			triangle.vertice[0].z = vertice[0].z;

			triangle.vertice[1].x =vertice[1].x;
			triangle.vertice[1].y =vertice[1].y;
			triangle.vertice[1].z =vertice[1].z;

			triangle.vertice[2].x = vertice[2].x;
			triangle.vertice[2].y = vertice[2].y;
			triangle.vertice[2].z = vertice[2].z;

			j = -1;
			while (++j < 3)
				triangle.vertice[j] = ft_scale_screen(triangle.vertice[j]);

			j = 1;
			while (++j < 3)
				printf("Le %d point x=%f\t\ty=%f\t\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);

			//####################################
			//on clip sur les bords de l'ecran

			//creation de la liste pas la plus haut
			//ft_create triangle list
			//ft on ajoute le triangle courant a la list
			//on test sur le bord gaude
			//n = ft_clip
			//while (i < n)
			//{
			//on traite puis on ajoute
			//}


			//on test sur le bord haut
			//n = ft_clip
			//while (i < n)
			//{
			//on traite puis on ajoute
			//}


			//on test sur le bord droit
			//n = ft_clip
			//while (i < n)
			//{
			//on traite puis on ajoute
			//}



			//on test sur le bord  bas
			//n = ft_clip
			//while (i < n)
			//{
			//on traite puis on ajoute
			//}
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 0, 0, 255);
			ft_draw_triangle_base(&(triangle.vertice[0]), &(triangle.vertice[1]), &(triangle.vertice[2]), s_win);
			k++;
		}
		//on boucle sur la liste de triangle pour les afficher
	}
	i++;
	printf("le i =%d\n", i);
}

printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAanewAAAAAAAAAAAAAAaa\n");
return;

//#########################################
printf("helloa\n");
SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 0, 0, 255);
SDL_RenderClear(s_win->renderer[s_win->interface]);

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
return;

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
	j = -1;
	while (++j < 3)
	{
		printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
	}
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
		printf("Le %d point x=%f\t\ty=%f\t\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
	}

	printf("\nON trie\n");
	ft_order_triangle_vertice(&(triangle.vertice[0]), &(triangle.vertice[1]), &(triangle.vertice[2]));
	j = -1;
	while (++j < 3)
	{
		printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
	}



	//#######################
	//creation de la list de tout les triangles





	printf("\nON affiche\n");
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 0, 0, 255);
	ft_draw_triangle_base(&(triangle.vertice[0]), &(triangle.vertice[1]), &(triangle.vertice[2]), s_win);
	j = -1;
	while (++j < 3)
	{
		printf("Le %d point x=%f\ty=%f\tz=%f\n", j, triangle.vertice[j].x, triangle.vertice[j].y, triangle.vertice[j].z);
	}

	exit(0);
	return;
	i++;
}
exit(0);
return;


t_mypolygon *polygon;

change->modif = 0;
SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
SDL_RenderClear(s_win->renderer[J_EDITOR]);

polygon = s_win->polygon_lst;
keep->polygon = polygon;
printf("\n\n\n\n\nAPLY\n");
while (polygon != NULL)
{
	printf("\nNEW POLYGON\n");
	if (change->display->triangle == 0)
	{
		keep->vec = polygon->vertex_lst;
 		printf("le AAAA = %d\n", polygon->number_of_vertex);
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


			printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa\n");

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


			printf("\n");

			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
			ft_draw_change(s_win, change);
			i = i + 3;
		}
	}
	polygon = polygon->next;
}
polygon = keep->polygon;
}
*/
