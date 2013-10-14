// bangla
// drzewo (+- max, przedzial)

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

struct Vert{
	int max, magic;					// magic jest wartoscia, ktora trzeba dodac do wszystkich podwezlow
	Vert(){}						// max jest maxem z przedzialu, ktore nie zwraca uwagi na magic 
	Vert(int a, int b):max(a),magic(b){} // w nadprzedzialach
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
	if(x < last)
		Tree[x].max = max(Tree[x*2].max, Tree[x*2+1].max) + Tree[x].magic;
	else
		Tree[x].max = Tree[x].magic;
}

void getMaxRec(int p, int k, int& res, int magic = 0, int xp = 0, int xk = last-1, int x = 1){		
	if(k < p || !(xp <= p && xk >= k))
		return;
	if(p == xp && k == xk)
		res = max(res, Tree[x].max + magic);
	else{
		getMaxRec(p, min(k, (xp+xk)/2), res, magic + Tree[x].magic, xp, (xp+xk)/2, 2*x);
		getMaxRec(max(p, (xp+xk)/2+1), k, res, magic + Tree[x].magic, (xp+xk)/2+1, xk, 2*x+1);
	}
}

int getMaxRange(int p, int k){
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
