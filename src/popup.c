/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:46:42 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/28 10:46:44 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_popup		param_pop_up(char *question, char *yes, char *no, SDL_Rect *rect)
{
	t_popup  popup;

	popup.message = question;
	popup.yes = yes;
	popup.no = no;
	popup.rect = rect;
    popup.position.x = -1;
	return (popup);
}

static void back_texture(t_win *wn, SDL_Texture **texture, char *name, t_popup popup)
{
    SDL_Texture *tmp;

    if (*texture == NULL)
    {
        *texture = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, popup.rect->w, popup.rect->h);
	    SDL_SetRenderTarget(wn->rend, *texture) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
    }
    tmp = findtexture(wn, "editor", "affichage", name);
    if (popup.position.x == -1)
	    SDL_RenderCopy(wn->rend, tmp, NULL, NULL) < 0 ? stop_exec("rendercopytexture failed\n", wn) : 0;
    else
	    SDL_RenderCopy(wn->rend, tmp, NULL, &(popup.position)) < 0 ? stop_exec("rendercopytexture failed\n", wn) : 0;
}

static void	text_texture(t_win *wn, char *msg, SDL_Color color, SDL_Rect rect)
{
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, msg, color, rect);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
}

// static SDL_Rect	*define_rect2(int x, int y, int w, int h)
// {
// 	SDL_Rect	*rect[1];

// 	rect[0]->x = x;
// 	rect[0]->y = y;
// 	rect[0]->w = w;
// 	rect[0]->h = h;
// 	return (rect[0]);
// }

int 		pop_up_message(t_win *wn, t_popup  popup)
{
	int				w;
	int				h;
	// SDL_Rect 		position;
	SDL_Texture 	*texture;
	char 			*str;
	static int 		a = 0;

	str = NULL;
    texture = NULL;
	//APPARITION SOURIS
	if (hitbox(wn->input->x, wn->input->y, popup.rect, 0) == TRUE)
		SDL_ShowCursor(SDL_ENABLE);
	//BLOC QUESTION
		// AFFICHAGE TEXTURE DE FOND
    back_texture(wn, &texture, "back_slider", popup);
		// NVELLE TEXTURE TEXTE AVEC TEXTURE DE FOND
	TTF_SizeText(wn->fonts->arial_path, popup.message, &w, &h);
	if (w > popup.rect->w && (ft_strchr(popup.message, ' ') != NULL || ft_strchr(str, ' ') != NULL))
	{
		popup.message = ft_strdup(popup.message);
		str = (ft_strchr(&(popup.message)[ft_strlen(popup.message) / 2], ' ') != NULL ? ft_strdup(ft_strchr(&(popup.message)[ft_strlen(popup.message) / 2], ' ') + 1) : ft_strdup(ft_strchr(popup.message, ' ') + 1));
		ft_bzero(ft_strstr(popup.message, str), ft_strlen(str));
		TTF_SizeText(wn->fonts->arial_path, popup.message, &w, &h);
		text_texture(wn, popup.message, wn->color.blanc, define_rect(popup.rect->w / 2 - w / 2, (3 * popup.rect->h / 4) / 2 - h, w, h));
		TTF_SizeText(wn->fonts->arial_path, str, &a, &h);
		text_texture(wn, str, wn->color.blanc, define_rect(popup.rect->w / 2 - a / 2, (3 * popup.rect->h / 4) / 2 + h, a, h));
	}
	if ((a > popup.rect->w || w > popup.rect->w) || (ft_strchr(popup.message, ' ') == NULL || ft_strchr(str, ' ') == NULL))
	{
		SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
		SDL_DestroyTexture(texture);
		texture = NULL;
		popup.position.x = -1;
		*(popup.rect) = (a >= w ? define_rect(wn->xscreen / 2 - (a + 30) / 2, popup.rect->y, a + 30, popup.rect->h) : define_rect(wn->xscreen / 2 - (w + 30) / 2, popup.rect->y, w + 30, popup.rect->h));
		back_texture(wn, &texture, "back_slider", popup);
		text_texture(wn, popup.message, wn->color.blanc, define_rect(popup.rect->w / 2 - w / 2, (3 * popup.rect->h / 4) / 2 - h, w, h));
		if (str != NULL)
			text_texture(wn, str, wn->color.blanc, define_rect(popup.rect->w / 2 - a / 2, (3 * popup.rect->h / 4) / 2 + h, a, h));
	}
	(str != NULL) ? free(popup.message) : 0;
	(str != NULL) ? free(str) : 0;

	//BLOC YES
		// AFFICHAGE TEXTURE DE FOND
	popup.position = define_rect(0, 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	back_texture(wn, &texture, "slider_window", popup);
		// AFFICHAGE TEXTE
	TTF_SizeText(wn->fonts->arial_path, popup.yes, &w, &h);
	text_texture(wn, popup.yes, wn->color.noir, define_rect(popup.position.x + popup.position.w / 2 - w / 2, popup.position.y + popup.position.h /2 - h / 2, w, h));

	//BLOC NO
		// AFFICHAGE TEXTURE DE FOND
	popup.position = define_rect(popup.rect->w / 2, 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	back_texture(wn, &texture, "fleche", popup);
		// AFFICHAGE TEXTE
	TTF_SizeText(wn->fonts->arial_path, popup.no, &w, &h);
	text_texture(wn, popup.no, wn->color.noir, define_rect(popup.position.x + popup.position.w / 2 - w / 2, popup.position.y + popup.position.h /2 - h / 2, w, h));
	
	// AFFICHAGE TEXTURE FINALE SUR RENDER
	SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("rendertarget failed\n", wn) : 0;
	SDL_RenderCopy(wn->rend, texture, NULL, popup.rect) < 0 ? stop_exec("rendercopy TEXTURE failed\n", wn) : 0;
	texture != NULL ? SDL_DestroyTexture(texture) : 0;
	
	// CLIC VRAI || FAUX
	// position = define_rect(popup.rect->x, popup.rect->y + 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, create_rect(popup.rect->x, popup.rect->y + 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4), 1) == TRUE)
		return(1);
	// position = define_rect(popup.rect->x + popup.rect->w / 2, popup.rect->y + 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, create_rect(popup.rect->x + popup.rect->w / 2, popup.rect->y + 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4), 1) == TRUE)
		return(2);
	return (0);
}