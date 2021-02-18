#include<iostream>
#include <cstring>
const int CAPACITY=100;
/** 
 * BKDR hash function in clang
 * @param key char* 字符串
 * @return int hashed value, we will get a int value
 */
int bkdrHash( char *key )
{
    unsigned int seed = 131;//i can be 13, 131, 1313,131313 etc
    unsigned int hash = 0;
    while( *key != '\n' && *key != 0 )
    {
            hash = hash * seed + ( *key++ );
    }
    return ( hash & 0x7FFFFFFF );
}

struct Ht_item {
    char* key;
    char* value;
};
  /**
   *  struct hashNodeList
   *
   *  Nodes, used to wrap elements stored in the hash table.  A policy
   *  template parameter of class template _Hashtable controls whether
   *  nodes also store a hash code. In some cases (e.g. strings) this
   *  may be a performance win.
   */
  
  struct hashNodeList
  {
    Ht_item *item;
    hashNodeList* m_nxt;

    hashNodeList() noexcept : m_nxt() { }
    hashNodeList(hashNodeList* next) noexcept : m_nxt(next) { }
  };

// class hastTable{
//     private:
//     hashNodeList** buckets=nullptr;
//     size_t bucketCount=1;
//     hashNodeList beforeBegin;
//     size_t elementsCount=0;

//     public:
//     Ht_item* create_item(char* key, char* value){
//             // Creates a pointer to a new hash table item
//         Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
//         item->key = (char*) malloc (strlen(key) + 1);
//         item->value = (char*) malloc (strlen(value) + 1);
        
//         strcpy(item->key, key);
//         strcpy(item->value, value);
    
//         return item;
//     }
//      hastTable* create_table(int size) {
//     // Creates a new HashTable
//     hastTable* table = (hastTable*) malloc (sizeof(hastTable));
//     table->bucketCount = size;
//     table->elementsCount = 0;
//     table->buckets = (Ht_item**) calloc (table->bucketCount, sizeof(Ht_item*));
//     for (int i=0; i<table->bucketCount; i++)
//         table->buckets[i] = NULL;
 
//     return table;
// }
// };
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
    bool isFull(){
        return count==size;
    }
    HashTable(int number) noexcept:size(){

    }
};

Ht_item* create_item(char* key, char* value) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    item->value = (char*) malloc (strlen(value) + 1);
     
    strcpy(item->key, key);
    strcpy(item->value, value);
 
    return item;
}

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;
 
    return table;
}

void free_items(Ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    for(int i=0;i<table->size;i++){
        Ht_item* item = table->items[i];
        if(item!=nullptr)
            free(item);
    }
    free(table->items);
    free(table);
}
void handle_collision(HashTable* table,Ht_item* item);
void ht_insert(HashTable* table, char* key, char* value){
    auto item=create_item(key,value);
    int index=bkdrHash(key);
    auto currentItem=table->items[index];
    if(currentItem==nullptr){
        if(table->isFull()){
            std::cout<<"table is full"<<std::endl;
            free_items(item);
            return;
        }
        table->items[index]=item;
        table->count++;
    }else{
        if(std::strcmp(key,currentItem->key)==0){
            std::strcpy(currentItem->value,value);
        }else{
            //handle collsion
            handle_collision(table, item);
        }
    }
}

char* ht_search(HashTable*table,char* key){
    int index=bkdrHash(key);
    auto desItem=table->items[index];
    if(desItem!=nullptr){
        if(std::strcmp(desItem->key,key)==0)
            return desItem->value;
    }
    return nullptr;
}

void handle_collision(HashTable* table,Ht_item* item){

}
void print_table(HashTable* table){
    for(int i=0;i<table->size;i++){
        if(table->items[i]){
            std::cout<<"key:" <<table->items[i]->key <<" value:"<<table->items[i]->value<<std::endl;
        }
    }
}
void print_search(HashTable* table,char* key){
    auto ret=ht_search(table,key);
    ret!=nullptr? std::cout<<"key is:"<<key<<"  value:"<<ret<<std::endl
    : std::cout<<"can't find value"<<std::endl;
}
int main() {
    HashTable* ht = create_table(CAPACITY);
    ht_insert(ht, "1", "First address");
    ht_insert(ht, "2", "Second address");
    print_search(ht, "1");
    print_search(ht, "2");
    print_search(ht, "3");
    print_table(ht);
    free_table(ht);
    return 0;
}