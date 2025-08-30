/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:48:53 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 16:20:32 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void print_redir(t_redir *r, int depth)
{
    while (r)
    {
        for (int i = 0; i < depth; ++i)
            printf("  ");

        if (r->type == R_IN)
            printf("REDIR_IN  < %s\n", r->filename);
        else if (r->type == R_OUT)
            printf("REDIR_OUT > %s\n", r->filename);
        else if (r->type == R_APPEND)
            printf("REDIR_APPEND >> %s\n", r->filename);
        else if (r->type == R_HEREDOC)
            printf("HEREDOC << %s\n", r->filename);

        r = r->next;
    }
}

void print_ast(t_ast *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; ++i)
        printf("  ");

    if (node->type == NODE_PIP)
        printf("PIPE\n");
    else if (node->type == NODE_AND)
        printf("AND\n");
    else if (node->type == NODE_OR)
        printf("OR\n");
    else if (node->type == NODE_SUB)
    {
        printf("SUBSHELL\n");
		print_redir(node->redirs, depth + 1);
    }
    else if (node->type == NODE_CMD)
    {
        printf("COMMAND:");
        for (int i = 0; node->cmd && node->cmd[i]; ++i)
            printf(" %s", node->cmd[i]);
        printf("\n");
        print_redir(node->redirs, depth + 1);
    }

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}


void	execute_ast()
{

}
