#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct LL1 LL1;
typedef struct Rules Rules;
typedef struct Stack Stack;

static const int NUMBER_OF_RULES = 40;
static const int WORD = 100;

struct LL1 {
    char nonTerminal[3];
    char terminal;
    char result[5];
    struct LL1 * next;
};

struct Rules{
    char name[3];
    char production[10][10];
    char follow[10];
    char first[10];
    int firstCounter;
    int followCounter;
    int count;
    int firstCalculator;
    int followCalculator;
    struct Rules * next;
};

struct Stack{
    char value[3];
    struct Stack * next;
};

void insertDefaultValues(struct Rules ** p, struct Rules * temp){
    if (*p == NULL) {
        temp->next = NULL;
        temp->firstCounter = 0;
        temp->followCounter = 0;
        temp->firstCalculator = 0;
        temp->followCalculator = 0;
        temp->first[0] = '\0';
        temp->follow[0] = '\0';
        *p = temp;
    } else {
        struct Rules * x = (*p);
        while(x->next != NULL){
            x = x->next;
        }
        x->next = temp;
        temp->firstCounter = 0;
        temp->firstCalculator = 0;
        temp->followCalculator =0;
        temp->followCounter = 0;
        temp->first[0] = '\0';
        temp->follow[0] = '\0';
        temp->next = NULL;
    }
}
char * substring(const char * string, int begin, int num){
    char * res;
    int j = 0;
    res = malloc((num)*sizeof(char));
    for (int i = begin; i < begin+num; ++i) {
        res[j] = string[i];
        j++;
    }
    res[num] = '\0';
    return res;
}

void inputGrammar(struct Rules ** p){
    char * allRules = malloc(NUMBER_OF_RULES * sizeof(char));
    char * token;
    struct Rules * temp;
    int k = 0;
    while(1) {
        scanf("%s",allRules);

        // is used to finished rules input
        if (strcmp(allRules, ".") == 0){
            return;
        }

        temp = malloc(sizeof(Rules));
        temp->name[0] = allRules[0];
        temp->name[1] = '\0';

        char *help = substring(allRules,3,strlen(allRules) - 3);
        token = strtok(help,"|");

        while (token != NULL) {
            strcpy(temp->production[k],token);
            int len = strlen(temp->production[k]);
            temp->production[k][len] = '\0';
            ++k;
            token = strtok(NULL,"|");
        }
        temp->count = k;
        k=0;

        if (*p == NULL) {
            temp->next = NULL;
            temp->firstCalculator = 0;
            temp->followCalculator = 0;
            *p = temp;
        } else {
            Rules * x = (*p);
            while(x->next != NULL){
                x =x->next;
            }
            x->next = temp;
            temp->firstCalculator = 0;
            temp->followCalculator = 0;
            temp->next = NULL;
        }
    }
}
