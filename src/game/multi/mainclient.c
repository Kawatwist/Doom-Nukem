/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainclient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:44:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/13 09:02:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "client.h"
#include <arpa/inet.h>

static void	tryconnect(t_win *wn, char *ip, int port)
{
	t_client	client;
	
	client.port = port;
	client.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (client.sockfd < 0)
		return (perror("Socket not opened :"));
	client.server = gethostbyname(ip);
	ft_bzero((char *)&client.serv_addr, sizeof(client.serv_addr));
	client.serv_addr.sin_family = AF_INET;
	ft_strncpy((char *)client.server->h_addr, (char *)&(client.serv_addr.sin_addr.s_addr), client.server->h_length);
	client.serv_addr.sin_port = htons(client.port);
	SDL_Delay(200);
	printf("Try to connect\n");
	if (connect(client.sockfd, (struct sockaddr *)&client.serv_addr, sizeof(client.serv_addr)) < 0)
		return (perror("Can't connect to the server : "));
	printf("Connected");
	SDL_Delay(200);
	write(client.sockfd, "Test", 4);
	wn->client = &client;
}

static int	inputclient(t_win *wn, int	select)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MULTI : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_UP) && select > 1 ? select -= 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_DOWN) && select < 3 ? select += 1 : 0;
	return (select);
}

static void	showclient(t_win *wn)
{
	wn->client == NULL ? SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Client"), NULL, NULL) : 0;
	wn->client != NULL ? SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Client2"), NULL, NULL) : 0;
}

void		mainclient(t_win *wn)
{
	static char *ip = "10.13.9.5";
	static char *port = "4242";
	static int	select = 1;

	if (select == 1)
		ip = text_box(wn, ip);
	else if (select == 2)
		port = text_box(wn, port);
	select = inputclient(wn, select);
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_RETURN) && select == 3 && wn->client == NULL? tryconnect(wn, ip, ft_atoi(port)) : 0;
	showclient(wn);
	if (wn->client == NULL)
	{
		printf("IP : %s\n", ip);
		printf("PORT : %s\n", port);
	}
}
