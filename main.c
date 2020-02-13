
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define WHEEL_MAX 100

struct Node
{
char data;

struct Node *next;
struct Node *prev;
};

struct Node *current = NULL;

/*function blueprints*/

void getChars(char **s, char wheel_file[]);
void createLinkedList(struct Node ** root, char wheelValues[]);
void traverse(struct Node * root);
void codeLetters(struct Node* root, char letters[], int **coded);



int main(int argc, char **argv)
{
  printf("Parameter Listing\n");

  int i;

  for (i = 1; i<argc; i++){
    printf("\t%d:%s\n",i,argv[i]);
  }
  if (argc<5)
  {
    printf ("Not enough arguments entered .\n ");
    exit (1);
  }

  char *wheel_file = argv[1];
  char *wheel;

  getChars(&wheel, wheel_file);
  printf("Coding Wheel values:\n\t %s\n",wheel);

  struct Node* root = NULL;
  createLinkedList(&root,wheel);
  free(wheel);


  if (argv[3] == "C")
  {
    /*take string to be coded*/
    int *coded;

    codeLetters(root,argv[4],&coded);
    free(coded);
  }



  if (argv[3] == "D")
  {
  /*take in numbers from argv[4] onwards to be decoded*/



  }
  /*store in file argv[2]*/
}
void getChars(char **str ,char wheel_file[])
{
  FILE * fp;
  char ch;
  int size;
  int x = 0;
  char prev;

  if ( ( fp = fopen (wheel_file , "r")) == NULL )
    {
      printf (" Unable to open file for read access .\n ");
      exit (1);
    }

  while((ch = fgetc(fp)) != EOF)
  {
    if(ch == '\n')
      size ++;
  }

  rewind(fp);

  if (!(*str = (char *)malloc(sizeof(char)*size)))
  {
    printf("Out of memory\n");
    exit(1);
  }

  /*deal with blank and repeating characters, ask!*/
  while( (ch = fgetc(fp)) != EOF)
  {
    if (ch != '\n')
      str[0][x++] = ch;

    if (ch == '\n' && prev == '\n')
      str[0][x++] = ' ';

    prev = ch;
  }
  str[0][x]='\0';
  fclose(fp);
}



void createLinkedList(struct Node** root, char wheel_values[]){

  int n;
  for(n =0; n<strlen(wheel_values);n++)
  {
    if(*root == NULL)
    {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node -> data = wheel_values[n];
    new_node -> next = new_node -> prev = new_node;
    *root = new_node;
    }

    else
    {
    struct Node* end = (struct Node*)malloc(sizeof(struct Node));
    end = (*root) -> prev;

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node -> data = wheel_values[n];

    (*root) -> prev = new_node;

    new_node -> prev = end;

    end -> next = new_node;
    }
  }
}

void traverse(struct Node* root){
  struct Node *trav = root;
  struct Node *end  = root -> prev;

  while (trav != end )
  {
    printf("traversing %c\n",trav->data);
    trav = trav -> next;
  }
  printf("traversing %c\n",trav->data);
}



void codeLetters(struct Node* root, char letters[], int **coded){
  struct Node *current = root;
  int i;
  struct Node *end     = root -> prev;

  if (!(*coded = (int *)malloc(sizeof(int)*strlen(letters))))
  {
    printf("Out of memory");
    exit(1);
  }

  for(i = 0; i<strlen(letters); i++)
  {
    int move = 0;
    printf("looking for %c from current %c\n",letters[i],current -> data);
    while(current != end)
    {
      move++;
      if(current -> data == letters[i])
      {
        printf("%c%d\n",current->data,i);
        break;
      }
      else
      {
      current = current -> next;
      }
    }
  }
}
