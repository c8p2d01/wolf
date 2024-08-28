#include "../../inc/parsing.h"

typedef struct s_stack
{
	t_intvctr	nodes[WIDTH * HEIGHT];
	int			top;
}	t_stack;

void	init_stack(t_stack *stack)
{
	stack->top = -1;
}

int	is_empty(t_stack *stack)
{
	return (stack->top == -1);
}

void	push(t_stack *stack, int x, int y)
{
	if (stack->top < WIDTH * HEIGHT)
	{
		stack->top++;
		stack->nodes[stack->top].x = x;
		stack->nodes[stack->top].y = y;
	}
}

t_intvctr	pop(t_stack *stack)
{
	t_intvctr	node;

	node.x = -1;
	node.y = -1;
	if (stack->top >= 0)
	{
		node = stack->nodes[stack->top];
		stack->top--;
	}
	return (node);
}

void	fill_iter(char **map, t_intvctr size, int startX, int startY)
{
	t_stack		stack;
	t_intvctr	node;
	int			x;
	int			y;

	init_stack(&stack);
	push(&stack, startX, startY);
	while (!is_empty(&stack))
	{
		node = pop(&stack);
		x = node.x;
		y = node.y;
		if (x < 0 || x >= size.x || y < 0 || y >= size.y || map[x][y] == ' ')
			continue;
		map[x][y] = ' ';
		push(&stack, x, y - 1);
		push(&stack, x - 1, y);
		push(&stack, x, y + 1);
		push(&stack, x + 1, y);
	}
}