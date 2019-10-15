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

void		print_message_with_time(t_win *wn, char *msg, SDL_Rect pos, Uint32 time) // CAN CHANGE DRAW TIME ?
{
	SDL_Color color;

	color.a = 0xFF;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	if (SDL_GetTicks() - time < 3000)
	{
		TTF_SizeText(wn->fonts->arial_path, msg, &pos.w, &pos.h);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_ITALIC);
		print_text_with_arial_path_full(wn, msg, color, pos);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	}
}

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
	if (show & 0x1)
		SDL_RenderDrawRect(rend, pos);
	if (check->x >= pos->x && check->y >= pos->y && check->x <= pos->x + pos->w && check->y <= pos->y + pos->h)
	{
		if (show & 0x2)
		{
			free(check);
			free(pos);
		}
		return (TRUE);
	}
	if (show & 0x2)
	{
		free(check);
		free(pos);
	}
	return (FALSE);
}