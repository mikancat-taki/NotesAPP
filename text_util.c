#include <ctype.h>
#include <string.h>


// 小文字化 + 先頭/末尾空白トリムの簡易関数
void normalize_text(char *s){
if(!s) return;
// trim left
char *start = s;
while(*start && isspace((unsigned char)*start)) start++;
// trim right
char *end = start + strlen(start) - 1;
while(end >= start && isspace((unsigned char)*end)) { *end = '\0'; end--; }
// move to head
if(start != s) memmove(s, start, strlen(start) + 1);
// lowercase
for(char *p = s; *p; ++p) *p = tolower((unsigned char)*p);
}
