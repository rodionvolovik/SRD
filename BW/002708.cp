#include <iostream>
using namespace std;

#define S           0
#define N           1
#define M           2
#define MAX_RESULT  1000000000

int getMask(char c, int *tab, int i, int size, int l) {
    if (c == 'S')
        return 1;
    else if (c == 'N')
        return 2;
    else if (c == 'M')
        return 4;
    else {
        int s1, s2, n1, n2, m1, m2;
        s1 = tab[0 + i];
        s2 = tab[0 + i - l];
        n1 = tab[N * size + i];
        n2 = tab[N * size + i - l];
        m1 = tab[M * size + i];
        m2 = tab[M * size + i - l];
        if (s1 != s2)
            return 1;
        else if (n1 != n2)
            return 2;
        else if (m1 != m2)
            return 4;
        else
            return 7;
    }
}

bool checkRows(int *tab, int i, int size, int l) {
    int s1, s2, n1, n2, m1, m2;

    s1 = tab[0 + i];
    s2 = tab[0 + i - l];
    n1 = tab[N * size + i];
    n2 = tab[N * size + i - l];
    m1 = tab[M * size + i];
    m2 = tab[M * size + i - l];
    if ((s1 == s2 && n1 == n2) ||
        (s1 == s2 && m1 == m2) ||
        (n1 == n2 && m1 == m2))
        return true;
    return false;
}

int lenCount(int l, int n, char *data, int *tab) {
    int     arr2[n];
    int     arr1[n];
    int     ll = l - 1;
    char    base = 0;
    int     var1, var2;
    int     k;
    int     mask;
    int     j;

	arr1[0] = 0;
	arr2[0] = 0;
    for (int i = 1; i < n; i++) {
        var1 = MAX_RESULT;
        var2 = 0;
        k = i - 1;
        if (i <= ll) {
            if (data[k] != '*') {
                if (base == 0)
                    base = data[k];
                else if (data[k] != base)
                    return MAX_RESULT;
            }
        } else {
            if (checkRows(tab, i, n, l)) {
                mask = getMask(data[k], tab, i, n, l);
                if (arr1[i - l] != MAX_RESULT) {
                    var1 = arr1[i - l] + 1;
                    var2 = mask;
                }
                j = i - l + 1;
                while (j < i) {
                    int tmpMask = mask & arr2[j];
                    if (tmpMask != 0 && (arr1[j] + 1) < var1) {
                        var1 = arr1[j] + 1;
                        var2 = tmpMask;
                    }
                    j++;
                }
            }
        }
        arr1[i] = var1;
        arr2[i] = var2;
        cout << "count:  " << arr1[i] <<"; maks: " << arr2[i] << endl;
    }
    return arr1[n - 1];
}

int minPrice(int n, int c, int k, char *data) {
    int baseTab[3][n + 1];
    int minVal = c + k * n;
    int l = 2;

    for (int i = 0; i < 3; i++)
        baseTab[i][0] = 0;
    for (int j = 0; j < n; j++) {
        baseTab[S][j + 1] = (data[j] == 'S' ? baseTab[S][j] + 1 : baseTab[S][j]);
        baseTab[N][j + 1] = (data[j] == 'N' ? baseTab[N][j] + 1 : baseTab[N][j]);
        baseTab[M][j + 1] = (data[j] == 'M' ? baseTab[M][j] + 1 : baseTab[M][j]);
    }
    int *baseTabLink = &baseTab[0][0];
    int len;
    while ((len = lenCount(l, n + 1, data, baseTabLink)) < MAX_RESULT) {
        int curVal = c * l + k * len;
        if (curVal < minVal)
            minVal = curVal;
        l++;
    }
    return minVal;
}

int main() {
    int     n, c, k, result;

    cin >> n >> c >> k;
    char    data[n + 1];
    for (int i = 0; i < n; i++)
        cin >> data[i];
    data[n] = '\0';
    result = minPrice(n, c, k, data);
    cout << result << endl;
    return 0;
}
