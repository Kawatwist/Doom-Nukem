/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:10:40 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/29 03:22:30 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "tga_reader.h"

void		showlinkedlist(t_win **wn, char *type, char *subtype)
{
	t_text *curr;

	curr = (*wn)->texture;
	printf("FIND %s | %s\n", type, subtype);
	while (curr->next_type != NULL && ft_strcmp(curr->type, type) != 0)
	{
		curr = curr->next_type;
		printf("=========TYPE=============\n");
		printf("%s->", curr->type);
		printf("%s->", curr->subtype);
		printf("%s\n", curr->name);
		printf("==========TYPE============\n");
		if (curr == NULL || curr->name == NULL)
			break ;
	}
	while (curr->next_subtype != NULL && ft_strcmp(curr->subtype, subtype) != 0)
	{
		printf("=======================\n");
		printf("%s->", curr->type);
		printf("%s->", curr->subtype);
		printf("%s\n", curr->name);
		printf("=======================\n");
		curr = curr->next_subtype;
		if (curr == NULL || curr->name == NULL)
			break ;
	}
	printf("\n");
	printf("FINAL TYPE=\t%s\n", curr->type);
	printf("FINAL SUBTYPE=\t%s\n", curr->subtype);
	while (curr->next != NULL)
	{
		printf("%s\n", curr->name);
		curr = curr->next;
	}
	printf("last = %s\n", curr->name);
	printf("\nEND OF FIND\t====================\n");
}

SDL_Texture	*initload2(t_win **wn, const char *path)
{
	t_tga		*tga;
	SDL_Surface	*surface;
	SDL_Texture	*txt;

	txt = NULL;
	if ((tga = load_tga(path)) == NULL)
	{
		free_tga(tga);
		stop_exec("Fail to load texture", *wn);
	}
	else
	{
		surface = SDL_CreateRGBSurfaceWithFormatFrom(tga->data,
				tga->w, tga->h, 32, 4 * tga->w, SDL_PIXELFORMAT_ARGB32);
		txt = SDL_CreateTextureFromSurface((*wn)->rend, surface);
		free_tga(tga);
	}
	return (txt);
}

static int	tga_to_txt(t_tga *tga, t_win *wn, t_text *txt)
{
	tga->surface = SDL_CreateRGBSurfaceWithFormatFrom(tga->data,
			tga->w, tga->h, 32, 4 * tga->w, SDL_PIXELFORMAT_ARGB32);
	if (tga->surface != NULL)
		txt->txt = SDL_CreateTextureFromSurface(wn->rend, tga->surface);
	else
	{
		free(txt->name);
		free(txt->subtype);
		free(txt->type);
		txt = NULL;
	}
	SDL_FreeSurface(tga->surface);
	return(0);
}

int			add_tga(t_win *wn, void *tga, char *path)
{
	char	*type;
	char	*subtype;
	char	*name;
	t_text	*pos;

	tga = (t_tga *)tga;
	if (!ft_strncmp("option\0", &path[16], ft_strchrlen(&path[16], '/')))
		type = ft_strdup("option\0");
	else if (!ft_strncmp("editor\0", &path[16], ft_strchrlen(&path[16], '/')))
		type = ft_strdup("editor\0");
	else if (!ft_strncmp("game\0", &path[16], ft_strchrlen(&path[16], '/')))
		type = ft_strdup("game\0");
	else
		type = ft_strdup("menu\0");
	subtype = ft_strdup("intro\0");
	name = ft_strndup(&path[26 + (!ft_strcmp("option", type) ? 2 : 0)], 3);
	pos = findpos(wn, type, subtype, name);
	tga_to_txt(tga, wn, pos);
	free_tga(tga);
	free(type);
	free(subtype);
	free(name);
	return (0);
}

int			load_texture(t_win *wn, char *type, char *subtype, char *name) // wn->load (variable path)
{
	t_tga	*tga;
	t_text	*txt;

	tga = NULL;
	txt = NULL;
	if (wn->load == NULL)
		return (1);
	((tga = (t_tga*)malloc(sizeof(tga))) == NULL) ? stop_exec("Malloc tga failed\n", wn): 0;
	tga = load_tga(wn->load);
	if (tga != NULL)
	{
		txt = findpos(wn, type, subtype, name);
		tga_to_txt(tga, wn, txt);
		free_tga(tga);
		return (0);
	}
	free_tga(tga);
	return (1);
}
