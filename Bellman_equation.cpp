#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
 
using namespace std;
 
const int N = 1e3+5;
const int inf = 1e9;
 
int dp[N][N]; //таблица динамики
int task[N]; //заданное состояние на каждом шаге
int answers[N]; //оптимальное управление на каждом шаге
 
struct bound {
    int left_bound;
    int right_bound;
};
 
int func (int y, int y1, int i) { //показатель эффективности; y = y_i, y1 = y_i-1
    int g1 = 0, g2 = 0;
    if (y > y1)
        g1 = 6 + 3 * (y - y1);
 
    if (y > task[i])
        g2 = 5*(y - task[i]);
 
    return (g1 + g2);
}
 
 
 
int main() {
    int n, m; //количество состояний, кол-во рабочих
    cin >> n >> m;
 
    for (int i = 0; i < n; ++i) //вводим заданное состояние на каждом шаге
        cin >> task[i];
 
    for (int i = 0; i < n; ++i) //инициализируем табличку
        for (int j = 0; j < m; ++j)
            dp[i][j] = inf;
 
    vector <bound> b; //границы на каждом шаге (можно убрать и вычислять всю таблицу)
 
    for (int i = 0; i < n; ++i) {
        bound x;
        cin >> x.left_bound >> x.right_bound;
        b.push_back(x);
    }
 
    //база динамики
    for (int j = b[n-1].left_bound; j <= b[n-1].right_bound; ++j) {
        if (j >= task[n-1])
            dp[n-1][j] = 0;
        else
            dp[n-1][j] = 6 + 3 * (task[n-1] - j);
    }
    answers[n-1] = task[n-1];
    //answers для n-2 -ого элемента (не база и не считается в цикле), равен максимальному индексу со значением равным минимуму в предыдущем состоянии

 
    for(int i = n - 2; i >= 0; --i) {
        for(int j = b[i].left_bound; j <= b[i].right_bound; ++j) {
            int f = func(j, task[i], i + 1);
            int mn = inf;
            for(int x = b[i].left_bound; x <= b[i].right_bound ; x++)
                mn = min(mn, dp[i + 1][x]);
            cout << i << " " << j << " " << mn << "\n";
            dp[i][j] = mn;
            if (dp[i][j] <= dp[i][j - 1]) {
                answers[i] = j;
            }
 
            dp[i][j] = min(dp[i][j],  dp[i][j-1]) + f;
        }
    }

    //выводим ответ
    int ans = 1e9;
    for(int i = 0; i <= m; i++) {
        if(dp[0][i]) {
            ans = min(ans, dp[0][i]);
        }
    }
    cout << "F_n = " << ans << "\n";
    for(int i = 0; i < n; i++)
        cout << answers[i] << " ";
    return 0;
}

//5 8
//5 7 8 4 6
//5 5
//5 8
//7 8
//8 8
//4 8

