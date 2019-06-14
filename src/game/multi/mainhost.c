/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:44:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/14 15:14:18 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"

static void	initserv(t_server *server)
{
	ft_bzero((char *)&server->serv_addr, sizeof(server->serv_addr));
	server->port = 2424;
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
	server->serv_addr.sin_port = htons(server->port);
	server->user[0].name = NULL;
	server->user[1].name = NULL;
	server->user[2].name = NULL;
}

static void	listenclient(t_win *wn)
{
	t_server *server;

	server = malloc(sizeof(t_server));
	server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->sockfd < 0)
		return (perror("Open socket :"));
	initserv(server);
	if (bind(server->sockfd, (struct sockaddr *)&server->serv_addr, sizeof(server->serv_addr)) < 0)
		return (perror("Bind failed :"));
	listen(server->sockfd, 5);
	server->len = sizeof(server->user[0].cli_addr);
	server->newsockfd = accept(server->sockfd, (struct sockaddr *)&server->user[0].cli_addr, (socklen_t *)&server->len);
	if (server->newsockfd < 0 || server->len < 0)
		return (perror("Open New socket :"));
	server->user[0].name = ft_memalloc(sizeof(char) * 8);
	read(server->newsockfd, server->user[0].name, 8);
	printf("%s\n", server->user[0].name);
	wn->serv = server;
}

static void	inputhost(t_win *wn)
{
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MULTI : 0;
	key_pressed(wn, SDL_SCANCODE_ESCAPE) && wn->menu->connected == 0 ? pthread_kill((pthread_t)wn->menu->conv, 1) : 0;
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
}

static void	showhost(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Host2"), NULL, NULL);
}

static void	waiting(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Host"), NULL, NULL);
	SDL_RenderPresent(wn->rend);
}

static void	*find_connection(void *params)
{
	t_thread	*thd;
	t_win		*wn;

	thd = (t_thread *)params;
	wn = (t_win *)thd->wn;
	listenclient(wn);
	add_chat(wn);
	return (NULL);
}

static void host_threads(t_win *wn)
{
	t_thread	*thread;

	thread = malloc(sizeof(t_thread));
	thread->wn = wn;
	thread->value = 666;
	thread->file = NULL;
	wn->menu->conv = thread;
	pthread_create(&thread->thd, NULL, find_connection, (void *)thread);
	wn->menu->connected = 1;
}

void	mainhost(t_win *wn)
{
	char		*old;

	wn->serv == NULL && wn->menu->connected == 0 ? host_threads(wn) : 0;
	old = NULL;
	wn->serv == NULL && wn->menu->connected == 0 ? waiting(wn) : 0;
	wn->serv != NULL && wn->menu->connected != 0 ? printf("Connected : %s\n\t %s\n\t%s\n", ((t_server *)wn->serv)->user[0].name, ((t_server *)wn->serv)->user[1].name, ((t_server *)wn->serv)->user[2].name) : 0;
	if (!(wn->flag & CONSOLE))
		wn->flag += CONSOLE;
	inputhost(wn);
	showhost(wn);
}
