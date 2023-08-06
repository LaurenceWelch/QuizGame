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
int lenOptions();
int splitIntoOptions(char str[]);
void substr(char str[], int start, int end);
void setRandomArray(int out[4], int numOptions);
void setRightAnswer(int when);

//globals
struct Option options[MAXOPTIONS];
char rightAnswer;

int main() {
    char input;
    srand(time(NULL));
    struct Question q;
    strcpy(q.question, "Which command lists files in the current directory?");
    strcpy(q.options, "ls;cat;tree;grep;mkdir;touch;");
    //initialize array
    for (int c = 0; c < MAXOPTIONS; c++) options[c].isEmpty = 1;
    //start the quiz
    printMessage(q.question, '-');
    if (printOptions(q.options) == -1) printf("error");
    while (1) {
        printf(">>");
        input = getUserInput();
        if (verifyInput(input)) break;
    }
    if (input == rightAnswer) printMessage("Good Job!", '-');
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
    printMessage("enter a, b, c, or d", '-');
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
    int out[4];
    //subtract 1 as 1 option is the answer
    int length = lenOptions() - 1;
    setRandomArray(out, length);
    char abcd[] = {'a', 'b', 'c', 'd'};
    int c;
    for (c = 0; c < 4; c++) {
        printf("%c: %s\n", abcd[c], options[out[c]].str);
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
    if (count < 4) {
        printf("must have atleast 4 options!");
        return -1;
    }
    return 1;
}

int lenOptions() {
    int c = 0;
    while (options[c].isEmpty != 1) c++;
    return c;
}

//index array representing a, b, c, and d
void setRandomArray(int outArr[4], int wrongLen) {
    int wrong[wrongLen];
    for (int c; c < wrongLen; c++) wrong[c] = c + 1;
    int when = rand() % 4;
    setRightAnswer(when);
    //pick 4, make sure right answer is included 
    for (int c = 0; c < 4; c++) {
        if (c == when) outArr[c] = 0;
        else {
            int rng = rand() % wrongLen;
            outArr[c] = wrong[rng];
            if (rng != wrongLen - 1) {
                int temp = wrong[rng];
                wrong[rng] = wrong[wrongLen - 1];
                wrong[wrongLen -1] = temp;
            }
            wrongLen--;
        }
    }
}

void setRightAnswer(int when) {
    if (when == 0) rightAnswer = 'a';
    else if (when == 1) rightAnswer = 'b';
    else if (when == 2) rightAnswer = 'c';
    else rightAnswer = 'd'; 
} 
