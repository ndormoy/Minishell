/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remix_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:40:21 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/11 11:41:28 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	check_file_valid_bis(t_command *tmp, t_command *previous)
{
	if ((access((tmp->cmd_to_exec[0]), F_OK | R_OK) < 0
			&& previous->type == CHV_L))
		return (TRUE);
	else if (access((tmp->cmd_to_exec[0]), F_OK) >= 0
		&& (previous->type == CHV_R
			|| previous->type == D_CHV_R))
		if (access((tmp->cmd_to_exec[0]), W_OK) < 0)
			return (TRUE);
	return (FALSE);
}
