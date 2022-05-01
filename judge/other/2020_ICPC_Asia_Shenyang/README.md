# G The Witchwood
非常简单
# F Kobolds and Catacombs
题面：[Kobolds and Catacombs](https://codeforces.com/gym/103202/problem/F)
    
思路：读取n个数到数组arr中，维护一个数组pre_max，其中pre_max[i]表示arr[0...i]中最大的数，维护一个数组last_min，其中last_min[i]表示arr[i...n - 1]中最小的数。对于i从0到n - 2，当pre_max[i] <= last_min[i + 1]时，分割次数+1（因为题目搞这个分组的目标还是要把这n个数排成非降序的，pre_max[i] <= last_min[i + 1]时，arr[i + 1...n - 1]中的数不会在排序后跑到arr[0...i]中，arr[0...i]中的数也不会在排序后跑到arr[i + 1...n - 1]中，所以可以以i为界分组）    
题目要分组数，所以答案为 分组数=分割次数+1

代码：
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int pre_max[maxn], last_min[maxn], arr[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, ans = 1;
    cin >> n;
    cin >> arr[0];
    pre_max[0] = arr[0];
    for(int i = 1; i < n; i++) {
        cin >> arr[i];
        pre_max[i] = max(arr[i], pre_max[i - 1]);
    };
    last_min[n - 1] = arr[n - 1];
    for(int i = n - 2; i >= 0; i--) {
        last_min[i] = min(last_min[i + 1], arr[i]);
    }
    for(int i = 0; i < n - 1; i++) {
        if(pre_max[i] <= last_min[i + 1])    ans++;
    }
    cout << ans << "\n";
    return 0;
}
```

# D Journey to Un'Goro
题面：[Journey to Un'Goro](https://codeforces.com/gym/103202/problem/D)  
思路：    
对于长度为n的路，定义长度为n + 1的数组cr，cr[i]代表前i块砖中红色砖的个数, cr[0] = 0, 则从第i步到第j步走过的红色砖个数为 cr[j] - cr[i - 1], 要想这个数为奇数，cr[j] 与 cr[i - 1]的奇偶性要不同。对于长度为n的路，要想(i, j)对最多，cr中 | 奇数个数 - 偶数个数 | <= 1(n + 1为奇数时等于1), 最大个数为 ceil((n + 1) / 2) * floor((n + 1) / 2)。    
对于寻找方案可以用深度优先搜索，从左到右枚举每一位的情况(先b后r，因为要字典序最小)。    
代码：
```c++
#include <bits/stdc++.h>
using namespace std;
string que;
int n, cnt = 0;

void solve(int pos, int odd, int even, int num) {
    if(cnt == 100 || max(odd, even) > ceil((double) (n + 1) / 2)) return;
    if(pos == n) {
        cnt++;
        printf("%s\n", que.c_str());
        return;
    }
    que.push_back('b');
    if(num % 2) solve(pos + 1, odd + 1, even, num);
    else        solve(pos + 1, odd, even + 1, num);
    que.pop_back();
    que.push_back('r');
    if(num % 2) solve(pos + 1, odd, even + 1, num + 1);
    else        solve(pos + 1, odd + 1, even, num + 1);
    que.pop_back();
}

int main() {
    scanf("%d", &n);
    printf("%lld\n", (long long) ((n + 1) / 2) * ((int) ceil((double) (n + 1) / 2)));
    solve(0, 0, 1, 0);
    return 0;
}
```

# H The Boomsday Project
题面：[The Boomsday Project](https://codeforces.com/gym/103202/problem/H)    
思路：    
一道动态规划题。    
设此人的租车总数为sumq，sumq <= 3 * 1e5，定义长度为sumq + 1的数组dp，dp[i]表示租车次数为i时所需的最小金钱，则dp[sumq]为答案。     
设给定的租车卡种类有n种，则实际租车卡有n + 1种(直接付钱可以看作有效期1天，有效次数一次的租车卡)     
状态转移方程：      
$$dp[i]=\min_{j = 1}^{n}(dp[max(i-g(i, j), 0)] + w[j])$$
其中$w[j]$代表第j张租车卡的价格，$g(i, j)$代表使用完第j种租车卡后，此人的租车次数达到i时，此人可使用这张租车卡租车的最大次数。    
这句话可能有点抽象，用测试样例二解释一下:
![图](/home/ca1se/ze.png)    
代码：
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
const int maxm = 1e5 + 5;
const int msumq = 300000 + 5;
 
struct Card {
    int d, k, c;
}cards[maxn];
pair<int, int> dqs[maxm];
pair<int, int> fp[maxm];
long long dp[msumq];
 
int get_date_index(int l, int r, int p) {
    if(l == r) {
        return fp[l].second;
    }else {
        int mid = (l + r) >> 1;
        if(fp[mid].first == p) {
            return fp[mid].second;
        }else if(fp[mid].first < p) {
            return get_date_index(mid + 1, r, p);
        }else {
            return get_date_index(l, mid, p);
        }
    }
}
 
int main() {
    int n, m, rm = 0, r, sumq = 0, dq, kq, qsum = 0;
    scanf("%d%d%d", &n, &m, &r);
    for(int i = 0; i < n; i++) {
        scanf("%d%d%d", &cards[i].d, &cards[i].k, &cards[i].c);
    }
    cards[n].d = 1, cards[n].k = 1, cards[n].c = r;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &dqs[rm].first, &dqs[rm].second);
        if(dqs[rm].second) rm++;
    }
    sort(dqs, dqs + rm, [](const pair<int, int>& x, const pair<int, int>& y) {
        return x.first < y.first;
    });
    for(int i = 0; i < rm; i++) {
        fp[i].first = dqs[i].first;
        fp[i].second = sumq + 1;
        sumq += dqs[i].second;
    }
    auto it = dqs;
    dp[0] = 0;
    for(int i = 1; i <= sumq; i++) {
        dq = get_date_index(0, rm - 1, max(0, it->first - cards[0].d + 1)) - 1;
        kq = i - cards[0].k;
        dp[i] = dp[max(dq, kq)] + cards[0].c;
        for(int k = 1; k < n + 1; k++) {
            dq = get_date_index(0, rm - 1, max(0, it->first - cards[k].d + 1)) - 1;
            kq = i - cards[k].k;
            dp[i] = min(dp[i], dp[max(dq, kq)] + cards[k].c);
        }
        if(++qsum == it->second) {
            qsum = 0;
            it++;
        }
    }
    printf("%lld\n", dp[sumq]);
    return 0;
}
```

# K Scholomance Academy
题面：[K Scholomance Academy](https://codeforces.com/gym/103202/problem/K)

思路：    
    
阅读理解题，读懂题就不难。一个classifier可以为正也可以为负，输入数据（拿"+ 2"举例）‘+’ 是classifier的真实正负性，‘2’是对classifier的打分，打分>=一个值(θ)时，classifier被预测为正，反之被预测为负。θ不同时classifier的正负性就可能不同。tpr与fpr就会变化。    
拿第一个输入样例来说, θ有四种情况：    
```
    (1) θ <= 1时， "+ 2":TP, "- 3":FP, "- 1":FP, TPR = 1 / 1 = 1, FPR = 2 / 2 = 1
    (2) 1 < θ <= 2时， "+ 2":TP, "- 3":FP, "- 1":TN, TPR = 1 / 1 = 1, FPR = 1 / 2 = 0.5
    (3) 2 < 0 <= 3时， "+ 2":FN, "- 3":FP, "- 1":TN, TPR = 0 / 1 = 0, FPR = 1 / 2 = 0.5
    (4) 3 < 0时，"+ 2":FN, "- 3":TN, "- 1":TN, TPR = FPR = 0
```
我们可以延续这种思路，从小到大枚举每个不同的分数，去计算此时的TPR与FPR，并记录FPR对应的最大TPR(这里可以用map，因为它自动对key排序,一会遍历时方便)，拿第一个例子来说，我们枚举θ=1, 2, 3来代表上述的情况(1), (2), (3)。 少了第四种情况，但可以看出，每一个输入样例都会有第一种情况(TPR = FPR = 1)与第四种情况(TPR = FPR = 0)。我们可以在枚举前记录这两种情况，然后枚举θ = 2, 3(代码中枚举了第一种情况,懒得改了)。    
枚举结束后，会记录三个个FPR以及对应的TPR: (0, 0), (0.5, 1), (1, 1), 则答案是 (0.5 - 0) * 0 + (1 - 0.5) * 1 = 0.5    
接下来就是如何快速枚举每一种情况:    
将输入数据按分数大小升序排序，设输入数据个数为n，定义pn、nn为输入数据中真实正负性为正、负的个数，对于i 从 1 到 n，定义P、N为枚举到第i个数据时，前i - 1个数据中真实正负性为正、负的个数。则该情况的下的TPR = (pn - P) / pn, FPR = (nn - N) / nn

代码：
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
struct C {
    char ch;
    long long val;
}arr[maxn];
long long pn = 0, nn = 0, P = 0, N = 0;
map<double, double> m;
int main() {
    int n;
    double ans = 0, fpr;
    scanf("%d", &n);
    m[0] = 0;
    for(int i = 0; i < n; i++) {
        scanf(" %c", &arr[i].ch);
        scanf("%lld", &arr[i].val);
        if(arr[i].ch == '+') pn++;
        else nn++;
    }
    sort(arr, arr + n, [](const C& x, const C& y){
        return x.val < y.val;
    });
    for(int i = 0; i < n; i++) {
        if(i && arr[i].val == arr[i - 1].val) {
            if(arr[i].ch == '+') P++;
            else N++;
            continue;
        }
        fpr = double(nn - N) / nn;
        m[fpr] = max(m[fpr], double(pn - P) / pn);
        if(arr[i].ch == '+') P++;
        else N++;
    }
    auto r = ++m.begin();
    for(auto it = m.begin(); r != m.end(); it = r, r++) {
        ans += (r->first - it->first) * it->second;
    }
    printf("%.15lf\n", ans);
    return 0;
}
```

