/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:40:26 by rvolovik          #+#    #+#             */
/*   Updated: 2017/07/13 09:59:33 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define MAX_NUMBER  999

int     main(void)
{
    int     n, o, m, number;
    int     numbers[MAX_NUMBER + 1];
    int     i = 0, j = 0;
    char    line[100];

    scanf("%d %d %d", &n ,&o ,&m);
    scanf("%s", line);

    int     digits[n];
    int     operations[o];
    while (i < n)
    {
        digits[i] = line[j] - 48;
        i++;
        j += 2;
    }
    scanf("%s", line);
    i = 0;
    j = 0;
    while (i < o)
    {
        operations[i] = line[j] - 48;
        i++;
        j += 2;
    }
    scanf("%d", &number);
    i = 0; j = 0;
    while (i < n)
        printf("%d\t", digits[i++]);
    printf("\n");
    while (j < o)
        printf("%d\t", operations[j++]);
    printf("\n%d\n", number);
    return (0);
}