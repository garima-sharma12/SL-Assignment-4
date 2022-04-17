#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//BT20CSE040 GARIMA SHARMA
//SL ASSIGNMENT 4

typedef struct node
{
	struct node* link1;
	struct node* link2;
	struct node* link3;
	//atmost 3 connections
	int data;
	bool flag;
	int count;
}heap_node;


heap_node *heap[8];

//function declarations
void createlink(int ,int ,int ,int );
void adjacency_list();
void adjacency_matrix();
int check_root(heap_node*,heap_node* );
void rfc_garbage(heap_node* );
void marking_node(heap_node* ,int ,int );
void marking(heap_node* );
void sweep();
void display(int );
void printnode(heap_node* );



void createlink(int link,int link1,int link2,int link3)
{
	if(link1!=-1)
	{
		heap[link]->link1=heap[link1];
		heap[link1]->count+=1;
	}
	if(link2!=-1)
	{
		heap[link]->link2=heap[link2];
		heap[link2]->count+=1;
	}
	if(link3!=-1)
	{
		heap[link]->link3=heap[link3];
		heap[link3]->count+=1;
	}	
}



int check_root(heap_node* root_node,heap_node* temp)
{
	//checks if root is there
	if(root_node==NULL)
	{
		return 0;
	}
	if(root_node->data==temp->data)
	{
		return 1;
	}
	if(check_root(root_node->link1,temp))
	{
		return 1;
	}
	if(check_root(root_node->link2,temp))
	{
		return 1;
	}
	if(check_root(root_node->link3,temp))
	{
		return 1;
	}
	return 0;
}

void rfc_garbage(heap_node* root_node)
{
	int i=0;
	while(i<=7)
	{
		if(check_root(root_node,heap[i])==0)
		{
			if(heap[i]->link1!=NULL)
			{
				heap[i]->link1->count-=1;
			}
			if(heap[i]->link2!=NULL)
			{
				heap[i]->link2->count-=1;
			}
			if(heap[i]->link3!=NULL)
			{
				heap[i]->link3->count-=1;
			}
			printf("Garbage value:");
			display(i);
			free(heap[i]);
			heap[i]=NULL;	
		}
		i++;
	}
}


void marking_node(heap_node* root_node,int i,int j)
{
	heap_node* prev,*current;
	current=root_node;
	while(current!=NULL)
	{
		if(current->link1==NULL)
		{
			current->flag=true;
			current=current->link2;
		}
		else
		{
			prev=current->link1;
			while((prev->link2!=NULL) && (prev->link2!=current))
			{
				prev=prev->link2;
			}
			if(prev->link2==NULL)
			{
				prev->link2=current;
				current=current->link1;
			}
			else
			{
				prev->link2=NULL;
				current->flag=true;
				current=current->link2;
			}
		}
	}
	current=root_node;
	
	while(current!=NULL)
	{
		if(current->link1==NULL)
		{
			current->flag=true;
			current=current->link3;
		}
		else
		{
			prev=current->link1;
			while ((prev->link3!= NULL) && (prev->link3 != current))
            {
            	prev = prev->link3;
			}
            if (prev->link3 == NULL) 
            {
                prev->link3 = current;
                current = current->link1;
            }
            else 
            {
                prev->link3 = NULL;
                current->flag=true;
                current = current->link3;
            }     
                
		}
	}
	
}

void marking(heap_node* root_node)
{
	
	if(root_node==NULL)
	{
		return;
	}
	if(root_node!=NULL)
	{
		root_node->flag=true;
	}
	
	marking(root_node->link1);
	marking(root_node->link2);
	marking(root_node->link3);
}

void sweep()
{
	int i=0;
	for(i=0;i<=7;i++)
	{
		if(heap[i]->flag==false)
		{
			if(heap[i]->link1!=NULL)
			{
				heap[i]->link1->count-=1;
			}
			if(heap[i]->link2!=NULL)
			{
				heap[i]->link2->count-=1;
			}
			if(heap[i]->link3!=NULL)
			{
				heap[i]->link3->count-=1;
			}
			printf("Garbage value:");
			display(i);
			free(heap[i]);
			heap[i]=NULL;
		}
	}
}

void adjacency_list()
{
	for(int i=0;i<=7;i++)
	{
		if(heap[i]!=NULL)
		{
			printf("Element:%d ",heap[i]->data);
			if(heap[i]->link1!=NULL)
			{
				printf("%d ->",heap[i]->link1->data);
			}
			if(heap[i]->link2!=NULL)
			{
				printf("%d ->",heap[i]->link2->data);
			}
			if(heap[i]->link3!=NULL)
			{
				printf("%d ->",heap[i]->link3->data);
			}
			printf("NULL\n");
		}
	}
}

void adjacency_matrix()
{
	int mat[8][8];
	int i,j,k;
	//initialize matrix
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			mat[i][j]=0;
		}
	}
	
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(heap[i]!=NULL && heap[j]!=NULL)
			{
				if(heap[i]->link1!=NULL)
				{
					if(i!=j &&heap[i]->link1->data==heap[j]->data)
					{
						mat[i][j]=1;
					}
				}
				if(heap[i]->link2!=NULL)
				{
					if(i!=j && heap[i]->link2->data==heap[j]->data)
					{
						mat[i][j]=1;
					}
				}
				if(heap[i]->link3!=NULL)
				{
					if(i!=j && heap[i]->link3->data==heap[j]->data)
					{
						mat[i][j]=1;
					}
				}
				
			}
		}
	}
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
}

void display(int i)
{
	printf("\nElement:%d\n",heap[i]->data);
	printf("reference count:%d\n",heap[i]->count);
	printf("size_freed:%d\n",sizeof(heap));
	printf("\n");
}

void printnode(heap_node* root)
{
	if(root==NULL)
	{
		return;
	}
	else
	{
		printf("Element:%d \t reference count:%d\n",root->data,root->count);
	}
	printnode(root->link1);
	printnode(root->link2);
	printnode(root->link3);
}


int main()
{
	int nodes[]={5,1,7,2,3,8,4,9,6,10};
	
	for(int i=0;i<=7;i++)
	{
		heap_node* new_node=(heap_node*)malloc(sizeof(heap_node));
		new_node->data=nodes[i];
		new_node->link1=NULL;
		new_node->link2=NULL;
		new_node->link3=NULL;
		new_node->count=0;
		new_node->flag=false;
		heap[i]=new_node;
	}
	heap_node*root1=heap[3];
	heap[3]->count+=1;
	heap_node*root2=heap[0];
	heap[0]->count+=1;
	
	createlink(0,1,6,7);
	createlink(2,5,7,-1);
	createlink(3,0,-1,-1);
	createlink(4,0,5,-1);
	createlink(5,6,-1,-1);
	
	printf("\nNodes linked to first root:\n");
	printnode(root1);
	
	printf("\nNodes linked to second node:\n");
	printnode(root2);
	
	printf("\nAll nodes:\n");
	adjacency_list();
	
	printf("\nAdjacency matrix fot the nodes:\n");
	adjacency_matrix();
	
	printf("\nGarbage collection starts..\n");
	marking(root1);
	printf("\nMarking done\n\n");
	sweep();
	printf("\nAfter garbage collection:\n");
	
	printf("\n\nAdjacency list now\n");
	adjacency_list();
	
	printf("\n\nAdjacency matrix now\n");
	adjacency_matrix();
}
