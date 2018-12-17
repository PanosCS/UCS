#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct searchState{
    char *state;//deixnei se mia thesh tou pinaka pou exei thn katastash
    int flag;//0 gia metopo, 1 gia kleisto
    float g;//kostos apo thn arxikh katastash
    float h;
    struct searchState *next;//epomenos sthn lista
    struct searchState *prev;//poios me eftiaxe
};

char **states;

int L=-1,M=-1,d=-1,N=-1,ak=-1,tk1=-1,tk2=-1;

void init(){
    int i,j,flag;

    for(i=0;i<N;i++){
        states[i] = (char *)malloc((d+1)*sizeof(char));
        if(states[i] == NULL){
            exit(0);
        }
    }
    i=0;
    do{
        for(j=0;j<d/2;j++){
            states[i][j] = 'A' + rand()%L;
        }
        for(j=d/2;j<d;j++){
            states[i][j] = '0' + rand()%M;
        }
        states[i][d] = '\0';

        flag = 1;
        for(j=0;j<i;j++){
            if(strcmp(states[i],states[j]) == 0){
                flag = 0;
                break;
            }
        }
        if(flag == 1){
            i++;
        }
    }while(i<N);

    for(i=0;i<N;i++){
        printf("%s\n",states[i]);
    }
}

void ucs(){
    struct searchState *metopo;

    struct searchState *temp, *newState, *nextState, *last;
    //proswrinos gia douleises, neakatastash gia na mpei, epomenos pou tha elegxw gia tk/epektash, teleytaios
    int counter;
    float g;

    metopo = (struct searchState *)malloc(sizeof(struct searchState));
    if(metopo == NULL){
        exit(0);
    }
    metopo->g = 0;
    metopo->state = states[ak-1];
    metopo->flag = 0;
    metopo->next = NULL;
    metopo->prev = NULL;

    last = metopo;
    nextState = metopo;
    while(nextState != NULL){
        //vriskw ton komvo me to <g pou einai sto metopo
        nextState = metopo;
        if(metopo->flag==1){
            //ean anhkei sto kleisto den einai ypopshfios
            while(nextState!=NULL && nextState->flag == 1){
                nextState = nextState->next;
            }
        }
        if(nextState == NULL){
            break;
        }
        temp = nextState->next;
        while(temp!=NULL){
            if(temp->flag == 0 ){
                if(temp->g < nextState->g){
                    nextState = temp;
                }
            }
            temp = temp->next;
        }

        //ton vgazw apo to ma
        nextState->flag = 1;
        //elegxw gia teliki
        if(strcmp(states[tk1-1], nextState->state) == 0 || strcmp(states[tk2-1], nextState->state) == 0 ||){
            break;
        }
        for(i=0;i<N;i++){
            counter = 0;
            g = 0;
            for(j=0;j<d;j++){
                if(newState->state[j] != states[i][j]){
                    counter++;
                    if(j<d/2){
                        g+=1;
                    }
                    else{
                        g+=0.5;
                    }
                }
            }
            if(counter==1){
                temp = (struct searchState *)malloc(sizeof(struct searchState));
                if(temp == NULL){
                    exit(0);
                }
                temp->g = newState->g + g;
                temp->state = states[i];
                temp->flag = 0;
                temp->next = NULL;
                temp->prev = newState;

                last->next = temp;
                last = temp;
            }
        }
    }
}
int main(){
    srand(100);

    while(L<1 || L>=10){
        printf("Dwse L: ");
        scanf("%d",&L);
    }

    while(M<1 || M>=10){
        printf("Dwse M: ");
        scanf("%d",&M);
    }

    while(d<=0 || d%2==1){
        printf("Dwse d: ");
        scanf("%d",&d);
    }

    while( N<=0){
        printf("Dwse N: ");
        scanf("%d",&N);
    }

    while(ak<=0 || ak>N){
        printf("Dwse ak: ");
        scanf("%d",&ak);
    }

    while(tk1<=0 || tk1>N){
        printf("Dwse tk1: ");
        scanf("%d",&tk1);
    }

    while(tk2<=0 || tk2>N || tk2 == tk1){
        printf("Dwse tk2: ");
        scanf("%d",&tk2);
    }

    states = (char **)malloc(N*sizeof(char *));
    if(states == NULL){
        exit(0);
    }

    init();
}
