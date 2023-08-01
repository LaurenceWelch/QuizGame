#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//functions
void printZone(char name[]);
void lvl1();
void attack();
void parseStr(char phrase[]);
int getWord(char word[], char phrase[]);
void look(char str[]);
void take(char str[]);
void help();
void addItem(char str[]);
int indexOf(char str[], char c);
int len(char str[]);
void printDesc(int lvl);

struct Person {
    int lvl;
    char name[30];
};

struct Item {
    int id;
    char name[30];
};

//globals
struct Person mc;
struct Item items[30];
struct Item stageItems[30];
struct Person people[30];
char desc[100];
char hint[100];

int main() {
    char name[30];
    printZone("May's Trial - Laurence Welch");
    printf("What is your first name?: ");
    fgets(name, sizeof(name), stdin);
    mc.lvl = 1;
    strcpy(mc.name, name);
    printf("Hello, %s", name);
    printf("Your journey begins here...\n");
    lvl1();
}

void parseStr(char phrase[]) {
    char word[30];
    getWord(word, phrase);
    if (strcmp(word, "look") == 0) look(phrase);
    else if (strcmp(word, "help") == 0) help();
    else printf("What now?");
}

void look(char string[]) {
    int count = 0;
    printf("looking around, you see a:\n");
    while (items[count].id != -1) {
        printf("%s\n", items[count].name);
        count++;
    } 
}

void take(char str[]) {
    
}

void help() {
    printf("%s\n", hint);
}

int getWord(char word[], char phrase[]) {
    int index = indexOf(phrase, ' ');
    if (index == -1) {
        strcpy(word, phrase);
        word[strcspn(word, "\n")] = '\0';
        return 1; 
    }
    int count;
    for (count = 0; count < index; count++) {
        word[count] = phrase[count];
    }
    word[count] = '\0';
    return 1;
}

void attack() {
    printf("You hit the training dummy for %i damage!", mc.lvl);
}

void lvl1() {
    //strcpy(hint, "Try typing 'look' (without the quotes) and press enter!");
    printZone("A Dark Arena");
    printDesc(1);
    printf("tip: type 'help' (without the quotes) and press enter\n");
    items[0].id = 1;
    strcpy(items[0].name, "key");
    items[1].id = -1;
    while(1) {
        char str[30];
        printf(">>");
        fgets(str, sizeof(str), stdin);
        parseStr(str);
    }
}    

void addItem(char str[]) {
    
}

int indexOf(char str[], char c) {
    int count = 0;
    while (str[count] != '\0') {
        if (str[count] == c) return count;
        count++;
    }
    return -1;
}

int len(char str[]) {
    return strcspn(str, "\0"); 
}

void printZone(char str[]) {
    int length = len(str);
    int count = 0;
    char first[100];
    char last[100];
    first[count] = '*';
    for (count = 1; count < length + 3; count++) {
        first[count] = '-'; 
    }
    first[count] = '*';
    first[count + 1] = '\n';
    first[count + 2] = '|';
    first[count + 3] = ' ';
    first[count + 4] = '\0';
    last[0] = ' ';
    last[1] = '|';
    last[2] = '\n';
    last[3] = '*';
    for (count = 4; count < length + 6; count++) {
        last[count] = '-';
    }
    last[count] = '*';
    last[count + 1] = '\0'; 
    printf("%s", first);
    printf("%s", str);
    printf("%s\n", last);
}

void printDesc(int lvl) {
    if (lvl == 1) {
        printf("This isn't a dream...?\nA strange sense of reality fades in as you awaken. You're in a cathedral of epic proportions. As you gaze about, a brash voice breaks the silence:\n\"Welcome, welcome!!!\"\n\"Today is... NOT AGAIN!!!\"\nThe voice breaks off for a second then returns.\n\"Just a second! Don't move...\"\nThe voice cuts off again and a stark silence sits in the air.\n");
    }
}
