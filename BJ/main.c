/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 15:10:35 by rvolovik          #+#    #+#             */
/*   Updated: 2017/07/07 21:02:10 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#define BLACK   '#'
#define WHITE   '.'

void    fill_mask(int index, int m, char *line, short *mask)
{
    for (int i = 0; i < m; i++)
    {
        if (line[i] == BLACK)
            mask[i] |= 1 << index;
    }
}

int     main(void)
{
    int     n, m, result;

    scanf("%d %d", &n, &m);
    short   mask[m];
    char    line[m];
    for (int j = 0; j < m; j++)
        mask[j] = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", line);
        fill_mask(i, m, line, mask);
    }
    printf("mask array:\n");
    for (int k = 0; k < m; k++)
        printf("(%hd)\t", mask[k]);
    printf("\n");
    return (0);
}