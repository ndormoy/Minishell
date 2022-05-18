/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:20:03 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 17:56:29 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Permet de supprimer les fichiers temporaires .heredoc*/

int	delete_heredoc_file(t_command *all_cmd)
{
	t_command	*tmp;

	tmp = all_cmd;
	while (tmp)
	{
		if (tmp->to_del == 1)
		{
			if (unlink(tmp->cmd_to_exec[0]) < 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*Permet de savoir si le dernier element du tableau stop
possede des quotes ou non. Si il possede des quote on renvoie
0, et on expandra pas. Si il n'en possede pas on revoie 1 et 
on expandra*/

int	is_expand_heredoc(char **stop)
{
	int	last;
	int	i;

	i = 0;
	last = ft_count_line(stop) - 1;
	while (stop[last][i])
	{
		if (stop[last][i] == QUOTE
			|| stop[last][i] == D_QUOTE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*Permet de compter combien il y a de quote dans le tableau str*/

int	count_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE)
			count++;
		i++;
	}
	return (count);
}

/*Cette fonction permet d'enlever les quote dans un tableau
normal*/

char	*trim_line_stop(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(sizeof(char), (ft_strlen(str) - count_quote(str) + 2));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i] != QUOTE && str[i] != D_QUOTE)
		{
			ret[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	ret[j] = '\0';
	return (ret);
}

/*Permet d'enlever les quotes dans le tableau stop, qui regroupe les
limitor du heredoc, renvoie ce tableau Stop*/

char	**trim_quote_stop(char **strs)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	ret = ft_calloc(sizeof(char *), (ft_count_line(strs) + 1));
	if (!ret)
		return (NULL);
	while (strs[i])
	{
		ret[i] = trim_line_stop(strs[i]);
		if (!ret)
			return (NULL);
		i++;
	}
	ft_free_tab_2d(strs);
	return (ret);
}
