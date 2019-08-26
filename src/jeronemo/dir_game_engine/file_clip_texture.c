#include <doom.h>
#include <header_game_engine.h>

static void ft_find_uv_texture(t_myvec *find, t_mytriangle **toadd, t_mytriangle **origin, char side)
{
    if (side & 0x4)
    {
        (*toadd)->texture[2].u = (((float)(fabsf(find->x - (*origin)->vertice[0].x)) / fabsf(((*origin)->vertice[2].x) - (*origin)->vertice[0].x)) * fabsf(((*origin)->texture[2].u) - ((*origin)->texture[0].u)));
        (*toadd)->texture[2].v = (((float)(fabsf(find->y - (*origin)->vertice[0].y)) / fabsf(((*origin)->vertice[2].y) - (*origin)->vertice[0].y)) * fabsf(((*origin)->texture[2].v) - ((*origin)->texture[0].v)));
        (*toadd)->texture[2].w = (*origin)->texture[2].w * ((float)(fabsf(((*origin)->texture[2].u) - ((*origin)->texture[0].u)) +  fabsf(((*origin)->texture[2].v) - ((*origin)->texture[0].v))) / 2);
    }
    else if (side & 0x2)
    {
        (*toadd)->texture[2].u = (((float)(fabsf(find->x - (*origin)->vertice[0].x)) / fabsf(((*origin)->vertice[2].x) - (*origin)->vertice[0].x)) * fabsf(((*origin)->texture[2].u) - ((*origin)->texture[0].u)));
        (*toadd)->texture[2].v = (((float)(fabsf(find->y - (*origin)->vertice[0].y)) / fabsf(((*origin)->vertice[2].y) - (*origin)->vertice[0].y)) * fabsf(((*origin)->texture[2].v) - ((*origin)->texture[0].v)));
        (*toadd)->texture[2].w = (*origin)->texture[2].w * ((float)(fabsf(((*origin)->texture[2].u) - ((*origin)->texture[0].u)) +  fabsf(((*origin)->texture[2].v) - ((*origin)->texture[0].v))) / 2);
    }
    else
    {
        (*toadd)->texture[2].u = (((float)(fabsf(find->x - (*origin)->vertice[0].x)) / fabsf(((*origin)->vertice[2].x) - (*origin)->vertice[0].x)) * fabsf(((*origin)->texture[2].u) - ((*origin)->texture[0].u)));
        (*toadd)->texture[2].v = (((float)(fabsf(find->y - (*origin)->vertice[0].y)) / fabsf(((*origin)->vertice[2].y) - (*origin)->vertice[0].y)) * fabsf(((*origin)->texture[2].v) - ((*origin)->texture[0].v)));
        (*toadd)->texture[2].w = (*origin)->texture[2].w * ((float)(fabsf(((*origin)->texture[2].u) - ((*origin)->texture[0].u)) +  fabsf(((*origin)->texture[2].v) - ((*origin)->texture[0].v))) / 2);
    }
}

static void ft_init_toadd_texture(t_mytriangle **toadd, t_mytriangle *origin)
{
	(*toadd)->texture[0].u = origin->texture[0].u;
	(*toadd)->texture[0].v = origin->texture[0].v;
	(*toadd)->texture[0].w = origin->texture[0].w;
	(*toadd)->texture[1].u = origin->texture[1].u;
	(*toadd)->texture[1].v = origin->texture[1].v;
	(*toadd)->texture[1].w = origin->texture[1].w;
	(*toadd)->texture[2].u = origin->texture[2].u;
	(*toadd)->texture[2].v = origin->texture[2].v;
	(*toadd)->texture[2].w = origin->texture[2].w;
}

void    ft_clipping_texture_one_side(t_win *wn, t_mytriangle **curr, t_mytriangle **toadd, char side)
{
    t_myvec tmp[1];

    ft_init_toadd_texture(toadd, *curr);
   if (((side & 0xF)) == 0x4)
    {
        (*toadd)->vertice[0] = (*curr)->vertice[0]; // point commun
		(*toadd)->vertice[1] = (*curr)->vertice[1]; // second point inside
		(*toadd)->vertice[2] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[0], ((side & 0xF0) >> 4)); // troisieme point bordure scren
		tmp[0] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[2], ((side & 0xF0) >> 4));
		ft_find_uv_texture(&tmp[0], toadd, curr, side & 0xF);
		(*curr)->vertice[2].x = tmp[0].x;
		(*curr)->vertice[2].y = tmp[0].y;
        (*curr)->vertice[0] = (*toadd)->vertice[2]; // point bordure screen 1
    }
    else if (((side & 0xF)) == 0x2)
    {
		(*toadd)->vertice[0] = (*curr)->vertice[0];
		(*toadd)->vertice[1] = (*curr)->vertice[2];
		(*toadd)->vertice[2] = find_intersection(wn, (*curr)->vertice[0], (*curr)->vertice[1], ((side & 0xF0) >> 4));
		tmp[0] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[1], ((side & 0xF0) >> 4));
		ft_find_uv_texture(&tmp[0], toadd, curr, side & 0xF);
		(*curr)->vertice[1].x = tmp[0].x;
		(*curr)->vertice[1].y = tmp[0].y;
        (*curr)->vertice[0] = (*toadd)->vertice[2];
	}
	else
	{
		(*toadd)->vertice[0] = (*curr)->vertice[1];
		(*toadd)->vertice[1] = (*curr)->vertice[2];
		(*toadd)->vertice[2] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[0], ((side & 0xF0) >> 4));
		tmp[0] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[0], ((side & 0xF0) >> 4));
		ft_find_uv_texture(&tmp[0], toadd, curr, side & 0xF);
        (*curr)->vertice[0] = tmp[0];
		(*curr)->vertice[0].x = tmp[0].x;
		(*curr)->vertice[0].y = tmp[0].y;
		(*curr)->vertice[2] = (*toadd)->vertice[2];
	}
}