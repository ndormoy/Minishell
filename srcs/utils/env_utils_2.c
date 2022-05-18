/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:00:53 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 14:00:54 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Trouve la ligne ou est la var d'env (si elle existe), sinon renvoie NULL*/

char	*ft_find_env_line(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!is_var_in_line(env[i], var, ft_strlen(var)))
			return (env[i]);
		i++;
	}
	return (NULL);
}
