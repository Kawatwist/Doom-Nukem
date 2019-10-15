/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 11:31:12 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/22 11:31:14 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void     stape_to_write(t_win *wn, char *str, int c, int w)
{
    int     a;
    int     h;

    TTF_SizeText(wn->fonts->arial_path, str, &a, &h);
	print_text_with_arial_path_full(wn, str, wn->color.noir, define_rect(c * wn->xscreen / 16 + w, (wn->yscreen / 32) / 2 - h / 2, a, h));
}

static void     write_on_texture(t_win *wn, int c, char *word, int b)
{
    int     w;
    int     h;

    TTF_SizeText(wn->fonts->arial_path, word, &w, &h);
    stape_to_write(wn, word, c, 0);
    if (c == 1)
        stape_to_write(wn, ((t_edit *)wn->edit)->map->name, c, w);
    else
    {
        if (b < -900)
            stape_to_write(wn, "-inv.", c, w);
        else if (b > 1000)
            stape_to_write(wn, "+inv.", c, w);
        else
            stape_to_write(wn, ft_itoa(b), c, w);
        (c == 9) ? stape_to_write(wn, " %", c, w + 30) : 0;
    }
}

void           info_bar(t_win *wn, t_edit *edit)
{
    SDL_Texture *texture;
    SDL_Texture *tmp;
    SDL_Rect    rect;
    int         b;

    texture = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, wn->xscreen, wn->yscreen / 32);
    tmp = findtexture(wn, "editor", "affichage", "background_map");
    SDL_SetRenderTarget(wn->rend, texture) < 0 ? stop_exec("rendertarget failed in barinfo\n", wn) : 0;
    SDL_RenderCopy(wn->rend, tmp, NULL, NULL) < 0 ? stop_exec("rendercopytexture failed in barinfo", wn) : 0;
    if (((t_edit *)wn->edit)->map->name == NULL)
        ((t_edit *)wn->edit)->map->name = "Untitled(1)";
    write_on_texture(wn, 1, "map_name : ", 0);
    b = ((wn->input->x - edit->map->x) * edit->indice->map_w) / edit->map->w / 10;
    write_on_texture(wn, 6, "x : ", b);
	b = ((wn->input->y - edit->map->y) * edit->indice->map_h) / edit->map->h / 10;
    write_on_texture(wn, 7, "y : ", b);
    b = edit->map->size * 100;
    write_on_texture(wn, 9, "zoom : ", b);
    SDL_SetRenderTarget(wn->rend, NULL);
    rect = define_rect(0, 31 * wn->yscreen / 32, wn->xscreen, wn->yscreen / 32);
    SDL_RenderCopy(wn->rend, texture, NULL, &rect) < 0 ? stop_exec("rendercopy failed in barinfo\n", wn) : 0;
    SDL_DestroyTexture(texture); // LEAKS
}