#ifndef TRIE_H_
#define TRIE_H_

#define ALPHABET_SIZE 26
#define TRAVERSE_TRIE for (int i = 0; i < ALPHABET_SIZE; i++)
#define NODE_BY_LETTER(letter) head->descendants[letter - 'a']

typedef struct trie trie_t;

typedef struct trie {
	trie_t* descendants[ALPHABET_SIZE];
    int is_final;
} trie_t;

void insert(trie_t *head, char *word);
int search(trie_t *head, char *word);
trie_t *create_trie();
void trie_to_file(trie_t *trie, int level, char *beginning, char *str, FILE *fp);
char *prefix_search(trie_t *head, char *word, FILE *fp);
//void print(trie_t *head);

#endif //TRIE_H_
