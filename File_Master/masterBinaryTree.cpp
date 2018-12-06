#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int infotype;
typedef struct tNode *address;
typedef struct tNode {
	infotype info;
	address left;
	address right;
} Node;

typedef address BinTree;

#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right
#define Nil NULL
#define empty(P) (P==NULL)

void CreateEmpty(BinTree *P) {
	*P = NULL;
}

address Allocation(infotype X) {
	address nodeBaru;
	nodeBaru = (Node*) malloc (sizeof(Node));
	
	Akar(nodeBaru) = X;
	Left(nodeBaru) = NULL;
	Right(nodeBaru) = NULL;
	
	return nodeBaru;
}

BinTree Tree (infotype Akar, BinTree L, BinTree R) {

	BinTree T;

	T = Allocation(Akar);
	if (T != Nil) {
		Left(T) = L;
		Right(T) = R;	
	}
	return T;
}

bool IsTreeEmpty(BinTree P) {
	return (P == NULL);
}

bool IsTreeOneElmt(BinTree P) {
	if (P!=NULL) {
		return (Left(P)==NULL && Right(P)==NULL);
	} else {
		return false;
	}
}

bool IsUnerLeft(BinTree P) {
	if (P!=NULL) {
		return (Left(P)!=NULL && Right(P)==NULL);
	} else {
		return false;
	}
}

bool IsUnerRight(BinTree P) {
	if (P!=NULL) {
		return (Left(P)==NULL && Right(P)!=NULL);
	} else {
		return false;
	}
}

void InsertNum(BinTree *P, infotype X) {
	
	if(empty(*P)) {
        *P=Allocation(X);
        return;
    }
    if(Akar(*P)==X) {
        return;
    }
    
    if(X<Akar(*P)) InsertNum(&Left(*P),X);
    else InsertNum(&Right(*P),X);

}

void PrintPreorder(BinTree P) {
	if (!IsTreeEmpty(P)) {
		PrintPreorder(Left(P));
		cout << Akar(P) << endl;
		PrintPreorder(Right(P));
	}
}

int NbDaun(BinTree P) {
	if (IsTreeOneElmt(P)) {
		return 1;
	} else {
		if (IsUnerLeft(P)) {
			return (NbDaun(Left(P)));
		} else if (IsUnerRight(P)) {
			return (NbDaun(Right(P)));
		} else {
			return (NbDaun(Left(P)) + NbDaun(Right(P)));
		}
	}
}

int NbElmt(BinTree P) {
	if (IsTreeEmpty(P)) {
		return 0;
	} else {
		return (1 + NbElmt(Left(P)) +NbElmt(Right(P)));
	}
}

int Tinggi(BinTree P) {
	int tLeft, tRight;
	
	if (IsTreeEmpty(P)) {
		return 0;
	} else {
		tLeft = Tinggi(Left(P));
		tRight = Tinggi(Right(P));
		
		if (tLeft > tRight) {
			return (1 + tLeft);
		} else {
			return (1 + tRight);
		}
	}
}

bool SearchTree(BinTree P, infotype X) {
	if (IsTreeEmpty(P)) {
		return false;
	} else {
		if (Akar(P) == X) {
			return true;
		} else {
			return (SearchTree(Left(P),X) || SearchTree(Right(P),X));
		}
	}
}

int LevelSearch(BinTree P, infotype X) {
	if (SearchTree(P, X)) {
		if (Akar(P) == X) {
			return 1;
		} else {
			if (X < Akar(P)) {
				return (1+LevelSearch(Left(P),X));
			} else {
				return (1+LevelSearch(Right(P),X));
			}
		}
	} else {
		return 0;
	}
}




// This section to print tree data like a tree command on windows CMD
/*
|_ 50   lev.(0)
|_|_ 30   lev.(1)
|_|_|_ 20   lev.(2)
|_|_|_ 40   lev.(2)
|_|_ 70   lev.(1)
|_|_|_ 60   lev.(2)
|_|_|_ 80   lev.(2)
*/
string genchar(string x, int n){
    string y ="";
    for(int i=0;i<n;i++){
        y+=x;
    }
    return y;
}

void draw(BinTree T,int i=1){
    if(!empty(T)){
        printf("%s %d   lev.(%d)\n",genchar("|_",i).c_str(),Akar(T),i-1);
        draw(Left(T),i+1);
        draw(Right(T),i+1);
    }
}
// add mostleaft to BST
void addLeafMost(BinTree *T, BinTree *L){
    if(empty(Left(*T))) Left(*T) = *L;
    else addLeafMost(&Left(*T),L);
}


// delete a node and recontructor tree by itself
void delNode(BinTree *T,infotype x){
    if(empty(*T)) return;
    
    if(x==Akar(*T)){
        if(empty(Left(*T)) && empty(Right(*T))) {
            *T = NULL;
            return;
        }

        BinTree temp = *T;
        *T = Right(*T);
        addLeafMost(T,&Left(temp));
        temp = NULL;
    
    }
    else if(x>Akar(*T)) delNode(&Right(*T),x);
    else delNode(&Left(*T),x);
    
}


int main(){
	BinTree T ;
	CreateEmpty(&T);
	InsertNum(&T,50);
    InsertNum(&T, 30); 
    InsertNum(&T, 20); 
    InsertNum(&T,50);
    InsertNum(&T, 40); 
    InsertNum(&T, 70); 
    InsertNum(&T, 60); 
    InsertNum(&T, 80);
	
	delNode(&T,50);
	// PrintPreorder(T);
	draw(T);

}

