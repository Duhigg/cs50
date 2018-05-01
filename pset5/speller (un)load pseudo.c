for each char in input word
  go to corresponding element in sprout
    if NULL, word is misspelled
    if != NULL, move to next letter
  once at end of input word
    check if is_word == TRUE

Unload

travel to lowest possible node
  free all pointers in children
  backtrack upwards, freeing all elements in
  each children array untill hit root node

  check recursion
