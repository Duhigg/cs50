// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define LENGHT 45
#define TRUE 1
#define FALSE 0

#include "dictionary.h"

// define a node struct for a TRIE
typedef struct node
{
    bool is_word;
    struct node *sprout[27];
}
node;

    node *root; // root node, do not alter

void recursion(node*);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *trav = root;
    int i;
    // iterate through characters in word
    for(i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            int word_idx = toupper(word[i]) - 'A';

                // go to corresponding element in sprout
                if(trav->sprout[word_idx])
                    trav = trav->sprout[word_idx];
        }
        else // current character must be an apostrophie, located in the last index of sprout(27)
        {
            int word_idx = 27;
            if(trav->sprout[word_idx])
                trav = trav->sprout[word_idx];
        }
    }
    // once at the end of input word, check if the words match
        if (i == strlen(word) - 1)
        {
            if(trav->is_word == 1)
                return true;
        }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
// lines marked with ¤ are awaiting editing
bool load(const char *dictionary)
{
    // TODO
    root = malloc(sizeof(node));
    node *trav = root;
    // store number of words in dictionary
    int words = 0;
    char temp[LENGHT + 1];
    FILE *temp_dict = fopen(dictionary, "r");
    while(fgets(temp, LENGHT + 1, temp_dict))
        words++;
    rewind(temp_dict); // rewind file position indicator


    int cor_idx; // variable for indexing characters in words and their corresponding index in sprout

    // for every dictionary word, iterate throught the TRIE
    for(int dict_idx = 0; dict_idx < words; dict_idx++)
    {
        // read a word from dict into a buffer of size LENGHT(45 CHARACTERS) + 1 (/0) - defined in main as 45
        fgets(temp, LENGHT + 1, temp_dict);
        // for each character in temp load into TRIE
        for(int word_idx = 0; word_idx < strlen(temp); word_idx++)
        {
                // check for case
                if(isalpha(temp[word_idx]))
                {
                    // current character's corresponding index in the alphabet(sprout)
                    temp[word_idx] = toupper(temp[word_idx]);
                    cor_idx = temp[word_idx] - (int) 'A';

                    /* trav is not null on first iteration for the word,
                        so check for roots cor_idx instead to avoid problems in next statement.
                    */
                    if(word_idx == 0)
                    {
                        if(root->sprout[cor_idx] == NULL)
                        {
                            node *new_node = calloc(sizeof(node), 1);
                            trav->sprout[cor_idx] = new_node;
                            trav = trav->sprout[cor_idx];
                        }
                    }

                    // if NULL, calloc a new node, have sprout[cor_idx] point to it and enter the new_node
                    if (trav->sprout[cor_idx] == NULL)
                    {
                        node *new_node = calloc(sizeof(node), 1);
                        // go into that node
                        trav->sprout[cor_idx] = new_node;
                        trav = trav->sprout[cor_idx];
                    }
                    else // if not NULL, point to existing new_node
                        trav = trav->sprout[cor_idx];
                }
                else // neither upper or lower, current character must be and apostrophie index n-1
                {
                    cor_idx = sizeof(trav->sprout) / sizeof(node);
                    // check for null pointers
                    if(trav->sprout[cor_idx] == NULL)
                    {
                            node *new_node = calloc(sizeof(node), 1);
                            trav->sprout[cor_idx] = new_node;
                            trav = trav->sprout[cor_idx];
                    }
                    else
                        trav = trav->sprout[cor_idx];
                    // if at end of word, set is_word to true
                    if(word_idx == strlen(temp) - 1)
                    {
                        trav->is_word = 1;
                        trav = root;
                    }

                }

        }
        if(dict_idx == words - 1)
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node* cursor;
    node *trav = root; // point trav to root
    unsigned int size_sprout = sizeof(trav->sprout) / sizeof(node); // sizeof sprout[]
    // iterate through root->sprout and free bottom up with recursion
    for(int root_idx = 0; root_idx < size_sprout; root_idx++)
    {
        if(trav->sprout[root_idx])
        {
            cursor = trav->sprout[root_idx];
            recursion(**cursor);
        }
    }

    if (root == NULL && trav == NULL)
    {
        //if(trav == NULL)
            free(trav);
        //if(root == NULL)
            free(root);

        return true;
    }
return false;
}

void recursion(node*) //¤ INCOMPLETE
{
    node *trav;
    // sizeof sprout[] pointer array
    unsigned int size_sprout = sizeof(trav->sprout) / sizeof(node);
    // loop to the bottom of the trie and free from bottom up
    for(int i = 0; i < size_sprout; i++)
    {
        if(cursor->sprout[i])
        {
            recursion(**cursor->sprout[i]);
            trav->sprout[i] = NULL; // just in case
        }
    }
    free(cursor);
}
