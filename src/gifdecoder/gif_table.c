/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:17 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:18 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"

t_table	*new_table(int key_size)
{
	int		key;
	int		init_bulk;
	t_table	*table;

	init_bulk = max(1 << (key_size + 1), 0x100);
	table = ft_malloc(sizeof(*table) + sizeof(t_entry) * init_bulk);
	if (table)
	{
		table->bulk = init_bulk;
		table->nentries = (1 << key_size) + 2;
		table->entries = (t_entry *) &table[1];
		key = 0;
		while (key < (1 << key_size))
		{
			table->entries[key] = (t_entry){1, 0xFFF, key};
			key++;
		}
	}
	return (table);
}

/* Add table entry. Return value:
 *  0 on success
 *  +1 if key size must be incremented after this addition
 *  -1 if could not realloc table */
int	add_entry(t_table **tablep, uint16_t length, \
											uint16_t prefix, uint8_t suffix)
{
	t_table	*table;

	table = *tablep;
	if (table->nentries == table->bulk)
	{
		table->bulk *= 2;
		table = realloc(table, sizeof(*table) + sizeof(t_entry) * table->bulk);
		if (!table)
			return (-1);
		table->entries = (t_entry *) &table[1];
		*tablep = table;
	}
	table->entries[table->nentries] = (t_entry){length, prefix, suffix};
	table->nentries++;
	if ((table->nentries & (table->nentries - 1)) == 0)
		return (1);
	return (0);
}

static int	inner_reader(t_gd_gif *gif, t_gif_read_vars *vars)
{
	if (vars->sub_len == 0)
	{
		read(gif->fd, &vars->sub_len, 1);
		if (vars->sub_len == 0)
			return (0x1000);
	}
	read(gif->fd, &vars->byte, 1);
	return (0);
}

uint16_t	get_key(t_gd_gif *gif, t_gif_read_vars *vars)
{
	int	bits_read;
	int	rpad;
	int	frag_size;
	int	key;

	key = 0;
	bits_read = 0;
	while (bits_read < vars->key_size)
	{
		rpad = (vars->shift + bits_read) % 8;
		if (rpad == 0)
		{
			if (inner_reader(gif, vars) == 0x1000)
				return (0x1000);
			(vars->sub_len)--;
		}
		frag_size = min(vars->key_size - bits_read, 8 - rpad);
		key |= ((uint16_t)((vars->byte) >> rpad)) << bits_read;
		bits_read += frag_size;
	}
	key &= (1 << vars->key_size) - 1;
	vars->shift = (vars->shift + vars->key_size) % 8;
	return (key);
}
