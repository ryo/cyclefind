#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/queue.h>

#include "cyclefind.h"

struct element {
	int id;
	struct element *next;
};

struct element *listhead;

CYCLEFIND_DECL(, struct element *) cf;

int
main(int argc, char *argv[])
{
#define N	1000
	struct element elm[N];
	struct element *e;
	int i;

	memset(elm, 0, sizeof(elm));

	/* insert head */
	for (i = 0; i < __arraycount(elm); i++) {
		elm[i].id = i;
		elm[i].next = listhead;
		listhead = &elm[i];
	}

	/* make loop */
	elm[123].next = &elm[456];

	/* cycle detection test */
	CYCLEFIND_INIT(&cf, 10000);
	for (e = listhead; e != NULL; e = e->next) {
		int n;
		if (CYCLEFIND_OVERLIMIT(&cf)) {
			printf("Overlimited. break\n");
			break;
		}

		if ((n = CYCLEFIND_TEST(&cf, e)) != 0) {
			printf("Looped! last %d link looped\n", n);
			break;
		}

		printf("%p: %d\n", e, e->id);
	}
}
