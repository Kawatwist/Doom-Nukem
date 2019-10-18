/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:44:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/09 16:56:51 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"

void			freeserv(t_win *wn, t_server *server)
{
	int		freeserv;

	freeserv = 0;
	if (server)
	{
		if (((wn->menu->ask & 0x03) < 3)
			&& ((wn->menu->ask & 0x0C) >> 2) < 3
			&& ((wn->menu->ask & 0x30) >> 4) < 3)
			freeserv = 1;
		server->user[0].name != NULL
			&& (wn->menu->ask & 0x03) < 3 ? free(server->user[0].name) : 0;
		server->user[1].name != NULL
			&& ((wn->menu->ask & 0x0C) >> 2) < 3 ? free(server->user[1].name) : 0;
		server->user[2].name != NULL
			&& ((wn->menu->ask & 0x30) >> 4) < 3 ? free(server->user[2].name) : 0;
		if (freeserv)
		{
			close(server->sockfd);
			free(server->username);
			free(server);
			wn->serv = NULL;
		}
	}
}

static t_server	*initserv(t_server *server)
{
	server = malloc(sizeof(t_server));
	server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->sockfd < 0)
		return (NULL);
	ft_bzero((char *)&server->serv_addr, sizeof(server->serv_addr));
	server->username = malloc(sizeof(char) * 8);
	if ((getlogin_r(server->username, 8)) == 0)
		printf("OK\n");
	printf("SERVER NAME = %s\n", server->username);
	server->port = 4242;
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
	server->serv_addr.sin_port = htons(server->port);
	if (bind(server->sockfd, (struct sockaddr *)&server->serv_addr, sizeof(server->serv_addr)) < 0)
		return (NULL);
	server->user[0].name = NULL;
	server->user[1].name = NULL;
	server->user[2].name = NULL;
	return (server);
}

static int	listenclient(t_win *wn, int	user)
{
	t_server *server;

	server = (t_server *)wn->serv;
	listen(server->sockfd, 5);
	server->len = sizeof(server->user[user].cli_addr);
	server->user[user].socket = accept(server->sockfd, (struct sockaddr *)&server->user[user].cli_addr, (socklen_t *)&server->len);
	if (server->user[user].socket < 0 || server->len < 0)
	{
		perror("Open New socket :");
		return (-1);
	}
	server->user[user].name = ft_memalloc(sizeof(char) * 8);
	read(server->user[user].socket, server->user[user].name, 8);
	return (0);
}

static void	*find_connection(void *params)
{
	t_thread	*thd;
	t_win		*wn;

	thd = (t_thread *)params;
	wn = (t_win *)thd->wn;
	if (listenclient(wn, thd->value) == -1)
		return (NULL);
	if (thd->value == 0)
		wn->menu->ask += 1;
	else if (thd->value == 1)
		wn->menu->ask += (1 << 2);
	else
		wn->menu->ask += (1 << 4);
	add_chat(wn, thd->value);
	return (NULL);
}

static void host_threads(t_win *wn, int user)
{
	t_thread	*thread;

	if (user == 0)
		wn->menu->ask += 1;
	else if (user == 1)
		wn->menu->ask += (1 << 2);
	else
		wn->menu->ask += (1 << 4);
	thread = malloc(sizeof(t_thread));
	thread->wn = wn;
	thread->value = user;
	thread->file = NULL;
	wn->menu->conv[user] = thread;
	pthread_create(&thread->thd, NULL, find_connection, (void *)thread);
}

void	mainhost(t_win *wn)
{
	(wn->serv == NULL) ? wn->serv = (t_server *)initserv((t_server *)wn->serv) : 0;
	if (wn->serv != NULL)
	{
		((wn->menu->ask & 0x03) == 1) ? host_threads(wn, 0) : 0;
		((wn->menu->ask & 0x0C) >> 2) == 1 ? host_threads(wn, 1) : 0;
		((wn->menu->ask & 0x30) >> 4) == 1 ? host_threads(wn, 2) : 0;
		if (!(wn->flag & CONSOLE))
			wn->flag += CONSOLE;
	}
	inputhost(wn);
	showhost(wn);
}
