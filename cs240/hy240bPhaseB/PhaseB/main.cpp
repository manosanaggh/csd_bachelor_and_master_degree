/****************************************************************
 * @file   main.c                                      	        *
 * @author Nikolaos <batsaras@csd.uoc.gr>                       *
 *                                                              *
 * @brief Header function for the needs of cs-240b project 2017 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
using namespace std;
#include "geo.h"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


/**
* @brief Add a new location to the system
*
* @param lid The location's id
*
* @return 1 on success
*         0 on failure
*/
int add_location(int lid)
{
    location* loc = (location*)malloc(sizeof(location));

    int i,j,c = 0;
    location* temp[MAX_LOCATIONS];

    for(i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i] != NULL && locations_array[i]->lid < lid) continue;
        else break;
    }

    for(j = i; j < MAX_LOCATIONS; j++){
        temp[c] = locations_array[j];
        c++;
    }

    loc->lid = lid;
    //loc->poi_sentinel = NULL;
    loc->poi_sentinel = (poi*)malloc(sizeof(poi));
    loc->poi_sentinel->pid = loc->poi_sentinel->type = loc->poi_sentinel->distance = -1;
    loc->poi_tree = loc->poi_sentinel;

    c = 0;
    if(locations_array[i] == NULL){
        locations_array[i] = loc;
    }
    else{
        for(j = i+1; j < MAX_LOCATIONS; j++){ locations_array[j] = temp[c];
        c++;}
        locations_array[i] = loc;
    }

    cout << "    ";
    cout << "Locations = ";
    for(i = 0; i < MAX_LOCATIONS && locations_array[i] != NULL; i++){
        cout << locations_array[i]->lid;
        if(locations_array[i+1] != NULL) cout << ",";
    }
    cout << endl << "DONE" << endl;
  return 1;
}

poi* Insert(poi* node,int pid,int type,int distance,poi* sentinel){
   poi* P;
   poi* Prev = sentinel;
   poi* Q;

   P = node;
   while(P != sentinel){
        if(P->pid == pid){
            P->type = type;
            P->distance = distance;
            return node;
        }
        Prev = P;
        if(pid < P->pid) P = P->lc;
        else P = P->rc;
   }

   Q = (poi*)malloc(sizeof(poi));
   Q->pid = pid;
   Q->type = type;
   Q->distance = distance;
   Q->lc = Q->rc = sentinel;
   Q->p = Prev;

   if(Prev == sentinel){
    return Q;
   }
   else if (pid < Prev->pid) Prev->lc = Q;
   else Prev->rc = Q;
   return node;
}

void PrintPOI(poi* node,poi* sentinel){
    if(node == sentinel) return;
    PrintPOI(node->lc,sentinel);
    cout << node->pid << ":" << node->type << ":" << node->distance << "  ";
    PrintPOI(node->rc,sentinel);
}

/**
* @brief Add point-of-interest (POI) to a location
*
* @param pid      POI's id
* @param type     The type of the POI
* @param distance The distance of POI from the locations reference point
* @param lid      The location of the POI
*
* @return 1 on success
*         0 on failure
*/

int add_poi_to_location(int pid, int type, int distance, int lid)
{
    int i,flag = 0;
    for(i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i] != NULL) if(locations_array[i]->lid == lid){flag = 1; break;}
    }
    if(!flag){cout << "To location den uparxei" << endl; return 0;}
    locations_array[i]->poi_tree = Insert(locations_array[i]->poi_tree,pid,
                                          type,distance,locations_array[i]->poi_sentinel);
    cout << "    ";
    cout << "Location = ";
    PrintPOI(locations_array[i]->poi_tree,locations_array[i]->poi_sentinel);
    cout << endl << "DONE" << endl;
  return 1;
}

poi* findMin(poi* node,poi* sentinel){
    poi* temp = node;
    while (temp->lc != sentinel) temp = temp->lc;
    return temp;
}

poi* Delete(poi* root, int pid, poi* sentinel){
    if (root == sentinel) return root;
    if (pid < root->pid) root->lc = Delete(root->lc, pid,sentinel);
    else if (pid > root->pid) root->rc = Delete(root->rc, pid,sentinel);
    else{
        if (root->lc == sentinel){
            poi* temp = root->rc;
            delete root;
            return temp;
        }
        else if (root->rc == sentinel){
            poi* temp = root->lc;
            delete root;
            return temp;
        }
        poi* temp = findMin(root->rc,sentinel);
        root->pid = temp->pid;
        root->rc = Delete(root->rc, temp->pid,sentinel);
    }
    return root;
}

