/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:40:20 by tsimitop          #+#    #+#             */
/*   Updated: 2024/09/10 18:40:22 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include "cub.h"
# include "configs.h"

void	scroll_hook(double xdelta, double ydelta, void *param);

void	print_setting(t_var *data);
void	test_setting(double xdelta, double ydelta, t_var *data);
void	norm_setting(double xdelta, double ydelta, t_var *data);
void	debug_setting(double xdelta, double ydelta, t_var *data);
void	fov_setting(double xdelta, double ydelta, t_var *data);
void	zoom_setting(double xdelta, double ydelta, t_var *data);
void	style_setting(double xdelta, double ydelta, t_var *data);
void	offset_setting(double xdelta, double ydelta, t_var *data);
void	height_setting(double xdelta, double ydelta, t_var *data);
void	width_setting(double xdelta, double ydelta, t_var *data);
void	move_setting(double xdelta, double ydelta, t_var *data);
void	turn_setting(double xdelta, double ydelta, t_var *data);
void	turn_mouse_setting(double xdelta, double ydelta, t_var *data);

#endif