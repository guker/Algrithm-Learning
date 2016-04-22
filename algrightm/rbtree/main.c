#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "rbtree.h"

int main()
{
	struct rb_tree tree;
	tree.root = NULL;

	int begin_key = 1;
	int end_key = 1000000;
	printf("init tree...\n");	
	printf("please input begin key:"); scanf("%d", &begin_key);
	printf("please input end key:"); scanf("%d", &end_key);

	printf("build tree...\n");	
	int i;
	for (i = begin_key; i <= end_key; i++) {
		printf("insert key:%d\n", i);
		rb_insert(&tree, i);
	}

	while (1) {
		char operate[32];
		int key;
	
		clock_t c1, c2;
		long offset;

		printf("please input operate:");
		scanf("%s", operate);
		
		if (!strcmp(operate, "i")) {
			printf("please input key:"); scanf("%d", &key);
			c1 = clock();
			rb_insert(&tree, key);
			c2 = clock();
		} else if (!strcmp(operate, "r")) {
			printf("please input key:"); scanf("%d", &key);
			c1 = clock();
			rb_remove(&tree, key);
			c2 = clock();
		} else if (!strcmp(operate, "s")) {
			printf("please input key:"); scanf("%d", &key);
			c1 = clock();
			struct rb_node *node = rb_search(&tree, key);
			if (node != NULL) {
				printf("find the key:%d\n", key);
			} else {
				printf("can not find the key:%d\n", key);
			}
			c2 = clock();
		} else if (!strcmp(operate, "q")) {
			break;
		} else {
			c1 = clock();
			printf("input operate error...\n");
			c2 = clock();
		}
		
		offset = c2 - c1;
		printf("take time:%ldms\n\n", offset);		
	}

	rb_free_tree(&tree);
	printf("please input any key to exit...\n");
	getchar();
	getchar();
	printf("bye.\n");
}
