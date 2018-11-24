#include <iostream>
#include <stdlib.h>
using namespace std;
/* Konstanta */
#define Nil NULL

/* Deklarasi infotype */
typedef int infotype;

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueue * address;
typedef struct tElmtQueue { 
	infotype Info;
	address Next; 
} ElmtQueue; 

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct { 
	address HEAD;  /* alamat penghapusan */
	address TAIL;  /* alamat penambahan */
} Queue;

/* Selektor */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).HEAD->Info
#define InfoTail(Q) (Q).TAIL->Info
#define Next(P) (P)->Next
#define Info(P) (P)->Info



/* Prototype manajemen memori */
void Alokasi (address *P, infotype X){
/* Kamus Lokal */
	/* Algoritma */
	//Algortima
	*P = (address)malloc(sizeof(ElmtQueue));
	if (P != Nil) {
	Info(*P) = X;
	Next(*P) = Nil;
	}
	else
	*P = Nil;
}
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Dealokasi (address  P){
	free(P);
}
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
bool IsEmpty (Queue Q) {
	/* Kamus Lokal */

	/* Algoritma */
	return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
int NbElmt(Queue Q){
/* Kamus Lokal */
	int count;
	address P;
	/* Algoritma */
	count=0;
	P=Head(Q);
	while(P!=Nil) {
	count=count+1;
	P=Next(P);
	}
	return(count);
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
void CreateEmpty(Queue * Q){
 	/* Algoritma */
	Head(*Q)=Nil;
	Tail(*Q)=Nil;
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void Add (Queue * Q, infotype X){
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    Alokasi(&P,X);
    if (P!=Nil) {
        if (IsEmpty(*Q)) {
            Head(*Q) = P;
        } else {
            Next(Tail(*Q)) = P;
        }
    Tail(*Q) = P;
    } /* else: alokasi gagal, Q tetap */
}
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil{} jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Del(Queue * Q, infotype * X){
	
	/* Kamus Lokal */
    address P;
    /* Algoritma */
    *X = InfoHead(*Q);
    P = Head(*Q);
    Head(*Q) = Next(Head(*Q));
    if (Head(*Q)==Nil) {
    Tail(*Q) = Nil;
    }
    Dealokasi(P);
}

int main (){
	int a, x, y;
	cin >> x;
	cin >> y;
	Queue Antri;
	CreateEmpty (&Antri);
	
	for(int i=0;i<x;i++){
		cin >> a;
		Add(&Antri,a);
	}
	
	for(int j=0;j<y;j++){
		for(int k=0;k<x/y;k++){
			Del(&Antri,&a);
			cout<<a<<" ";
		}
		cout<<endl;
	}
	Del(&Antri,&a);
	cout<<a;
}
