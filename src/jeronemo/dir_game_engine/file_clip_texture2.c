#include <doom.h>
#include <header_game_engine.h>

void    ft_clipping_texture_two_point(t_win *wn, t_mytriangle **curr, char nb, char side)
{
    t_myvec tmp[2];

    if (!(nb & 0x4))
    {
		printf("0x4 !\n");
	    tmp[0] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[0], side);
	    tmp[1] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[1], side);
        (*curr)->texture[0] = ft_find_uv_texture(&tmp[0], curr, (2 << 8) + 0);
        (*curr)->texture[1] = ft_find_uv_texture(&tmp[1], curr, (2 << 8) + 1);
	    (*curr)->vertice[0] = tmp[0];
	    (*curr)->vertice[1] = tmp[1];
    }
    if (!(nb & 0x2))
    {
		printf("0x2 !\n");
	    tmp[0] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[0], side);
	    tmp[1] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[2], side);
        (*curr)->texture[2] = ft_find_uv_texture(&tmp[0], curr, (1 << 8) + 2);
        (*curr)->texture[0] = ft_find_uv_texture(&tmp[1], curr, (1 << 8) + 0);
	    (*curr)->vertice[2] = tmp[0];
	    (*curr)->vertice[0] = tmp[1];
	}
	if (!(nb & 0x1))
	{
		printf("0x1 !\n");
        tmp[0] = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[0], side);
	    tmp[1] = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[0], side);
        (*curr)->texture[2] = ft_find_uv_texture(&tmp[0], curr, (0 << 8) + 1);
        (*curr)->texture[1] = ft_find_uv_texture(&tmp[1], curr, (0 << 8) + 1);
	    (*curr)->vertice[2] = tmp[0];
	    (*curr)->vertice[1] = tmp[1];
	}
}