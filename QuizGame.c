#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constants
#define MAXOPTIONS 10
#define MAXOPTIONLENGTH 30
#define MAXQUESTIONS 100

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
void freeQuestions();

//globals
struct Option options[MAXOPTIONS];
char rightAnswer;
struct Question* questions;
int score = 0;
int maxScore = 0;

int main() {
    char input;
    srand(time(NULL));

    //open file questions.txt
    FILE* fp;
    fp = fopen("questions.txt", "r");
    if (fp == NULL) {
        printf("put \'questions.txt\' in this directory, closing\n");
        return 0;
    }

    //get data from text
    questions = malloc(MAXQUESTIONS * sizeof(struct Question));
    int c = 0; 
    int index = 0;
    char s[100];
    while (fgets(s, 100, fp) && index < MAXQUESTIONS) {
        s[strcspn(s, "\n")] = '\0';
        if (c % 2 == 0) {
            strcpy(questions[index].question, s);
        }
        else {
            strcpy(questions[index].options, s);
            index++;
        }
        c++;
    }
    fclose(fp);
    maxScore = index * 10;

    //main loop
    for (int c = 0; c < index; c++) {
        //setup options array
        for (int c = 0; c < MAXOPTIONS; c++) {
            options[c].isEmpty = 1;
        }
        printMessage(questions[c].question, '-');
        printf("(\'q\' to quit)\n");
        printOptions(questions[c].options);
        while (1) {
            printf(">>");
            input = getUserInput();
            if (input == 'q') {
                freeQuestions();
                return 0;
            }
            if (verifyInput(input) == 1) break;
        }
        if (input == rightAnswer) {
            printMessage("Good Job!", '-');
            printf("(press enter)");
            fgets(s, 100, stdin);
            s[strcspn(s, "\n")] = '\0';
            score += 10;
        }
    }
    
    //free questions array
    printf("You score %i points out of %i!\n", score, maxScore);
    freeQuestions();
    return 0;
}

void freeQuestions() {
    free(questions);
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
    printMessage("enter a, b, c, d, or q (for quit)", '-');
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
    if (splitIntoOptions(str) == -1) return -1;
    int out[4];
    //subtract 1 as we only want the wrong answers
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
