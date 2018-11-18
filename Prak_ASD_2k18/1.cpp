#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int infotype;
typedef struct TElmtStack *address;
typedef struct TElmtStack{
    infotype info;
    address next;
} ElmtStack;

struct Stack {
    address top;
};

#define Top(S) (S).top
#define InfoTop(S) (S).top->info 
#define Next(P) (P)->next
#define Info(P) (P)->info

bool IsEmpty(Stack S) {
    return (Top(S) == NULL);
}

void CreateEmpty(Stack *S) {
    Top(*S) = NULL;
}

void Deallocation(address P) {
    free(P);
}

address Allocation(infotype X) {
    address NewElmt;
    NewElmt = (ElmtStack*) malloc (sizeof(ElmtStack));

    Info(NewElmt) = X;
    Next(NewElmt) = NULL;

    return NewElmt;
}

void Push(Stack *S, infotype X) {
    address NewElmt;
    NewElmt = Allocation(X);

    if (NewElmt != NULL) {
        Next(NewElmt) = Top(*S);
        Top(*S) = NewElmt;
    }
}

void Pop(Stack *S, infotype *X) {
    if (!IsEmpty(*S)) {
        address temp;
        temp = Top(*S);
        
        *X = Info(temp);
        Top(*S) = Next(temp);
        Next(temp) = NULL;
        Deallocation(temp);
    }
}

int main() {
    infotype n, sum = 0;
    Stack data;
    infotype x;

    CreateEmpty(&data);
    
    cin>>n;
    
    for(int i=0; i<n; i++){
        cin>>x;
        Push(&data , x);
        sum = sum + x;
    }
    
    while(!IsEmpty(data)){
        Pop(&data , &x);
        cout<<x<<endl;
    }
    cout<<sum;
    
    
    return 0;
}
