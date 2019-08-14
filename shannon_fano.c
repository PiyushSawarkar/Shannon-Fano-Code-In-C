#include<stdio.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
typedef struct {
    float freq;
    char alph;
    char *str;
}node;
int splitter(node[],int,int);
void shanon_fano(node[],int,int);
void sort_array(node[],int);
int splitter(node L[],int low,int high){
    int i=low;
    float sum_i=0.0,sum_c;
    float min_count=999.999;
    int temp;
    float diff;
    int partition_element_index;
    while(i<high){
        sum_i+=L[i].freq;
        sum_c=0;
        for(temp=i+1;temp<=high;temp++){
            sum_c+=L[temp].freq;
        }
        diff=sum_c-sum_i;
        if(diff<0){
            diff*=-1;
        }
        if(diff<min_count){
            min_count=diff;
            partition_element_index=i;
        }
        i++;
    }
    for(int i=low;i<=partition_element_index;i++){
        strcat(L[i].str,"0");
    }
    for(int i=partition_element_index+1;i<=high;i++){
        strcat(L[i].str,"1");
    }
    return partition_element_index;
}
void shanon_fano(node L[],int low,int high){
    int partition_element_index;
    if(low<high){
        partition_element_index=splitter(L,low,high);
        shanon_fano(L,low,partition_element_index);
        shanon_fano(L,partition_element_index+1,high);
    }
}
void sort_array(node L[],int n){
    node temp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(L[j].freq<L[j+1].freq){
                temp=L[j];
                L[j]=L[j+1];
                L[j+1]=temp;
            }
        }
    }
}
int main(){
    int n,choice;
    printf("\nEnter Number of alphabets: ");
    scanf("%d",&n);
    node L[n];
    float P;
    ask_again:
    printf("\nPress:\n1.Probability Values\n2.Frequency Values\n");
    scanf("%d",&choice);
    if(choice==1){
       printf("\nEnter 'Probability Alphabet' :\n");
        for(int i=0;i<n;i++){
            scanf("%f %c",&P,&L[i].alph);
            L[i].freq=log2f(1/P);
            L[i].str=(char*)malloc(n);
            strcpy(L[i].str,"");
        } 
    }
    else if(choice==2){
        printf("\nEnter 'Frequency Alphabet' :\n");
        for(int i=0;i<n;i++){
            scanf("%f %c",&L[i].freq,&L[i].alph);
            L[i].str=(char*)malloc(n);
            strcpy(L[i].str,"");
        }
    }
    else{
        printf("Wrong option");
        goto ask_again;
    }
    sort_array(L,n); 
    shanon_fano(L,0,n-1);
    printf("\nThe Output is:");
    for(int i=0;i<n;i++){
        printf("\n%c %s",L[i].alph,L[i].str);  
    }
    printf("\n"); 
    return 0;
}
/*
to compile the file: $ gcc filename.c -lm
to Execute it: $ ./a.out
*/
/*
Input Data Set-1
Enter Number of alphabets: 5
Freq Alph
0.22 A
0.30 B
0.05 C
0.15 D
0.28 E

Output for Input Data Set-1:
B 00
E 01
A 10
D 110
C 111

Input Data Set-2
Enter Number of alphabets: 5
Prob Alph
0.8585 A
0.8122 B
0.9659 C
0.9012 D
0.8235 E

Output for Input Data Set-2:
B 00
E 01
A 10
D 110
C 111

*/



