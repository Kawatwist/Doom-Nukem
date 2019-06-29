/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/29 19:54:53 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>


void	ft_order_triangle_vertice(t_myvec *v1, t_myvec *v2, t_myvec *v3)
{
	t_myvec		temp;
	int			j;
	int			i;
	t_myvec		tab[3];


	tab[0] =  *v1;
	tab[1] =  *v2;
	tab[2] =  *v3;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (tab[j].y > tab[j + 1].y)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
				i = 0;
			}
			j++;
		}
		i++;
	}
	*v1 = tab[0];
	*v2 = tab[1];
	*v3 = tab[2];
}

void	ft_fill_bottom_flat_triangle(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_mywin *s_win)
{
	float				invslope1;
	float				invslope2;
	float				curx1;
	float				curx2;
	t_myputtheline		s_line;;
	int					scanline_y;

	invslope1 = (v2->x - v1->x) / (v2->y - v1->y);
	invslope2 = (v3->x - v1->x) / (v3->y - v1->y);
	curx1 = v1->x;
	curx2 = v1->x;
	scanline_y = v1->y;
	while (scanline_y < v2->y - 1)
	{
		s_line.un.a = (int)curx1;
		s_line.un.b = scanline_y;
		s_line.deux.a = (int)curx2;
		s_line.deux.b = scanline_y;
		ft_draw_line(s_win, &s_line);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline_y++;
	}
}

void	ft_fill_top_flat_triangle(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_mywin *s_win)
{
	float	invslope1 = (v3->x - v1->x) / (v3->y - v1->y);
	float	invslope2 = (v3->x - v2->x) / (v3->y - v2->y);

	float	curx1 = v3->x;
	float	curx2 = v3->x;
	t_myputtheline		s_line;;

	int		scanline_y = v3->y;
	while (scanline_y > v1->y)
	{
		s_line.un.a = (int)curx1;
		s_line.un.b = scanline_y;
		s_line.deux.a = (int)curx2;
		s_line.deux.b = scanline_y;
		ft_draw_line(s_win, &s_line);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline_y--;
	}
}

void	ft_fill_triangle_one_color(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_mywin *s_win)
{
	t_myvec				v4;
	t_myputtheline		s_line;;

	if (v2->y == v3->y)
		ft_fill_bottom_flat_triangle(v1, v2, v3, s_win);
	else if (v1->y == v2->y)
		ft_fill_top_flat_triangle(v1, v2, v3, s_win);
	else
	{
		v4.y = v2->y;
		v4.x = v1->x + ((v2->y - v1->y) / (v3->y - v1->y)) * (v3->x - v1->x);
		s_line.un.a = v2->x;
		s_line.un.b = v2->y;
		s_line.deux.a = v4.x;
		s_line.deux.b = v4.y;
		ft_draw_line(s_win, &s_line);
		ft_fill_bottom_flat_triangle(v1, v2, &v4, s_win);
		ft_fill_top_flat_triangle(v2, &v4, v3, s_win);
	}
}

void	ft_fill_triangle_shade(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_mywin *s_win, float shade)
{
	t_myvec				v4;
	t_myputtheline		s_line;;
	t_mycolor			color;

	color = ft_setcolor(GREEN);


	ft_order_triangle_vertice(v1, v2, v3);







	shade = 255;
	SDL_SetRenderDrawColor(s_win->renderer[s_win->current_window], color.rrr, color.ggg - v1->shade, color.bbb, shade);
	if (v2->y == v3->y)
		ft_fill_bottom_flat_triangle(v1, v2, v3, s_win);
	else if (v1->y == v2->y)
		ft_fill_top_flat_triangle(v1, v2, v3, s_win);
	else
	{
		v4.y = v2->y;
		v4.x = v1->x + ((v2->y - v1->y) / (v3->y - v1->y)) * (v3->x - v1->x);
		s_line.un.a = v2->x;
		s_line.un.b = v2->y;
		s_line.deux.a = v4.x;
		s_line.deux.b = v4.y;
		ft_draw_line(s_win, &s_line);
		ft_fill_bottom_flat_triangle(v1, v2, &v4, s_win);
		ft_fill_top_flat_triangle(v2, &v4, v3, s_win);
	}
}

