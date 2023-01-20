Anagnostakis Emmanouil
csd3618

Exoume mia semaphore mutex gia ton elegxo tou critical section sto opoio exei kathe fora access mono o chef i enas ek twn mageirwn. 
Xrisimopioume 4 threads, to chef_thread pou elegxei tin chef_function pou sigxronizei tous mageires me enan int s = 0, 1, 2, 3 (0 = chef, 1 = cook_1, 2 = cook_2 , 3 = cook_3) kai alla 3 cook1_thread, cook2_thread,
cook3_thread pou elegxoun tin cook_function, tin opoia to kathe ena tin kalei me diaforetiko argument afoy o kathe mageiras kanei diaforetiki douleia kathws diaxeirizetai diaforetiko yliko.
Kathe ektelesi einai diaforetiki afoy xrisimopioyntai random numbers. Telos exoyme tin createANDconsume pou vazei kathisterisi 5 sec me klisi tis sleep() metaksu tvn ektelesevn toy programmatos.
To programma termatizei me Ctrl+C.
