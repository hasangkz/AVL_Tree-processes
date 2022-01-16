#include <iostream>
#include <ctime>


class Node
{
    public:
    int deger;
    Node *sol;
    Node *sag;
    int yukseklik;
};

int max(int a, int b);

int yukseklik(Node *N)
{
    if (N == NULL)
        return 0;
    return N->yukseklik;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
Node* newNode(int deger)
{
    Node* node = new Node();
    node->deger = deger;
    node->sol = NULL;
    node->sag = NULL;
    node->yukseklik = 1; 
        
    return(node);
}

Node *sagRotate(Node *y)
{
    Node *x = y->sol;
    Node *T2 = x->sag;
 
    x->sag = y;
    y->sol = T2;
 
    y->yukseklik = max(yukseklik(y->sol),
                    yukseklik(y->sag)) + 1;
    x->yukseklik = max(yukseklik(x->sol),
                    yukseklik(x->sag)) + 1;

    return x;
}

Node *solRotate(Node *x)
{
    Node *y = x->sag;
    Node *T2 = y->sol;
 
    y->sol = x;
    x->sag = T2;

    x->yukseklik = max(yukseklik(x->sol),   
                    yukseklik(x->sag)) + 1;
    y->yukseklik = max(yukseklik(y->sol),
                    yukseklik(y->sag)) + 1;
    return y;
}

int getdenge(Node *N)
{
    if (N == NULL)
        return 0;
    return yukseklik(N->sol) - yukseklik(N->sag);
}

Node* ekle(Node* node, int deger)
{
   
    if (node == NULL)
        return(newNode(deger));
 
    if (deger < node->deger)
        node->sol = ekle(node->sol, deger);
    else if (deger > node->deger)
        node->sag = ekle(node->sag, deger);
    else 
        return node;

    node->yukseklik = 1 + max(yukseklik(node->sol),
                        yukseklik(node->sag));
 
    int denge = getdenge(node);
 
    if (denge > 1 && deger < node->sol->deger)
        return sagRotate(node);
 
    if (denge < -1 && deger > node->sag->deger)
        return solRotate(node);
 
    
    if (denge > 1 && deger > node->sol->deger)
    {
        node->sol = solRotate(node->sol);
        return sagRotate(node);
    }
 
    if (denge < -1 && deger < node->sag->deger)
    {
        node->sag = sagRotate(node->sag);
        return solRotate(node);
    }

    return node;
}
 
Node * minValueNode(Node* node)
{
    Node* current = node;
 
    while (current->sol != NULL)
        current = current->sol;
 
    return current;
}

Node* deleteNode(Node* root, int deger)
{
     
    if (root == NULL)
        return root;
 
    if ( deger < root->deger )
        root->sol = deleteNode(root->sol, deger);

    else if( deger > root->deger )
        root->sag = deleteNode(root->sag, deger);
    else
    {
        if( (root->sol == NULL) ||
            (root->sag == NULL) )
        {
            Node *temp = root->sol ?
                         root->sol :
                         root->sag; 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
            *root = *temp;
            free(temp);
        }
        else
        {
            Node* temp = minValueNode(root->sag);
            root->deger = temp->deger;
            root->sag = deleteNode(root->sag,
                                     temp->deger);
        }
    }
 
    if (root == NULL)
    return root;
 
    root->yukseklik = 1 + max(yukseklik(root->sol),
                           yukseklik(root->sag));

    int denge = getdenge(root);
 
    if (denge > 1 &&
        getdenge(root->sol) >= 0)
        return sagRotate(root);
 
    if (denge > 1 &&
        getdenge(root->sol) < 0)
    {
        root->sol = solRotate(root->sol);
        return sagRotate(root);
    }
 
    if (denge < -1 &&
        getdenge(root->sag) <= 0)
        return solRotate(root);
 
    if (denge < -1 &&
        getdenge(root->sag) > 0)
    {
        root->sag = sagRotate(root->sag);
        return solRotate(root);
    }
 
    return root;
}

void arama(Node *root,int deger)
{
  Node *temp = root;
  bool found = false;
  while(temp != NULL)
  {
      if(deger == temp->deger)
      {
          found = true;
          break;
      }
      else
      {
          if(deger < temp->deger)
            temp = temp->sol;
          else
            temp = temp->sag;

      }
  }
  if(found)
  {
      std::cout << deger <<  " bulundu" << std::endl;
  }
  else
  {
      std::cout << deger << " bulunamadi" << std::endl;
  }

}

void preOrder(Node *root)
{
    if(root != NULL)
    {
        std::cout << root->deger << " ";
        preOrder(root->sol);
        preOrder(root->sag);
    }
}

void printArray(int array[30])
{
    for(int i = 0; i < 30; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    srand(time(NULL));

    int array[30];

    for(auto& iter:array)
    {
        iter = rand() + 1;
    }
    printArray(array);

    Node *root = NULL;

    for(int i = 0; i < 30; i++)
    {
       root = ekle(root, array[i]);
    }
    preOrder(root);
    return 0;
}