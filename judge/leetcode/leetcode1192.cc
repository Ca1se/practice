;class Solution {
	vector<int> ver;
	vector<int> Next;
	vector<int> head;
	vector<int> low;
	vector<int> dfn;
	vector<vector<int>> ans;
	int tot, num;

	void add(int x, int y) {
		ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
	}

	void tarjan(int x, int by_edge) {
		dfn[x] = low[x] = ++num;

		for(int i = head[x]; i; i = Next[i]) {
			int y = ver[i];
			if(!dfn[y]) {
				tarjan(y, i);
				low[x] = min(low[x], low[y]);
				if(low[y] > dfn[x]) {
					ans.push_back((vector<int>){x, y});
				}
			}else if(i != (by_edge ^ 1)) {
				low[x] = min(low[x], dfn[y]);
			}
		}
	}

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
		const int len = (connections.size() + 5) * 2;
        ver.resize(len);
		Next.resize(len);
		head.resize(len, 0);
		low.resize(len);
		dfn.resize(len, 0);
		tot = 1, num = 0;

		for(const auto& it: connections) {
			add(it[0], it[1]), add(it[1], it[0]);
		}

		for(int i = 0; i < n; i++) {
			if(!dfn[i]) {
				tarjan(i, 0);
			}
		}

		return ans;
    }
};
