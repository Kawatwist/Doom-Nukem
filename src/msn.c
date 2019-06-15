/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:55:16 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/15 11:41:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static char *removemsg(char *msg)
{
	int		len;
	int		len2;
	char	*ret;

	len = ft_strlen(msg);
	len2 = len - ft_strlen(ft_strchr(msg, ']')) + 1;
	ret = malloc(sizeof(char) * len - 3);
	ft_memcpy(ret, msg, len2);
	ft_memcpy(&ret[len2], &msg[len2 + 5], len - (len2 + 4));
	ret[len - 4] = '\0';
	free(msg);
	return(ret);
}

static char	*convmsg(char *msg)
{
	int		i;
	int		nb;
	char	*ret;

	i = -1;
	nb = 0;
	while (msg[++i])
		msg[i] != -66 ? nb++ : 0;
	ret = malloc(sizeof(char) * nb + 1);
	i = -1;
	nb = 0;
	while (msg[++i])
	{
		if (msg[i] != -66)
		{
			ret[nb] = msg[i];
			nb++;
		}
	}
	ret[nb] = '\0';
	return (ret);
}

void		add_chat(t_win *wn)
{
	char *msg;
	int	len;
	
	while (TRUE)
	{
		msg = NULL;
		len = 0;
		msg = (wn->serv == NULL ? get_msg_client(wn) : get_msg_server(wn));
		msg = convmsg(msg);
		len = ft_strlen(msg) - ft_strlen(ft_strchr(msg, ']')) + 2;
		if (ft_strncmp(&msg[len], "/msg", 3))
		{
			free(msg);
			msg = NULL;
		}
		else
			msg = removemsg(msg);
		if (wn->console->index < CONSOLE_MAX_LINE_NB && msg != NULL)
		{
			wn->console->history[wn->console->index] = ft_strdup(msg);
			wn->console->index++;
		}
		else if (msg != NULL)
		{
			free(wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB]);
			wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB] = NULL;
			wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB] = ft_strdup(msg);
			wn->console->index++;
		}
	}
}

int			chat_box(t_win *wn, char *msg)
{
	if (ft_strlen(msg) <= 4)
		return (0);
	wn->serv == NULL && key_pressed(wn, SDL_SCANCODE_RETURN) ? send_msg_from_client(wn, msg) : send_msg_from_server(wn, msg);
	if (ft_strncmp(msg, "/msg", 4))
		return (0);
	return (1);
}
