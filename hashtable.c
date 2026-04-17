/*
* Open Addressing Method 
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
	char name[MAX_NAME];
	int age;
} person;

person *hash_table[TABLE_SIZE];

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
		}else if(hash_table[i] == DELETED_NODE){
			printf("\t%i\t---<deleted>\n", i);
		}else {
			printf("\t%i\t%s\n", i, hash_table[i]->name);
		}
	}
}

bool hash_table_insert(person *p) {
	if (p == NULL)
		return false;
	int index = hash(p->name);
	for(int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if(hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
			hash_table[try] = p;
			return true;
		}
	}

	return false;
}

person *hash_table_lookup(char *name) {
	int index = hash(name);
	for(int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if(hash_table[try] == NULL) return NULL; // not here
		if(hash_table[try] == DELETED_NODE) continue;
		if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
			return hash_table[try];
		}
	}
	return NULL;
}

person *hash_table_delete(char *name) {
	int index = hash(name);
	for(int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL) return NULL;
		if (hash_table[try] == DELETED_NODE) continue;
		if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
			person *tmp = hash_table[try];
			hash_table[try] = DELETED_NODE;
			return tmp;
		}
	}
	return NULL;
}

int main() {
	init_hashtable();
	person jacob = {.name = "Jacob", .age = 29};
	person john = {.name = "John", .age = 24};
	person kate = {.name = "Kate", .age = 26};
	person alex = {.name = "Alex", .age = 27};
	person sara = {.name = "Sara", .age = 28};
	person max = {.name = "Max", .age = 28};
	person albie = {.name = "Albie", .age = 28};
	person cornell = {.name = "Cornell", .age = 28};

	hash_table_insert(&jacob);
	hash_table_insert(&john);
	hash_table_insert(&kate);
	hash_table_insert(&alex);
	hash_table_insert(&sara);
	hash_table_insert(&max);
	hash_table_insert(&albie);
	hash_table_insert(&cornell);


	person *tmp = hash_table_lookup("Sara");
	if(tmp != NULL) printf("Found\n");
	else printf("NOT FOUND\n");

	tmp = hash_table_lookup("George");
	if(tmp != NULL) printf("Found\n");
	else printf("NOT FOUND\n");


	tmp = hash_table_delete("Sara");





	print_table();
	return 0;
}
