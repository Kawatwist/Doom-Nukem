/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:44:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/13 08:58:25 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"

static void	initserv(t_server *server)
{
	ft_bzero((char *)&server->serv_addr, sizeof(server->serv_addr));
	server->port = 4242;
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
	server->serv_addr.sin_port = htons(server->port);
}

static void	listenclient(t_win *wn)
{
	t_server server;
	char buffer[256];

	server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server.sockfd < 0)
		return (perror("Open socket :"));
	initserv(&server);
	if (bind(server.sockfd, (struct sockaddr *)&server.serv_addr, sizeof(server.serv_addr)) < 0)
		return (perror("Bind failed :"));
	listen(server.sockfd, 5);
	server.len = sizeof(server.cli_addr);
	server.newsockfd = accept(server.sockfd, (struct sockaddr *)&server.cli_addr, (socklen_t *)&server.len);
	if (server.newsockfd < 0 || server.len < 0)
		return (perror("Open New socket :"));
	ft_bzero(buffer, 256);
	read(server.newsockfd, buffer, 6);
	printf("%s\n", buffer);
	wn->serv = &server;
}

static void	inputhost(t_win *wn)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MULTI : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
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

void	mainhost(t_win *wn)
{
	wn->serv == NULL ? waiting(wn) : 0;
	wn->serv == NULL ? listenclient(wn) : 0;
	inputhost(wn);
	showhost(wn);
}
