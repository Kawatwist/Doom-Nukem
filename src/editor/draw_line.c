#include "doom.h"

void	draw_line(SDL_Renderer *renderer, float x1, float y1, float x2, float y2)
{
	int	dx;
	int	dy;
	int	error;

	error = x2 - x1;
	dx = error * 2;
	dy = (y2 - y1) * 2;
	while (x1 < x2)
	{
		SDL_RenderDrawPoint(renderer, x1, y1);
		x1 = x1 + 1;
		if ((error = error - dy) < 0)
		{
			y1 = y1 + 1;
			error = error + dx;
		}
	}
}
/*
void	draw_line(SDL_Renderer *renderer, float x1, float y1, float x2, float y2)
{
	int	dx;
	int dy;
	int	error;

	if((dx = x2 - x1) != 0)
	{
		if(dx > 0)
		{
			if ((dy = y2 - y1) != 0)
			{
				if (dy > 0)
				{
					if (dx > dy)
					{
						int error;

						dx = (error = dx) * 2;
						dy = dy * 2;
					   	while(42)
						{
							SDL_RenderDrawPoint(renderer, x1, y1)
								if ((x1 = x1 + 1) == x2)
									break;
							if ((error = error - dy) < 0)
							{
								y1 = y1 + 1;
								error = error + dx;
							}
						}
						else

					}
				}
			}
		}
	}
}*/
