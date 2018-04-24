// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // define a node struct for a TRIE
    typedef struct node
    {
        bool is_word;
        struct node *sprout[27];
    }
    node;

    // root node, do not alter
    node *root = malloc(sizeof(node));

    // store number of words in dictionary
    int words = 0;
    char *temp = malloc(45 * sizeof(char));
    FILE *temp_dict = fopen(dictionary, "r");
    while(fgets(temp, 45 + 1, temp_dict) != NULL)
        words++;

    // traverse pointer for traversing through the trie
    node *trav = root;

    // set the file position indicator of dictionar to the beginning of the file, [not sure if necessary]
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
                if(isupper(word_buffer[word_idx]))
                {
                    // word's characters index corresponding to sprouts index... TBE
                    cor_idx = word_buffer[word_idx] - (int) 'A';
                    // check for null pointers in
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
                if(islower(word_buffer[word_idx]))
                {
                    // index for the alphabet
                    cor_idx = word_buffer[word_idx] - (int) 'a';
                    // check for null pointers in
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
                /*  if neither upper or lower, current character must be and apostrophie
                    and the index is therefore the last index of sprout
                */
                else
                {
                    // last index of sprout
                    cor_idx = sizeof(sprout) / sizeof(node) - 1;
                    // check for null pointers
                    switch(trav->sprout[cor_idx] == NULL)
                    {
                        case TRUE :
                            node *new_node = mallock(sizeof(node));
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
