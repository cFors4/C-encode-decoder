
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
void codeLetters(struct Node* root, char letters[], int **coded, int lenWheel);
void decodeNumbers(struct Node* root, int numbers[], char **decoded, int len);

int main(int argc, char **argv)
{
  /*List parameters from the inputs of argv*/
  printf("Parameter Listing\n");
  int i;
  for (i = 1; i<argc; i++)
  {
    printf("\t%d:%s\n",i,argv[i]);
  }

  /*checking enough parameters*/
  if (argc<5)
  {
    printf ("Not enough arguments entered .\n ");
    exit (1);
  }

  /*getting wheel characters from wheel file*/
  char *wheel_file = argv[1];
  char *wheel;

  getChars(&wheel, wheel_file);
  printf("Coding Wheel values:\n\t %s\n",wheel);

  /*creating linked list from characters read in*/
  struct Node* root = NULL;
  createLinkedList(&root, wheel);

  int lenWheel;
  lenWheel = strlen(wheel);

  /*free wheel to avoid memory leakage*/
  free(wheel);

  /*checking mode coding or decoding*/
  if (strcmp(argv[3],"C")==0)
  {
    /*take string to be coded*/
    int *coded;
    int n;
    char input[] = " ";

    codeLetters(root, argv[4], &coded, lenWheel);


    FILE *f = fopen(argv[2], "w");
    for(n = 0; n<strlen(argv[4]);n++){
      char buffer[5] = "hell";
      sprintf(buffer,"%d",coded[n]);
      printf("%s\n",buffer);
      strncat(input, buffer, 1);
      strncat(input, " ", 1);
      printf("%s\n",input);

    }
    fwrite(input, sizeof(char), sizeof(strlen(argv[4])), f);
    fclose(f);

    free(coded);
  }



  if (strcmp(argv[3],"D")==0)
  {
    /*take in numbers from argv[4] onwards to be decoded*/
    char *decoded;
    int n;

    int size = argc - 4 ;
    int* numbers  = (int*)calloc( size, sizeof(int));

    for( n = 0; n < size; n++){
      sscanf( argv[n + 4], "%d", &numbers[n]);
    }
    decodeNumbers(root, numbers, &decoded, size);

    FILE *f = fopen(argv[2], "w");
    fwrite(decoded, sizeof(char), sizeof(decoded), f);
    fclose(f);

    free(decoded);
  }



  /*store in file argv[2]*/
  return 0;
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

  while( (ch = fgetc(fp)) != EOF)
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
    new_node -> next = (*root);

    end -> next = new_node;
    }
  }
}



void codeLetters(struct Node* root, char letters[], int **coded, int lenWheel){
  struct Node *current = root;
  int i;

  if (!(*coded = (int *)malloc(sizeof(int)*strlen(letters))))
  {
    printf("Out of memory");
    exit(1);
  }

  for(i = 0; i<strlen(letters); i++)
  {
    int move = 0;
    printf("looking for %c from current %c\n",letters[i],current -> data);

    while (move<lenWheel)
    {
      if(current -> data == letters[i])
        break;

      else
      {
      current = current -> next;
      move++;
      }
    }
    if(move>((strlen(letters)/2)))
      move = move - lenWheel;

    printf("it took %d move\n",move);
    coded[0][i] = move;
    printf("%dwow\n",coded[0][i]);
  }
}


void decodeNumbers(struct Node* root, int numbers[], char **decoded, int len){
  struct Node *current = root;
  int i;

  printf("%d len\n",len);
  if (!(*decoded = (char *)malloc(sizeof(char)*len)))
  {
    printf("Out of memory");
    exit(1);
  }



  for(i = 0; i<len; i++)
  {

    int moves = numbers[i];
    while(moves != 0)
    {
      printf("%d moves left on %d\n",moves,numbers[i]);

      if (moves<0)
      {
        current = current -> prev;

        moves++;
      }
      else
      {
        printf("going to letter %c\n",current -> next -> data);
        current = current -> next;
        moves--;
      }
    }
    printf("%c added to decoded\n",current->data);
    decoded[0][i] = current -> data;
  }
}