int unavailable_poi(int pid, int lid)
{
    int i,flag = 0;
    for(i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i]!=NULL) if(locations_array[i]->lid == lid){flag = 1; break;}
    }
    if(!flag){cout << "To location den uparxei" << endl; return 0;}
    locations_array[i]->poi_tree = Delete(locations_array[i]->poi_tree,
                                              pid,locations_array[i]->poi_sentinel);
    cout << "    ";
    cout << "Location = ";
    PrintPOI(locations_array[i]->poi_tree,locations_array[i]->poi_sentinel);
    cout << endl << "DONE" << endl;
  return 1;
}

/*poi* TreeSuccessor(poi* z,poi* sentinel){
    if(z == sentinel) return z;
    else if(z->lc != sentinel) return z->lc;
    else if(z->rc != sentinel) return z->rc;
}

poi* IOD(poi* node,poi* sentinel,int pid){
   poi* P;

   P = node;
   while(P != sentinel){
        if(P->pid == pid){
            return node;
        }
        if(pid < P->pid) P = P->lc;
        else P = P->rc;
   }
   return P;
}

poi* Delete(poi* R,int pid,poi* sentinel){
    poi* z = R;
    poi* y;
    poi* x;
    z = IOD(z,sentinel,pid);
    if(z->lc == sentinel || z->rc == sentinel) y = z;
    else y = TreeSuccessor(z,sentinel);
    if(y->lc != sentinel) x = y->lc;
    else x = y->rc;
    if(x != sentinel) x->p = y->p;
    if(y->p == sentinel) return x;
    else if(y == y->p->lc) y->p->lc = x;
    else y->p->rc = x;
    if(y != z){
        z->pid = y->pid;
        z->distance = y->distance;
        z->type = y->type;
        z->lc = y->lc;
        z->rc = y->rc;
        z->p = y->p;
    }
    return R;
}

int unavailable_poi(int pid, int lid)
{
    int i,flag = 0;
    for(i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i]!=NULL) if(locations_array[i]->lid == lid){flag = 1; break;}
    }
    if(!flag){cout << "To location den uparxei" << endl; return 0;}

    locations_array[i]->poi_tree = Delete(locations_array[i]->poi_tree,pid,locations_array[i]->poi_sentinel);

    cout << "    ";
    cout << "Location = ";
    PrintPOI(locations_array[i]->poi_tree,locations_array[i]->poi_sentinel);
    cout << endl << "DONE" << endl;
  return 1;
}*/

int H1(int key){
    int p = primes_g[m];
    m++;
    return (((rand()%(p-1)) * key + rand()%(p-1)) % p) % max_users_g;
}


int H2(int key){
    int p = primes_g[m];
    m++;
    return (((rand()%(p-1)) * key + rand()%(p-1)) % p) % max_users_g;
}

/**
* @brief Register user
*
* @param uid The user's id
*
* @return 1 on success
*         0 on failure
*/
int register_user(int uid)
{
    int i;
    i = H1(uid);
    if(users_hashtable[i].uid != 0){
        i += H2(uid);
        i = i%max_users_g;
    }
    users_hashtable[i].uid = uid;

    cout << "    ";
    cout << "Users = ";
    for(i = 0; i < max_users_g; i++){
        if(users_hashtable[i].uid != 0) cout << users_hashtable[i].uid << "  ";
    }
    cout << endl << "DONE" << endl;
  return 1;
}

user_poi* InsertUPOI(user_poi* node,int upid)
{
   user_poi* P;
   user_poi* Prev = NULL;
   user_poi* Q;

   P = node;
   while(P != NULL){
        if(P->upid == upid){
            return node;
        }
        Prev = P;
        if(upid < P->upid) P = P->lc;
        else P = P->rc;
   }

   Q = (user_poi*)malloc(sizeof(user_poi));
   Q->upid = upid;
   Q->lc = Q->rc = NULL;
   if(Prev == NULL){
    return Q;
   }
   else if (upid < Prev->upid) Prev->lc = Q;
   else Prev->rc = Q;
    return node;
}

void PrintUPOI(user_poi* node){
    if(node == NULL) return;
    PrintUPOI(node->lc);
    cout << node->upid << "  ";
    PrintUPOI(node->rc);
}

