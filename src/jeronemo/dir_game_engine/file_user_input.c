/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:01:40 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/21 10:15:39 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_myraster	*ft_keyboard_event_check(t_win *wn, t_myraster *raster)
{
	if (wn->state[SDL_SCANCODE_ESCAPE])
	{
		printf("ESCAPE PRESSED\n");
		raster->quit = TRUE;
		wn->interface = MGAME;
		wn->menu->choice = 10;
	}
	if (key_pressed(wn, SDL_SCANCODE_SPACE) && wn->interface == RGAME)
		wn->interface = DGAME;
	else if (key_pressed(wn, SDL_SCANCODE_SPACE))
		wn->interface = RGAME;
	if (wn->state[SDL_SCANCODE_UP])
		raster->v_camera.y -= 1;   // a changer apres pour que ce soit clair que le y est inverser
	if (wn->state[SDL_SCANCODE_DOWN])
		raster->v_camera.y += 1;
	if (wn->state[SDL_SCANCODE_LEFT])
		raster->v_camera.x -= 1;
	if (wn->state[SDL_SCANCODE_RIGHT])
		raster->v_camera.x += 1;
	if (wn->state[SDL_SCANCODE_A])
		raster->translate_right = 1;
	if (wn->state[SDL_SCANCODE_D])
		raster->translate_left = 1;
	if (wn->state[SDL_SCANCODE_W])
		raster->avancer = 1;
	if (wn->state[SDL_SCANCODE_S])
		raster->reculer = 1;
	if (wn->state[SDL_SCANCODE_S] || wn->state[SDL_SCANCODE_W] || wn->state[SDL_SCANCODE_D]
			|| wn->state[SDL_SCANCODE_A] || wn->state[SDL_SCANCODE_RIGHT]
			|| wn->state[SDL_SCANCODE_LEFT] || wn->state[SDL_SCANCODE_DOWN]
			|| wn->state[SDL_SCANCODE_UP])
		raster->modif = 1;
	if (wn->state[SDL_SCANCODE_U] && !wn->old[SDL_SCANCODE_U])
	{
		if (raster->leave_mouse)
		{
			wn->input->x = wn->xscreen / 2;
			wn->input->y = wn->yscreen / 2;
			SDL_WarpMouseInWindow(wn->window, wn->input->x, wn->input->y);
			raster->leave_mouse = 0;
		}
		else
			raster->leave_mouse = 1;
	}
	if (key_pressed(wn, SDL_SCANCODE_B))
	{
		if (raster->debug == 1)
		{
			raster->debug = 0;
		}
		else
		{
			raster->debug = 1;
		}
	}
	return (raster);
}


t_myraster	*ft_mouse_event_check(t_win *wn, t_myraster *raster)
{
	if ((wn->interface == RGAME || wn->interface == DGAME) && !((t_myraster*)wn->rasterizer->tmp)->leave_mouse)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_CaptureMouse(SDL_ENABLE);
		raster->theta_camera += ((wn->input->x - (wn->xscreen / 2)) / 10);
		raster->pitch  = (((wn->yscreen / 2) - (wn->input->y)) / 10) + raster->pitch > 90 ? 90 : raster->pitch + (((wn->yscreen >> 1) - wn->input->y) / 10);
		raster->pitch < -90 ? raster->pitch = -90 : 0;
		SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2);
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_CaptureMouse(SDL_DISABLE);
	}
	if (((wn->input->x - (wn->xscreen >> 1)) || (wn->input->y - (wn->yscreen >> 1))) && !((t_myraster*)wn->rasterizer->tmp)->leave_mouse)
		 raster->modif = 1;
	return (raster);
}

t_myraster	*ft_input_event_check(t_win *wn, t_myraster *raster)
{
	raster = ft_keyboard_event_check(wn, raster);
	raster = ft_mouse_event_check(wn, raster);
	return(raster);
}
