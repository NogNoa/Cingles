#include <stddef.h>

#include "tree_count.h"

struct tnode *talloc(void);
struct htnode *htalloc(void);
char *KnR_strdup(char *);


struct tnode *addtree(struct tnode *p, char *w)
{  /* addtree: add a node with w, at or below p */
	int cond;
	
	if (p == NULL) { /* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = KnR_strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++; /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

struct htnode *haddtree(struct htnode *p, char* word, char *head, int h_len)
{  /* haddtree: add a node with w[0,h_len], at or below p */
	int cond;

	if (p == NULL)  
	{	p = htalloc(); 
		p->head = KnR_strdup(head);
		p->count = 1;
		p->left = p->right = NULL;
		p->headroot = addtree(p->headroot,word);
	} else if ((cond = strcmp(head, p->head)) == 0)
	{	p->count++; 
		p->headroot = addtree(p->headroot,word);
	} else if (cond < 0)
		p->left = haddtree(p->left, word, head, h_len);
	else 
		p->right = haddtree(p->right, word, head, h_len);
	return p;
}

_Bool shouldignore(char* word, char* ignore_me[], int ig_size)
{
	for(int k=0;k<ig_size;k++)
	{	if (strcmp(word, ignore_me[k]) == 0)
			return 1;
	}
	return 0;
}

void treeprint(struct tnode *p)
{  /* treeprint: in-order print of tree p */
	if (p != NULL) 
	{	treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

void tree_line_print(struct tnode *p)
{  /* treeprint: in-order print of tree p */
	if (p != NULL) 
	{	tree_line_print(p->left);
		printf("%s ", p->word);
		tree_line_print(p->right);
	}
}

void htreeprint(struct htnode *p)
{  /* treeprint: in-order print of tree p */
	if (p != NULL) 
	{	htreeprint(p->left);
		printf("%4d %s: ", p->count, p->head);
		tree_line_print(p->headroot);
		putchar('\n');
		htreeprint(p->right);
	}
}