/**
* @brief User is interested in POI
*
* @param uid The user's id
* @param pid The POI's id
*
* @return 1 on success
*         0 on failure
*/
int interesting_poi(int uid, int pid)
{
    int i,flag = 0;
    for(i = 0; i < max_users_g; i++){
        if(users_hashtable[i].uid == uid){flag = 1; break;}
    }
    if(!flag){cout << "O user den uparxei" << endl; return 0;}
    users_hashtable[i].interesting_poi = InsertUPOI(users_hashtable[i].interesting_poi,pid);
    users_hashtable[i].upoi_count++;
    cout << "    ";
    cout << "Users POI = ";
    PrintUPOI(users_hashtable[i].interesting_poi);
    cout << endl << "DONE" << endl;
  return 1;
}

void IO(user_poi* node,user_poi* arr,int i,int length){
    if(node == NULL) return;
    IO(node->lc,arr,i,length);
    if(i < length){
    arr[i] = *node;
    i++;}
    IO(node->rc,arr,i,length);
}

void IO2(user_poi* node,int upid){
    if(node == NULL) return;
    IO2(node->lc,upid);
    if(node->upid == upid) cout << node->upid << "  ";
    if(node->upid == upid) return;
    IO2(node->rc,upid);
}

/**
* @brief Group users
*
* @param uid1 The id of the 1st user
* @param uid2 The id of the 2nd user
*
* @return 1 on success
*         0 on failure
*/
int group_users(int uid1, int uid2)
{
    user temp1;
    user temp2;
    int flag1 = 0,flag2 = 0;
    for(int i = 0; i < max_users_g; i++){
        if(users_hashtable[i].uid == uid1){flag1 = 1; temp1 = users_hashtable[i];}
        if(users_hashtable[i].uid == uid2){flag2 = 1; temp2 = users_hashtable[i];}
    }
    if(!flag1){cout << "O xrhsths me uid1 den yparxei" << endl; return 0;}
    if(!flag2){cout << "O xrhsths me uid2 den yparxei" << endl; return 0;}
    user_poi* arr;
    arr = (user_poi*)malloc(temp1.upoi_count*sizeof(user_poi));
    IO(temp1.interesting_poi,arr,0,temp1.upoi_count);
    cout << "     USER 1 = ";
    PrintUPOI(temp1.interesting_poi);
    cout << endl << "     USER 2 = ";
    PrintUPOI(temp2.interesting_poi);
    cout << endl << "     Intersection = ";
    for(int i = 0; i < temp1.upoi_count; i++){
        IO2(temp2.interesting_poi,arr[i].upid);
    }
    cout << endl << "DONE" << endl;
  return 1;
}

poi* InorderTreeSuccessor(poi* node,int pid,poi* sentinel){
   poi* P;
   P = node;
   while(P != sentinel){
        if(P->pid == pid){
            return node;
        }
        if(pid < P->pid) P = P->lc;
        else P = P->rc;
   }
   return P;
}

void InorderTreeSuccessor2(poi* node,int pid,poi* sentinel){
    if(node == sentinel) return;
    InorderTreeSuccessor2(node->lc,pid,sentinel);
    if(node->pid <= pid && node->pid != -1) cout << node->pid << ":" << node->type << ":" << node->distance << "  ";
    if(node->pid > pid && node->pid != -1) return;
    InorderTreeSuccessor2(node->rc,pid,sentinel);
}

/**
* @brief Find the inorder successors from one pid the other
*
* @param lid  The location's id
* @param pid1 A point of interest
* @param pid2 A point of interest
*
* @return 1 on success
*         0 on failure
*/
int inorder_successors(int lid, int pid1, int pid2)
{
    int i,flag = 0;
    for(i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i] != NULL) if(locations_array[i]->lid == lid){flag = 1; break;}
    }
    if(!flag){cout << "To location den uparxei" << endl; return 0;}
    int x,y;
    if(pid1 < pid2){x = pid1; y = pid2;}
    else if(pid1 > pid2) {x = pid2; y = pid1;}

    poi* temp;
	cout << "     Location: " << lid << endl;
    temp = InorderTreeSuccessor(locations_array[i]->poi_tree,x,locations_array[i]->poi_sentinel);
	cout << "     Inorder Traversal: ";
    InorderTreeSuccessor2(temp,y,locations_array[i]->poi_sentinel);
	cout << endl << "DONE" << endl;
  return 1;
}

void InOrderPrintX(poi* node,poi* sentinel){
    if(node == sentinel) return;
    InOrderPrintX(node->lc,sentinel);
    cout << node->pid << ":" << node->type << ":" << node->distance << "  ";
    InOrderPrintX(node->rc,sentinel);
}

