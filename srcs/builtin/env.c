/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:27:53 by gmary             #+#    #+#             */
/*   Updated: 2022/03/29 14:51:13 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/* Permet de trouver le PREMIER egal dans une ligne mais*/

int	find_equal_in_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	g_status = 0;
	while (env[i])
	{
		j = 0;
		if (!find_equal_in_line(env[i]))
		{
			while (env[i][j])
			{
				if (env[i][j] != BACK_SLASH)
					ft_putchar_fd(env[i][j], 1);
				j++;
			}
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}

char	**ft_create_env(char **envp)
{
	char	**env;
	int		line;
	int		i;

	i = 0;
	line = ft_count_line(envp);
	env = malloc(sizeof(char *) * (line + 1));
	if (!env)
		return (NULL);
	while (i < line)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			ft_free_tab_2d(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}
