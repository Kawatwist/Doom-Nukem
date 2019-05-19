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

static void	readcommand(t_win *wn, char *command)
{
	ft_strcmp(command, "kill") == 0 ? stop_exec("KILL !\n", wn) : 0;
	ft_strcmp(command, "slow") == 0 ? wn->debugcine *= -1 : 0;
	ft_strcmp(command, "fs") == 0 ? wn->full_screen *= -1 : 0;
	ft_strncmp(command, "value", 5) == 0
		&& ft_strlen(command) > 5
		? wn->debugconsole = ft_atoi(&(command[5])) : 0;
	ft_strncmp(command, "sky", 3) == 0
		&& ft_strlen(command) > 3
		? wn->sky = ft_atoi(&(command[3])) : 0;
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

static char *printable_input(t_win *wn, char *command)
{
	int				i;
	char			str[2];
	char			key_val;

	i = 0;
	key_val = 0;
	while (i <= 98)
	{
		if (key_pressed(wn, i))
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

static void stock_in_history(t_win *wn, char *command)
{
	if (wn->console->index <= CONSOLE_MAX_LINE_NB)
	{
		wn->console->history[wn->console->index] = ft_strdup(command);
		wn->console->index++;
	}
	else
	{
		free(wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB]);
		wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB] = NULL;
		wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB] = ft_strdup(command);
		wn->console->index++;
	}

}

static void	showconsole(t_win *wn)
{
	SDL_Rect	bg;

	if (wn->xscreen > 300)
	{
		bg.w = 600;
		bg.h = ARIEL_FONT_SIZE * (CONSOLE_MAX_LINE_NB + 1);
		bg.x = 0;
		bg.y = wn->yscreen - bg.h;
		SDL_SetRenderDrawColor(wn->rend, 50, 50, 50, 0);
		SDL_RenderFillRect(wn->rend, &bg);
		bg.w = 600;
		bg.h = ARIEL_FONT_SIZE;
		bg.x = 0;
		bg.y = wn->yscreen - bg.h;
		SDL_SetRenderDrawColor(wn->rend, 100, 100, 100, 0);
		SDL_RenderFillRect(wn->rend, &bg);
	}
}


void			print_text_with_ariel_font(t_win *wn, char *s, SDL_Color color, SDL_Rect position)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Solid(wn->fonts->ariel, s, color);
	if (surface == NULL)
		stop_exec("TTF_RenderText()failed", wn);
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	if (texture == NULL)
		stop_exec("SDL_CreateTextureFromSurface()failed", wn);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(wn->rend, texture, NULL, &position);
}

static void		print_one_line(t_win *wn, char *s, int posi_x, int posi_y)
{
	SDL_Color		color;
	int				w;
	int				h;
	SDL_Rect		position;


	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = SDL_ALPHA_OPAQUE;
	TTF_SizeText(wn->fonts->ariel, s, &w, &h);
	position.x = posi_x;
	position.y = posi_y;
	// position.w = w < XSCREEN / 4 ? w : 200;
	position.w = w - 5;
 	position.h = h - 5;
	print_text_with_ariel_font(wn, s, color, position);
}


static void		print_command(t_win *wn, char *s, int posi_x, int posi_y)
{
	SDL_Color		color;
	int				w;
	int				h;
	SDL_Rect		position;


	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = SDL_ALPHA_OPAQUE;
	TTF_SizeText(wn->fonts->ariel, s, &w, &h);
	position.x = posi_x;
	position.y = posi_y - 5;
	// position.w = w < XSCREEN / 4 ? w : 200;
	position.w = w;
 	position.h = h;
	print_text_with_ariel_font(wn, s, color, position);
}

static void	print_console_history(t_win *wn)
{
	int		i;
	int		count;

	count = 1;
	i = (wn->console->index  - 1);
	if (wn->console->index == 0)
		return ;
	while (i  >= 0)
	{
		print_one_line(wn, wn->console->history[i % CONSOLE_MAX_LINE_NB], 35, wn->yscreen - (count + 1) * ARIEL_FONT_SIZE);
		i--;
		count++;
		if (count > CONSOLE_MAX_LINE_NB)
			break;
	}
}

static void	inputconsole(t_win *wn)
{
	static char		*command = NULL;

	command = printable_input(wn, command);
	if ((key_pressed(wn, SDL_SCANCODE_BACKSPACE)) && command != NULL && ft_strlen(command))
		command[ft_strlen(command) - 1] = 0;
	if ((command != NULL) && ft_strlen(command))
		print_command(wn, command, 35, wn->yscreen - ARIEL_FONT_SIZE);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE))
		 wn->debug *= -1;
	if (key_pressed(wn, SDL_SCANCODE_RETURN) && command != NULL)
	{
		stock_in_history(wn, command);
		readcommand(wn, command);
		free(command);
		command = NULL;
	}
}

void		mainconsole(t_win *wn)
{
	showconsole(wn);
	inputconsole(wn);
	print_console_history(wn);
}
