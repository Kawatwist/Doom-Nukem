#include <doom.h>
#include <header_game_engine.h>

void    ft_clipping_texture_two_point(t_win *wn, t_mytriangle **curr, char nb)
{
    t_myvec tmp;

    if (!(nb & 0x4))
    {
	    tmp = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[0], nb);
        (*curr)->texture[0] = ft_find_uv_texture(&tmp, curr, (2 << 8) + 0);
	    (*curr)->vertice[0] = tmp;
	    tmp = find_intersection(wn, (*curr)->vertice[2], (*curr)->vertice[1], nb);
        (*curr)->texture[1] = ft_find_uv_texture(&tmp, curr, (2 << 8) + 1);
	    (*curr)->vertice[1] = tmp;
    }
    if (!(nb & 0x2))
    {
	    tmp = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[0], nb);
        (*curr)->texture[0] = ft_find_uv_texture(&tmp, curr, (1 << 8) + 0);
	    (*curr)->vertice[0] = tmp;
	    tmp = find_intersection(wn, (*curr)->vertice[1], (*curr)->vertice[2], nb);
        (*curr)->texture[2] = ft_find_uv_texture(&tmp, curr, (1 << 8) + 2);
	    (*curr)->vertice[2] = tmp;
	}
	if (!(nb & 0x1))
	{
        tmp = find_intersection(wn, (*curr)->vertice[0], (*curr)->vertice[1], nb);
        (*curr)->texture[1] = ft_find_uv_texture(&tmp, curr, (0 << 8) + 1);
	    (*curr)->vertice[1] = tmp;
	    tmp = find_intersection(wn, (*curr)->vertice[0], (*curr)->vertice[2], nb);
        (*curr)->texture[2] = ft_find_uv_texture(&tmp, curr, (0 << 8) + 2);
	    (*curr)->vertice[2] = tmp;
	}
}