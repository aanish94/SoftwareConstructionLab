#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int helper(char a)
{
  if (isalpha(a))
  {
    if (a < 'N' || (a >='a' && a < 'n'))
    {
      return  a + 13;
    }
    return a - 13;
  }
  return a;
}
int charlentest(char * cur,char * cmp)
{
  int temp1 = 0;
  int temp2 = 0;
  if (cur)  while (cur[temp1] != EOF) temp1++;
  if (cmp) while (cmp[temp2] != EOF) temp2++;
  if (temp1 > temp2) return temp1;
  return temp2;
}

int rot13cmp(const void * a, const void * b)
{
	char *s1 = *(char**) a;
	char *s2 = *(char**) b;

	int s1index = 0;
	int s2index = 0;
	int len = charlentest(s1,s2);
	int j;
	for (j = 0; j < len; j++)
	  {
	    s1index = helper(s1[j]);
	    s2index = helper(s2[j]);
	    
	    if (s1index > s2index) return 1;
	    if (s1index < s2index) return -1;
	  }
	return 0;
}

int main(void)
{
  int buffersize = 200480;
  char * p = (char*) malloc(sizeof(char) * buffersize);
  if (!p) exit(1);
  int c;
  int count = 0;
  char **pToChar = (char**) malloc(sizeof(char*) * buffersize);
  if (!pToChar) exit(1);
  pToChar[0] = p;
  int numWord = 0;
  //READ IN CHARACTER BY CHARACTER FROM FILE  
  do 
    {
        c = getchar(); //This reads next char in
	if (c == EOF) //Denotes (E)nd (O)f (F)ile
	{
	  p[count++] = '\n'; //Add newline if not present
	  numWord++;
	  break; //There are no more characters to read
	}
	//REALLOCATE MEMORY AS NEEDED
	if (count >= buffersize) 
	{
	  p = (char*) realloc(p,buffersize *2);
	  buffersize *= 2; //Double buffer size 
	  if (!p) { exit(1); } //Memory reallocation failed
	}
	//Cast c to a (char) an store in p 
	p[count++] = (char) c;
	if (p[count-1] == '\n') //Newline is the delimiter
	{
	  //REALLOCATE MEMORY AS NEEDED
	  if (numWord >= buffersize)
	  {
	    pToChar = (char **) realloc(pToChar,buffersize*2);
	    buffersize *=2; //Double buffer size
	    if (!p) exit(1); //Memory reallocation failed
	  }
	  //Store the "words" between newlines in pToChar
	  pToChar[++numWord] = p + count;
	}
}
while (c!=EOF);

qsort(pToChar, numWord, sizeof(char*),rot13cmp);
int l;
for (l = 0; l < numWord; l++)
   {
     int ii = 0;
     while ( ii  < buffersize)
       {
	 char current = pToChar[l][ii];
	 int error = putc(current,stdout);
	 if (error == EOF) exit(1);
	 if (current == '\n') { break;}
	 ii++;
       }
   } 
free(pToChar);
free(p);
return 0;
}



