#include <stdio.h>
#include <string.h>

//functions
void printZone(char name[]);
void lvl1();
void attack();
void parseStr(char phrase[]);
int getWord(char word[], char phrase[]);
void look(char str[]);
void help();
void addItem(char str[]);
int indexOf(char str[], char c);
int len(char str[]);
void setHint(char str[]);

struct Person {
    int lvl;
    char name[30];
};

struct Item {
    char name[30];
};

struct Person mc;
struct Item items[30];
struct Person people[30];
char desc[100];
char hint[100];

//strings
char lvl1intro[] = "An impressive but somewhat childish voice booms through some kind of amplification: \"Welcome, welcome, welcome!\"";

int main() {
    char name[30];
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
    printf("You look around...\n");
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
    setHint("Try typing 'look' (without the quotes) and press enter!");
    printZone("A Dark Arena");
    printf("%s", lvl1intro);
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

void setHint(char str[]) {
    int count = 0;
    while (str[count] != '\0') {
        hint[count] = str[count];
        count++;
    }
}

void printZone(char str[]) {
    int length = len(str);
    int count;
    char first[30];
    char last[30];
    first[count] = '*';
    for (count = 1; count < length + 3; count++) {
        first[count] = '-'; 
    }
    first[count] = '*';
    first[count + 1] = '\n';
    first[count + 2] = '|';
    first[count + 3] = ' ';
    first[count + 4] = '\0';
    //last
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
