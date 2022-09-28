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

void	init(t_var *var, char *path)
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
	var->map = init_texture("OOOOOOOO",
							"OP     O",
							"O      O",
							"O      O",
							"O 0    O",
							"O  0   O",
							"O      O",
							"OOOOOOOO", NULL);
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
				var->ory = -1;
				//printf("player at %i %i\n", y, x);
			}
		}
	}
	if (path)
	{
		for (int i = 0; path[i]; i++)
		{
			switch (path[i]) {
				case 'n' : var->ply--; break;//n
				case 's' : var->ply++; break;//s
				case 'w' : var->plx--; break;//w
				case 'e' : var->plx++; break;//e
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

	for (int r = 1; r <= WIDTH; r++)
	{
		rx = var->orx + rotx - ((rotx * 2) / WIDTH) * r;
		ry = var->ory + roty - ((roty * 2) / WIDTH) * r;
		double temp = pow(pow(rx, 2) + pow(ry, 2), 0.5);
		rx /= temp;
		ry /= temp;

		h = (1 - (fabs(var->plx) - abs((int)var->plx))) / fabs(rx);
		v = (1 - (fabs(var->ply) - abs((int)var->ply))) / fabs(ry);
		//printf("pV %lf %lf    pH %lf %lf\t", var->plx + rx * v, var->ply + ry * v, var->plx + rx * h, var->ply + ry * h);
		delta_h = 1 / fabs(rx);
		delta_v = 1 / fabs(ry);
		//printf("S %lf    pos %lf    V0 %lf %lf    V1 %lf %lf    V2 %lf %lf\t", rx * v, var->plx, var->plx + rx * v, var->ply + ry * v, var->plx + rx * (v + delta_v), var->ply + ry * (v + delta_v), var->plx + rx * (v + 2 * delta_v), var->ply + ry * (v + 2 * delta_v));
		if (h == delta_h)
			h = 0;
		if (v == delta_v)
			v = 0;

		char	t = 'T';
		int		tx, ty;
		double dst = 0;
		while (1)
		{
			if (v < h)
				dst = v;
			else
				dst = h;
			//dst == v ? printf("	V %lf %lf\t", (var->plx + rx * dst), (var->ply + ry * dst)) : printf("	H %lf %lf\t", (var->plx + rx * dst), (var->ply + ry * dst));

			if (ry > 0)	// N
			{
				if (rx > -0.f)	// NE
				{
					tx = (int)(var->plx + rx * dst);
					ty = (int)(var->ply + ry * dst);
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == 'O')
					{
						//printf("WALL NE	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", (int)(var->plx + rx * dst), (int)(var->ply + ry * dst));
						t = 'W';
						if (dst == v)
							t = 'N';
						// write(1, "\n", 1);
						break;
					}
				}
				else		// NW
				{
					tx = (int)(var->plx + rx * dst) - 1;
					ty = (int)(var->ply + ry * dst);
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == 'O')
					{
						//printf("WALL NW %lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", -1 + (int)(var->plx + rx * dst), (int)(var->ply + ry * dst));
						t = 'E';
						if (dst == v)
							t = 'N';
						// write(1, "\n", 1);
						break;
					}
				}
			}
			else		// S
			{
				if (rx > 0)	// SE
				{
					tx = (int)(var->plx + rx * dst);
					ty = (int)(var->ply + ry * dst) - 1;
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == 'O')
					{
						 //printf("WALL SE	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", (int)(var->plx + rx * dst), -1 + (int)(var->ply + ry * dst));
						t = 'W';
						if (dst == v)
							t = 'S';
						// write(1, "\n", 1);
						break;
					}
				}
				else		// SW
				{
					tx = (int)(var->plx + rx * dst) - 1;
					ty = (int)(var->ply + ry * dst) - 1;
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == 'O')
					{
						//printf("WALL SW	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", -1 + (int)(var->plx + rx * dst), -1 + (int)(var->ply + ry * dst));
						t = 'E';
						if (dst == v)
							t = 'S';
						// write(1, "\n", 1);
						break;
					}
				}
			}
			if (dst == v)
				v += delta_v;
			else
				h += delta_h;
			if (dst > RENDER)
			{
				dst = RENDER + 1;
				break ;
			}
			// if (r > 14)
			// 	printf("%s DEBUG %s\n rx %lf ry %lf dst %lf\n", RED, NORMAL, rx, ry, dst);
		}
		// RD - dst -> wall height
		if (RENDER - dst < 0)
			continue ;
		int renhgt = ((RENDER - dst) / RENDER) * HEIGHT;
		int draws = (HEIGHT - renhgt) / 2;
		for (int i = draws; i < draws + renhgt; i++)
		{
			//printf("dst %lf  renhght %i start %i \n", dst, renhgt, draws);
			var->cvs[i][r - 1] = t;
		}
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		printf("	%s\n", var->cvs[i]);
	}
}

int main(int argc, char **argv)
{
	t_var var;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		init(&var, argv[1]);
	}
	else
		init(&var, NULL);
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