void InOrderPrintY(user_poi* node){
    if(node == NULL) return;
    InOrderPrintY(node->lc);
    cout << node->upid << "  ";
    InOrderPrintY(node->rc);
}

/**
* @brief Print all locations
*
* @return 1 on success
*         0 on failure
*/
int print_locations()
{
    int x = 1;
    cout << "LOCATIONS:" << endl;
    for(int i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i] != NULL){
            cout << "    Location" << x << ": ";
            InOrderPrintX(locations_array[i]->poi_tree,locations_array[i]->poi_sentinel);
            cout << endl;
            x++;
        }
    }
    cout << "DONE" << endl;
  return 1;
}

/**
* @brief Print all users
*
* @return 1 on success
*         0 on failure
*/
int print_users()
{
    int x = 1;
    cout << "USERS:" << endl;
    for(int i = 0; i < max_users_g; i++){
            cout << "    User" << x << " = ";
            InOrderPrintY(users_hashtable[i].interesting_poi);
            cout << endl;
            x++;
    }
    cout << "DONE" << endl;
  return 1;
}

/**
* @brief Search for user
*
* @param uid The id of the user we are looking for
*
* @return 1 on success
*         0 on failure
*/
int search_user(int uid)
{
    int i,flag = 0;
    for(i = 0; i < max_users_g; i++){
        if(users_hashtable[i].uid == uid){flag = 1; break;}
    }
    if(!flag){cout << "O xrhsths den uparxei" << endl; return 0;}
    cout << "     Interesting_poi: ";
    InOrderPrintY(users_hashtable[i].interesting_poi);
    cout << endl << "DONE" << endl;
  return 1;
}

void InOrderDeletePOI(poi* node,poi* sentinel){
    if(node == sentinel) return;
    InOrderDeletePOI(node->lc,sentinel);
    delete node;
    InOrderDeletePOI(node->rc,sentinel);
}

void InOrderDeleteUPOI(user_poi* node){
    if(node == NULL) return;
    user_poi* temp1 = node->lc;
    user_poi* temp2 = node->rc;
    InOrderDeleteUPOI(temp1);
    delete node;
    InOrderDeleteUPOI(temp2);
}

/**
* @brief Cleanup resources
*
* @return 1 on success
*         0 on failure
*/
int free_world()
{
    for(int i = 0; i < MAX_LOCATIONS; i++){
        if(locations_array[i] != NULL){
            InOrderDeletePOI(locations_array[i]->poi_tree,locations_array[i]->poi_sentinel);
            delete locations_array[i];
        }
    }

    for(int i = 0; i < max_users_g; i++){
        InOrderDeleteUPOI(users_hashtable[i].interesting_poi);
    }

    delete users_hashtable;
    cout << "All dynamically allocated memory has been freed." << endl;
  return 1;
}

