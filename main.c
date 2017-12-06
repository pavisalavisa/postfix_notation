// iz zadanog postfiksa izracunajte rezultat

#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 64000
#define DELIMITER ' '
#define READ "r"

struct _element;
typedef struct _element* Position;
struct _element{
    int el;
    Position next;
};

Position createNode();
int calculate(int,int,char);
int push(Position,int);
int pop(Position);
int deleteNode(Position,int);
char* getFileContents(char*);
int calculatePostfixNotation(char*,Position);

int main(int argc, char**argv)
{
    Position stog=createNode();
    char* buff=getFileContents("postfiks.txt");
    printf("procitali smo %s\n",buff);
    //int rezultatd
    printf("Vrijednost ucitanog izraza je : %d",calculatePostfixNotation(buff,stog));
    return 0;
}

int calculatePostfixNotation(char* buffer,Position stog)
{
    int prviOperand,drugiOperand,result,tmpBroj;
    char* token;
    token=strtok(buffer," ");
    while(token!=NULL)
    {
        if(isdigit(token[0]))
        {
            sscanf(token," %d",&tmpBroj);
            push(stog,tmpBroj);
        }
        else{
            drugiOperand=pop(stog);
            prviOperand=pop(stog);
            result=calculate(prviOperand,drugiOperand,token[0]);
            push(stog,result);
        }
        token=strtok(NULL," ");
    }

    return pop(stog);
}

int push(Position head,int value)
{
    if(head==NULL)return -1;
    Position tmp=createNode();
    tmp->el=value;
    tmp->next=head->next;
    head->next=tmp;
    return 0;
}

int pop(Position head)
{
    if(head==NULL)
        return -1;
    if(head->next==NULL)
        return -2;
    int x=head->next->el;
    deleteNode(head,head->next->el);
    return x;
}

int deleteNode(Position head,int value)
{
    Position tmp;
    if(head==NULL)return -1;
    while(head->next->el!=value&&head->next!=NULL)
        head=head->next;
    if(head->next==NULL)return -2;
    tmp=head->next;
    head->next=tmp->next;
    free(tmp);
    return 0;
}

int calculate(int x,int y,char op)
{
    if(op=='+')
        return x+y;
    if(op=='-')
        return x-y;
    if(op=='*')
        return x*y;
    return x/y;

}

Position createNode()
{
    Position p=NULL;
    p=(Position)malloc(sizeof(struct _element));
    if(p==NULL)return NULL;
    p->next=NULL;
    return p;
}

char* getFileContents(char* fName)
{
    FILE* fp=NULL;
    char*buffer=NULL;
    fp=fopen(fName,READ);
    if(fp==NULL)
        return NULL;

    buffer=(char*)malloc(BUFF_SIZE*sizeof(char));
    while(!feof(fp))
    {
        fgets(buffer,BUFF_SIZE-1,fp);
    }
    fclose(fp);
    return buffer;
}
