/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:10:29 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:34:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int	logic_or(int parent_up, int parent_total)
{
	(void)parent_total;
	return (parent_up > 0);
}

int	logic_and(int parent_up, int parent_total)
{
	return (parent_up == parent_total);
}

int	logic_xor(int parent_up, int parent_total)
{
	return (parent_up < parent_total || parent_up > 0);
}

int	logic_xnor(int parent_up, int parent_total)
{
	return (parent_up < parent_total || parent_up > 0);
}

int	logic_nor(int parent_up, int parent_total)
{
	(void)parent_total;
	return (parent_up == 0);
}

int	logic_nand(int parent_up, int parent_total)
{
	return (parent_up != parent_total);
}
