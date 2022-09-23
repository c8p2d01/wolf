#include "cub.h"

char	**init_texture(char *first, ...)
{
	va_list	var;
	int i = 0;
	int l = 0;

	va_start(var, first);
	for (char* lal = first; lal != NULL; lal = va_arg(var, char *))
	{
		i++;
	}
	va_end(var);
	char **res = calloc(i + 1, sizeof(char*));
	va_start(var, first);
	for (char* lal = first; l < i; lal = va_arg(var, char *))
	{
		res[l] = strdup(lal);
		l++;
	}
	return (res);
}

void	init(t_var *var)
{
	// textures raw
	var->east = init_texture("EEEEEEEEEEEEEEEEEE",
							 "E----------------E",
							 "E---EEEEEEEEEE---E",
							 "E---E------------E",
							 "E---E------------E",
							 "E---EEEEEEE------E",
							 "E---E------------E",
							 "E---E------------E",
							 "E---EEEEEEEEEE---E",
							 "E----------------E",
							 "EEEEEEEEEEEEEEEEEE", NULL);
	var->west = init_texture("WWWWWWWWWWWWWWWWWW",
							 "W-----------------W",
							 "W--WW---------WW--W",
							 "W---WW---W---WW---W",
							 "W---WW--WWW--WW---W",
							 "W----W--W-W--W----W",
							 "W----WWWW-WWWW----W",
							 "W-----WW---WW-----W",
							 "W-----------------W",
							 "W-----------------W",
							 "WWWWWWWWWWWWWWWWWW", NULL);
	var->south = init_texture("SSSSSSSSSSSSSSSSSS",
							 "S----------------S",
							 "S------SSSS------S",
							 "S---SSS----SSS---S",
							 "S--SS------------S",
							 "S----SSS--SSS----S",
							 "S------------SS--S",
							 "S---SSS----SSS---S",
							 "S------SSSS------S",
							 "S----------------S",
							 "SSSSSSSSSSSSSSSSSS", NULL);
	var->north = init_texture("NNNNNNNNNNNNNNNNNN",
							 "W----------------W",
							 "W--N----------N--W",
							 "W--NN---------N--W",
							 "W--N-NN-------N--W",
							 "W--N---NN-----N--W",
							 "W--N-----NN---N--W",
							 "W--N-------NN-N--W",
							 "W--N---------NN--W",
							 "W----------------W",
							 "NNNNNNNNNNNNNNNNNN", NULL);
	// map
	var->map = init_texture("OOOOOOOOOOOOOOOOOOO",
							"O                 O",
							"O                 O",
							"O   P             O",
							"O                 O",
							"O                 O",
							"O                 O",
							"OOOOOOOOOOOOOOOOOOO", NULL);
	// player
	for (int x = 0; var->map[x]; x++)
	{
		for (int y = 0; var->map[x][y]; y++)
		{
			if (var->map[x][y] == 'P')
			{
				var->plx = y;
				var->ply = x;
				var->orx = -1;
				var->ory = 0;
				printf("player at %i %i\n", y, x);
			}
		}
	}
}

void	rem(t_var *var)
{
	for(int i = 0; var->east[i]; i++)
		free(var->east[i]);
	free(var->east);
	for(int i = 0; var->west[i]; i++)
		free(var->west[i]);
	free(var->west);
	for(int i = 0; var->south[i]; i++)
		free(var->south[i]);
	free(var->south);
	for(int i = 0; var->north[i]; i++)
		free(var->north[i]);
	free(var->north);
	for(int i = 0; var->map[i]; i++)
		free(var->map[i]);
	free(var->map);
}
/*
	\    \   /     /	
	 \  0------#  /		0------#0------#0------#
	  \ |  N   | /		|  N   ||  N   ||  N   |
	   X|W   E |X		|W   E ||W   E ||W   E |
	  / |  S   | \		|  S   ||  S   ||  S   |
	 /  #------#  \		#------##------##------#
	/    /   \     \	
	0 -> coordinate in map
	/ or \ -> incoming rays

	from different ray incomig angles different sides should be hit and tracked
	e.g. from south east walls should compare against coordinate + 1 in either direction

	check intersection only at raylengths where a wall could be
	-> find a vectorlength for the neares horizontal and neares vertical and from there on iterate in steps
*/

