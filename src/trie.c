#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "string.h"

trie_t *create_trie()
{
	trie_t *buff = malloc(sizeof(trie_t));
	buff->is_final = 0;
	TRAVERSE_TRIE
		buff->descendants[i] = NULL;
	return buff;
}

void insert_trie(trie_t *head, char *word)
{
	if (*word == '\0') { head->is_final = 1; return; }
	NODE_BY_LETTER(*word) = NODE_BY_LETTER(*word) ? 
	                        NODE_BY_LETTER(*word) : 
	                        create_trie();
	trie_t *buff = NODE_BY_LETTER(*word);
	insert_trie(buff, ++word);
}

int search(trie_t *head, char *word)
{
	trie_t *buff = head;
	for (; *word != '\0', buff->descendants[*word - 'a'] != NULL; word++)
		buff = buff->descendants[*word - 'a'];
	if (buff->is_final == 1)
		return 1;
	return 0;
}

char *prefix_search(trie_t *head, char *word, FILE *fp)
{
	if (head == NULL)
		return NULL;
	trie_t *buff = head;
	char str[20], beginning[20];
	strcpy(beginning, word);
	for (; *word != '\0', buff->descendants[*word - 'a'] != NULL; word++)
		buff = buff->descendants[*word - 'a'];

	trie_to_file(buff, 0, beginning, str, fp);

}

void trie_to_file(trie_t *trie, int level, char* beginning, char *str, FILE *fp)
{
	if (trie->is_final)
	{
		str[level] = '\0';
		fprintf(fp, "%s%s\n", beginning, str);
	}
	TRAVERSE_TRIE
		if (trie->descendants[i] != NULL)
		{
			str[level] = i + 'a';
			trie_to_file(trie->descendants[i], level + 1, beginning, str, fp);
		}
}
