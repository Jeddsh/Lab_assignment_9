#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    // create a next pointer (for linkedlist structure)
	struct RecordType* next;
};

// Fill out this structure
struct HashType
{
    // create a pointer to a RecordType
	struct RecordType* RecordHeads;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
	return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        struct RecordType *temp = *ppData;
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    // call the hash function to get the index
	int index = hash(record->id,tableSize);
    // if the RecordType at that index is NULL
	if(hashTable[index].RecordHeads == NULL){
        // set 'record' equal to the HashType pointer in the table at index
        hashTable[index].RecordHeads = record;
    }
    // else
	else{
        // traverse to the end of the linkedlist and add 'record' to the end of it
        struct RecordType *temp = hashTable[index].RecordHeads, *current;

        while(temp != NULL){
            current = temp;
            temp = temp->next;
		}
        current -> next = record;
	}
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    // for each entry in the table
	for(int i = 0; i < tableSize;i++){
        // print the contents in that index
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
		printf("Index  %d -> ", i);
		struct RecordType *temp = hashTable[i].RecordHeads;
        while(temp != NULL){
            printf("%d, %c, %d -> ",temp->id,temp->name,temp->order);
            temp = temp->next;
		}
		printf("NULL\n\n");
	}
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    struct HashType *hashTable; 
    // create a variable hashTableSize (11) and assign it a value
    int hashTableSize = 11;
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    hashTable = (struct HashType*) calloc(hashTableSize,sizeof(struct HashType));
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    struct RecordType *temp = pRecords;
    for(int i = 0; i < recordSz;i++){
        insertRecord(hashTable,&pRecords[i],hashTableSize);
    }
    // call the display records function
    displayRecordsInHash(hashTable,hashTableSize);
    // free all the allocated memory
    free(hashTable);

    free(pRecords);

    return 0;
}