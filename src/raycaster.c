#include "../inc/cub.h"

double	veclen(int dimension, ...)
{
	double	sum = 0;
	va_list	coordinate;
	va_start(coordinate, dimension);

	for (int i = 0; i < dimension; i++)
	{
		sum += pow(va_arg(coordinate, double), 2);
	}
	return (pow(sum, 0.5));
}

void	normalize(int dimension, ...)
{
	va_list	coordinate;
	double	values[dimension];
	va_start(coordinate, dimension);

	for (int i = 0; i < dimension; i++)
	{
		values[i] = *(va_arg(coordinate, double *));
	}
	va_end(coordinate);

	va_start(coordinate, dimension);
	double	length = 0;
	if (dimension == 2)
		length = veclen(dimension, values[0], values[1]);
	else if (dimension == 3)
		length = veclen(dimension, values[0], values[1], values[2]);
	for (int i = 0; i < dimension; i++)
	{
		double	*num = va_arg(coordinate, double *);
		*num /= length;
	}
	va_end(coordinate);
}

void	rayCreation(t_var	*data, double *rayX, double *rayY, int rayNumber)
{
	static double projectionX,projectionY;
	static bool projectionCalc;

	if (!projectionCalc)
	{
		normalize(2, &data->orientationX, &data->orientationY);
		double	rotator = veclen(2, data->orientationX, data->orientationY) * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
		projectionX = data->orientationY;
		projectionY = data->orientationX * -1;
		normalize(2, &projectionX, &projectionY);

		projectionX *= rotator;
		projectionY *= rotator;
		normalize(2, &projectionX, &projectionY);
		projectionCalc = true;
	}

	*rayX = data->orientationX + projectionX - ((projectionX * 2) / WIDTH) * rayNumber;
	*rayY = data->orientationY + projectionY - ((projectionY * 2) / WIDTH) * rayNumber;

	normalize(2, rayX, rayY);
}

void	firstStep(t_var *data, double *rayR, double *dst, bool isX)
{
	double	delta = 1 / fabs(*rayR);

	double	pos = isX ? data->positionX : data->positionY;
	*dst = (1 - (fabs(pos) - abs((int)pos))) / fabs(*rayR);

	if (*dst == delta)
		*dst = 0;
}

int		rayMarcher(t_var *data, double *dst, int rayNumber)
{
	double	rayX, rayY;

	rayCreation(data, &rayX, &rayY, rayNumber);

	double	minX, minY;
	firstStep(data, &rayX, &minX, true);
	firstStep(data, &rayY, &minY, false);

	double	stepX, stepY;
	stepX = 1 / fabs(rayX);
	stepY = 1 / fabs(rayY);

	int		color = 0;
	// Coordinates to check incoming angle
	int		traceWallX, traceWallY;
	(*dst) = 0;

	while(true)
	{
		(*dst) = minX < minY ? minX : minY;
		if (rayY >= 0)			// North
		{
			if (rayX > 0)	// North-East Wall ?
			{
				traceWallX = (int)(data->positionX + rayX * (*dst));
				traceWallY = (int)(data->positionY + rayY * (*dst));
				if (traceWallX >= 0 && traceWallX < WIDTH && 
					traceWallY >= 0 && traceWallY < HEIGHT &&
					data->map[traceWallY][traceWallX] == 'O')
				{
					color = EAST;
					if ((*dst) == minY)
						color = NORTH;
					if (rayNumber == DEBUG)
					{
						if ((*dst) == minY)
							{data->map[traceWallY][traceWallX] = 'N'; printf("N horizontal wall\n");}
						else
							{data->map[traceWallY][traceWallX] = 'E'; printf("N E vertical wall\n");}
						printMap(data);
						data->map[traceWallY][traceWallX] = 'O';
					}
					break ;
				}
			}
			else				// North-West Wall ?
			{
				traceWallX = (int)(data->positionX + rayX * (*dst)) - 1;
				traceWallY = (int)(data->positionY + rayY * (*dst));
				if (traceWallX >= 0 && traceWallX < WIDTH && 
					traceWallY >= 0 && traceWallY < HEIGHT &&
					data->map[traceWallY][traceWallX] == 'O')
				{
					color = WEST;
					if ((*dst) == minY)
						color = NORTH;
					if (rayNumber == DEBUG)
					{
						if ((*dst) == minY)
							{data->map[traceWallY][traceWallX] = 'N'; printf("N horizontal wall\n");}
						else
							{data->map[traceWallY][traceWallX] = 'W'; printf("N W vertical wall\n");}
						printMap(data);
						data->map[traceWallY][traceWallX] = 'O';
					}
					break ;
				}
			}
		}
		else					// South
		{
			if (rayX > 0)	// South-East Wall ?
			{
				traceWallX = (int)(data->positionX + rayX * (*dst));
				traceWallY = (int)(data->positionY + rayY * (*dst)) - 1;
				if (traceWallX >= 0 && traceWallX < WIDTH && 
					traceWallY >= 0 && traceWallY < HEIGHT &&
					data->map[traceWallY][traceWallX] == 'O')
				{
					color = EAST;
					if ((*dst) == minY)
						color = SOUTH;
					if (rayNumber == DEBUG)
					{
						if ((*dst) == minY)
							{data->map[traceWallY][traceWallX] = 'S'; printf("S horizontal wall\n");}
						else
							{data->map[traceWallY][traceWallX] = 'E'; printf("S E vertical wall\n");}
						printMap(data);
						data->map[traceWallY][traceWallX] = 'O';
					}
					break ;
				}
			}
			else				// South-West Wall ?
			{
				traceWallX = (int)(data->positionX + rayX * (*dst)) - 1;
				traceWallY = (int)(data->positionY + rayY * (*dst)) - 1;
				if (traceWallX >= 0 && traceWallX < WIDTH && 
					traceWallY >= 0 && traceWallY < HEIGHT &&
					data->map[traceWallY][traceWallX] == 'O')
				{
					color = WEST;
					if ((*dst) == minY)
						color = SOUTH;
					if (rayNumber == DEBUG)
					{
						if ((*dst) == minY)
							{data->map[traceWallY][traceWallX] = 'S'; printf("S horizontal wall\n");}
						else
							{data->map[traceWallY][traceWallX] = 'W'; printf("S W vertical wall\n");}
						printMap(data);
						data->map[traceWallY][traceWallX] = 'O';
					}
					break ;
				}
			}
		}
		if ((*dst) == minY)
		{
			if (rayNumber == DEBUG)
			{
				printf("adding hori\n");
			}
			minY += stepY;
		}
		else
		{
			if (rayNumber == DEBUG)
			{
				printf("adding verti\n");
			}
			minX += stepX;
		}
		if ((*dst) > RENDER)
		{
			(*dst) = RENDER + 1;
			break ;
		}
	}
	return (color);
}

