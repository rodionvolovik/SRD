/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rodionvolovik@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 16:42:36 by rvolovik          #+#    #+#             */
/*   Updated: 2017/07/08 20:02:35 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define MAX_RESULT  2000000000
#define N_MAX       1000
#define DATA_NUM    3
#define S           0
#define N           1
#define M           2
#define S_SYM       1
#define N_SYM       2
#define M_SYM       4
#define X_SYM       7

void    init_arr(int *arr, int content, int n)
{
    arr[0] = 0;
    arr[1] = content;
}

int     check_numbers(int a, int b, int c)
{
    if (a == b && a != c)
        return (M_SYM);
    else if (a == c && a != b)
        return (N_SYM);
    else if (b == c && a != c)
        return (S_SYM);
    return (-1);
}

int     main(void)
{
    int         n, c, k, m, l = 1, result;
    char        data[N_MAX + 1];
    int         i, j;
    int         min_val;

    while (i <= N_MAX)
        data[i++] = '\0';
    scanf("%d %d %d", &n, &c, &k);
    scanf("%s", data);

    int     table[DATA_NUM][n + 1];
    int     arr1[n + 1], arr2[n + 1];
    int     *tableptr;
    for (i = 0; i < DATA_NUM; i++)
        table[i][0] = 0;
    i = 0;
    while (data[i])
    {
        table[S][i + 1] = data[i] == 'S' ? table[S][i] + 1 : table[S][i];
        table[N][i + 1] = data[i] == 'N' ? table[N][i] + 1 : table[N][i];
        table[M][i + 1] = data[i] == 'M' ? table[M][i] + 1 : table[M][i];
        i++;
    }
    tableptr = &table[0][0];
    init_arr(arr1, MAX_RESULT, n);
    init_arr(arr2, 0, n);
    min_val = l * c + k * n;
    l++;
    int     var1 = MAX_RESULT;
    int     var2 = 0;
    int     mask = 0;
    int     t;
    i = L;
    j = 1;
    while (i <= N)
    {
        if ((mask = check_numbers(table[0][i], table[1][i], table[2][i])) >= 0)//two of three rows where numbers are not deffer
        {
            if (arr1[i - L] != MAX_RESULT)
            {
                var1 = arr[i - L] + 1;
                var2 = mask;
            }
            j = i - L + 1;
            while (j < i)
            {
                if (mask & arr2[j] != 0 && arr1[j] + 1 < var1)
                {
                    var1 = arr1[j] + 1;
                    var2 = mask & arr2[j];
                }
                j++;
            }
        }
        arr1[i] = var1;
        arr2[i] = var2;
        i++;
    }
    // for (i = 0; i < DATA_NUM; i++)
    // {
    //     for (j = 0; j < n + 1; j++)
    //         printf("%d\t", table[i][j]);
    //     printf("\n");
    // }
    // printf("%d\n", result);
    return (0);
}