#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

typedef struct node* list;


list new_node() {
	list temp;
	temp = (list)malloc(sizeof(struct node));

	temp->next = NULL;

	return temp;
}

list append(list head, int value) {
	list temp, p;
	temp = new_node();
	temp->data = value;
	if (head == NULL) {
		head = temp;
	}
	else {
		p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = temp;
	}
	return head;
}

int len(list head) {
	int length = 1;
	list temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
		length++;
	}
	return length;
}

list remove_head(list head, int number) {
	int length = len(head);
	list newhead = head;
	list oldhead;
	if (number < length) {
		for (int i = 0; i < number; i++) {
			oldhead = newhead;
			newhead = newhead->next;
			free(oldhead);
		}
		return newhead;
	}
	else {
		return NULL;
	}
}

list remove_tail(list head) {
	int length = len(head);

	list temp = head;

	for (int i = 0; i < length - 2; i++) {
		temp = temp->next;
	}
	temp->next = NULL;
	return head;
}


int subscript(list head, int index) {
	int length = len(head);
	list temp = head;
	if (index < length) {
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp->data;
	}

}


list prepend(list head, int value) {
	list newhead;
	newhead = new_node();
	newhead->data = value;
	newhead->next = head;
	return newhead;
}

list extend(list head, list body) {
	for (int i = len(body) - 1; i >= 0; i--) {
		head = prepend(head, subscript(body, i));
	}
	return head;
}


int main(int argc, char* argv[]) {
	list worm;
	if (argc <= 1) {
		return 0;
	}
	else {
		worm = append(NULL, atoi(argv[1]));
		for (int i = 2; i < argc; i++) {
			worm = prepend(worm, atoi(argv[i]));
		}
	}
	int life = 0;
	while (worm != NULL && len(worm)) {
		life += 1;
		if (subscript(worm, 0)) {
			int i = 1;

			list active;
			active = append(NULL, subscript(worm, 0));

			for (int i = 1; i < len(worm) && subscript(worm, i) >= subscript(worm, 0); i++) {
				active = append(active, subscript(worm, i));
			}

			active = prepend(remove_head(active, 1), subscript(active, 0) - 1);

			list tempworm;

			worm = remove_head(worm, len(active));

			tempworm = append(NULL, 0);

			for (int j = 0; j <= life; j++) {
				tempworm = extend(tempworm, active);
			}

			tempworm = remove_tail(tempworm);

			if (worm != NULL) {
				tempworm = extend(worm, tempworm);
			}

			worm = tempworm;
		}
		else {
			worm = remove_head(worm, 1);
		}
	}
	printf("%d", life);
	return life;
}