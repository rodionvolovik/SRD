/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rodionvolovik@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 16:42:36 by rvolovik          #+#    #+#             */
/*   Updated: 2017/07/10 10:57:50 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define MAX_RESULT  2000000000
#define N_MAX       1000
#define DATA_NUMBER 3
#define S           0
#define N           1
#define M           2
#define S_SYM       1
#define N_SYM       2
#define M_SYM       4
#define X_SYM       7

void    init_arr(int *arr, int content, int n, int length)
{
    arr[0] = 0;
    for (int i = 1; i < length; i++)
        arr[i] = content;
}

int     min_val_count(int c, int m, int l, int k)
{
    return (l * c + k * m);
}

int     check_condition(int iS, int i_LS, int iN, int i_LN, int iM, int i_LM)
{
    int     count = 0;
    int     mask = 0;

    if (iS - i_LS == 0)
        count++;
    else
        mask = S_SYM;
    if (iN - i_LN == 0)
        count++;
    else
        mask = N_SYM;
    if (iM - i_LM == 0)
        count++;
    else
        mask = M_SYM;
    if (count == 2)
        return (mask);
    else if (count == 3)
        return (X_SYM);
    return (-1);
}

int    solver(int n, int c, int k, char *data)
{
    int     m, l = 1;
    int     table[DATA_NUMBER][n + 1];
    int     arr1[n + 1], arr2[n + 1];
    int     var1, var2, mask;
    int     min_val;
    int     i, j;

    for (i = 0; i < DATA_NUMBER; i++)
        table[i][0] = 0;
    i = 0;
    while (data[i])
    {
        table[S][i + 1] = data[i] == 'S' ? table[S][i] + 1 : table[S][i];
        table[N][i + 1] = data[i] == 'N' ? table[N][i] + 1 : table[N][i];
        table[M][i + 1] = data[i] == 'M' ? table[M][i] + 1 : table[M][i];
        i++;
    }

    arr1[0] = 0;
    arr2[0] = 0;
    min_val = min_val_count(c, n, l++, k);

    int     ii, ll, flag = 0;

    while (arr1[n] < MAX_RESULT)
    {
        i = 1;
        ii = i - 1;
        ll = l - 1;
        while (i <= n)
        {
            var1 = MAX_RESULT;
            var2 = 0;
            if (i <= ll)
            {
                if (data[ii] != '*')
                {
                    if (!flag)
                        flag = data[ii];
                    else if (data[ii] != flag)
                    {
                        arr1[n] = MAX_RESULT;
                        break;
                    }
                }
            }
            else
            {
                if ((mask = check_condition(table[S][i], table[S][i - l], table[N][i], table[N][i - l], table[M][i], table[M][i - l])) >= 0)
                {
                    // printf("mask = %d\n", mask);
                    if (arr1[i - l] != MAX_RESULT)
                    {
                        var1 = arr1[i - l] + 1;
                        var2 = mask;
                    }
                    j = i - l + 1;
                    while (j < i)
                    {
                        if ((mask & arr2[j]) != 0 && arr1[j] + 1 < var1)
                        {
                            var1 = arr1[j] + 1;
                            var2 = mask & arr2[j];
                        }
                        j++;
                    }
                }
            }
            arr1[i] = var1;
            arr2[i] = var2;
            i++;
        }
        if (arr1[n] != MAX_RESULT)
        {
            if (min_val_count(c, arr1[n], l, k) <= min_val)
                min_val = min_val_count(c, arr1[n], l, k);
        }
        l++;
    }
    return (min_val);
}

int     main(void)
{
    int         n, c, k, result;
    char        data[N_MAX + 1];
    int         i;

    scanf("%d %d %d", &n, &c, &k);
    scanf("%s", data);
    result = solver(n, c, k, data);
    printf("%d\n", result);
    return (0);
}

// TEST CASES
// > ./a.out
// 7 13 8
// S***N*M
// 58
// > ./a.out
// 10 42 68
// **SSS*NM**
// 492
// > ./a.out
// 20 71 30
// ***S*S*M**N*********
// 423
// > ./a.out
// 30 49 84
// S**M*SSSS*NNN*N***NN**M*NNN**S
// 1358