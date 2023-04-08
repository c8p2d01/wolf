#include "../inc/cub.h"

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
	var->map = init_texture("OOOOOOOOOOOOOOOOO",
							"O               O",
							"O               O",
							"O               O",
							"O               O",
							"O         P     O",
							"O               O",
							"O               O",
							"O               O",
							"O               O",
							"OOOOOOOOOOOOOOOOO", NULL);
	// player
	for (int x = 0; var->map[x]; x++)
	{
		for (int y = 0; var->map[x][y]; y++)
		{
			if (var->map[x][y] == 'P')
			{
				var->positionX = y;
				var->positionY = x;
				var->orientationX = -1;
				var->orientationY = 0;
				var->map[x + (int)var->orientationY][y + (int)var->orientationX] = 'D';
				printf("player at %i %i\n", y, x);
			}
		}
	}
	if (path)
	{
		for (int i = 0; path[i]; i++)
		{
			switch (path[i]) {
				case 'n' : var->positionY--; break;//n
				case 's' : var->positionY++; break;//s
				case 'w' : var->positionX--; break;//w
				case 'e' : var->positionX++; break;//e
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

int	createRGB(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	putPixel(int color)
{
	unsigned char r = color >> 16;
	unsigned char g = color >> 8;
	unsigned char b = color;
	r /= 43; g /= 43; b /= 43;
	char col = 16 + r*36 + g*6 + b;
	printf("\e[48;5;%im  ", col);
}

void	render(t_var *var)
{
	// Sky and Floor coloring
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		memset(var->canvas[i], SKY, WIDTH);
		var->canvas[i][WIDTH] = 0;
	}
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		memset(var->canvas[i + (HEIGHT / 2)], FLOOR, WIDTH);
		var->canvas[i + (HEIGHT / 2)][WIDTH] = 0;
	}
	// rays

	// projection plane on which to cast rays to avoid fishEye view
	double rotx = var->orientationY;
	double roty = -var->orientationX;
	double planelen = pow(pow(var->orientationX, 2) + pow(var->orientationY, 2), 0.5) * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
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
		rx = var->orientationX + rotx - ((rotx * 2) / WIDTH) * r;
		ry = var->orientationY + roty - ((roty * 2) / WIDTH) * r;
		double temp = pow(pow(rx, 2) + pow(ry, 2), 0.5);
		rx /= temp;
		ry /= temp;

		h = (1 - (fabs(var->positionX) - abs((int)var->positionX))) / fabs(rx);
		v = (1 - (fabs(var->positionY) - abs((int)var->positionY))) / fabs(ry);
		//printf("pV %lf %lf    pH %lf %lf\t", var->positionX + rx * v, var->positionY + ry * v, var->positionX + rx * h, var->positionY + ry * h);
		delta_h = 1 / fabs(rx);
		delta_v = 1 / fabs(ry);
		//printf("S %lf    pos %lf    V0 %lf %lf    V1 %lf %lf    V2 %lf %lf\t", rx * v, var->positionX, var->positionX + rx * v, var->positionY + ry * v, var->positionX + rx * (v + delta_v), var->positionY + ry * (v + delta_v), var->positionX + rx * (v + 2 * delta_v), var->positionY + ry * (v + 2 * delta_v));
		if (h == delta_h)
			h = 0;
		if (v == delta_v)
			v = 0;

		int	t = 0;
		int		tx, ty;
		double dst = 0;
		while (1)
		{
			if (v < h)
				dst = v;
			else
				dst = h;
			//dst == v ? printf("	V %lf %lf\t", (var->positionX + rx * dst), (var->positionY + ry * dst)) : printf("	H %lf %lf\t", (var->positionX + rx * dst), (var->positionY + ry * dst));

			if (ry > 0)	// N
			{
				if (rx > -0.f)	// NE
				{
					tx = (int)(var->positionX + rx * dst);
					ty = (int)(var->positionY + ry * dst);
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
					{
						//printf("WALL NE	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", (int)(var->positionX + rx * dst), (int)(var->positionY + ry * dst));
						t = createRGB(255,255,0);
						if (dst == v)
							t = createRGB(255,255,0);;
						// write(1, "\n", 1);
						break;
					}
				}
				else		// NW
				{
					tx = (int)(var->positionX + rx * dst) - 1;
					ty = (int)(var->positionY + ry * dst);
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
					{
						//printf("WALL NW %lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", -1 + (int)(var->positionX + rx * dst), (int)(var->positionY + ry * dst));
						t = createRGB(0,255,0);
						if (dst == v)
							t = createRGB(0,0,255);
						// write(1, "\n", 1);
						break;
					}
				}
			}
			else		// S
			{
				if (rx > 0)	// SE
				{
					tx = (int)(var->positionX + rx * dst);
					ty = (int)(var->positionY + ry * dst) - 1;
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
					{
						 //printf("WALL SE	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", (int)(var->positionX + rx * dst), -1 + (int)(var->positionY + ry * dst));
						t = createRGB(255,255,0);
						if (dst == v)
							t = createRGB(255,0,0);
						// write(1, "\n", 1);
						break;
					}
				}
				else		// SW
				{
					tx = (int)(var->positionX + rx * dst) - 1;
					ty = (int)(var->positionY + ry * dst) - 1;
					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
					{
						//printf("WALL SW	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
						// printf("    seen pos %i %i ", -1 + (int)(var->positionX + rx * dst), -1 + (int)(var->positionY + ry * dst));
						t = createRGB(0,255,0);
						if (dst == v)
							t = createRGB(255,0,0);
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
		int renhgt = ((RENDER -  dst) / RENDER) * HEIGHT;
		int draws = (HEIGHT / 2) - (renhgt / 2);
		for (int i = draws; i <= draws + renhgt; i++)
		{
			//printf("dst %lf  renhght %i start %i \n", dst, renhgt, draws);
			var->canvas[i][r] = t;
		}
	}
	// for (int i = 0; i < (int)strlen(var->canvas[0]); i++)
	// {
	// 	printf("\e[38;5;%im%i", (((i - (i % 10)) * 2) % 256), i % 10);
	// }

	printf("\e[0m\n");
	for (int y = 0; y < HEIGHT; y++)
	{
		printf("\t");
		for (int x = 0; x < (int)strlen((char *)var->canvas[0]) / 4; x++)
		{
			putPixel(var->canvas[y][x]);
		}
		printf("\e[0m\e[38;5;%im%i\e[0m\n", (((y - (y % 10)) + 200) % 256), y % 10);
	}
}

int main(int argc, char **argv)
{
	// printf("%i\n",createRGB(44,44,44));
	t_var var;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		init(&var, argv[1]);
	}
	else
		init(&var, NULL);
	renderer(&var);
	printMap(&var);
	printFrame(&var);
	/* plans:
		raycasting;
		-> make a ray (one pwe width)
		-> repeatedly check the next possible wall intersection until a wall is hit
			pythagoras and map comparison
		figure out the position on the texture and the height to be displayed
		display each texture line
	 */
	// rem(&var);
	return (0);
}
