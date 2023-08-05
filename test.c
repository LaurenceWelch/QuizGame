#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constants
const int MAXOPTIONS = 10;
const int MAXOPTIONLENGTH = 30;

//structs
struct Question {
    char question[100];
    char options[100];
};

struct Option {
    int isEmpty;
    char str[MAXOPTIONLENGTH];
};

//declaration
char getUserInput();
int verifyInput(char ch);
void printMessage(char str[], char border);
int printOptions(char str[]);
int len(char str[]);
int splitIntoOptions(char str[]);
void substr(char str[], int start, int end);

//globals
struct Option options[MAXOPTIONS];

int main() {
    char input;
    srand(time(NULL));
    struct Question q;
    strcpy(q.question, "Which command lists files in the current directory?");
    strcpy(q.options, "ls;cat;tree;grep;mkdir;touch;");

    int c = 0;
    for (c = 0; c < MAXOPTIONS; c++) options[c].isEmpty = 1;
    if (printOptions(q.options) != -1) printf("done");
    return 0;
    printMessage(q.question, '?');
    while (1) {
        printf(">>");
        input = getUserInput();
        verifyInput(input);
    }
    return 0;
}

char getUserInput() {
    char input[10]; 
    fgets(input, sizeof(input), stdin);
    char ch = input[0];
    return input[0];
}

int verifyInput(char ch) {
    if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd') {
        return 1;
    }
    printMessage("enter a, b, c, or d", '!');
    return -1;
}

//pretty style
void printMessage(char str[], char border) {
    int strlen = len(str);
    int length = strlen + 5; 
    char arr[length];
    int c;
    for (c = 0; c < length - 1; c++) {
        char ch = (c == 0 || c == length - 2) ? '*' : border;
        arr[c] = ch;        
    }
    arr[length - 1] = '\0';
    printf("%s\n", arr);
    printf("| "); 
    printf("%s", str);
    printf(" |\n");
    printf("%s\n", arr);
}

int len(char str[]) {
    int c = 0;
    while (str[c] != '\0') {
        c++; 
    }
    return c;
}

int printOptions(char str[]) {
    if (!splitIntoOptions(str)) return -1;
    int c = 0;
    while (options[c].isEmpty != 1 && c < MAXOPTIONS) {
        printf("%s\n", options[c].str);
        c++;
    }
    return 1;
}

int splitIntoOptions(char str[]) {
    int c = 0;
    int count = 0;
    int currStrIndex = 0;
    while (str[c] != '\0' && count <= MAXOPTIONS) {
        if (str[c] == ';') {
            options[count].str[currStrIndex] = '\0';
            currStrIndex = 0;
            options[count].isEmpty = 0;
            count++;
        }
        else {
            options[count].str[currStrIndex] = str[c];
            currStrIndex++;
            if (currStrIndex == MAXOPTIONLENGTH) {
                return -1;
            } 
        }
        c++;
    }
    return 1;
}


