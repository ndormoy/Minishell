/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:30 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/06 14:03:07 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	manage_check_cmd_list(t_token *tmp, t_to_clean *clean)
{
	if (check_cmd_list(tmp) < 0)
	{
		ft_lstclear(&tmp, free);
		free(clean);
		return (FALSE);
	}
	return (TRUE);
}

int	manage_check_quote(char *line, t_to_clean *clean)
{
	if (check_quote(line) == FALSE)
	{
		ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
		free(clean);
		free(line);
		return (FALSE);
	}
	return (TRUE);
}

char	**manage_line_bis_2(t_command *cmd_all, t_to_clean *clean,
		char **env, t_token *expanded)
{
	remix_2(&cmd_all);
	manage_line_clean(clean, cmd_all, expanded);
	return (env);
}

void	check_if_exit(t_to_clean *clean, t_command *all, t_token *expanded)
{
	prio_exit(all);
	if (((condition_if_exit(all) == TRUE) && all->cmd_to_exec[1]
			&& (is_str_digit(all->cmd_to_exec[1]) == FALSE))
		|| (all->next && (condition_if_exit(all) == TRUE)
			&& (is_redirection_type(all->next) == FALSE)))
	{
		manage_line_clean(clean, all, expanded);
		exit (g_status);
	}
	manage_line_clean(clean, all, expanded);
}
