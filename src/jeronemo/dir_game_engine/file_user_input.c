/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:01:40 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 11:15:07 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

void	ft_keyboard_event_check(t_win *wn, Uint8 *old, t_myraster *raster)
{
	(void)old;
	if (wn->state[SDL_SCANCODE_ESCAPE])
	{
		raster->quit = TRUE;
		wn->interface = MENU;
		wn->menu->choice = 0;
	}
	if (wn->state[SDL_SCANCODE_UP] == 1/* && old[SDL_SCANCODE_UP] == 0*/)
	{
		raster->v_camera.y -= 1;   // a changer apres pour que ce soit clair que le y est inverser
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_DOWN] == 1 /*&& old[SDL_SCANCODE_DOWN] == 0*/)
	{
		raster->v_camera.y += 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_LEFT] == 1 /*&& old[SDL_SCANCODE_LEFT] == 0*/)
	{
		raster->v_camera.x -= 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_RIGHT] == 1/* && old[SDL_SCANCODE_RIGHT] == 0*/)
	{
		raster->v_camera.x += 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_A] == 1/* && old[SDL_SCANCODE_A] == 0*/)
	{
		raster->translate_right = 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_D] == 1/* && old[SDL_SCANCODE_D] == 0*/)
	{
		raster->translate_left = 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_W] == 1/* && old[SDL_SCANCODE_W] == 0*/)
	{
		raster->avancer = 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_S] == 1/* && old[SDL_SCANCODE_S] == 0*/)
	{
		raster->reculer = 1;
		raster->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0)
	{
		if (raster->leave_mouse == 1)
		{
			SDL_WarpMouseInWindow(wn->window, XSCREEN / 2, YSCREEN / 2);
			raster->leave_mouse = 0;
			wn->input->x = wn->xscreen / 2;
			wn->input->y = wn->yscreen / 2;
		}
		else
		{
			raster->leave_mouse = 1;
		}
	}
}

void		ft_mouse_event_check(t_win *wn, t_myraster *raster)
{
	(void)raster;
	//		printf("lalalala\n");
	if (!raster->leave_mouse)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2) ;
		(raster->theta_camera  += (wn->input->x - (wn->xscreen / 2)) / 10);
		(raster->pitch  += ((wn->input->y) - (wn->yscreen / 2) ) /10);
		//	raster->theta_camera += 1;
		//> 360
		//				? wn->player->rawx -= 360 : 0;
		//	(wn->player->rawy += (wn->input->y - (wn->yscreen / 2))) > YSCREEN
		//				? wn->player->rawy = YSCREEN : 0;
		//		raster->theta_camera += (wn->input->x - (wn->xscreen / 2)) ;
		raster->modif = 1;
	}
	else
		SDL_ShowCursor(SDL_ENABLE);
}

static void mouseconfig(t_win *wn)
  {
		SDL_ShowCursor(wn->interface != RGAME ? SDL_ENABLE : SDL_DISABLE);
			SDL_CaptureMouse(wn->interface == RGAME ? 1 : 0);
	wn->interface == RGAME
? SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2) : 0;
}

void	ft_input_event_check(t_win *wn, t_myraster *raster)
{
//	SDL_PollEvent(&(wn->ev));
//	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
//	wn->input->oldmouse = wn->input->mouse;
//	wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
	ft_keyboard_event_check(wn, raster->old, raster);
	ft_mouse_event_check(wn, raster);
	mouseconfig(wn);
}
