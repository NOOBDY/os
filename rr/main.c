#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  struct node_t *next;
  int times;
} Node;

typedef struct {
  Node *head;
  Node *curr;
} LinkedList;

Node *new_node(int times) {
  Node *n = malloc(sizeof(Node));
  n->next = NULL;
  n->times = times;

  return n;
}

void print_ll(LinkedList *ll) {
  Node *ptr = ll->head;

  while (ptr != NULL) {
    printf("%d ", ptr->times);
    ptr = ptr->next;
  }

  printf("\n");
}

void exec(LinkedList *ll) {
  ll->curr->times -= 1;

  Node *ptr = ll->head;

  if (ll->head->times == 0) {
    if (ll->curr == ll->head) {
      ll->curr = ll->head->next;
    }
    ll->head = ll->head->next;
    free(ptr);
    return;
  }

  while (ptr->next != NULL) {
    Node *tmp = ptr->next;

    if (tmp->times == 0) {
      ll->curr = tmp->next;
      ptr->next = tmp->next;
      free(tmp);
      continue;
    }

    ptr = ptr->next;
  }
}

void next(LinkedList *ll) {
  ll->curr = ll->curr->next;

  if (ll->curr == NULL) {
    ll->curr = ll->head;
  }
}

int main(void) {
  Node *n0 = new_node(4);
  Node *n1 = new_node(2);
  Node *n2 = new_node(3);

  LinkedList ll = {
      n0,
      n0,
  };

  n0->next = n1;
  n1->next = n2;

  for (int i = 0; i < 10; ++i) {

    print_ll(&ll);

    exec(&ll);

    if (ll.head == NULL) {
      break;
    }

    next(&ll);
  }
}
