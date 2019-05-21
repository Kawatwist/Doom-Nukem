/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_input_and_read.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:00:23 by jleblond          #+#    #+#             */
/*   Updated: 2019/05/19 18:00:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void stock_in_history(t_win *wn, char *command)
{
	if (wn->console->index < CONSOLE_MAX_LINE_NB)
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

static char	*readcommand(t_win *wn, char *command)
{
	if(ft_strcmp(command, "kill") == 0)
		stop_exec("KILL !\n", wn);
	else if (ft_strcmp(command, "slow") == 0)
		wn->debugcine *= -1;
	else if(ft_strcmp(command, "fs") == 0)
		wn->full_screen *= -1;
	else if(ft_strncmp(command, "value", 5) == 0 && ft_strlen(command) > 5)
		wn->debugconsole = ft_atoi(&(command[5]));
	else if (ft_strncmp(command, "sky", 3) == 0 && ft_strlen(command) > 3)
		wn->sky = ft_atoi(&(command[3]));
	else
		command = ft_strjoinfree(command, ft_strdup(" *Invalid command"), 3);
	return (command);
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

void	inputconsole(t_win *wn)
{
	static char		*command = NULL;

	command = printable_input(wn, command);
	if ((key_pressed(wn, SDL_SCANCODE_BACKSPACE)) && command != NULL && ft_strlen(command))
		command[ft_strlen(command) - 1] = 0;
	if (key_pressed(wn, SDL_SCANCODE_UP) && wn->console->index > 0)
	{
		command = ft_strdup(wn->console->history[wn->console->index - 1]);
		if (ft_strchrlen(command, '*') != -1)
			command[ft_strchrlen(command, '*') - 1] = 0;
	}
	if ((command != NULL) && ft_strlen(command))
		print_command(wn, command, 35, wn->yscreen - ARIEL_FONT_SIZE);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE))
		 wn->debug *= -1;
	if (key_pressed(wn, SDL_SCANCODE_RETURN) && command != NULL)
	{
		command = readcommand(wn, command);
		stock_in_history(wn, command);
		free(command);
		command = NULL;
	}
}
