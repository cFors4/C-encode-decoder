# include "codeMessage.h"


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
    error("not enough arguments");
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
    char buffer[12] = "hell";
    codeLetters(root, argv[4], &coded, lenWheel);

    for(n = 0; n<strlen(argv[4]);n++)
    {
      sprintf(buffer,"%d",coded[n]);
      strncat(input, buffer, 2);
      strncat(input, " ", 1);
    }
    int size = strlen(input);

    FILE *f = fopen(argv[2], "w");
    fwrite(input, sizeof(char), size, f);
    fclose(f);
  }
  else if (strcmp(argv[3],"D")==0)
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
  else{
    error("Invalid mode, must be C or D");
  }

  return 0;
}



void error(char message[])
{
  fprintf(stderr, "ERROR: %s\n",message);
  exit(EXIT_FAILURE);
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
      error(" Unable to open file for read access");
    }

  while( (ch = fgetc(fp)) != EOF)
  {
    if(ch == '\n')
      size ++;
  }

  rewind(fp);

  if (!(*str = (char *)malloc(sizeof(char)*size)))
  {
    error("Out of memory");
  }

  /*read characters from file until reached end of file*/
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



void createLinkedList(struct Node** root, char wheel_values[])
{
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



void codeLetters(struct Node* root, char letters[], int **coded, int lenWheel)
{
  struct Node *current = root;
  int i;

  if (!(*coded = (int *)malloc(sizeof(int)*strlen(letters))))
  {
    error("out of memory");
  }

  for(i = 0; i<strlen(letters); i++)
  {
    int move = 0;
    while (move < lenWheel)
    {
      if(current -> data == letters[i])
        break;

      else
      {
      current = current -> next;
      move++;
      }
    }
    if(move>((lenWheel/2)))
      move = move - lenWheel;

    coded[0][i] = move;
  }
}


void decodeNumbers(struct Node* root, int numbers[], char **decoded, int len)
{
  struct Node *current = root;
  int i;

  if (!(*decoded = (char *)malloc(sizeof(char)*len)))
  {
    error("out of memory");
  }

  for(i = 0; i<len; i++)
  {

    int moves = numbers[i];
    while(moves != 0)
    {
      if (moves<0)
      {
        current = current -> prev;
        moves++;
      }
      else
      {
        current = current -> next;
        moves--;
      }
    }
    decoded[0][i] = current -> data;
  }
}
