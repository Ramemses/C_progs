#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors {ERROR_KEY = -1};
enum status_t {DELETED = -100};
enum table_e {TABLE_SIZE = 10};

typedef struct node_t{
	char* key;
	int value;
	struct node_t* next;
} Node;

typedef struct hasht_t{
	unsigned size;
	unsigned old_size;
	unsigned elems;
	double resize_border;
	Node** table;
} HashTable;


Node* create_node(char* key, int value) // Создаем ячейку таблицы
{
	Node* node = malloc(sizeof(Node));
	if (node == NULL) return NULL;
	
	node->value = value;
	node->next = NULL;
	node->key = strdup(key);
	
	if (node->key == NULL) return NULL;

	return node;
}


HashTable* create_table() //Создаем хэш-таблицу
{
	HashTable* hash_table= calloc(1, sizeof(HashTable));
	if (hash_table == NULL) return NULL;

	hash_table->size = TABLE_SIZE;
	hash_table->old_size = TABLE_SIZE;
	hash_table->resize_border = 0.75;

	hash_table->table = malloc(sizeof(Node*) * hash_table->size);
	if (hash_table->table == NULL) return NULL;
	for (int i = 0; i < TABLE_SIZE; i++)
		hash_table->table[i] = NULL;

	return hash_table;
}


unsigned hash(char* key, unsigned size) //Хэш-функция
{
	unsigned hash_value = 0;
	while(*key){
		hash_value = (hash_value << 3) + *key++;
	}
	return hash_value % size;
}


void __insert__(Node** table, unsigned size, char* key, int value)
{
	
	unsigned index = hash(key, size);
	Node* current = table[index];
	
	while (current != NULL){
		if (strcmp(current->key, key) == 0) return;
		current = current->next;
	}

	Node* node = create_node(key, value);
	if (node == NULL) return ;
	
	node->next = table[index];
	table[index] = node;

}


void resize_table(HashTable* hash_table)
{
	Node** table = calloc(hash_table->size * 2, sizeof(Node*));
	if (table == NULL) return;

	hash_table->old_size = hash_table->size;
	hash_table->size *= 2;	
	
	for (int i = 0; i < hash_table->old_size; i++){
		Node* ceil = hash_table->table[i];
		while(ceil != NULL){
			unsigned new_index = hash(ceil->key, hash_table->size);
			__insert__(table, hash_table->size, ceil->key, ceil->value);
			ceil = ceil->next;
		}
	}
	free(hash_table->table);
	hash_table->table = table;
}	


void insert(HashTable* hash_table, char* key, int value)
{
	if (hash_table->size * hash_table->resize_border <= hash_table->elems) resize_table(hash_table);
	__insert__(hash_table->table, hash_table->size,  key, value);
	hash_table->elems += 1;
}


Node* __get__(HashTable* hash_table, char* key)
{
	unsigned index = hash(key, hash_table->size);
	Node* node = hash_table->table[index];

	while(node != NULL){
		if (strcmp(node->key, key) == 0) return node;		
		node = node->next;
	}
	return NULL;
}


int get_value(HashTable* hash_table, char* key)
{
	Node* node = __get__(hash_table, key);	
	if (node == NULL) return ERROR_KEY;

	return node->value;
}


int delete(HashTable* hash_table, char* key)
{
	Node* node = __get__(hash_table, key);
	if (node == NULL) return ERROR_KEY;

	int value = node->value;
	Node* tmp = node;
	node = node->next;
	free(tmp);

	return value;
}


void print_table(HashTable* hash_table)
{
	printf("{ ");
	for (int i = 0; i < hash_table->size; i++){
		Node* ceil = hash_table->table[i];
		while(ceil != NULL){
			printf("%s: %d, ", ceil->key, ceil->value);	
			ceil = ceil->next;
		}
	}
	printf(" }\n");

}


void show_table(HashTable* hash_table)
{
	for (int i = 0; i < hash_table->size; i++){
		printf("---------\n");
		printf("index = %d\n", i);
		Node* ceil = hash_table->table[i];
		while(ceil != NULL){
			printf("%s: %d, ", ceil->key, ceil->value);
			ceil = ceil->next;
		}
		printf("\n-----------\n");
	}
}


