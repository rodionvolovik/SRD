/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rodionvolovik@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 16:26:41 by rvolovik          #+#    #+#             */
/*   Updated: 2017/07/08 16:26:45 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define BLACK   '#'
#define WHITE   '.'

void    fill_mask(int index, int m, char *line, int *mask)
{
    for (int i = 0; i < m; i++)
    {
        if (line[i] == BLACK)
            mask[i] |= 1 << index;
    }
}

int     is_config_valid(int config, int mask)
{
    if ((config & mask) == mask)
        return (1);
    return (0);
}

int   newQ(int new_mask, int prevconfig, int n)
{
    int     count = 0;
    
    for (int i = 0; i < n; i++)
    {
        if (((new_mask >> (n - 1 - i)) & 1) == 1 && ((prevconfig >> (n - 1 - i)) & 1) == 0
            && ((new_mask >> (n - 2 - i)) & 1) == 1 && ((prevconfig >> (n - 2 - i)) & 1) == 0)
            {
                count++;
                i++;
            }
    }
    return (count);
}

int    solver(int n, int m, int *mask)
{
    int   q_config = 1 << n;
    int   res[q_config][m], restmp;
    int     i, j;
    int   new_mask;

    for (i = 0; i < q_config; i++)
        for (j = 0; j < m; j++)
            res[i][j] = 0;
    for (j = 1; j < m; j++)// cols iterator
    {
        for (i = 0; i < q_config; i++)// iterator of the configurations
        {
            new_mask = 0;
            if (is_config_valid(i, mask[j]))
            {
                new_mask |= mask[j] ^ i;
                for (int k = 0; k < q_config; k++)
                {
                    if (is_config_valid(k, mask[j - 1]))
                    {
                        restmp = res[k][j - 1] + newQ(new_mask, k, n);
                        if (restmp > res[i][j])
                            res[i][j] = restmp;
                    }
                }
            }
        }
    }
    // for(int i = 0; i < q_config; i++)
    // {
    //     for(j = 0; j < m; j++)
    //         printf("%d\t", res[i][j]);
    //     printf("\n");
    // }
    return (res[q_config - 1][m - 1]);
}

int     main(void)
{
    int   n, m, result;

    scanf("%d %d", &n, &m);
    int   mask[m];
    char    line[m];
    for (int j = 0; j < m; j++)
        mask[j] = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", line);
        fill_mask(i, m, line, mask);
    }
    // printf("mask array:\n");
    // for (int k = 0; k < m; k++)
    //     printf("(%d)\t", mask[k]);
    // printf("\n");
    result = solver(n, m, mask);
    printf("%d\n", result);
    return (0);
}