/*
* External Chaining Method 
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person{
	char name[MAX_NAME];
	int age;
	struct person *next;
};

struct person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
	int length = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;
	for (int i = 0; i < length; i++) {
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}
	return hash_value;
}

void init_hashtable() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
}

void print_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) {
			printf("\t%i\t----\n", i);
		}else {
			printf("\t%i\t ", i);
			struct person *tmp = hash_table[i];
			while (tmp != NULL) {
				printf("%s - ", tmp->name);
				tmp = tmp->next;
			}
			printf("\n");
	}
	}
}

bool hash_table_insert(struct person *p) {
	if (p == NULL)
		return false;
	int index = hash(p->name);
	p->next = hash_table[index];
	hash_table[index] = p;
	return true;
}

struct person *hash_table_lookup(char *name) {
	int index = hash(name);
	struct person *tmp = hash_table[index];
	while(tmp!=NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
		tmp = tmp -> next;
	}
	return tmp;
}

struct person *hash_table_delete(char *name) {
	int index = hash(name);
	struct person *tmp = hash_table[index];
	struct person *prev = NULL;
	while(tmp != NULL  && strncmp(tmp->name, name, MAX_NAME) != 0) {
		prev = tmp;
		tmp = tmp ->next;
	}
	if(tmp == NULL) return NULL;
	if(prev == NULL) {
		// deleting the head
		hash_table[index] = tmp->next;
	} else {
		prev->next = tmp->next;
	}
	return tmp;
}

int main() {
	init_hashtable();
	struct person jacob = {.name = "Jacob", .age = 29};
	struct person john = {.name = "John", .age = 24};
	struct person kate = {.name = "Kate", .age = 26};
	struct person alex = {.name = "Alex", .age = 27};
	struct person sara = {.name = "Sara", .age = 28};
	struct person max = {.name = "Max", .age = 28};
	struct person albie = {.name = "Albie", .age = 28};
	struct person jane = {.name = "Jane", .age = 28};
	struct person cornell = {.name = "Cornell", .age = 28};

	hash_table_insert(&jacob);
	hash_table_insert(&john);
	hash_table_insert(&kate);
	hash_table_insert(&alex);
	hash_table_insert(&sara);
	hash_table_insert(&max);
	hash_table_insert(&albie);
	hash_table_insert(&jane);
	hash_table_insert(&cornell);


	struct person *tmp = hash_table_lookup("Sara");
	if(tmp != NULL) printf("Found\n");
	else printf("NOT FOUND\n");

	tmp = hash_table_lookup("George");
	if(tmp != NULL) printf("Found\n");
	else printf("NOT FOUND\n");


	tmp = hash_table_delete("Sara");





	print_table();
	return 0;
}
