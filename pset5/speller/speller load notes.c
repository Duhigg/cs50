LINKED LISTS

typedef struct node
{
  char word[LENGHT + 1];
  struct node *next;
}
node;

// creating nodes is just allocating memory
node *node1 = malloc(sizeof(node));
node *node2 = malloc(sizeof(node));
strcpy(node1->word, "Hello");
strcpy(node2->word, "dawg");
node1->next = node2;

HASH TABLE
an array of linked lists, each element of an array is a node pointer

typdef struct node
{
  char word[LENGHT + 1];
  struct node *next;
}
node;

node *hashtable[50];

// fscan words from the dictionary into the hashtable
while (fscanf(file, "%s", word) != EOF)
{
  node *new_node = malloc(sizeof(node));
  // check for null pointer
  if (new_node == NULL)
  {
    unload();
    return false; so speller quits
  }
  // cope read word into new_node
  strcpy(new_node->word, word);

  new_node->next = head;
  head = new_node;
}

TRIE
every node contains an array of node pointers
  one for every letter of the alphabet + '\''
  each element in the array points to another node
    if that node is NULL, then that letter is not the next
    letter of any word in that sequence
every node indicates wherer it is the
last character of a word

typedef struct node
{
  bool is_word;
  struct node *children[27];
}
node;

node *root;

load

for every dictionary word, iterate throught the TRIE
each element in children corrseponds to a different letter
check the value at children[i]
  if NULL, malloc a new node, have children[i] point to it
  if not NULL, move to new node and continue
if at end of word, set is_word to true
