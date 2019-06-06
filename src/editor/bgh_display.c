/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bgh_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:25:35 by llejeune          #+#    #+#             */
/*   Updated: 2019/06/05 17:25:39 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	print_bgh_editor(t_win *wn)
{
	SDL_Rect 		dst;

	dst.x = 5.5 * wn->xscreen / 7;
	dst.y = 0;
	dst.w = 1.5 * wn->xscreen / 7;
	dst.h = 3 * wn->yscreen / 7;
	if (wn->edit_image.bgh == 1)
		wn->edit_image.texture_bgh = findtexture(wn, "editor", "affichage", "history");
	else if (wn->edit_image.bgh == 0)
		wn->edit_image.texture_bgh = findtexture(wn, "editor", "affichage", "background_map");
	(wn->edit_image.texture_bgh == NULL) ? stop_exec("texture bgh failed in print_bgh\n", wn) : 0;
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_bgh, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_history\n", wn);
	bg_or_h(wn);
}

void		print_path(t_win *wn, char *s, int posi_x, int posi_y)
{
	SDL_Color		color;
	int				w;
	int				h;
	static int 		x = 0;
	SDL_Rect		position;

	color = wn->color.noir;
	TTF_SizeText(wn->fonts->arial_path, s, &w, &h);
	position.x = posi_x;
	position.y = posi_y - 5;
	position.w = w;
 	position.h = h;
 	SDL_QueryTexture(wn->edit_image.bg_path, NULL, NULL, &w, &h);
 	wn->edit_image.pos_path = define_rect(0 + x, 0, w - x, h);
	print_text_with_arial_path(wn, s, color, position);
	if ((w - x) > wn->edit_image.bg.w) //revoir pos_path, c'est les positions de la texture a copier sur le rend, pas les positions ou copier sur le rend /!\ //
	{
		w = w - x;
		x++;
	}
}

void	bg_or_h(t_win *wn)
{
	if (wn->edit_image.bgh == 0)
		print_bg(wn);
	// else if (wn->edit_image.bgh == 1)
	// 	print_history(wn);
}

// void 	load_background(t_win *wn, char *command)
// {

// }

// void 	fonction_pour_message_erreur_bg(t_win *wn, char *message)

void 	print_bg(t_win *wn)
{
	static char		*path = NULL;

	wn->edit_image.bg.x = 5.6 * wn->xscreen / 7;
	wn->edit_image.bg.y = 2 * wn->yscreen / 7;
	wn->edit_image.bg.w = 1.30 * wn->xscreen / 7;
	wn->edit_image.bg.h = 26;
	SDL_SetRenderDrawColor(wn->rend, 250, 250, 250, 0);
	(SDL_RenderFillRect(wn->rend, &wn->edit_image.bg) < 0) ? stop_exec("fillrect failed in print_bg\n", wn) : 0;
	path = printable_input(wn, path);
	if ((key_pressed(wn, SDL_SCANCODE_BACKSPACE)) && path != NULL && ft_strlen(path))
		path[ft_strlen(path) - 1] = 0;
	if ((path != NULL) && ft_strlen(path))
		print_path(wn, path, wn->edit_image.bg.x + 5, wn->edit_image.bg.y + 5);
	if (key_pressed(wn, SDL_SCANCODE_RETURN))
	{
		//charger command si lien valide sinon message d'erreur "<command> doesn't exist."
		free(path); // ajouter free(path) et path = NULL dans fonction chargement bg
		path = NULL; // faire ternaire (path != NULL) ? load_bg : ft_pr_mess_err_bg
	}
}