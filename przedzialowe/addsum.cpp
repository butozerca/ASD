// drzewo (+- przedzia³, suma przedzia³)

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

struct Vert{
	int sum, magic;					// magic jest jakby obwodem dotychczasowych zawolan do drzewa i pozwala na
	Vert(){}						// wykonywanie tych operacji, ktore sa potrzebne do liczenia wynikow
	Vert(int a, int b):sum(a),magic(b){}
};

int T[100];
Vert Tree[200];
int last;

void print(){
	printf("print:\n");
	for(int i = 1; i < 2*last; ++i){
		printf("[%d %d] ", Tree[i].sum, Tree[i].magic);
		if(__builtin_popcount(i+1)==1)printf("\n");
	}
}

void makeTree(int xp = 0, int xk = last-1, int x = 1){
	if(x >= 2*last)return;
	Tree[x] = Vert(0, 0);
	makeTree(xp, (xp+xk)/2, x*2);
	makeTree((xp+xk)/2+1, xk, x*2+1);
}

void addToRange(int p, int k, int val, int xp = 0, int xk = last-1, int x = 1){
	if(k < p || !(xp <= p && xk >= k))
		return;
	Tree[x].sum += val*(k-p+1);
	
	if(x >= last)return;
	if(xp == p && xk == k){	
		Tree[2*x].magic += val;
		Tree[2*x+1].magic += val;
	}
	else{
		addToRange(p, min(k, (xp+xk)/2), val, xp, (xp+xk)/2, x*2);
		addToRange(max(p, (xp+xk)/2+1), k, val, (xp+xk)/2+1, xk, x*2+1);
	}
}

int getSumRange(int p, int k, int xp = 0, int xk = last-1, int x = 1){			
	if(k < p || !(xp <= p && xk >= k))
		return 0;
	
	Tree[x].sum += Tree[x].magic * (xk - xp + 1);
	if(x < last){
		Tree[2*x].magic += Tree[x].magic;
		Tree[2*x+1].magic += Tree[x].magic;
	}
	Tree[x].magic = 0;
	if(xp == p && xk == k)
		return Tree[x].sum;
	else
		return getSumRange(p, min(k, (xp+xk)/2), xp, (xp+xk)/2, x*2) + 
			getSumRange(max(p, (xp+xk)/2+1), k, (xp+xk)/2+1, xk, x*2+1);
}

int main(){
	int n, q, w;
	scanf("%d", &n);
	last = int(pow(2,ceil(log2(n))));
	makeTree();
//	for(int i = 0; i < n; ++i)
//		scanf("%d", T+i);
	print();
	scanf("%d", &q);
	for(int i = 0; i < q; ++i){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		addToRange(a, b, c);
		print();
	}
	scanf("%d", &w);
	for(int i = 0; i < w; ++i){
		int a, b;
		scanf("%d %d", &a, &b);
		printf("res: %d\n", getSumRange(a, b));
		print();
	}
	
	
	return 0;
}
