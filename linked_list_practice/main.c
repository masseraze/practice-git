#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <linux/types.h>
#include "list.h"
struct listnode* createlist(int *arr, int n){
    struct listnode *head = NULL, *curr =NULL;
    for(int i=0;i<n;i++){
    struct listnode *node = (struct listnode*)malloc(sizeof(struct listnode));
         
        node->val = *(arr+i);
        node->next = NULL;
        if(!head){
	    head = node;
	}
	else{
	    curr->next = node;
	}
	curr = node;
    }
    return head;
}

void printlist(struct listnode *head){
    printf("list:\n");
    while(head){
        printf("%d, ",head->val);
	head = head->next;
    }
    printf("\n");
}

struct listnode *mergetwolists(struct listnode *L1, struct listnode *L2){
    struct listnode *head = NULL, **ptr = &head, **node=NULL;

    //while(L1 && L2){
    for(node = NULL; L1 && L2 ; *node = (*node)->next){
        node = (L1->val < L2->val)? &L1:&L2;
	*ptr = *node;
	ptr = &(*ptr)->next;
	//node = &(*node)->next;
    }

    *ptr = L1 ? L1:L2;
    //*ptr = ( L1 | L2);
    return head;
}

bool deletemiddle(struct listnode **indir){
    if(!(*indir)->next){
        return false;
    }
    struct listnode *prev = NULL;
    for(struct listnode *fast = *indir; fast != NULL && fast->next != NULL; fast = fast->next->next){
	    prev = *indir;
	    indir = &(*indir)->next;
    }
    // printf("value in indir: %d\n",(*indir)->val);
    // prev->next = (*indir)->next;
    // printf("value in prev: %d, value in next prev:
    // %d\n",prev->val,prev->next->val);
    /*correct method*/
    struct listnode *next = (*indir)->next;
    // printf("value in next: %d, ", next->val);
    // printf("value in indir(after prev->next linked): %d\n",(*indir)->val);
    free(*indir);
    prev->next = next;
    return true;
}

struct listnode *partition(struct listnode *head, int x) {
  struct listnode *l2 = NULL;
  struct listnode **p1 = &head, **p2 = &l2;

  for (struct listnode *node = head; node; node = node->next) {
    // for (; head; head = head->next) {
    struct listnode ***indir = head->val < x ? (&p1) : (&p2);
    **indir = node;
    *indir = &(**indir)->next;
    /*
    if (node->val < x) {
      *p1 = node;
      p1 = &(*p1)->next;
    } else {
      *p2 = node;
      p2 = &(*p2)->next;
    }
    */
  }
  *p1 = l2;
  *p2 = NULL;
  return head;
}

struct listnode *partition1(struct listnode *head, int x) {
  struct listnode *l1 = malloc(sizeof(struct listnode));
  struct listnode *l2 = malloc(sizeof(struct listnode));
  l1->val = 0, l1->next = NULL, l2->val = 0, l2->next = NULL;

  struct listnode *ptr1 = l1, *ptr2 = l2;
  for (; head; head = head->next) {
    if (head->val < x) {
      ptr1->next = head;
      ptr1 = ptr1->next;
    } else {
      ptr2->next = head;
      ptr2 = ptr2->next;
    }
  }

  ptr2->next = NULL;
  ptr1->next = l2->next;
  return l1->next;
}

struct listnode *reverse(struct listnode *head) {
  struct listnode *prev = NULL;
  struct listnode *next = NULL;
  for (struct listnode *node = head; node;) {
    next = node->next;
    node->next = prev;
    prev = node;
    node = next; // node->next(previous)
  }
  head = prev;
  return head;
}

struct listnode *reversek(struct listnode *head, int x) {
  struct listnode *prev = NULL;
  struct listnode *next = NULL;
  struct listnode *test = NULL;
  struct listnode *node = head;
  int stop = 0;
  int go = 0;
  int total = 0;
  int initial = 1;
  while (!stop) {
    test = node;
    for (int k = 0; k < x; k++) {
      if (test == NULL) {
        stop = 1;
        go = 0;
        break;
      } else {
        // total++;
        go = 1;
      }
      printf("k: %d, test->val: %d,total:%d\n", k, test->val, total);
      test = test->next;
    }
    total++;
    if (go == 1) {
      for (int k = 0; k < x; k++) {
        next = node->next;
        node->next = prev;
        prev = node;
        printf("prev to node %d \n", prev->val);
        node = next; // node->next(previous)
      }
      if (initial == 1) {
        head = prev;
        initial = 0;
      }
      go = 0;
    }
  }
  return head;
}

int main(){
  int arr1[] = {1, 5, 2, 6, 3};
  int arr2[] = {998, 932, 91, 698};
  struct listnode *l1 = createlist(arr1, 5);
  struct listnode *l2 = createlist(arr2, 4);
  printlist(l1);
  printlist(l2);
  struct listnode *mergedlist = mergetwolists(l1, l2);
  printlist(mergedlist);

  struct listnode *partitionlist = partition(mergedlist, 5);
  printlist(partitionlist);
  bool i = deletemiddle(&mergedlist);
  printlist(mergedlist);

  struct listnode *descendlist = descend(mergedlist);
  printlist(descendlist);

  while (descendlist) {
    struct listnode *temp = descendlist;
    descendlist = descendlist->next;
    free(temp);
  }
        return 0;
}
