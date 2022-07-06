#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data,color;
    struct node *left,*right;
};

struct node* insert(struct  node*,int);
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);
int color(struct node*);
struct node* rotateleft(struct node*);
struct node* rotateright(struct node*);
struct node* check(struct node*);


int main()
{
    int i,j,x,c;
    struct node *p= NULL;
    for(i=10;i>0;i--)
    {
        p=insert(p,i);
        if(p!=NULL)
            if(p->color==1)
                p->color=0;
        printf("\n");
        inorder(p);

    }
    while(1)
    {
     printf("\n1.insert\n2.print\n3.exit\nenter your choise:");
     scanf("%d",&c);
     if(c==1)
        {
          printf("\nenter element");
          scanf("%d",&x);
          p=insert(p,x);
          if(p!=NULL)
            if(p->color==1)
                p->color=0;
        }
    else if(c==2)
        {
            inorder(p);
            printf("\n");
            preorder(p);
            printf("\n");
            postorder(p);
            printf("\n");
        }
    else
        break;
    }

    return 0;
}

struct node* insert(struct node *pr , int d)
{
    struct node *temp1,*temp2;
    if(pr==NULL)
    {
        pr= (struct node*) malloc(sizeof(struct node));
        pr->data=d;
        pr->color=1;
        pr->left=pr->right=NULL;
        return pr;
    }
    if((pr->data)==d)
    {
        printf("this element is duplicate\n");
        return pr;
    }
    else if((pr->data)<d)
        pr->right=insert(pr->right,d);
    else
        pr->left=insert(pr->left,d);
    if(pr->color==0)
    {
        pr=check(pr);
    }
    return pr;
}

struct node* check(struct node  *pr)
{
    int lc,rc,llc,lrc,rrc,rlc;
    struct node *t;
    lc=color(pr->left);
    rc=color(pr->right);
    if(lc==0 && rc==0)
        return(pr);
    if(lc==1)
    {
        llc=color(pr->left->left);
        lrc=color(pr->left->right);
        if(llc==1 ||lrc==1)
        {
            if(rc==1)
            {
                pr->color=1;
                pr->left->color=0;
                pr->right->color=0;
                return(pr);
            }
            if(lrc==1)
                pr->left=rotateleft(pr->left);
            pr=rotateright(pr);
            pr->color=0;
            pr->right->color=1;
            return(pr);

        }
    }
    if(rc==1)
    {
        rlc=color(pr->right->left);
        rrc=color(pr->right->right);
        if(rlc==1 ||rrc==1)
        {
            if(lc==1)
            {
                pr->color=1;
                pr->left->color=0;
                pr->right->color=0;
                return(pr);
            }
            if(rlc==1)
                pr->right=rotateright(pr->right);
            pr=rotateleft(pr);
            pr->color=0;
            pr->left->color=1;
            return(pr);
        }
    }
    return(pr);
}

int color(struct node *pr)
{
    if(pr==NULL)
        return(0);
    else
        return(pr->color);
}


struct node* rotateleft(struct node *pr)
{
    struct node *x;
    x=pr->right;
    pr->right=x->left;
    x->left=pr;
    return x;
}

struct node* rotateright(struct node *pr)
{
    struct node *x;
    x=pr->left;
    pr->left=x->right;
    x->right=pr;
    return x;
}


void inorder(struct node *p)
{
    if(p==NULL)
    return;
    inorder(p->left);
    printf("(%d,%d) ",p->data,p->color);
    inorder(p->right);
}

void preorder(struct node *p)
{
    if(p==NULL)
    return;
    printf("%d ",p->data);
    preorder(p->left);
    preorder(p->right);
}
void postorder(struct node *p)
{
    if(p==NULL)
    return;
    postorder(p->left);
    postorder(p->right);
    printf("%d ",p->data);
}
