/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:31:46 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 13:31:55 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	token_is_redir(t_token *tmp_token)
{
	if (tmp_token->type == CHV_L)
		return (1);
	if (tmp_token->type == D_CHV_L)
		return (1);
	if (tmp_token->type == CHV_R)
		return (1);
	if (tmp_token->type == D_CHV_R)
		return (1);
	return (0);
}

int	token_is_operator(t_token *tmp_token)
{
	if (tmp_token->type == PIPE)
		return (1);
	if (tmp_token->type == CHV_L)
		return (1);
	if (tmp_token->type == D_CHV_L)
		return (1);
	if (tmp_token->type == CHV_R)
		return (1);
	if (tmp_token->type == D_CHV_R)
		return (1);
	return (0);
}

/* Transforme notre liste token en liste de cmd*/

t_command	*token_to_cmd(t_token *all, t_to_clean *clean)
{
	t_command	*cmd_all;
	t_token		*tmp_token;

	cmd_all = NULL;
	tmp_token = all;
	while (tmp_token)
	{	
		if (!token_is_operator(tmp_token))
			ft_add_back_cmd(&cmd_all,
				create_new_cmd_node(token_to_tab(tmp_token, clean),
					tmp_token, clean));
		while (tmp_token && !token_is_operator(tmp_token))
			tmp_token = tmp_token->next;
		if (tmp_token && token_is_operator(tmp_token))
			ft_add_back_cmd(&cmd_all,
				create_new_cmd_node(token_op_to_tab(tmp_token, clean),
					tmp_token, clean));
		if (tmp_token)
			tmp_token = tmp_token->next;
	}
	return (cmd_all);
}
