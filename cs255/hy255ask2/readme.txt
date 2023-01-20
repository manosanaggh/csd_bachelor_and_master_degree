Anagnostakis Emmanouil

Sto arxeio mystring_ars.c oi synarthseis pou epistrefoun pinaka epistrefoun char*, giati den uparxei allos tropos na epistrafei pinakas apo synarthsh.

Apanthseis erwthsewn:

1) I ms_copy mporei na kalesei tin assert kai na elenksei an to megethos tou src einai mikrotero i iso me to megethos tou dest(assert(sizeof(src)<=sizeof(dest));).
To idio isxuei kai gia tis ms_ncopy, ms_concat, ms_nconcat.

2) Oi ms_ncopy,ms_nconcat kai ms_ncompare mporoun na kalesoun assert(n>=0); kai na elenksoun ontws oti to n den einai arnhtiko.
