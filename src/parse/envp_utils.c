/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:25:31 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:17:56 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/*
copy envp array to tools->envp
store in list? so we can modify and add content in between?
sort input
'export' built in -> prints list as
	'declare -x [..]'

*/