void		ft_update_raster(t_mywin *s_win, t_myraster *raster/*, t_mytriangle *triangle_array*/)
{
	(void)s_win;
	printf("update raster\n");

	t_mytriangle	*triangle;
	triangle = ft_get_triangle();


	int i;

	printf("Liste des triangle\n");
	i = 0;
	while (i < 12)
	{
		if ((i + 1) % 2)
		printf("triangle n=%d\n", i);
		printf("x =%f y=%f z=%f\t", triangle[i].vertice[0].x, triangle[i].vertice[0].y, triangle[i].vertice[0].z);
		printf("x =%f y=%f z=%f\t", triangle[i].vertice[1].x, triangle[i].vertice[1].y, triangle[i].vertice[1].z);
		printf("x =%f y=%f z=%f\n", triangle[i].vertice[2].x, triangle[i].vertice[2].y, triangle[i].vertice[2].z);
		i++;
	}

	int ftheta;
	int shade = 1;
	ftheta = 0;

	raster->v_camera.x = 0;
	raster->v_camera.y = 0;
	raster->v_camera.z = 0;
	t_myvec		normal;
	while (1)
	{
		triangle = ft_get_triangle();
		ft_set_raster_trans(0, 0, 3, raster);
		ft_set_raster_rot_x(ftheta, raster);
		//ft_set_raster_rot_y(ftheta, raster);
		ft_set_raster_rot_z(ftheta * 0.5, raster);
		ft_clear_window(s_win);
		i = 0;
		while (i < 12)
		{
			//ROTATION Z
			triangle[i].vertice[0] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle[i].vertice[0]);
			triangle[i].vertice[1] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle[i].vertice[1]);
			triangle[i].vertice[2] = ft_matrix_multiply_vector(raster->mat_rot_z, triangle[i].vertice[2]);
			//ROTATION X
			triangle[i].vertice[0] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle[i].vertice[0]);
			triangle[i].vertice[1] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle[i].vertice[1]);
			triangle[i].vertice[2] = ft_matrix_multiply_vector(raster->mat_rot_x, triangle[i].vertice[2]);
			//TRANSLATION (offset in screen)
			triangle[i].vertice[0] = ft_matrix_multiply_vector(raster->mat_trans, triangle[i].vertice[0]);
			triangle[i].vertice[1] = ft_matrix_multiply_vector(raster->mat_trans, triangle[i].vertice[1]);
			triangle[i].vertice[2] = ft_matrix_multiply_vector(raster->mat_trans, triangle[i].vertice[2]);
			//CULLING
			normal = ft_calculate_normal_of_points(triangle[i].vertice[0], triangle[i].vertice[1], triangle[i].vertice[2]);
			normal = ft_normalise(normal);
			if (
					(normal.x * (triangle[i].vertice[0].x - raster->v_camera.x) +
					normal.y * (triangle[i].vertice[0].y - raster->v_camera.y) +
					normal.z * (triangle[i].vertice[0].z - raster->v_camera.z)) < 0.0
			   )
			{
				//PROJECTION
				triangle[i].vertice[0] = ft_matrix_multiply_vector(raster->mat_proje, triangle[i].vertice[0]);
				triangle[i].vertice[1] = ft_matrix_multiply_vector(raster->mat_proje, triangle[i].vertice[1]);
				triangle[i].vertice[2] = ft_matrix_multiply_vector(raster->mat_proje, triangle[i].vertice[2]);
				//SCALE
				triangle[i].vertice[0] = ft_scale_screen(triangle[i].vertice[0]);
				triangle[i].vertice[1] = ft_scale_screen(triangle[i].vertice[1]);
				triangle[i].vertice[2] = ft_scale_screen(triangle[i].vertice[2]);
				//DRAW FILL TRIANGLE
				SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 0, 0, 255, 255);
				ft_fill_triangle_shade(&(triangle[i].vertice[0]), &(triangle[i].vertice[1]), &(triangle[i].vertice[2]), s_win,  shade);
				//DRAW MESH
				SDL_SetRenderDrawColor(s_win->renderer[s_win->interface], 255, 0, 0, 255);
				ft_draw_triangle_base(&(triangle[i].vertice[0]), &(triangle[i].vertice[1]), &(triangle[i].vertice[2]), s_win);
			}
			i++;
		}
		ftheta++;
		if (ftheta == 360 * 2)
			ftheta = 0;
		SDL_RenderPresent(s_win->renderer[s_win->interface]);
		SDL_Delay(20);
	}
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
