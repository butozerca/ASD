// nie bangla
// drzewo (+- max, suma przedzial)

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

struct Vert{
	int max, magic;					// magic jest jakby obwodem dotychczasowych zawolan do drzewa i pozwala na
	Vert(){}						// wykonywanie tylko tych operacji, ktore sa potrzebne do liczenia wynikow
	Vert(int a, int b):max(a),magic(b){}
};

Vert Tree[200];
int last;

void makeTree(){};

void print(){
	printf("print:\n");
	for(int i = 1; i < 2*last; ++i){
		printf("[%d %d] ", Tree[i].max, Tree[i].magic);
		if(__builtin_popcount(i+1)==1)printf("\n");
	}
}

void setUpTree(int n){
	last = int(pow(2,ceil(log2(n))));
	makeTree();
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
	if(p == xp && k == xk)
		Tree[x].magic += val;
	else{
		addToRange(p, min(k, (xp+xk)/2), val, xp, (xp+xk)/2, x*2);
		addToRange(max(p, (xp+xk)/2+1), k, val, (xp+xk)/2+1, xk, x*2+1);
	}
}

void getMaxRec(int p, int k, int& res, int xp = 0, int xk = last-1, int x = 1){
	printf("gMRec: %d %d %d %d %d %d %d\n", p, k, res, xp, xk,x);		
	if(k < p || !(xp <= p && xk >= k))
		return;
	Tree[x].max += Tree[x].magic;
	if(x < last){
		Tree[2*x].magic += Tree[x].magic;
		Tree[2*x+1].magic += Tree[x].magic;
	}
	Tree[x].magic = 0;
	if(p == xp && k == xk)
		res = max(res, Tree[x].max);
	else{
		getMaxRec(p, min(k, (xp+xk)/2), res, xp, (xp+xk)/2, 2*x);
		getMaxRec(max(p, (xp+xk)/2+1), k, res, (xp+xk)/2+1, xk, 2*x+1);
	}
}

int getMaxRange(int p, int k){
	printf("gMRange: %d %d\n", p, k);
	int res = 0;
	getMaxRec(p, k, res);
	return res;
}



int main(){
	int n, q, w;
	printf("rozmiar drzewa: ");
	scanf("%d", &n);
	setUpTree(n);
	print();
	printf("liczba addow: ");
	scanf("%d", &q);
	for(int i = 0; i < q; ++i){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		addToRange(a, b, c);
		print();
	}
	printf("liczba getow: ");
	scanf("%d", &w);
	for(int i = 0; i < w; ++i){
		int a, b;
		scanf("%d %d", &a, &b);
		printf("res: %d\n", getMaxRange(a, b));
		print();
	}
	
	
	return 0;
}
