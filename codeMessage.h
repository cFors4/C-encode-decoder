# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*structure definition*/

struct Node
{
char data;

struct Node *next;
struct Node *prev;
};

/*function blueprints*/

void error(char message[]);
void getChars(char **s, char wheel_file[]);
void createLinkedList(struct Node ** root, char wheelValues[]);
void codeLetters(struct Node* root, char letters[], int **coded, int lenWheel);
void decodeNumbers(struct Node* root, int numbers[], char **decoded, int len);



