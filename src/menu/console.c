/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:19:22 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/12 15:36:13 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	readcommand(t_win *wn)
{
	ft_strcmp(wn->command, "kill") == 0 ? stop_exec("KILL !\n", wn) : 0;
	ft_strcmp(wn->command, "slow") == 0 ? wn->debugcine *= -1 : 0;
	ft_strcmp(wn->command, "fs") == 0 ? full_screen(wn) : 0;
	ft_strncmp(wn->command, "value", 5) == 0
		&& ft_strlen(wn->command) > 5
		? wn->debugconsole = ft_atoi(&(wn->command[5])) : 0;
	ft_strncmp(wn->command, "sky", 3) == 0
		&& ft_strlen(wn->command) > 3
		? wn->sky = ft_atoi(&(wn->command[3])) : 0;
	free(wn->command);
	wn->command = NULL;
}

static void	historyconsole(t_win *wn)
{
	static char **history = NULL;


	(void)history;
	(void)wn;
}

void	sub_print_command(t_win *wn, SDL_Texture *texture, int len)
{
	int				tex_width;
	int				tex_height;
	SDL_Rect		position;

	tex_width = 0;
	tex_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &tex_width, &tex_height);
	position.x = 35;
	position.y = YSCREEN - 70;
	position.w = 20 * len;
 	position.h = 20;
	SDL_RenderCopy(wn->rend, texture, NULL, &position);
}

static void		print_command(t_win *wn, char *s)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	TTF_Font		*font;

	font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 35);  //init font outside the loop later
	if (font == NULL)
		stop_exec("TTF_OpenFont()failed", wn);
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = SDL_ALPHA_OPAQUE;
	surface = TTF_RenderText_Solid(font, s, color);
	if (surface == NULL)
		stop_exec("TTF_RenderText()failed", wn);
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	if (texture == NULL)
		stop_exec("SDL_CreateTextureFromSurface()failed", wn);
	SDL_FreeSurface(surface);
	sub_print_command(wn, texture, ft_strlen(s));
	TTF_CloseFont(font); // relocate it outside the loop
}


static char	printable_key_check(int i)
{
	if ((i >= SDL_SCANCODE_A) && (i <= SDL_SCANCODE_Z))
		return (i - SDL_SCANCODE_A + 'a');
	else if ((i >= SDL_SCANCODE_1) && (i <= SDL_SCANCODE_9))
		return (i - SDL_SCANCODE_1 + '1');
	else if ((i >= SDL_SCANCODE_KP_1) && (i <= SDL_SCANCODE_KP_9))
		return (i - SDL_SCANCODE_KP_1 + '1');
	else if ( i == SDL_SCANCODE_SPACE)
		return (' ');
	else if (i == SDL_SCANCODE_0)
		return ('0');
	else if (i == SDL_SCANCODE_KP_0)
		return ('0');
	else
		return (INVALID);
}

static int	 key_pressed(t_win *wn, int key_value)
{
	if (wn->state[key_value] && !(wn->old[key_value]))
		return (TRUE);
	return (FALSE);
}

static char *printable_input(t_win *wn, char *command)
{
	int				i;
	char			str[2];
	char			key_val;

	i = 0;
	key_val = 0;
	while (i <= 98)
	{
		if (key_pressed(wn, i) == TRUE)
		{
			key_val = printable_key_check(i);
			if (key_val != INVALID)
			{
				str[0] = key_val;
				str[1] = '\0';
				if (command == NULL)
					command = ft_strdup(str);
				else
					command = ft_strjoinfree(command, ft_strdup(str), 3);
			}
		}
		i++;
	}
	return (command);
}

static void	inputconsole(t_win *wn)
{
	static char		*command = NULL;

	command = printable_input(wn, command);
	if ((key_pressed(wn, SDL_SCANCODE_BACKSPACE) == TRUE) &&  command != NULL && ft_strlen(command))
		command[ft_strlen(command) - 1] = 0;
	if ((command != NULL) && ft_strlen(command))
		print_command(wn, command);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE) == TRUE)
		 wn->debug *= -1;
	if (key_pressed(wn, SDL_SCANCODE_RETURN) == TRUE && command != NULL)
	{
		wn->command = ft_strdup(command);
		free(command);
		command = NULL;
	}
}

static void	showconsole(t_win *wn)
{
	SDL_Rect	bg;

	if (wn->xscreen > 300)
	{
		bg.x = 0;
		bg.y = wn->yscreen - 500;
		bg.w = 600;
		bg.h = 500;
		SDL_SetRenderDrawColor(wn->rend, 50, 50, 50, 0);
		SDL_RenderFillRect(wn->rend, &bg);
		bg.x = 30;
		bg.y = wn->yscreen - 70;
		bg.w = 540;
		bg.h = 30;
		SDL_SetRenderDrawColor(wn->rend, 150, 150, 150, 0);
		SDL_RenderFillRect(wn->rend, &bg);
	}
}

void		mainconsole(t_win *wn)
{
	showconsole(wn);
	inputconsole(wn);
	if (wn->command && wn->command != NULL)
		readcommand(wn);
	historyconsole(wn);
}