int	terminalColor(int r, int g, int b)
{
	r /= 43; g /= 43; b /= 43;
	return (16 + r*36 + g*6 + b);
}

void	printFrame(t_var *data)
{
	printf("\e[0m\n");
	for (int y = 0; y < HEIGHT; y++)
	{
		printf("\t");
		for (int x = 0; x < WIDTH; x++)
		{
			putPixel(data->canvas[y][x]);
		}
		printf("\e[0m\n");
	}
}

void	printMap(t_var *data)
{
	printf("\e[0m\n");
	int		len = 0;
	char	c;
	while (data->map[len])
		len++;
	for (int y = 0; y < len; y++)
	{
		printf("\t");
		for (int x = 0; x < strlen(data->map[0]); x++)
		{
			c = data->map[y][x];
			printf("\e[48;5;%im  ", c == 'O' ? terminalColor(200,200,200) :
									c == ' ' ? terminalColor(100,100,100) :
									c == 'P' ? terminalColor(255,100,100) :
									c == 'D' ? terminalColor(100,255,100) :
									c == 'N' ? 21 :
									c == 'S' ? 196 :
									c == 'W' ? 226 :
									c == 'E' ? 46 : 16);
		}
		printf("\e[0m\n");
	}
}

void	stretcher(t_var *data, int rayNumber, double dst, int color)
{
	int renderHeight = ((double)((double)RENDER - dst) / (double)RENDER) * HEIGHT;
	int draws = (HEIGHT / 2) - (renderHeight / 2);
	for (int i = draws; i <= draws + renderHeight; i++)
	{
		data->canvas[i][rayNumber] = color;
	}
}

void	renderer(t_var *data)
{
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		for (int x = 0; x < WIDTH; x++)
			data->canvas[i][x] = SKY;
		data->canvas[i][WIDTH] = 0;
	}
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		for (int x = 0; x < WIDTH; x++)
			data->canvas[i + (HEIGHT / 2)][x] = FLOOR;
		data->canvas[i + (HEIGHT / 2)][WIDTH] = 0;
	}

	int		color = 42;
	double	dst = RENDER + 1;

			printf("\t");
	for (int r = 0; r < WIDTH; r++)
	{
		color = rayMarcher(data, &dst, r);
		if (RENDER - dst < 0)
		{
			continue ;
		}
		stretcher(data, r, RENDER, color);
	}
}

// int main()
// {
// 	t_var	data;
// 	double	rayX, rayY;
// 	data.orientationX = -1;
// 	data.orientationY = -1;
// 	for(int i = 0; i < WIDTH; i++)
// 	{
// 		rayCreation(&data, &rayX, &rayY, i);
// 		printf("ray %i	%lf	%lf\n", i, rayX, rayY);
// 	}
// }
