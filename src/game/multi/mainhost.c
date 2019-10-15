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

static t_server	*initserv(t_server *server)
{
	server = malloc(sizeof(t_server));
	server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->sockfd < 0)
		return (NULL);
	ft_bzero((char *)&server->serv_addr, sizeof(server->serv_addr));
	server->username = malloc(sizeof(char) * 8);
	getlogin_r(server->username, 8);
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

static void	freeserv(t_win *wn, t_server *server)
{
	int		freeserv;

	freeserv = 0;
	if (server)
	{
		if (((wn->menu->ask & 0x03) < 3) && ((wn->menu->ask & 0x0C) >> 2) < 3 && ((wn->menu->ask & 0x30) >> 4) < 3)
			freeserv = 1;
		server->user[0].name != NULL && (wn->menu->ask & 0x03) < 3 ? free(server->user[0].name) : 0;
		server->user[1].name != NULL && ((wn->menu->ask & 0x0C) >> 2) < 3 ? free(server->user[1].name) : 0;
		server->user[2].name != NULL && ((wn->menu->ask & 0x30) >> 4) < 3 ? free(server->user[2].name) : 0;
		if (freeserv)
		{
			free(server->username);
			free(server);
			wn->serv = NULL;
		}
	}
}

static void	listenclient(t_win *wn, int	user)
{
	t_server *server;

	server = (t_server *)wn->serv;
	listen(server->sockfd, 5);
	server->len = sizeof(server->user[user].cli_addr);
	server->user[user].socket = accept(server->sockfd, (struct sockaddr *)&server->user[user].cli_addr, (socklen_t *)&server->len);
	if (server->user[user].socket < 0 || server->len < 0)
		return (perror("Open New socket :"));
	server->user[user].name = ft_memalloc(sizeof(char) * 8);
	read(server->user[user].socket, server->user[user].name, 8);
	printf("TEST LISTEN CLIENT\n");
}

static void	inputhost(t_win *wn)
{
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MULTI : 0;
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? freeserv(wn, (t_server *)wn->serv) : 0;
	if ((wn->menu->ask & 0x03) == 1 || (wn->menu->ask & 0x03) == 2)
	{
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? pthread_kill((pthread_t)wn->menu->conv[0], 1) : 0;
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->ask = wn->menu->ask & (U_MAX - 0x03) : 0;
	}
	if ((wn->menu->ask & 0x0C) >> 2 == 1 || (wn->menu->ask & 0x0C) >> 2 == 2)
	{
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? pthread_kill((pthread_t)wn->menu->conv[1], 1) : 0;
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->ask = wn->menu->ask & (U_MAX - 0x0C) : 0;
	}
	if ((wn->menu->ask & 0x30) >> 4 == 1 || (wn->menu->ask & 0x30) >> 4  == 2)
	{
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? pthread_kill((pthread_t)wn->menu->conv[2], 1) : 0;
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->ask = wn->menu->ask & (U_MAX - 0x30) : 0;
	}
	//key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
	if ((wn->menu->ask & 0x03) == 0 && hitbox(wn->input->x, wn->input->y, create_rect(707, 338, 528, 114)) && mouse_pressed(wn, SDL_BUTTON_LEFT))
		wn->menu->ask += 1;
	if ((wn->menu->ask & 0x0C) == 0 && hitbox(wn->input->x, wn->input->y, create_rect(707, 622, 528, 114)) && mouse_pressed(wn, SDL_BUTTON_LEFT))
		wn->menu->ask += (1 << 2);
	if ((wn->menu->ask & 0x30) == 0 && hitbox(wn->input->x, wn->input->y, create_rect(707, 853, 528, 114)) && mouse_pressed(wn, SDL_BUTTON_LEFT))
		wn->menu->ask += (1 << 4);
}

static void	showhost(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Host"), NULL, NULL);
	if ((wn->menu->ask & 0x03) == 3)
		print_one_line(wn, ((t_server *)wn->serv)->user[0].name, 880, 380);
	else if ((wn->menu->ask & 0x03) == 1 || (wn->menu->ask & 0x03) == 2)
		print_one_line(wn, "Waiting", 880, 380);
	else
		print_one_line(wn, "Free slot", 880, 380);
	if (((wn->menu->ask & 0x0C) >> 2) == 3)
		print_one_line(wn, ((t_server *)wn->serv)->user[1].name, 880, 660);
	else if (((wn->menu->ask & 0x0C) >> 2) == 1 || ((wn->menu->ask & 0x0C) >> 2) == 2)
		print_one_line(wn, "Waiting...", 880, 660);
	else
		print_one_line(wn, "Free slot", 880, 660);
	if (((wn->menu->ask & 0x30) >> 4) == 3)
		print_one_line(wn, ((t_server *)wn->serv)->user[2].name, 880, 890);
	else if (((wn->menu->ask & 0x30) >> 4) == 1 || ((wn->menu->ask & 0x30) >> 4) == 2)
		print_one_line(wn, "Waiting...", 880, 890);
	else
		print_one_line(wn, "Free slot", 880, 890);
//	SDL_RenderFillRect(wn->rend, create_rect(wn->xscreen / 1.4, wn->yscreen >> 1, 50, 50));
//	SDL_RenderFillRect(wn->rend, create_rect(wn->xscreen / 1.4, wn->yscreen / 1.6, 50, 50));
//	SDL_RenderFillRect(wn->rend, create_rect(wn->xscreen / 1.4, wn->yscreen / 1.4, 50, 50));
}

static void	*find_connection(void *params)
{
	t_thread	*thd;
	t_win		*wn;

	thd = (t_thread *)params;
	wn = (t_win *)thd->wn;
	listenclient(wn, thd->value);
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
	wn->serv == NULL ? wn->serv = (t_server *)initserv((t_server *)wn->serv) : 0;
	if (wn->serv != NULL)
	{
		(wn->menu->ask & 0x03) == 1 ? host_threads(wn, 0) : 0;
		((wn->menu->ask & 0x0C) >> 2) == 1 ? host_threads(wn, 1) : 0;
		((wn->menu->ask & 0x30) >> 4) == 1 ? host_threads(wn, 2) : 0;
		if (!(wn->flag & CONSOLE))
			wn->flag += CONSOLE;
	}
	inputhost(wn);
	showhost(wn);
}
