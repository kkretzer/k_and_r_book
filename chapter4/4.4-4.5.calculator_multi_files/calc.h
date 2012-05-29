#define NUMBER  '0' /* signal that a number was found */
#define ASSIGNVAR ':' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void printtop();
void duptop();
void swaptop2();
int getch(void);
void ungetch(int);
