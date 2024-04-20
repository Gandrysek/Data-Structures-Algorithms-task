#include <iostream>
using namespace std;

int  prim_check(int k, int n) {

    if (n == 1) { return 0; }
    for (int i = n / 2; i > 1; i--) {
        if (n % i == 0) {
            return 0;

        }
    }
    return 1;
};

void solve(int n, int k, int index, int c, int** arr, int& kol, int* tmp)
{

    if (n == 0 && tmp[1] == c) {

        for (int i = 1; i < index; i++) {

            arr[kol][i - 1] = tmp[i];


        }
        kol++;
        return;
    }

    for (int i = k; i > 1; i--) {
        if (i > n) {
            continue;
        }
        else if (i <= n) {

            if (prim_check(k, i) == 1) {
                tmp[index] = i;
                solve(n - i, i, index + 1, c, arr, kol, tmp);
            }
        }
    }
}

int main()
{
    int n, k, q;
    cin >> q;
    while (q > 0) {
        int kol = 0;
        int index = 1;
        int** arr = new int* [25];
        for (int i = 0; i < 25; i++) {

            arr[i] = new int[25];
        }
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                arr[i][j] = NULL;
            }
        }
        int* tmp = new int[30];
        cin >> n >> k;
        int c = k;
        solve(n, k, index, c, arr, kol, tmp);
        int j;
        for (int i = kol - 1; i >= 0; i--) {
            for (j = 0; j < 15; j++) {
                if (arr[i][j] != NULL) {
                    if (arr[i][j + 1] == NULL) {
                        cout << arr[i][j];
                    }
                    else {
                        cout << arr[i][j] << "+";
                    }
                }

            }

            cout << endl;

        }

        delete[] tmp;
        for (int i = 0; i < 25; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        q--;
    }
    return 0;
}