/**
* @brief Initialize hash parameters
*
* @return null
*/
void initialize()
{
    users_hashtable = (user*)malloc(sizeof(user)*max_users_g);
    for(int i = 0; i < max_users_g; i++){user u; u.uid = 0; u.upoi_count = 0;
    u.interesting_poi = NULL; users_hashtable[i] = u;}
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
  FILE *fin = NULL;
  char buff[BUFFER_SIZE], event;


  /* Check command buff arguments */
  if ( argc != 2 ) {
    fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Open input file */
  if (( fin = fopen(argv[1], "r") ) == NULL ) {
    fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
    perror("Opening test file\n");
    return EXIT_FAILURE;
  }

  /* Read input file buff-by-buff and handle the events */
  while ( fgets(buff, BUFFER_SIZE, fin) ) {

    DPRINT("\n>>> Event: %s", buff);

    switch(buff[0]) {

      /* Comment */
    case '#':
      break;

      /* Maximum users */
    case '0':
      {
	sscanf(buff, "%c %u", &event, &max_users_g);
	DPRINT("%c %u\n", event, max_users_g);
	break;
      }

      /* Maximum user id */
    case '1':
      {
	sscanf(buff, "%c %u", &event, &max_uid_g);
	DPRINT("%c %u\n", event, max_uid_g);
	initialize();
	break;
      }

      /* Add location
       * L <lid> */
    case 'L':
      {
	int lid;
	sscanf(buff, "%c %d", &event, &lid);
	DPRINT("%c %d\n", event, lid);


	if ( add_location(lid) ) {
	  DPRINT("L %d succeeded\n", lid);
	} else {
	  fprintf(stderr, "L %d failed\n", lid);
	}

	break;
      }

      /* Add POI to location
       * P <pid> <type> <distance> <lid> */
    case 'P':
      {
	int pid, type, distance, lid;

	sscanf(buff, "%c %d %d %d %d", &event, &pid, &type, &distance, &lid);
	DPRINT("%c\n", event);

	if ( add_poi_to_location(pid, type, distance, lid) ) {
	  DPRINT("%c %d %d %d %d succeeded\n", event, pid, type, distance, lid);
	} else {
	  fprintf(stderr,
		  "%c %d %d %d %d failed\n", event, pid, type, distance, lid);
	}

	break;
      }

      /* POI is not available
       * A <pid> <lid> */
    case 'A':
      {
	int pid;
	int lid;
	sscanf(buff, "%c %d %d", &event, &pid, &lid);
	DPRINT("%c %d %d\n", event, pid, lid);

	if ( unavailable_poi(pid, lid) ) {
	  DPRINT("%c %d %d succeeded\n", event, pid, lid);
	} else {
	  fprintf(stderr, "%c %d %d failed\n", event, pid, lid);
	}

	break;
      }

      /* Register user
       * R <uid> <hotel-id> */
    case 'R':
      {
	int uid;
	sscanf(buff, "%c %d", &event, &uid);
	DPRINT("%c %d\n", event, uid);

	if ( register_user(uid) ) {
	  DPRINT("%c %d succeeded\n", event, uid);
	} else {
	  fprintf(stderr, "%c %d failed\n", event, uid);
	}

	break;
      }

      /* User interested in poi
       * I <uid> <pid> */
    case 'I':
      {
	int uid, pid;
	sscanf(buff, "%c %d %d", &event, &uid, &pid);
	DPRINT("%c %d %d\n", event, uid, pid);

	if ( interesting_poi(uid, pid) ) {
	  DPRINT("%c %d %d succeeded\n", event, uid, pid);
	} else {
	  fprintf(stderr, "%c %d %d failed\n", event, uid, pid);
	}

	break;
      }

      /* Group users
       * G <uid1> <uid2> */
    case 'G':
      {
	int uid1, uid2;
	sscanf(buff, "%c %d %d", &event, &uid1, &uid2);
	DPRINT("%c %d %d\n", event, uid1, uid2);

	if ( group_users(uid1, uid2) ) {
	  DPRINT("%c %d %d succeeded\n", event, uid1, uid2);
	} else {
	  fprintf(stderr, "%c %d %d failed\n", event, uid1, uid2);
	}

	break;
      }

      /* Find inorder successors
       * B <lid> <pid1> <pid2> */
    case 'B':
      {
	int lid, pid1, pid2;
	sscanf(buff, "%c %d %d %d\n", &event, &lid, &pid1, &pid2);
	DPRINT("%c %d %d %d\n", event, lid, pid1, pid2);

	if ( inorder_successors(lid, pid1, pid2) ) {
	  DPRINT("%c %d %d %d succeeded\n", event, lid, pid1, pid2);
	} else {
	  fprintf(stderr, "%c %d %d %d failed\n", event, lid, pid1, pid2);
	}

	break;
      }

      /* Print locations
       * X */
    case 'X':
      {
	sscanf(buff, "%c", &event);
	DPRINT("%c\n", event);

	if ( print_locations() ) {
	  DPRINT("%c succeeded\n", event);
	} else {
	  fprintf(stderr, "%c failed\n", event);
	}

	break;
      }

      /* Print users
       * Y */
    case 'Y':
      {
	sscanf(buff, "%c", &event);
	DPRINT("%c\n", event);

	if ( print_users() ) {
	  DPRINT("%c succeeded\n", event);
	} else {
	  fprintf(stderr, "%c failed\n", event);
	}

	break;
      }

      /* Search user
       * Z */
    case 'Z':
      {
	int uid;
	sscanf(buff, "%c %d", &event, &uid);
	DPRINT("%c\n", event);

	if ( search_user(uid) ) {
	  DPRINT("%c %d succeeded\n", event, uid);
	} else {
	  fprintf(stderr, "%c %d failed\n", event, uid);
	}

	break;
      }

      /* Empty line */
    case '\n':
      break;

      /* Ignore everything else */
    default:
      DPRINT("Ignoring buff: %s \n", buff);

      break;
    }
  }

  free_world();
  return (EXIT_SUCCESS);
}
