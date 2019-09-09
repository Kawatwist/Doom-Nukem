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
	popup.str = NULL;
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

static void bloc_message(t_win *wn, SDL_Texture **texture, t_popup popup)
{
	int 	w;
	int 	h;
	int 	a;

	a = 0;
	TTF_SizeText(wn->fonts->arial_path, popup.message, &w, &h);
	if (w > popup.rect->w && (ft_strchr(popup.message, ' ') != NULL || ft_strchr(popup.str, ' ') != NULL))
	{
		popup.message = ft_strdup(popup.message);
		popup.str = (ft_strchr(&(popup.message)[ft_strlen(popup.message) / 2], ' ') != NULL ? ft_strdup(ft_strchr(&(popup.message)[ft_strlen(popup.message) / 2], ' ') + 1) : ft_strdup(ft_strchr(popup.message, ' ') + 1));
		ft_bzero(ft_strstr(popup.message, popup.str), ft_strlen(popup.str));
		TTF_SizeText(wn->fonts->arial_path, popup.message, &w, &h);
		text_texture(wn, popup.message, wn->color.blanc, define_rect(popup.rect->w / 2 - w / 2, (3 * popup.rect->h / 4) / 2 - h, w, h));
		TTF_SizeText(wn->fonts->arial_path, popup.str, &a, &h);
		text_texture(wn, popup.str, wn->color.blanc, define_rect(popup.rect->w / 2 - a / 2, (3 * popup.rect->h / 4) / 2 + h, a, h));
	}
	if ((a > popup.rect->w || w > popup.rect->w) || (ft_strchr(popup.message, ' ') == NULL || ft_strchr(popup.str, ' ') == NULL))
	{
		SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
		SDL_DestroyTexture(*texture);
		*texture = NULL;
		popup.position.x = -1;
		*(popup.rect) = (a >= w ? define_rect(wn->xscreen / 2 - (a + 30) / 2, popup.rect->y, a + 30, popup.rect->h) : define_rect(wn->xscreen / 2 - (w + 30) / 2, popup.rect->y, w + 30, popup.rect->h));
		back_texture(wn, &(*texture), "back_slider", popup);
		text_texture(wn, popup.message, wn->color.blanc, define_rect(popup.rect->w / 2 - w / 2, (3 * popup.rect->h / 4) / 2 - h, w, h));
		if (popup.str != NULL)
			text_texture(wn, popup.str, wn->color.blanc, define_rect(popup.rect->w / 2 - a / 2, (3 * popup.rect->h / 4) / 2 + h, a, h));
	}
}

static void	conditions_popup(t_win *wn, t_popup popup)
{
	if (hitbox(wn->input->x, wn->input->y, popup.rect, 0) == TRUE)
		SDL_ShowCursor(SDL_ENABLE);
	if (popup.rect->x < 0 || popup.rect->x > wn->xscreen || popup.rect->y < 0 || popup.rect->y > wn->yscreen)
		print_message(wn, "Origin popup out of screen", wn->color.blanc);
	if (popup.rect->w > wn->xscreen || popup.rect->h > wn->yscreen)
		print_message(wn, "Rect size is too big", wn->color.blanc);
}

int 		pop_up_message(t_win *wn, t_popup  popup)
{
	int				w;
	int				h;
	SDL_Texture 	*texture;

    texture = NULL;
	conditions_popup(wn, popup);
	//BLOC QUESTION
    back_texture(wn, &texture, "back_slider", popup);
	bloc_message(wn, &texture, popup);
	//BLOC YES
	popup.position = define_rect(0, 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	back_texture(wn, &texture, "slider_window", popup);
	TTF_SizeText(wn->fonts->arial_path, popup.yes, &w, &h);
	text_texture(wn, popup.yes, wn->color.noir, define_rect(popup.position.x + popup.position.w / 2 - w / 2, popup.position.y + popup.position.h /2 - h / 2, w, h));
		if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, create_rect(popup.rect->x, popup.rect->y + 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4), 1) == TRUE)
	return(1);
	//BLOC NO
	popup.position = define_rect(popup.rect->w / 2, 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	back_texture(wn, &texture, "fleche", popup);
	TTF_SizeText(wn->fonts->arial_path, popup.no, &w, &h);
	text_texture(wn, popup.no, wn->color.noir, define_rect(popup.position.x + popup.position.w / 2 - w / 2, popup.position.y + popup.position.h /2 - h / 2, w, h));
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, create_rect(popup.rect->x + popup.rect->w / 2, popup.rect->y + 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4), 1) == TRUE)
		return(2);	
	// AFFICHAGE TEXTURE FINALE SUR RENDER
	SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("rendertarget failed\n", wn) : 0;
	SDL_RenderCopy(wn->rend, texture, NULL, popup.rect) < 0 ? stop_exec("rendercopy TEXTURE failed\n", wn) : 0;
	texture != NULL ? SDL_DestroyTexture(texture) : 0;
	(popup.str != NULL) ? free(popup.message) : 0;
	(popup.str != NULL) ? free(popup.str) : 0;
	return (0);
}
