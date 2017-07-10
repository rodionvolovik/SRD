/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rodionvolovik@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 11:00:06 by rvolovik          #+#    #+#             */
/*   Updated: 2017/07/10 18:44:22 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void     find_further_city(int room, int *matrix, int *visited, int n, int *longest, int *distance)
{
    int     i;
    int     tmp;

    visited[room] = 1;
    for (i = 0; i < n; i++)
    {
        if (!visited[i] && matrix[room * n + i])
        {
            tmp = matrix[room * n + i];
            distance[1] += tmp;
            if (distance[0] < distance[1])
            {
                distance[0] = distance[1];
                *longest = i;
            }
            find_further_city(i, matrix, visited, n, longest, distance);
            distance[1] -= tmp;
        }
    }
    visited[room] = 0;
}

int     distance(int room, int *matrix, int *visited, int n)
{
    int     longest = 0;
    int     distance[2];
    int     result = 0;

    distance[0] = 0;
    distance[1] = 0;
    find_further_city(room, matrix, visited, n, &longest, distance);
    if (longest == 0)
        return (0);
    else
        find_further_city(longest, matrix, visited, n, &longest, distance);
    return (distance[0]);
}

int    solver(void)
{
    int     max_result = 0;
    char    line = '\n';
    int     city1, city2, cost;
    int     n, i, j;
    int     *ptr;
    int     tmp;
    
    while (line == '\n')
        scanf("%c", &line);
    n = line - 48;
    
    int     matrix[n][n];
    int     visited[n];
    
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        for (j = 0; j < n; j++)
            matrix[i][j] = 0;
    }
    
    for (i = 0; i < n - 1; i++)
    {
        scanf("%d %d %d", &cost, &city1, &city2);
        matrix[city1 - 1][city2 - 1] = cost;
        matrix[city2 - 1][city1 - 1] = cost;
    }
    ptr = &matrix[0][0];
    int     tmp_result;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= i; j++)
        {
            if (matrix[i][j])
            {
                tmp = matrix[i][j];
                matrix[i][j] = 0;
                matrix[j][i] = 0;

                // printf("deleted edge = %d\n", tmp);
                if ((tmp_result = distance(i, ptr, visited, n) + distance(j, ptr, visited, n)) + tmp > max_result)
                    max_result = tmp_result + tmp;
                    
                matrix[i][j] = tmp;
                matrix[j][i] = tmp;
            }
        }
    }
    return (max_result);
}

int     main(void)
{
    int     test_number;
    
    scanf("%d", &test_number);
    int     result[test_number];
    // printf("test_number %d\n", test_number);
    for (int test_case = 0; test_case < test_number; test_case++)
        result[test_case] = solver();  // n - number of rooms);
    for (int test_case = 0; test_case < test_number; test_case++)
        printf("%d %d\n", test_case + 1, result[test_case]);
    return (0);
}