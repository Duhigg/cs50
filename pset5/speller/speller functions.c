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
    node *trav; // traverse pointer for traversing through the trie
    node *new_node;
    node *cursor;// temporal cursor for recursion in unloading

void recursion(node *);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // iterate through characters in word
    for(int i = 0; i < strlen(word); i++)
    {
        int word_idx = toupper(word[i]) - 'A';

            // go to corresponding element in sprout
            trav = root;
            if(trav->sprout[word_idx])
            {
                trav->sprout[word_idx] = new_node;
            }
            // once at the end if input word, check if the words match
            if (word_idx == strlen(word) - 1)
            {
                if(trav->is_word == 1)
                    return true;
            }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
// lines marked with ¤ are awaiting editing
bool load(const char *dictionary)
{
    // TODO
    root = malloc(sizeof(node));
    trav = root;
    // store number of words in dictionary
    int words = 0;
    char temp[LENGHT + 1];
    FILE *temp_dict = fopen(dictionary, "r");
    while(fgets(temp, LENGHT + 1, temp_dict))
        words++;
    rewind(temp_dict); // rewind file position indicator


    int cor_idx; // variable for indexing characters in words and their corresponding index in sprout
    int count = 0; // counter for how many words read

    // for every dictionary word, iterate throught the TRIE
    for(int dict_idx = 0; dict_idx < words; dict_idx++)
    {
        // read a word from dict into a buffer of size LENGHT(45 CHARACTERS) + 1 (/0) - defined in main as 45
        char word_buffer[LENGHT + 1];
        fgets(word_buffer, LENGHT + 1, temp_dict);
        // for each character in word_buffer load into TRIE
        for(int word_idx = 0; word_idx < strlen(word_buffer); word_idx++)
        {
                // check for case
                if(isalpha(word_buffer[word_idx]))
                {
                    // current character's corresponding index in the alphabet(sprout)
                    word_buffer[word_idx] = toupper(word_buffer[word_idx]);
                    if(word_buffer[word_idx] > 91 && word_buffer[word_idx] < 123)
                    {
                        printf("line 92 shouldn't happen."); //¤debug
                        return 4;
                    }
                    cor_idx = word_buffer[word_idx] - (int) 'A';

                    // if NULL, malloc a new node, have sprout[cor_idx] point to it
                    if (trav->sprout[cor_idx] == NULL)
                    {
                        new_node = malloc(sizeof(node));

                        // set sprout to NULL, rid of magic numbers(27)? ¤ unnecessary loop?
                        for(int p = 0; p < 27; p++)
                        {
                            new_node->sprout[p] = NULL; //
                        }
                        // go into that node
                        trav->sprout[cor_idx] = new_node;
                    }
                    else // if not NULL, point to existing new_node
                        trav->sprout[cor_idx] = new_node;

                    // if at end of word, set is_word to true
                    if(word_idx == strlen(word_buffer) - 1)
                    {
                        trav->is_word = 1;
                        trav = root;
                        count++;

                    }

                }
                else // neither upper or lower, current character must be and apostrophie index n-1
                {
                    cor_idx = sizeof(trav->sprout) / sizeof(node);
                    // check for null pointers
                    if(trav->sprout[cor_idx] == NULL)
                    {

                            new_node = malloc(sizeof(node));
                            trav->sprout[cor_idx] = new_node;
                    }
                    else
                        trav->sprout[cor_idx] = new_node;
                    // if at end of word, set is_word to true
                    if(word_idx == strlen(word_buffer) - 1)
                    {
                        trav->is_word = 1;
                        trav = root;
                        count++;
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


void recursion()
{
    unsigned int size_sprout = sizeof(trav->sprout) / sizeof(node); // sizeof sprout[]

    for(int i = 0; i < size_sprout; i++)
    {
        if(trav->sprout[i])
        {
            recursion(trav->sprout[i]);
            trav->sprout[i] = NULL; // just in case
        }
    }
    free(cursor);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    unsigned int size_sprout = sizeof(trav->sprout) / sizeof(node); // sizeof sprout[]
    trav = root; // point trav to root
    // iterate through root->sprout and free bottom up with recursion
    for(int root_idx = 0; root_idx < size_sprout; root_idx++)
    {
        if(trav->sprout[root_idx])
        {
            cursor = trav->sprout[root_idx];
            recursion(cursor);
        }
    }
    //
    if(root == NULL && new_node == NULL && trav == NULL)
    {
        free(root);
        free(new_node);
        free(trav);
        return true;
    }
    else
        printf("line 200");
return false;
}
