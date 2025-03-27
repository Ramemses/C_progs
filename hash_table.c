#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status_t {DELETED = -100};
enum table_e {TABLE_SIZE = 10};


typedef struct node_t{
	char* key;
	int value;
	struct node_t* next;
} Node;


typedef struct hasht_t{
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

	hash_table->table = malloc(sizeof(Node*) * TABLE_SIZE);
	if (hash_table->table == NULL) return NULL;
	for (int i = 0; i < TABLE_SIZE; i++)
		hash_table->table[i] = NULL;

	return hash_table;
}

unsigned hash(char* key) //Хэш-функция
{
	unsigned hash_value = 0;
	while(*key){
		hash_value = (hash_value << 5) + *key++;
	}
	return hash_value % TABLE_SIZE;
}

void insert(HashTable* hash_table, char* key, int value)
{	
	unsigned index = hash(key);
	Node* current = hash_table->table[index];
	
	while (current != NULL){
		if (strcmp(current->key, key) == 0) return;
		current = current->next;
	}

	Node* node = create_node(key, value);
	if (node == NULL) return ;
	
	node->next = hash_table->table[index];
	hash_table->table[index] = node;
}


void show_table(HashTable* hash_table)
{
	for (int i = 0; i < TABLE_SIZE; i++){
		printf("-----------\n");
		printf("index = %d\n", i);
		Node* ceil = hash_table->table[i];
		while(ceil != NULL){
			printf("%s: %d, ", ceil->key, ceil->value);
			ceil = ceil->next;
		}
		printf("\n-----------\n");
	}
}


