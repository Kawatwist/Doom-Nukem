/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 13:22:42 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/20 17:26:06 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

void	stop_com(t_win *wn, int user)
{
	int		i;

	i = 1;
	if (wn->serv && wn->serv != NULL)
	{
		setsockopt(((t_server *)wn->serv)->user[user].socket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));
		shutdown(((t_server *)wn->serv)->user[user].socket, 2);
		wn->menu->ask = wn->menu->ask & (U_MAX - (3 << (user * 2)));
	}
	if (wn->serv && wn->client != NULL)
	{
		setsockopt(((t_client *)wn->client)->sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));
		shutdown(((t_client *)wn->client)->sockfd, 2);
		wn->menu->connected = 0;
	}
	pthread_kill((pthread_t)wn->menu->conv[0], 1);
}
