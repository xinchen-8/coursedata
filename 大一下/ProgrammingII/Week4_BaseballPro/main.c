#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Membersize 9
#define Blowsize 5

struct member{
    int number;
    int runtime;
    int blowscore;
    int blowpoints[Blowsize];
};

void computing(struct member *blowers, int outtime, int *score){
    int *base = malloc(4*sizeof(int));
    int *reg = malloc(4*sizeof(int));
    
    reg[3] = outtime;
    reg[0] = 0;
    while(reg[3]>0&&reg[0]<Membersize*Blowsize-1){printf("%d\n",reg[3]);
        for(reg[1]=0;reg[1]<blowers[reg[0]%9].blowpoints[reg[0]/9];reg[1]++){
            
            for(reg[2]=3;reg[2]>0;reg[2]--){
                base[reg[2]] = base[reg[2]-1];
                blowers[base[2]-1].runtime++;

                if(base[3]!=0) *score++;
                if(reg[2]==0){
                    base[0] = blowers[reg[0]%9].number;
                    blowers[reg[0]%9].runtime++;
                    blowers[reg[0]%9].blowscore+=blowers[reg[0]%9].blowpoints[reg[0]/9];
                }
                else base[0] = 0;
            }
            
        }
        if(blowers[reg[0]%9].blowpoints[reg[0]/9]==0) reg[3]--;
        if((outtime-reg[3])%3==0) memset(base,0,4*sizeof(int));
        reg[0]++;
    }
    free(base);
    free(reg);
}

void sorting(struct member *blowers){
    int *reg = malloc(2*sizeof(int));
    struct member *regb = malloc(sizeof(struct member));
    for (reg[0]=0; reg[0]<Membersize; reg[0]++) {
        reg[1] = reg[0];
        while (reg[1] > 0 && (blowers[reg[1]-1].runtime<blowers[reg[1]].runtime||blowers[reg[1]-1].runtime==blowers[reg[1]].runtime&&blowers[reg[1]-1].blowscore<blowers[reg[1]].blowscore)) {
        *regb = blowers[reg[1]];
        blowers[reg[1]] = blowers[reg[1]-1];
        blowers[reg[1]-1] = *regb;
        reg[1]--;
        }
    }
    free(reg);
    free(regb);
}

int main(){
    
    struct member blowers[Membersize] = {0};
    for(int i=0;i<Membersize;i++) memset(blowers[i].blowpoints,0,Blowsize*sizeof(int));
    int outtime=0,score=0;
    char inputreg = '0';

    int times=0;
    for(int i=0;i<Membersize;i++){
        scanf(" %d",&times);

        blowers[i].number = i+1;
        for(int j=0;j<times;j++){
            scanf("%s",&inputreg);
            blowers[i].blowpoints[j] = inputreg-'0';
            if(blowers[i].blowpoints[j]=='H'-'0') blowers[i].blowpoints[j]=4;
        }
    }
    scanf(" %d",&outtime);

    computing(blowers,outtime,&score);
    sorting(blowers);
    
    printf("%d\n",score);
    for(int i=0;i<3;i++) printf("%d %d %d\n",blowers[i].number,blowers[i].runtime,blowers[i].blowscore);
    return 0;
}