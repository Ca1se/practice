/*从左到右有n个木块，编号为0~n-1, 要求模拟以下4种操作(下面的a和b都是木块编号)
move a onto b: 把a和b上方的木块全部归位，然后把a摞在b上面。
move a over b: 把a上方的木块全部归位，然后把a放在b所在木块堆的顶部。
pile a onto b: 把b上方的木块全部归位，然后把a及上面的木块整体摞在b上面。
pile a over b: 把a及上面的木块整体摞在b所在木块堆的顶部。*/
//输出最后每堆的高度
#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int MAXN = 30;
int n;
vector<int> pile[MAXN];

void find_one(int a,int& p,int& h)
{
	for (p = 0; p < (n > MAXN ? MAXN : n); p++)
		for (h = 0; h < (int)pile[p].size(); h++)
			if (a == pile[p][h])	return;
}

void clear_one(int a)
{
	int p, h;
	find_one(a, p, h);
	for (int i=pile[p].size()-1; i>h; i--)
	{
		pile[pile[p][i]].push_back(pile[p][i]);
		pile[p].pop_back();
	}
}



void print()
{
	for (int i = 0; i < (n > MAXN ? MAXN : n); i++)
	{
		for (int j = 0; j < (int)pile[i].size(); j++)
		{
			cout << pile[i][j];
		}
		cout << endl;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	cin >> n;
	int a, b;
	string in1, in2;
	for (int i = 0; i < (n > MAXN ? MAXN : n); i++)	pile[i].push_back(i);
	while (cin >> in1 >> a >> in2 >> b)
	{
		int p, h;
		if (a == b) return 0;
		if(in1=="move")
			if (in2 == "onto")
			{
				clear_one(a);
				clear_one(b);
				find_one(a, p, h);
				pile[p].pop_back();
				find_one(b, p, h);
				pile[p].push_back(a);
			}
			else
			{
				clear_one(a);
				find_one(a, p, h);
				pile[p].pop_back();
				find_one(b, p, h);
				pile[p].push_back(a);
			}
		else
			if (in2 == "onto")
			{
				clear_one(b);
				find_one(b, p, h);
				int temp = p;
				find_one(a, p, h);
				for (int i = h; i < (int)pile[p].size(); i++)
					pile[temp].push_back(pile[p][i]);
				pile[p].resize(h);
			}
			else
			{
				find_one(b, p, h);
				int temp = p;
				find_one(a, p, h);
				for (int i = h; i < (int)pile[p].size(); i++)
					pile[temp].push_back(pile[p][i]);
				pile[p].resize(h);
			}
	}
	print();
	fclose(stdin);
	fclose(stdout);
}