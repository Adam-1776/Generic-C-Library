#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "scanner.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "bst.h"
#include "heap.h"
#include "queue.h"
#include "stack.h"
bool integer=false;
bool real=false;
bool string=false;
bool inc=false;
bool dec=false;
void test(){
if(integer==true){printf("integer - true\n");} else printf("integer - false\n");
if(real==true){printf("real - true\n");} else printf("real - false\n");
if(string==true){printf("string - true\n");} else printf("string - false\n");
if(inc==true){printf("inc - true\n");} else printf("inc - false\n");
if(dec==true){printf("dec - true\n");} else printf("dec - false\n");}
int compSTRING(void *v,void *w){return strcmp(getSTRING(v),getSTRING(w));}
int rcompSTRING(void *v,void *w){return strcmp(getSTRING(w),getSTRING(v));}
int rcompREAL(void *v,void *w){
if(getREAL(w)<getREAL(v)) return -1;
else return 1;}
int compREAL(void *v,void *w){
if(getREAL(w)<getREAL(v)) return 1;
else return -1;}
int rcompINTEGER(void *a,void *b) { return getINTEGER(b) - getINTEGER(a); }
static void skipWhiteSpaces(FILE *fp){
int ch;
while ((ch = fgetc(fp)) != EOF && isspace(ch))continue;
if (ch != EOF) ungetc(ch,fp);}
int stringPendind(FILE *fp){
int ch,result = 0;
skipWhiteSpaces(fp);
ch = fgetc(fp); //printf("character : %c\n",ch);
if (ch == EOF) return -3;
if (ch != '\"' && ch!='"') {ungetc(ch,fp); //printf("returning -1\n");
return -1;}
if (ch == '\"' ||ch=='"') result = 1;
else {result=-1;}
ungetc(ch,fp);
return result;}
bool stahp=true;
int readInts(FILE *fp){
int x,result;
result = fscanf(fp,"%d",&x);
if(result == EOF){ stahp=false;
return 0;}
if (result == 0){
fprintf(stderr,"SCAN ERROR: attempt to read an integer failed\n");
fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
exit(1);} return x;}
double readReals(FILE *fp){
int result; double x;
result = fscanf(fp," %lf",&x);
if(result == EOF){stahp=false; return 0.0;}
if (result == 0){
fprintf(stderr,"SCAN ERROR: attempt to read a real number failed\n");
fprintf(stderr,"offending character was <%c>\n",fgetc(fp)); exit(2);}
return x;}

int main(int argc,char **argv){
if(argc==1){printf("No arguments given.\n"); return 0;}
int argIndex=1;
while (argIndex < argc && argv[argIndex][0] == '-' && argv[argIndex][2] == '\0'){
switch (argv[argIndex][1]){
case 'v':
printf("Program written by Adam Rizk.\nThis program is able to sort in O(nlogn) time because");
printf(" the heapsort algorithm\ntraverses each level of the tree, which takes log(n) time, and does this n times.\n"); return 0;
break;
case 'i':
if(real==false && string==false) integer=true;
else{printf("Illegal command.\n"); return 0;}
++argIndex; break;
case 'r':
if(integer==false && string==false) real=true;
else{printf("Illegal command.\n"); return 0;}
++argIndex; break;
case 's':
if(integer==false && real==false) string=true;
else{printf("Illegal command.\n"); return 0;}
++argIndex; break;
case 'I':
if(dec==false) inc=true;
else{printf("Illegal command.\n"); return 0;}
++argIndex; break;
case 'D':
if(inc==false) dec=true;
else{printf("Illegal command.\n"); return 0;};
++argIndex; break;
default :
++argIndex; break;}}

if(integer==false && real==false && string==false){integer=true;}
if(inc==false && dec==false){inc=true;}

FILE *fp; int ysod=0; int i=0; double kdf=0.0; char *drrcs=0;
if((fp=fopen(argv[argc-1], "r"))==NULL){printf("Error opening %s\n",argv[argc-1]); return 0;}

if(integer==true&&inc==true){HEAP *p=newHEAP(displayINTEGER,compareINTEGER,freeINTEGER);
while(1)
{argIndex=readInts(fp); if(stahp==false){break;}
insertHEAP(p,newINTEGER(argIndex));}
buildHEAP(p); INTEGER *m; ysod=sizeHEAP(p);
for(i=0;i<ysod;++i){
m=extractHEAP(p);
displayINTEGER(m,stdout);
if(i==ysod-1){printf("\n");} else{printf(" ");}}}

else if(integer==true&&dec==true){HEAP *p=newHEAP(displayINTEGER,rcompINTEGER,freeINTEGER);
while(1)
{argIndex=readInts(fp); if(stahp==false){break;}
insertHEAP(p,newINTEGER(argIndex));}
buildHEAP(p); INTEGER *m; ysod=sizeHEAP(p);
for(i=0;i<ysod;++i){
m=extractHEAP(p);
displayINTEGER(m,stdout);
if(i==ysod-1){printf("\n");} else{printf(" ");}}}

else if(real==true&&inc==true){HEAP *p=newHEAP(displayREAL,compREAL,freeREAL);
while(1){kdf=readReals(fp);
if(stahp==false){break;} insertHEAP(p,newREAL(kdf));}
buildHEAP(p); REAL *m; ysod=sizeHEAP(p);
for(i=0;i<ysod;++i){
m=extractHEAP(p);
displayREAL(m,stdout);
if(i==ysod-1){printf("\n");} else{printf(" ");}}}

else if(real==true&&dec==true){HEAP *p=newHEAP(displayREAL,rcompREAL,freeREAL);
while(1){kdf=readReals(fp);
if(stahp==false){break;} insertHEAP(p,newREAL(kdf));}
buildHEAP(p); REAL *m; ysod=sizeHEAP(p);
for(i=0;i<ysod;++i){
m=extractHEAP(p);
displayREAL(m,stdout);
if(i==ysod-1){printf("\n");} else{printf(" ");}}}

else if(string==true&&inc==true){HEAP *p=newHEAP(displaySTRING,compSTRING,freeSTRING);
int ksld=0;
while((ksld=stringPendind(fp))){
if(ksld==-3){break;}
if(ksld==1) drrcs=readString(fp);
else drrcs=readToken(fp);
insertHEAP(p,newSTRING(drrcs));}
buildHEAP(p); STRING *m; ysod=sizeHEAP(p);
for(i=0;i<ysod;++i){
m=extractHEAP(p);
displaySTRING(m,stdout);
if(i==ysod-1){printf("\n");} else{printf(" ");}}}

else if(string==true&&dec==true){HEAP *p=newHEAP(displaySTRING,rcompSTRING,freeSTRING);
int ksld=0;
while((ksld=stringPendind(fp))){
if(ksld==-3){break;}
if(ksld==1) drrcs=readString(fp);
else drrcs=readToken(fp);
insertHEAP(p,newSTRING(drrcs));}
buildHEAP(p); STRING *m; ysod=sizeHEAP(p);
for(i=0;i<ysod;++i){
m=extractHEAP(p);
displaySTRING(m,stdout);
if(i==ysod-1){printf("\n");} else{printf(" ");}}}

else{printf("There was an error.\n");}
return 0;
}


