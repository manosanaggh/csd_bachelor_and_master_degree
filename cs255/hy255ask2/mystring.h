/*Anagnostakis Emmanouil
Askisi 2
mystring.h*/

#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <stddef.h>
#include <assert.h>
/*Takes a string as an argument(str) and returns its length
(total characters contained in it).
Does not read anything from stdin and print anything to stdout.
Checks if str is NULL.*/
size_t ms_length(const char* str);

/*Takes two strings as arguments(dest and src), concatenates
the second(src) to the end of the first(dest) and returns
the result of the concatenation.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char* ms_concat(char* dest, const char* src);

/*Takes two strings(dest and src) and a number as arguments(n),
concatenates n number of characters of the second(src)
to the end of the first(dest) and returns the result of
the concatenation.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char* ms_nconcat(char* dest, const char* src, size_t n);

/*Takes two strings as arguments(str1 and str2), compares them
by the value of their characters and returns 1
if the first(str1) is greater than the second(str2), -1 if the
first(str1) is less than the second(str2) and 0 if they are equal.
Does not read anything from stdin and print anything to stdout.
Checks if str1 or str2 is NULL.*/
int ms_compare(const char* str1, const char* str2);

/*Takes two strings(str1 and str2) and a number(n) as arguments, compares the
first n number of characters in the strings by their value and returns 1
if the first(str1) is greater than the second(str2), -1 if the
first(str1) is less than the second(str2) and 0 if they are equal.
Does not read anything from stdin and print anything to stdout.
Checks if str1 or str2 is NULL.*/
int ms_ncompare(const char* str1, const char* str2,size_t n);

/*Takes two strings as arguments(dest and src),
copies the second(src) to the first(dest)
and returns the new copy.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char* ms_copy(char* dest,const char* src);

/*Takes two strings(dest and src) and a number(n) as
arguments, copies the first n number of
characters of the second string(src) to the first(dest)
and returns the new copy.
Does not read anything from stdin and print anything to stdout.
Checks if src is NULL.*/
char* ms_ncopy(char* dest,const char* src,size_t n);

/*Takes two strings(haystack and needle) as arguments and searches
the first occurence of the second(needle) contained in the first(haystack).
Returns the occurence if found otherwise NULL.
Does not read anything from stdin and print anything to stdout.
Checks if haystack or needle is NULL.*/
char* ms_search(const char* haystack,const char* needle);
#endif
