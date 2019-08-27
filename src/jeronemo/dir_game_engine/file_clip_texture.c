#include <doom.h>
#include <header_game_engine.h>

static t_mytexture ft_find_uv_texture(t_myvec *inter, t_mytriangle **origin, short pos) //[P1][P2]
{
	t_mytexture ret;
	unsigned char	p1;
	unsigned char	p2;

	p1 = (pos & 0xFF00) >> 8;
	p2 = (pos & 0xFF);
	ret.u = (*origin)->texture[p1].u + ((*origin)->texture[p2].u - (*origin)->texture[p1].u) * ((inter->x - (*origin)->vertice[p1].x) / ((*origin)->vertice[p2].x - (*origin)->vertice[p1].x));
	ret.v = (*origin)->texture[p1].v + ((*origin)->texture[p2].v - (*origin)->texture[p1].v) * ((inter->y - (*origin)->vertice[p1].y) / ((*origin)->vertice[p2].y - (*origin)->vertice[p1].y));
    // ret.u = (((float)(fabsf(inter->x - (*origin)->vertice[p1].x)) / fabsf(((*origin)->vertice[p2].x) - (*origin)->vertice[p1].x)) * fabsf(((*origin)->texture[p2].u) - ((*origin)->texture[p1].u)));
    // ret.v = (((float)(fabsf(inter->y - (*origin)->vertice[p1].y)) / fabsf(((*origin)->vertice[p2].y) - (*origin)->vertice[p1].y)) * fabsf(((*origin)->texture[p2].v) - ((*origin)->texture[p1].v)));
	// ret.w = 0;//(((float)(fabsf(inter->z - (*origin)->vertice[p1].z)) / fabsf(((*origin)->vertice[p2].z) - (*origin)->vertice[p1].z)) * fabsf(((*origin)->texture[p2].w) - ((*origin)->texture[p1].w)));
	return (ret);
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

// static void	ft_check_texture_valide(t_mytriangle **toadd)
// {
// 	(*toadd)->texture[0].u > 1 || (*toadd)->texture[0].u < 0 ? (*toadd)->texture[0].u = 0.5 : 0;
// 	(*toadd)->texture[1].u > 1 || (*toadd)->texture[1].u < 0 ? (*toadd)->texture[1].u = 0.5 : 0;
// 	(*toadd)->texture[2].u > 1 || (*toadd)->texture[2].u < 0 ? (*toadd)->texture[2].u = 0.5 : 0;
// 	(*toadd)->texture[0].v > 1 || (*toadd)->texture[0].v < 0 ? (*toadd)->texture[0].v = 0.5 : 0;
// 	(*toadd)->texture[1].v > 1 || (*toadd)->texture[1].v < 0 ? (*toadd)->texture[1].v = 0.5 : 0;
// 	(*toadd)->texture[2].v > 1 || (*toadd)->texture[2].v < 0 ? (*toadd)->texture[2].v = 0.5 : 0;
// 	(*toadd)->texture[0].w > 1 || (*toadd)->texture[0].w < 0 ? (*toadd)->texture[0].w = 0.5 : 0;
// 	(*toadd)->texture[1].w > 1 || (*toadd)->texture[1].w < 0 ? (*toadd)->texture[1].w = 0.5 : 0;
// 	(*toadd)->texture[2].w > 1 || (*toadd)->texture[2].w < 0 ? (*toadd)->texture[2].w = 0.5 : 0;
// }

void    ft_clipping_texture_one_side(t_win *wn, t_mytriangle **curr, t_mytriangle **toadd, char side)
{
    t_myvec tmp[1];
	t_mytexture tmptxt[1];

    ft_init_toadd_texture(toadd, *curr);
   if (((side & 0xF)) == 0x4)
    {
		(*toadd)->vertice[0] = (*curr)->vertice[0];
		(*toadd)->vertice[1] = (*curr)->vertice[1];
		(*toadd)->vertice[2] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[0], ((side & 0xF0) >> 4));
		(*toadd)->texture[2] = ft_find_uv_texture(&(*toadd)->vertice[2], curr, (0 << 8) + (2));
		(*curr)->vertice[0] = (*toadd)->vertice[2];
		tmp[0] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[2], ((side & 0xF0) >> 4));
		tmptxt[0] = ft_find_uv_texture(&tmp[0], curr, (1 << 8) + (2));
		(*curr)->texture[1] = (*toadd)->texture[2];
		(*curr)->vertice[2] = tmp[0];
		(*curr)->texture[2] = tmptxt[0];
    }
    else if (((side & 0xF)) == 0x2)
    {
		(*toadd)->vertice[0] = (*curr)->vertice[0];
		(*toadd)->vertice[2] = (*curr)->vertice[2];
		(*toadd)->vertice[1] = find_intersection(wn, (*curr)->vertice[0], (*curr)->vertice[1], ((side & 0xF0) >> 4));
		(*toadd)->texture[1] = ft_find_uv_texture(&(*toadd)->vertice[1], curr, (0 << 8) + (1));
		(*curr)->vertice[0] = (*toadd)->vertice[1];
		tmp[0] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[2], ((side & 0xF0) >> 4));
		tmptxt[0] = ft_find_uv_texture(&tmp[0], curr, (1 << 8) + (2));
		(*curr)->vertice[1] = tmp[0];
		(*curr)->texture[1] = tmptxt[0];
		(*curr)->texture[0] = (*toadd)->texture[1];
	}
	else
	{
		(*toadd)->vertice[1] = (*curr)->vertice[1];
		(*toadd)->vertice[2] = (*curr)->vertice[2];
		(*toadd)->vertice[0] = find_intersection(wn, (*curr)->vertice[0], (*curr)->vertice[1], ((side & 0xF0) >> 4));
		(*toadd)->texture[0] = ft_find_uv_texture(&(*toadd)->vertice[0], curr, (1 << 8) + (0));
		(*curr)->vertice[1] = (*toadd)->vertice[0];
		tmp[0] = find_intersection(wn, (*curr)->vertice[0], (*curr)->vertice[2], ((side & 0xF0) >> 4));
		tmptxt[0] = ft_find_uv_texture(&tmp[0], curr, (2 << 8) + (0));
		(*curr)->vertice[0] = tmp[0];
		(*curr)->texture[0] = tmptxt[0];
		(*curr)->texture[1] = (*toadd)->texture[0];
	}
	// ft_check_texture_valide(toadd);
	// ft_check_texture_valide(curr);
}