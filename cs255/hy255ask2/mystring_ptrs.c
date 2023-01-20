#include "mystring.h"

/*Takes a string as an argument(str) and returns its length
(total characters contained in it).
Does not read anything from stdin and print anything to stdout.
Checks if str is NULL.*/
size_t ms_length(const char* str){
    size_t length = 0;
    assert(str != NULL);
    while(*(str+length) != '\0'){
       length++;
    }
    return length;
}

/*Takes two strings as arguments(dest and src),
copies the second(src) to the first(dest)
and returns the new copy.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char* ms_copy(char* dest,const char* src){
   int i;
   assert(src!=NULL);
   for(i = 0; *(src+i) != '\0'; i++){
      *(dest+i) = *(src+i);
   }
   *(dest+i)='\0';
   return dest;
}

/*Takes two strings(dest and src) and a number(n) as
arguments, copies the first n number of
characters of the second string(src) to the first(dest)
and returns the new copy.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char* ms_ncopy(char* dest,const char* src,size_t n){
   int i;
   assert(src!=NULL);
   for(i = 0; i < n; i++){
      *(dest+i) = *(src+i);
   }
   *(dest+i)='\0';
   return dest;
}

/*Takes two strings as arguments(str1 and str2), compares them
by the value of their characters and returns 1
if the first(str1) is greater than the second(str2), -1 if the
first(str1) is less than the second(str2) and 0 if they are equal.
Does not read anything from stdin and print anything to stdout.
Checks if str1 or str2 is NULL.*/
int ms_compare(const char* str1,const char* str2){
   int i,count1 = 0,count2 = 0;
   assert(str1!=NULL && str2!=NULL);
   for(i = 0; *(str1+i) != '\0' && *(str2+i) != '\0'; i++){
      if(*(str1+i) > *(str2+i)){
         count1++;
      }
      else if(*(str1+i) < *(str2+i)){
         count2++;
      }
   }
   if(count1 > count2){
      return 1;
   }
   else if(count1 < count2){
      return -1;
   }
   else{
      return 0;
   }
}

/*Takes two strings(str1 and str2) and a number(n) as arguments, compares the
first n number of characters in the strings by their value and returns 1
if the first(str1) is greater than the second(str2), -1 if the
first(str1) is less than the second(str2) and 0 if they are equal.
Does not read anything from stdin and print anything to stdout.
Checks if str1 or str2 is NULL.*/
int ms_ncompare(const char* str1,const char* str2,size_t n){
   int i,count1 = 0,count2 = 0;
   assert(str1!=NULL && str2!=NULL);
   for(i = 0; *(str1+i) != '\0' && *(str2+i) != '\0' && i < n; i++){
      if(*(str1+i) > *(str2+i)){
         count1++;
      }
      else if(*(str1+i) < *(str2+i)){
         count2++;
      }
   }
   if(count1 > count2){
      return 1;
   }
   else if(count1 < count2){
      return -1;
   }
   else{
      return 0;
   }
}

/*Takes two strings(haystack and needle) as arguments and searches
the first occurence of the second(needle) contained in the first(haystack).
Returns the occurence if found otherwise NULL.
Does not read anything from stdin and print anything to stdout.
Checks if haystack or needle is NULL.*/
char *ms_search(const char *haystack,const char *needle){
   int i,j = 0;
   assert(haystack != NULL && needle != NULL);
   for(i = 0; *(haystack+i) != '\0' && *(needle+j) != '\0'; i++){
      if(*(haystack+i) == *(needle+j)){
         j++;
      }
      if(j == ms_length(needle)){
         return (char*)needle;
      }
   }
   return NULL;
}

/*Takes two strings as arguments(dest and src), concatenates
the second(src) to the end of the first(dest) and returns
the result of the concatenation.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char *ms_concat(char *dest, const char *src){
    int i, j,srcLength = 0;
    assert(src != NULL);
    i = ms_length(dest);
    srcLength = ms_length(src);
    for(j = 0; j < srcLength; j++){
        *(dest+i) = *(src+j);
        i++;
    }
    *(dest+i) = '\0';
    return dest;
}

/*Takes two strings(dest and src) and a number as arguments(n),
concatenates n number of characters of the second(src)
to the end of the first(dest) and returns the result of
the concatenation.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char *ms_nconcat(char *dest, const char *src,size_t n){
    int i, j;
    assert(src != NULL);
    i = ms_length(dest);
    for(j = 0; j < n; j++)
    {
        *(dest+i) = *(src+j);
        i++;
    }
    *(dest+i) = '\0';
    return dest;
}
