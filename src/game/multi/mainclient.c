/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainclient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:44:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/17 15:54:59 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "client.h"
#include <arpa/inet.h>

static void ft_bcopy(const void *src, void *dst, size_t len)
{
	ft_memmove(dst, src, len);
}

static int	checkstr(char *ip, int port)
{
	if (ip == NULL || port == 0)
		return (1);
	while (ip++ && *ip)
		if ((*ip != '.' && *ip < '0') || *ip > '9')
			return (1);
	if (port < 1000)
		return (1);
	return (0);
}

static void	tryconnect(t_win *wn, char *ip, int port)
{
	t_client	*client;

	if (checkstr(ip, port))
		return ;
	client = malloc(sizeof(t_client));
	client->username = malloc(sizeof(char) * 8);
	getlogin_r(client->username, 8);
	client->username == NULL ? client->username = ft_strdup("NULL") : 0;
	client->port = port;
	client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (client->sockfd < 0)
		return (perror("Socket not opened :"));
	client->server = gethostbyname(ip);
	ft_bzero((char *)&client->serv_addr, sizeof(client->serv_addr));
	client->serv_addr.sin_family = AF_INET;
	ft_bcopy((void *)client->server->h_addr, (void *)&(client->serv_addr.sin_addr.s_addr), (size_t)client->server->h_length);
	client->serv_addr.sin_port = htons(client->port);
	if (connect(client->sockfd, (struct sockaddr *)&client->serv_addr, sizeof(client->serv_addr)) < 0)
		return (perror("Can't connect to the server : "));
	write(client->sockfd, client->username, ft_strlen(client->username));
	wn->client = client;
	wn->menu->connected = 1;
}

static int	inputclient(t_win *wn, int	select, char *ip, char *port)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MULTI : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_UP) && select > 1 ? select -= 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_DOWN) && select < 3 ? select += 1 : 0;
//	key_pressed(wn, SDL_SCANCODE_RETURN) && select == 3 && wn->client == NULL && port != NULL && ip != NULL ? tryconnect(wn, ip, ft_atoi(port)) : 0;
	key_pressed(wn, SDL_SCANCODE_RETURN) && select == 3 && wn->client == NULL && port != NULL && ip != NULL ? wn->menu->connected = 1 : 0;
//	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 0 : 0;
//	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MENU : 0;
	return (select);
}

static void	showclient(t_win *wn, char *ip, char *port)
{
	wn->client == NULL ? SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Client"), NULL, NULL) : 0;
	wn->client != NULL ? SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Client2"), NULL, NULL) : 0;
	ip != NULL && ft_strlen(ip) && wn->client == NULL ? print_one_line(wn, ip, (wn->xscreen >> 1) - ((ft_strlen(ip) >> 1) * 10), wn->yscreen >> 1) : 0;
	port != NULL && ft_strlen(port) && wn->client == NULL ? print_one_line(wn, port, (wn->xscreen >> 1) - ((ft_strlen(port) >> 1) * 10), (wn->yscreen / 3) << 1) : 0;

static void	*msn_client(void *params)
{
	t_thread	*thd;
	t_win		*wn;
	char		*ip;
	int			port;

	thd = (t_thread *)params;
	wn = (t_win *)thd->wn;
	ip = thd->str;
	port = thd->value;
	tryconnect(wn, ip, port);
	while (TRUE)
		add_chat(wn, 0);
	return (NULL);
}

static void	client_threads(t_win *wn, char *ip, int port)
{
	t_thread	*thread;

	thread = malloc(sizeof(t_thread));
	thread->wn = wn;
	thread->str = ip;
	thread->value = port;
	thread->file = NULL;
	wn->menu->conv[0] = thread;
	pthread_create(&thread->thd, NULL, msn_client, (void *)thread);
}

void		mainclient(t_win *wn)
{
	static char *ip = NULL;
	static char *port = NULL;
	static int	select = 1;
	static Uint32		time = 0;
	static Uint32		difftime = 0;

	if (wn->menu->connected == 1)
	{
		time = SDL_GetTicks();
		client_threads(wn, ip, ft_atoi(port));
		wn->menu->connected = 2;
	}
	if (select == 1)
		ip = text_box(wn, ip);
	else if (select == 2)
		port = text_box(wn, port);
	select = inputclient(wn, select, ip, port);
	showclient(wn, ip ,port);
	difftime = SDL_GetTicks();
	if (difftime - time > TIMEOUT && wn->menu->connected == 2)
	{
		pthread_kill((pthread_t)wn->menu->conv[0], 1);
		print_one_line(wn, "Timeout", (wn->xscreen >> 1) - ((ft_strlen(ip) >> 1) * 10), (wn->yscreen >> 2) * 3);
		wn->menu->connected = 0;
	}
}