void	render(t_var *var)
{
	// Sky and Floor coloring
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		memset(var->cvs[i], SKY, WIDTH);
		var->cvs[i][WIDTH] = 0;		
	}
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		memset(var->cvs[i + (HEIGHT / 2)], FLOOR, WIDTH);
		var->cvs[i + (HEIGHT / 2)][WIDTH] = 0;
	}

	// rays

	// projection plane on which to cast rays to avoid fishEye view
	double rotx = var->ory;
	double roty = -var->orx;
	double planelen = pow(pow(var->orx, 2) + pow(var->ory, 2), 0.5) * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
	double tmp = pow(pow(rotx, 2) + pow(roty, 2), 0.5);
	rotx /= tmp;
	roty /= tmp;
	rotx *= planelen;
	roty *= planelen;

	// ray direction vector, normed
	double rx, ry;
	// first step to walls (startlength)
	double h, v;
	// stepsize in between same kinds of walls
	double delta_h, delta_v;

	for (int r = 1; r < WIDTH; r++)
	{
		rx = var->orx + rotx - ((rotx * 2) / WIDTH) * r;
		ry = var->ory + roty - ((roty * 2) / WIDTH) * r;
		double temp = pow(pow(rx, 2) + pow(ry, 2), 0.5);
		rx /= temp;
		ry /= temp;

		h = (1 - (fabs(var->plx) - abs((int)var->plx))) / fabs(rx);
		v = (1 - (fabs(var->ply) - abs((int)var->ply))) / fabs(ry);
		// printf("nexts %lf %lf     %lf %lf\n", var->plx + rx * v, var->ply + ry * v, var->plx + rx * h, var->ply + ry * h);
		delta_h = 1 / fabs(rx);
		delta_v = 1 / fabs(ry);

		double c = 0;
		while (1)
		{
			if (v < h)
				c = v;
			else
				c = h;
			if (rx > 0)	// N
			{
				if (ry >= -0.f)	// NE
				{
					if (var->map[(int)(var->ply + ry * c)][(int)(var->plx + rx * c)] == 'O')
					{
						// printf("WALL NE	%lf %lf dst %lf\n", rx * c, ry * c, pow(pow(rx * c, 2) + pow(ry * c, 2), 0.5));
						printf("seen pos %i %i", (int)(var->plx + rx * c), (int)(var->ply + ry * c));
						c == v ? printf("V\n") : printf("H\n");
						break;
					}
				}
				else		// NW
				{
					if (var->map[(int)(var->ply + ry * c)][(int)(var->plx + rx * c)] == 'O')
					{
						// printf("WALL NW	%lf %lf dst %lf\n", rx * c, ry * c, pow(pow(rx * c, 2) + pow(ry * c, 2), 0.5));
						printf("seen pos %i %i", 1 + (int)(var->plx + rx * c), (int)(var->ply + ry * c));
						c == v ? printf("V\n") : printf("H\n");
						break;
					}
				}
			}
			else		// S
			{
				if (ry > 0)	// SE
				{
					if (var->map[1 + (int)(var->ply + ry * c)][(int)(var->plx + rx * c)] == 'O')
					{
						// printf("WALL SE	%lf %lf dst %lf\n", rx * c, ry * c, pow(pow(rx * c, 2) + pow(ry * c, 2), 0.5));
						printf("seen pos %i %i", (int)(var->plx + rx * c), 1 + (int)(var->ply + ry * c));
						c == v ? printf("V\n") : printf("H\n");
						break;
					}
				}
				else		// SW
				{
					if (var->map[1 + (int)(var->ply + ry * c)][1 + (int)(var->plx + rx * c)] == 'O')
					{
						// printf("WALL SW	%lf %lf dst %lf\n", rx * c, ry * c, pow(pow(rx * c, 2) + pow(ry * c, 2), 0.5));
						printf("seen pos %i %i", 1 + (int)(var->plx + rx * c), 1 + (int)(var->ply + ry * c));
						c == v ? printf("V\n") : printf("H\n");
						break;
					}
				}
			}
			if (c == v)
				v += delta_v;
			else
				h += delta_h;
		}
	}

	// for (int i = 0; i < HEIGHT; i++)
	// {
	// 	printf("	%s\n", var->cvs[i]);
	// }
}

int main(void)
{
	t_var var;

	init(&var);
	render(&var);
	/* plans:
		raycasting;
		-> make a ray (one pwe width)
		-> repeatedly check the next possible wall intersection until a wall is hit
			pythagoras and map comparison
		figure out the position on the texture and the height to be displayed
		display each texture line
	 */
	rem(&var);
	return (0);
}
