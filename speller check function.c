// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// define a node struct for a TRIE
typedef struct node
{
    bool is_word;
    struct node *sprout[27];
}
node;

#define TRUE 1
#define FALSE 0

#include "dictionary.h"

/*// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
} */

// Loads dictionary into memory, returning true if successful else false
// lines marked with ¤ are awaiting editing
bool load(const char *dictionary)
{
    // TODO


    // root node, do not alter
    node *root = malloc(sizeof(node));
    // traverse pointer for traversing through the trie
    node *trav = root;

    // set sprouts pointer to NULL, rid of magic numbers? ¤
    for(int p = 0; p < 27; p++)
    {
        root->sprout[p] = NULL;
        trav->sprout[p] = NULL; // edited for debuggin ¤
    }

    // store number of words in dictionary
    int words = 0;
    char *temp = malloc(45 * sizeof(char));
    FILE *temp_dict = fopen(dictionary, "r");
    while(fgets(temp, 45 + 1, temp_dict) != NULL)
        words++;



    // set the file position indicator of dictionar to the beginning of the file, [¤not sure if necessary]
    rewind(temp_dict);

    // variable for indexing characters in words and their corresponding index in sprout
    int cor_idx;

    // for every dictionary word, iterate throught the TRIE
    for(int dict_idx = 0; dict_idx < words; dict_idx++)
    {
        // read a word from dict into a buffer of size LENGHT(45 CHARACTERS) - defined in main as 45
        char *word_buffer = malloc(45 * sizeof(char));
        fgets(word_buffer, 45 + 1, temp_dict);
        // realloc to get rid of excess memory? not sure if necessary(?)
        realloc(word_buffer, strlen(word_buffer) * sizeof(char));
        // for each character in word_buffer load into TRIE


        for(int word_idx = 0; word_idx < strlen(word_buffer); word_idx++)
        {
                // check for case
                if(isalpha(word_buffer[word_idx]))
                {
                    // current character's corresponding index in the alphabet(sprout)
                    if(toupper(word_buffer[word_idx]))
                    {
                        cor_idx = word_buffer[word_idx] - (int) 'A';
                    }
                    else
                        cor_idx = word_buffer[word_idx] - (int) 'a';

                    // if NULL, malloc a new node, have sprout[cor_idx] point to it
                    if (trav->sprout[cor_idx] == NULL)
                    {
                        node *new_node = malloc(sizeof(node));

                        // set sprouts to NULL, rid of magic numbers(27)? ¤ unnecessary loop?
                        for(int p = 0; p < 27; p++)
                        {
                            new_node->sprout[p] = NULL; //
                        }
                        // go into that node
                        trav->sprout[cor_idx] = new_node;
                    }
                    else // if not NULL, point to new_node since there already is one(?) ¤
                            trav->sprout = new_node;;
                    // if at end of word, set is_word to true
                    if(word_idx == strlen(word_buffer) - 1)
                    {
                        is_word == 1;
                        trav->sprout = root;
                    }

                }
                else // neither upper or lower, current character must be and apostrophie index n-1
                {
                    // last index of sprout
                    cor_idx = sizeof(node->sprout) / sizeof(node) - 1;
                    // check for null pointers
                    switch(trav->sprout[cor_idx] == NULL)
                    {
                        case TRUE :
                            node *new_node = malloc(sizeof(node));
                            trav->sprout[cor_idx] = new_node;
                            break;
                        default :
                            trav->sprout[cor_idx] = new_node;
                    }
                    // if at end of word, set is_word to true
                    if(word_idx == strlen(word_buffer) - 1)
                    {
                        is_word == 1;
                        trav->sprout = root;
                    }

                }

        }
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
    return false;
}
