/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_coor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:14:06 by llejeune          #+#    #+#             */
/*   Updated: 2019/09/15 13:14:09 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void               print_text(t_win *wn, char *txt, float pos_line)
{
    int     w;
    int     h;
    SDL_Rect    rect;

    TTF_SizeText(wn->fonts->arial, txt, &w, &h);
    ((t_edit *)wn->edit)->var->w = w;
    ((t_edit *)wn->edit)->var->h = h;
    rect = define_rect(wn->xscreen / 8 - w * 2, pos_line * 7.5 * wn->yscreen / 64, w * 2, h * 2);
    TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_BOLD);
    print_text_with_ariel_font(wn, txt, wn->color.noir, rect);
    TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_NORMAL);
}

static void         val_coor(t_win *wn, float pos, SDL_Texture **texture, char *nb)
{
    SDL_Rect        cursor;
    int             w;
    int             h;

    cursor.x = wn->input->x;
    cursor.y = wn->input->y;
    SDL_SetRenderTarget(wn->rend, NULL);
    if (boxhitbox(wn->rend, &cursor, create_rect((3 * wn->xscreen / 4) + wn->xscreen / 8 + ((t_edit *)wn->edit)->var->w * 2, (0.5 * wn->yscreen / 8) + pos * (7.5 * wn->yscreen / 8) / 8, ((t_edit *)wn->edit)->var->w * 2, ((t_edit *)wn->edit)->var->h * 2), 1) && mouse_pressed(wn, SDL_BUTTON_LEFT))
        printf("lalalalalala\n");
    else
    {
        SDL_SetRenderTarget(wn->rend, *texture);
        TTF_SizeText(wn->fonts->arial, nb, &w, &h);
        print_text_with_ariel_font(wn, nb, wn->color.noir, define_rect(wn->xscreen / 8 + ((t_edit *)wn->edit)->var->w, pos * 7.5 * wn->yscreen / 64, w * 2, h * 2));
    }
}

SDL_Texture        *print_coor(t_win *wn, t_edit *edit)
{
    SDL_Texture     *texture;
    SDL_Texture     *tmp;
    char            *nb;

    // couleur fond texture
    texture = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, wn->xscreen / 4, 7.5 * wn->yscreen / 8);
    tmp = findtexture(wn, "editor", "affichage", "params");
    SDL_SetRenderTarget(wn->rend, texture);
    SDL_RenderCopy(wn->rend, tmp, NULL, NULL);
    
    // print x
    print_text(wn, "x : ", 1);
    nb = ft_itoa(((wn->input->x - ((t_edit *)wn->edit)->map->x) * ((t_edit *)wn->edit)->indice->map_w) / ((t_edit *)wn->edit)->map->w / 10);
    val_coor(wn, 1, &texture, nb);
    // print y
    print_text(wn, "y : ", 1.5);
    nb = ft_itoa(((wn->input->y - edit->map->y) * edit->indice->map_h) / edit->map->h / 10);
    val_coor(wn, 1.5, &texture, nb);
    // print z
    print_text(wn, "z : ", 2);
    nb = ft_itoa(edit->indice->val_z);
    val_coor(wn, 2, &texture, nb);
    // print rot
    print_text(wn, "rot : ", 2.5);
    // print zoom
    print_text(wn, "zoom : ", 3);
    nb = ft_itoa(edit->map->size * 100);
    val_coor(wn, 3, &texture, nb);

    SDL_SetRenderTarget(wn->rend, NULL);
    return (texture);
}