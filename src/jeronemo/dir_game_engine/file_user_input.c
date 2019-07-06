/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:01:40 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/06 13:16:58 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>



void	ft_keyboard_event_check(t_win *wn, Uint8 *old, t_mychange *change, t_myraster *raster)
{
(void)old;
	/* change->v_forward = ft_vector_multiply(change->v_look_dir, 2.0); */
	if (wn->state[SDL_SCANCODE_ESCAPE])
		change->quit = TRUE;


	if (wn->state[SDL_SCANCODE_UP] == 1/* && old[SDL_SCANCODE_UP] == 0*/)
	{
		printf("Fleche Haut => on increment camera y\n");
		raster->v_camera.y -= 1;   // a changer apres pour que ce soit clair que le y est inverser  
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_DOWN] == 1 /*&& old[SDL_SCANCODE_DOWN] == 0*/)
	{
		printf("Fleche Haut => on decrement camera y\n");
		raster->v_camera.y += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_LEFT] == 1 /*&& old[SDL_SCANCODE_LEFT] == 0*/)
	{
		printf("Fleche Gauche => on decrement camera x\n");
		raster->v_camera.x -= 2;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_RIGHT] == 1/* && old[SDL_SCANCODE_RIGHT] == 0*/)
	{
		printf("Fleche Droite => on increment camera x\n");
		raster->v_camera.x += 2;
		change->modif = 1;
	}

	if (wn->state[SDL_SCANCODE_A] == 1/* && old[SDL_SCANCODE_A] == 0*/)
	{
		raster->theta_camera += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_D] == 1/* && old[SDL_SCANCODE_D] == 0*/)
	{
		raster->theta_camera -= 1;
		change->modif = 1;
	}


	if (wn->state[SDL_SCANCODE_W] == 1/* && old[SDL_SCANCODE_W] == 0*/)
	{
		/* change->v_forward = ft_vector_multiply(change->v_look_dir, 2.0); */

		printf("On incremente du vecteur forward\n");
		/* change->v_camera = ft_vector_add(change->v_camera, change->v_forward); */
		change->avancer = 1;
		raster->avancer = 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_S] == 1/* && old[SDL_SCANCODE_S] == 0*/)
	{
		/* change->v_forward = ft_vector_multiply(change->v_look_dir, 2.0); */
		change->reculer = 1;
		raster->reculer = 1;

		printf("On decremente du vecteur forward\n");
		/* change->v_camera = ft_vector_sub(change->v_forward, change->v_camera); */
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

void		ft_mouse_event_check(t_win *wn, t_mychange *change)
{
	(void)change;
	if ((wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) && ((wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT)) == 0)  )
		;
}

void	ft_input_event_check(t_win *wn, t_mychange *change, t_myraster *raster)
{
	SDL_PollEvent(&(wn->ev));
	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
	/* wn->input->oldmouse = wn->input->mouse; */
	/* wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y); */
	ft_keyboard_event_check(wn, change->old, change, raster);
	/* ft_mouse_event_check(wn, change); */
}
