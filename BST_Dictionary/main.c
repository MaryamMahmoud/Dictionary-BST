#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the binary search tree structure
typedef struct  {
   struct  BSTNode *left;
   struct  BSTNode *right;
  // struct BSTNode *parent;
     char data[150];
}BSTNode;

// initialize the root
  BSTNode *root = NULL;

// a function to create new node in the BST

 BSTNode *newBSTNode(char *d) {
      BSTNode *newnode;
      newnode = (struct BSTNode *)malloc(sizeof(BSTNode));
      strcpy(newnode->data, d);
      newnode->left = newnode->right = NULL;
      return newnode;
}
// a function that inserts the file words in the BST
void inorder(BSTNode *node)
{
    if(node)
    {
        inorder(node->left);
        printf(" %s - ",node->data);
        inorder(node->right);
    }
    else
    {
     //   printf("Tree is empty!\n");
    return;}

}

void insert(char *data) {

        int test = 0;
        BSTNode *parent = NULL, *current_node = NULL, *newnode = NULL;
// to insert the first node (root)
        if (root == NULL) {
                root = newBSTNode(data);
                return;
        }

        for (current_node = root; current_node !=NULL;
           current_node = (test > 0) ? current_node->right : current_node->left) {
                test = strcmp(data, current_node->data);
                parent = current_node;
        }
        newnode = newBSTNode(data);
        if(test > 0)
            parent->right = newnode;
        else
            parent->left = newnode;
        return;
  }

// calculate the size of tree (number of nodes)

   int size(BSTNode *root)
   {
			return (root == NULL) ? 0 :
				1 + size(root->left) + size(root->right);
    }

//calculate the height of tree(longest branch)

  int height(BSTNode *node)
  {
      if(node == NULL)
        return -1;
      else
      {
          int left_side;
          int right_side;
          left_side = height(node->left);
          right_side = height(node->right);
          if(right_side > left_side)
             return (right_side+1);
           else
            return (left_side+1);
      }
  }


 int main()
 {
     int choice;
     int x,y;
      FILE *f;
     char ch[150];
     char str[150];
    f=fopen("EN-US-randomized-unique updated.txt","r");
    if (f!=NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%s",&ch);
            insert(ch);
        }
    }
        fclose(f);

        while(1) {
        printf("\n**************************\n");
        printf("Welcome to my dictionary\n");
        printf("**************************\n\n");
        printf("1-Tree's Height\n2-Tree's size\n3-check for a sentence\n4-Exit\n");
        printf("Please enter your choice\n");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            x = height(root);
            printf("\nthe tree's height is %d",x);
        //   inorder(root);
            break;
        case 2:
          y=size(root);
          printf("\nthe tree's size is %d",y);
            break;
        case 3:
            printf("\nplease enter any sentence to check\n");
            fflush(stdin);
            gets(str);
            check_words(str);
            break;
        case 4:
            exit(0);
        default:
            printf("You entered an invalid option\n");
            printf("Please enter any key to continue...");
            getchar();
            break;
        }
     }
     return 0;
 }

void search(char *str) {

        BSTNode *temp = NULL;

        BSTNode* p = NULL;
        BSTNode* q = NULL;
        int found = 0;
        int test = 0;

        if (root == NULL) {
                printf("The BST is empty!\n");
                return;
        }
        temp = root;
        BSTNode* leaf=temp;
        while (temp) {
                    leaf=temp;
                    test = strcmp(temp->data, str);
                if (test == 0) {
                        printf("\n\nThe word (%s) is spelled correctly", str);
                        found = 1;
                        break;
                }
                if(test > 0)
                    temp = temp->left;
                else
                    temp = temp ->right;
        }
        if (found==0){
                printf("\n\nThe word (%s) is spelled wrong\n", str);
                printf("Some suggestions :");
                printf("\n%s ",leaf->data);
                search_other_words(root,p,q,leaf->data);
        }
        return;
  }
  void search_other_words(BSTNode* root,BSTNode* pre,BSTNode* w,char *data)
{
    if (root == NULL)
        return ;

    if (strcmp(root->data,data)==0)
    {
        if (root->left != NULL)
        {
            BSTNode* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
        if(pre)
            printf("\n%s ",pre->data);
        if (root->right != NULL)
        {
            BSTNode* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            w = tmp ;
        }
        if(w)
            printf("\n%s ",w->data);
        return ;
    }
    if (strcmp(root->data,data) > 0)
    {
        w = root ;
        search_other_words(root->left, pre, w, data) ;
    }
    else
    {
        pre = root ;
        search_other_words(root->right, pre, w, data) ;
    }
}
void check_words(char *c)
{
    char *w = strtok(c," ");
    while(w!=NULL){
        search(w);
        w=strtok(NULL," ");
    }
}
