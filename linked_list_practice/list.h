#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <linux/types.h>

struct listnode{
	int val;
	struct listnode *next;
};

struct listnode *descend(struct listnode *head);
