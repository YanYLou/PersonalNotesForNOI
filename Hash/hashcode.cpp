////////////////////////////////////////////////////
//为了有效复杂化密码,考虑使用多项式滚动哈希对字符串生成 16 进制哈希
//每个字符串的哈希唯一，哈希值最长不超过 16 位，便于用于密码
//说明：具体实现由 AI 完成
////////////////////////////////////////////////////

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;	
const int seed = 131;

signed main() {
	    ios::sync_with_stdio(0); cin.tie(0);
	    char s[N];
		cin >> (s + 1);
		int n = strlen(s + 1);
		int hash = 0;
		for (int i = 1; i <= n; ++i) {
			hash = hash * seed + s[i];
		}
		cout << hex << hash << '\n';
		return 0;
}

