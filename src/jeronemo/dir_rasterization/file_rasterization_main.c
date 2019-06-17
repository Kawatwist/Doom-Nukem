/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/17 18:55:22 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_keyboard_event_check(t_win *wn, Uint8 *old, t_mychange *change)
{

	if (wn->state[SDL_SCANCODE_ESCAPE])
		change->quit = TRUE;
	if (wn->state[SDL_SCANCODE_Q] == 1 && old[SDL_SCANCODE_Q] == 0)
	{
		if (change->display->panel == 1)
			change->display->panel = 0;
		else
			change->display->panel = 1;
		change->modif = 1;
		/* printf("switch perspective\n"); */
	}
	if (wn->state[SDL_SCANCODE_E] == 1 && old[SDL_SCANCODE_E] == 0)
	{
		if (change->display->color == 1)
			change->display->color = 0;
		else
			change->display->color = 1;
		change->modif = 1;
		/* printf("switch color\n"); */
	}
	if (wn->state[SDL_SCANCODE_G] == 1 && old[SDL_SCANCODE_G] == 0)
	{
		if (change->display->shade == 1)
			change->display->shade = 0;
		else
			change->display->shade = 1;
		change->modif = 1;
		/* printf("switch color\n"); */
	}
	if (wn->state[SDL_SCANCODE_P] == 1 && old[SDL_SCANCODE_P] == 0)
	{
		if (change->display->projection == orthographique)
			change->display->projection = perspective;
		else
			change->display->projection = orthographique;
		change->modif = 1;
		/* printf("switch perspective\n"); */
	}
	if (wn->state[SDL_SCANCODE_T] == 1 && old[SDL_SCANCODE_T] == 0)
	{
		if (change->display->triangle == 1)
			change->display->triangle = 0;
		else
			change->display->triangle = 1;
		change->modif = 1;
		/* printf("switch affichage triangle\n"); */
	}
	if (wn->state[SDL_SCANCODE_M] == 1 && old[SDL_SCANCODE_M] == 0)
	{
		if (change->display->mesh == 1)
			change->display->mesh = 0;
		else
			change->display->mesh = 1;
		change->modif = 1;
		/* printf("switch affichage mesh\n"); */
	}
	if (wn->state[SDL_SCANCODE_C] == 1 && old[SDL_SCANCODE_C] == 0)
	{
		if (change->display->culling_face == 1)
			change->display->culling_face = 0;
		else
			change->display->culling_face = 1;
		change->modif = 1;
		/* printf("switch culling\n"); */
	}
	if (wn->state[SDL_SCANCODE_N] == 1 && old[SDL_SCANCODE_N] == 0)
	{
		if (change->display->mesh_normal == 1)
			change->display->mesh_normal = 0;
		else
			change->display->mesh_normal = 1;
		change->modif = 1;
		/* printf("switch mesh normal\n"); */
	}
	if (wn->state[SDL_SCANCODE_B] == 1 && old[SDL_SCANCODE_B] == 0)
	{
		if (change->display->triangle_normal == 1)
			change->display->triangle_normal = 0;
		else
			change->display->triangle_normal = 1;
		change->modif = 1;
		/* printf("switch triangle normal\n"); */
	}
	if (wn->state[SDL_SCANCODE_J] == 1 )
	{
		change->angle_x += 1;
		change->modif = 1;
		/* printf("rotation sur x\n"); */
	}
	if (wn->state[SDL_SCANCODE_U] == 1 )
	{
		change->angle_x -= 1;
		change->modif = 1;
		/* printf("rotation sur x\n"); */
	}
	if (wn->state[SDL_SCANCODE_K] == 1 )
	{
		/* printf("rotation sur y\n"); */
		change->angle_y += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_I] == 1 )
	{
		/* printf("rotation sur y\n"); */
		change->angle_y -= 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_L] == 1 )
	{
		/* printf("rotation sur z\n"); */
		change->angle_z += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_O] == 1 )
	{
		/* printf("rotation sur z\n"); */
		change->angle_z -= 1;
		change->modif = 1;
	}
	/* if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0) */
	/* { */
	/* 	/1* printf("zoom\n"); *1/ */
	/* 	change->zoom += 1; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_I] == 1 && old[SDL_SCANCODE_I] == 0) */
	/* { */
	/* 	/1* printf("zoom\n"); *1/ */
	/* 	change->zoom -= 1; */
	/* 	change->modif = 1; */
	/* } */
	if (wn->state[SDL_SCANCODE_UP] == 1 && old[SDL_SCANCODE_UP] == 0)
	{
		printf("Fleche Bas => on decrement camera y\n");
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
		change->theta -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0)
	{
		printf("D => on decrement le theta\n");
		change->translation_x += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0)
	{
		/* printf("Translation UP\n"); */
		change->translation_y -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0)
	{
		/* printf("Translation DOWN\n"); */
		change->translation_y += 5;
		change->modif = 1;
	}
	/* if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0) */
	/* { */
	/* 	/1* printf("Translation LEFT\n"); *1/ */
	/* 	change->translation_x -= 5; */
	/* 	change->modif = 1; */
	/* } */
	/* if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0) */
	/* { */
	/* 	/1* printf("Translation RIGHT\n"); *1/ */
	/* 	change->translation_x += 5; */
	/* 	change->modif = 1; */
	/* } */
	if (wn->state[SDL_SCANCODE_Z] == 1 && old[SDL_SCANCODE_Z] == 0)
	{
		/* printf("Translation Z\n"); */
		change->translation_z += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_X] == 1 && old[SDL_SCANCODE_X] == 0)
	{
		/* printf("Translation X\n"); */
		change->translation_z -= 5;
		change->modif = 1;
	}
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
	change->translation_z = 0;

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


	change->v_camera.x = 0;
	change->v_camera.y = 0;
	change->v_camera.z = 0;
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

void		ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep)
{
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



	/* t_myvec v1, v2, v3; */

	/* v1.x = 0; */
	/* v1.y = 5; */
	/* v2.x = 0; */
	/* v2.y = 10; */
	/* v3.x = 0; */
	/* v3.y = 1; */
	/* printf(" =%f =%f =%f \n", v1.y, v2.y, v3.y); */
	/* ft_order_triangle_vertice(&v1, &v2, &v3); */
	/* ft_fill_triangle(&v1, &v2, &v3, s_win); */
	/* printf(" =%f =%f =%f \n", v1.y, v2.y, v3.y); */



	ft_init_launch_rasterization(&keep, &change);
	ft_launch_bsp_tree(s_win, wn);
	SDL_Init(SDL_INIT_EVERYTHING);
	s_win->current_window = J_EDITOR;
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
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
			ft_apply_modif(s_win, &change, &keep);
			if (change.display->panel == 1)
				ft_display_panel(s_win, &change);
			change.modif = 0;
			SDL_RenderPresent(s_win->renderer[J_EDITOR]);
		}
		SDL_Delay(1);
		setkeyboard(change.old, wn->state);
	}
}




