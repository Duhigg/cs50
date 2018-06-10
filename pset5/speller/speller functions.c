// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>


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

bool rec_empty(struct node *);
int rec_size(struct node *, int *);

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
            int cor_idx = toupper(word[i]) - 'A';
            // go to corresponding element in sprout
            if(trav->sprout[cor_idx])
                trav = trav->sprout[cor_idx];
            else
                return false;
        }
        else // current character must be an apostrophie, located in the last index of sprout(26)
        {
            int cor_idx = 26;
            if(trav->sprout[cor_idx])
                trav = trav->sprout[cor_idx];
            else
                return false;
        }
    }
    // once at the end of input word, check if the words match
      //printf("i == %d\nstrlen(word) == %lu\n", i, strlen(word));
        if (i == strlen(word))
        {
            if(trav->is_word == 1)
                return true;
        }

       // printf("is_word: %d\n", trav->is_word);

    return false;
}

// Loads dictionary into memory, returning true if successful else false
// lines marked with ¤ are awaiting editing
bool load(const char *dictionary)
{
    // TODO
    root = calloc(sizeof(node), 1);
    node *trav = root;
    // store number of words in dictionary
    unsigned int words = 0;
    char temp[LENGHT + 1];
    FILE *temp_dict = fopen(dictionary, "r");
    while(fgets(temp, LENGHT + 1, temp_dict))
        words++;
    rewind(temp_dict); // rewind file position indicator

    //printf("(load) words: %d\n", words);

    int cor_idx; // variable for indexing characters in words and their corresponding index in sprout
    int word_idx; // index of the current char of word in temp
    // for every dictionary word, iterate throught the TRIE
    for(int dict_idx = 0; dict_idx < words; dict_idx++)
    {
        // read a word from dict into a buffer of size LENGHT(45 CHARACTERS) + 1 (/0) - defined in main as 45
        fgets(temp, LENGHT + 1, temp_dict);
        // for each character in temp load into TRIE
        for(word_idx = 0; word_idx < strlen(temp) - 1; word_idx++)
        {
                // check for case
                if(isalpha(temp[word_idx]))
                {
                    // current character's corresponding index in the alphabet(sprout)
                    temp[word_idx] = toupper(temp[word_idx]);
                    cor_idx = temp[word_idx] - (int) 'A';

                    /* trav is not null on first iteration for the word,
                    so check for root's cor_idx instead to avoid problems in next statement.
                    */
                    if(word_idx == 0)
                    {
                        if(root->sprout[cor_idx] == NULL)
                        {
                            node *new_node = calloc(sizeof(node), 1);
                            trav->sprout[cor_idx] = new_node;
                            trav = trav->sprout[cor_idx];
                        }
                        else
                            trav = root->sprout[cor_idx];
                    }
                    else
                    {
                        // if NULL, calloc a new node, have sprout[cor_idx] point to it and enter the new_node
                        if (trav->sprout[cor_idx] == NULL)
                        {
                            node *new_node = calloc(sizeof(node), 1);
                            trav->sprout[cor_idx] = new_node;
                            trav = trav->sprout[cor_idx];
                        }
                        else // if not NULL, point to existing new_node
                            trav = trav->sprout[cor_idx];
                    }
                }
                else // temp[word_idx] is not a character therefore it must be and apostrophie, index n-1 in sprout = 26
                {
                    cor_idx = 26;
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
        // if at end of word, set is_word to true
       // printf("word_idx: %d\nstrlen(temp) - 1: %lu\n", word_idx, strlen(temp) - 1);
        if(word_idx == strlen(temp) - 1)
        {
            trav->is_word = 1;
            trav = root;
        }
        if(dict_idx == words - 1)
        {
         fclose(temp_dict);
         return true;
        }
    }
    return false;
}

    // Returns number of words in dictionary if loaded else 0 if not yet loaded
    unsigned int size(void)
    {
        /* Use recursion(rec_size) to search for is_word == 1 and increase count++
            if is_word == 0 continue until it == 1.
        */
        // count_sum to be returned to main, count for rec_sum().
        int *count;
        count = malloc(sizeof(int));
        //count_sum = malloc(sizeof(int));
        *count = 0;
        if(!root)
            return 0;
        else
        {
            node *trav = root;
            for (int i = 0; i < 27; i++)
            {
                /* if trav->sprout[i] is not a null value there's a index value,
                go into that node and check, in rec_sze, if the path contains a word(is_word == 1)
                 */
                if(trav->sprout[i])
                {
                    trav = trav->sprout[i];
                    if(trav->is_word == 1)
                        (*count)++;
                    rec_size(trav, count);
                }
            }
        }
        unsigned int n = *count;
        free(count);
        return n;
    }

    int rec_size(struct node *trav, int *count)
    {
        for (int i = 0; i < 27; i++)
        {
           if(trav->sprout[i])
            {
                trav = trav->sprout[i];
                if(trav->is_word == 1)
                {
                    (*count)++;
                    //printf("cur_char: %c\n", (char) (i + 'A'));
                }
                rec_size(trav, count);
            }
        }
        /* I think I am returning the value stored in the address
        that count is pointing to back to size(), is that so?
        */
        return *count;
    }

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *trav = root; // point trav to root
    int root_idx;
    const int size_sprout = 27; // sizeof sprout[]
    // iterate through root->sprout and free bottom up with recursion
    for(root_idx = 0; root_idx < size_sprout; root_idx++)
    {
        if(trav->sprout[root_idx])
        {
            cursor = trav->sprout[root_idx];
            if(!rec_empty(cursor))
                return false;
        }
    }
    return true;
}

bool rec_empty(struct node *cursor)
{
    // loop to the bottom of the trie if(!) and free from bottom up
    for(int i = 0; i < 27; i++)
    {
        if(cursor->sprout[i])
        {
            if(!rec_empty(cursor->sprout[i]))
                return false;
            cursor->sprout[i] = NULL; // just in case
        }
    }
    free(cursor);
    return true;
}
