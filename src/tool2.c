/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:34:54 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/10 13:34:56 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

void 		print_message(t_win *wn, char *msg, SDL_Color color)
{
	SDL_Rect 	rect;
	int 		w;
	int 		h;
	static Uint32 	time = 0;

	(time == 0) ? time = SDL_GetTicks() : 0;
	if (SDL_GetTicks() - time < 3000)
	{
		TTF_SizeText(wn->fonts->arial_path, msg, &w, &h);
		rect = define_rect(wn->xscreen / 2 - w / 2, 5 * wn->yscreen / 7 - h / 2, w, h);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_ITALIC);
		print_text_with_arial_path_full(wn, msg, color, rect);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	}
	else
	{
		time = 0;
		((t_edit *)wn->edit)->var->map_saved = 0;
	}
}

int		boxhitbox(SDL_Renderer *rend, SDL_Rect *check, SDL_Rect *pos, char show)
{
	if (show == 1)
		SDL_RenderDrawRect(rend, pos);
	if (check->x >= pos->x && check->y >= pos->y && check->x <= pos->x + pos->w && check->y <= pos->y + pos->h)
		return (TRUE);
	return (FALSE);
}

t_popup		param_pop_up(char *question, char *yes, char *no, SDL_Rect *rect)
{
	t_popup  popup;

	popup.message = question;
	popup.yes = yes;
	popup.no = no;
	popup.rect = rect;
	return (popup);
}

int 		pop_up_message(t_win *wn, t_popup  popup)
{
	int				w;
	int				h;
	SDL_Rect 		position;
	// SDL_Surface		*surface;
	SDL_Texture 	*tmp;
	SDL_Texture 	*texture;
	char 			*str;
	static int 		a = 0;

	str = NULL;
	//APPARITION SOURIS
	if (hitbox(wn->input->x, wn->input->y, popup.rect) == TRUE)
		SDL_ShowCursor(SDL_ENABLE);
	//BLOC QUESTION
	(void)popup.yes;
	(void)popup.no;
		// AFFICHAGE TEXTURE DE FOND
	texture = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, popup.rect->w, popup.rect->h);
	SDL_SetRenderTarget(wn->rend, texture) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
	tmp = findtexture(wn, "editor", "affichage", "back_slider");
	SDL_RenderCopy(wn->rend, tmp, NULL, NULL) < 0 ? stop_exec("rendercopytexture failed\n", wn) : 0;
	
		// NVELLE TEXTURE TEXTE AVEC TEXTURE DE FOND
	TTF_SizeText(wn->fonts->arial_path, popup.message, &w, &h);
	if (w > popup.rect->w && (ft_strchr(popup.message, ' ') != NULL || ft_strchr(str, ' ') != NULL))
	{
		popup.message = ft_strdup(popup.message);
		str = (ft_strchr(&(popup.message)[ft_strlen(popup.message) / 2], ' ') != NULL ? ft_strdup(ft_strchr(&(popup.message)[ft_strlen(popup.message) / 2], ' ') + 1) : ft_strdup(ft_strchr(popup.message, ' ') + 1));
		ft_bzero(ft_strstr(popup.message, str), ft_strlen(str));
		TTF_SizeText(wn->fonts->arial_path, popup.message, &w, &h);
		TTF_SizeText(wn->fonts->arial_path, str, &a, &h);
		position = define_rect(popup.rect->w / 2 - w / 2, (3 * popup.rect->h / 4) / 2 - h, w, h);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
		print_text_with_arial_path_full(wn, popup.message, wn->color.blanc, position);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
		position = define_rect(popup.rect->w / 2 - a / 2, (3 * popup.rect->h / 4) / 2 + h, a, h);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
		print_text_with_arial_path_full(wn, str, wn->color.blanc, position);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	}
	if ((a > popup.rect->w || w > popup.rect->w) || (ft_strchr(popup.message, ' ') == NULL || ft_strchr(str, ' ') == NULL))
	{
		SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
		SDL_DestroyTexture(texture);
		*(popup.rect) = (a >= w ? define_rect(wn->xscreen / 2 - (a + 30) / 2, popup.rect->y, a + 30, popup.rect->h) : define_rect(wn->xscreen / 2 - (w + 30) / 2, popup.rect->y, w + 30, popup.rect->h));
		texture = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, popup.rect->w, popup.rect->h);
		SDL_SetRenderTarget(wn->rend, texture) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
		tmp = findtexture(wn, "editor", "affichage", "back_slider");
		SDL_RenderCopy(wn->rend, tmp, NULL, NULL) < 0 ? stop_exec("rendercopytexture failed\n", wn) : 0;
		position = define_rect(popup.rect->w / 2 - w / 2, (3 * popup.rect->h / 4) / 2 - h, w, h);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
		print_text_with_arial_path_full(wn, popup.message, wn->color.blanc, position);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
		if (str != NULL)
		{
			position = define_rect(popup.rect->w / 2 - a / 2, (3 * popup.rect->h / 4) / 2 + h, a, h);
			TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
			print_text_with_arial_path_full(wn, str, wn->color.blanc, position);
			TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
		}
	}
	SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("setrendertarget failed\n", wn) : 0;
	// SDL_RenderCopy(wn->rend, texture, NULL, popup.rect) < 0 ? stop_exec("rendercopy texture failed\n", wn) : 0;
	// texture != NULL ? SDL_DestroyTexture(texture) : 0;
	(str != NULL) ? free(popup.message) : 0;
	(str != NULL) ? free(str) : 0;

	//BLOC YES
		// AFFICHAGE TEXTURE DE FOND ET CLIC
	SDL_SetRenderTarget(wn->rend, texture) < 0 ? stop_exec("setrendertardetvrai failed\n", wn) : 0;
	tmp = findtexture(wn, "editor", "affichage", "slider_window");
	position = define_rect(0, 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	SDL_RenderCopy(wn->rend, tmp, NULL, &position) < 0 ? stop_exec("rendercopy texture vrai failed\n", wn) : 0;
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, &position) == TRUE)
		return(1);
		// AFFICHAGE TEXTE
	TTF_SizeText(wn->fonts->arial_path, popup.yes, &w, &h);
	position = define_rect(position.x + position.w / 2 - w / 2, position.y + position.h /2 - h / 2, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, popup.yes, wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);

	//BLOC NO
		// AFFICHAGE TEXTURE DE FOND ET CLIC
	SDL_SetRenderTarget(wn->rend, texture) < 0 ? stop_exec("setrendertardetFAUX failed\n", wn) : 0;
	tmp = findtexture(wn, "editor", "affichage", "fleche");
	position = define_rect(popup.rect->w / 2, 3 * popup.rect->h / 4, popup.rect->w / 2, popup.rect->h / 4);
	SDL_RenderCopy(wn->rend, tmp, NULL, &position) < 0 ? stop_exec("rendercopy texture faux failed\n", wn) : 0;
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, &position) == TRUE)
		return(2);
		// AFFICHAGE TEXTE
	TTF_SizeText(wn->fonts->arial_path, popup.no, &w, &h);
	position = define_rect(position.x + position.w / 2 - w / 2, position.y + position.h /2 - h / 2, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, popup.no, wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	SDL_SetRenderTarget(wn->rend, NULL) < 0 ? stop_exec("rendertarget faux failed\n", wn) : 0;
	SDL_RenderCopy(wn->rend, texture, NULL, popup.rect) < 0 ? stop_exec("rendercopy texture failed\n", wn) : 0;
	texture != NULL ? SDL_DestroyTexture(texture) : 0;
	return (0);
}