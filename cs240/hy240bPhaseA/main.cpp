/************************************************************//**
 * @file   zoo.h                                      			*
 * @author Antonis Papaioannou <papaioan@csd.uoc.gr>  			*
 *                                                    			*
 * @brief Header function for the needs of cs-240a project 2016 *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include "geo.h"
using namespace std;
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
* @return true on success
*         false on failure
*/
int add_location(int lid) {
    location* temp1;
    location* temp2;
    location* temp3;

    temp1 = locations_list;
    temp2 = NULL;
    while(temp1 != NULL && temp1->lid < lid){
        temp2 = temp1;
        temp1 = temp1->next;
    }

    temp3 = (location*)malloc(sizeof(location));
    temp3->lid = lid;
    temp3->next = temp1;

    if(temp2 == NULL){
        locations_list = temp3;
    }
    else{
        temp2->next = temp3;
    }

    location* temp4 = locations_list;
    cout << "    ";
    cout <<"Locations = ";
    while(temp4 != NULL){
        cout << temp4->lid;
        temp4 = temp4->next;
        if(temp4 != NULL){
            cout << ",";
        }
    }
    cout << endl << "DONE" << endl;

    return 1;
}

/**
* @brief Add point-of-interest (POI) to a location
*
* @param pid POI's id
* @param type The type of the POI
* @param distance The distance of POI from the locations reference point
* @param lid The location of the POI
*
* @return true on success
*         false on failure
*/
int add_poi_to_location(int pid, int type, int distance, int lid) {
    location* temp1 = locations_list;
    while(temp1 != NULL && temp1->lid != lid){
        temp1 = temp1->next;
    }

    poi* temp5;
    poi* temp2;
    poi* temp3;
    poi* temp6;

    temp5 = temp1->poi_list;
    temp2 = NULL;
    int sum = 0;
    while(temp5 != NULL && sum+temp5->distance < distance){
        sum += temp5->distance;
        temp2 = temp5;
        temp5 = temp5->next;
    }

    temp3 = (poi*)malloc(sizeof(poi));
    temp3->distance = distance-sum;
    temp3->pid = pid;
    temp3->type = type;
    temp3->next = temp5;

    if(temp3->next != NULL){
        temp3->next->distance = temp3->next->distance-temp3->distance;
    }

    if(temp2 == NULL){
        temp1->poi_list = temp3;
    }
    else{
        temp2->next = temp3;
        temp3->prev = temp2;
    }

    poi* temp4 = temp1->poi_list;
    cout << "    ";
    cout << "Location = ";
    while(temp4 != NULL){
        cout << temp4->pid << ":" << temp4->type << ":" << temp4->distance;
        temp4 = temp4->next;
        if(temp4 != NULL){
            cout << ",";
        }
    }
    cout << endl << "DONE" << endl;

	return 1;
}

/**
* @brief A POI is unavailable to vistors
*
* @param pid The POI's id
* @param lid The location's id
*
* @return true on success
*         false on failure
*/
int unavailable_poi(int pid, int lid) {
    location* temp = locations_list;
    while(temp != NULL && temp->lid != lid){
        temp = temp->next;
    }

    poi* temp2 = temp->poi_list;
    poi* temp3 = NULL;
    while(temp2 != NULL){
        if(temp2 == temp->poi_list && temp2->pid == pid && temp2->next != NULL){
            temp->poi_list = temp2->next;
            temp2->next->prev = NULL;
            temp2->next->distance += temp2->distance;
            delete temp2;
            break;
        }
        if(temp2->next->pid == pid && temp2->next->next == NULL){
            temp3 = temp2->next;
            temp2->next = NULL;
            delete temp3;
            break;
        }
        if(temp2->next != NULL && temp2->next->next != NULL){
            if(temp2->next->pid == pid){
                temp3 = temp2->next;
                temp3->next->distance += temp3->distance;
                temp2->next = temp3->next;
                temp3->next->prev = temp2;
                delete temp3;
                break;
            }
        }
        temp2 = temp2->next;
    }

    poi* temp4 = temp->poi_list;
    cout << "    ";
    cout << "Locations = ";
    while(temp4 != NULL){
        cout << temp4->pid << ":" << temp4->type << ":" << temp4->distance;
        temp4 = temp4->next;
        if(temp4 != NULL){
            cout << ",";
        }
    }
    cout << endl << "DONE" << endl;

	return 1;
}

/**
* @brief Register user
*
* @param uid The user's id
*
* @return true on success
*         false on failure
*/
int register_user(int uid) {
    if(users_list == NULL) {users_sentinel = (user*)malloc(sizeof(user)); users_sentinel->uid = -1; users_list = users_sentinel;}
    user* temp;
    temp = (user*)malloc(sizeof(user));
    temp->uid = uid;
    temp->next = users_list;
    users_list = temp;

    user* temp4 = users_list;
    cout << "    ";
    cout << "Users = ";
    while(temp4 != users_sentinel){
        cout << temp4->uid;
        temp4 = temp4->next;
        if(temp4 != users_sentinel){
            cout << ",";
        }
    }
    
    cout << endl << "DONE" << endl;

	return 1;
}

/**
* @brief User is interested in POI
*
* @param uid The user's id
* @param pid The POI's id
*
* @return true on success
*         false on failure
*/
int interesting_poi(int uid, int pid) {
    user* temp = users_list;
    while(temp != users_sentinel && temp->uid != uid){
        temp = temp->next;
    }

    user_poi* temp1;
    user_poi* temp2;
    user_poi* temp3;

    temp1 = temp->interesting_poi;
    temp2 = NULL;
    while(temp1 != NULL && temp1->upid < pid){
        temp2 = temp1;
        temp1 = temp1->next;
    }

    temp3 = (user_poi*)malloc(sizeof(user_poi));
    temp3->upid = pid;
    temp3->next = temp1;

    if(temp2 == NULL){
       temp->interesting_poi = temp3;
    }
    else{
        temp2->next = temp3;
    }

    user_poi* temp4 = temp->interesting_poi;
    cout << "    ";
    cout <<"POI = ";
    while(temp4 != NULL){
        cout << temp4->upid;
        temp4 = temp4->next;
        if(temp4 != NULL){
            cout << ",";
        }
    }
    cout << endl << "DONE" << endl;

	return 1;
}

/**
* @brief Group users
*
* @param uid1 The id of the 1st user
* @param uid2 The id of the 2nd user
* @param uid3 The id of the 3rd user
*
* @return true on success
*         false on failure
*/
int group_users(int uid1, int uid2, int uid3) {
    user* temp = users_list;
    user* temp1;
    user* temp2;
    user* temp3;
    while(temp != users_sentinel){
        if(temp->uid == uid1){
            temp1 = temp;
        }
        if(temp->uid == uid2){
            temp2 = temp;
        }
        if(temp->uid == uid3){
            temp3 = temp;
        }
        temp = temp->next;
    }

    int i = 1;
    cout << "    ";
    cout <<"User" << i << " = ";
    user_poi* p = temp1->interesting_poi;
    while(p != NULL){
        cout << p->upid;
        p = p->next;
        if(p != NULL){
            cout << ",";
        }
    }
    i++;

    cout << endl << "    ";
    cout <<"User" << i << " = ";
    p = temp2->interesting_poi;
    while(p != NULL){
        cout << p->upid;
        p = p->next;
        if(p != NULL){
            cout << ",";
        }
    }
    i++;

    cout << endl << "    ";
    cout <<"User" << i << " = ";
    p = temp3->interesting_poi;
    while(p != NULL){
        cout << p->upid;
        p = p->next;
        if(p != NULL){
            cout << ",";
        }
    }

    cout << endl << "    ";
    cout <<"Intersection" << " = ";
    p = temp1->interesting_poi;
    user_poi* p2 = temp2->interesting_poi;
    user_poi* p3 = temp3->interesting_poi;
    user_poi* tempP2 = NULL;
    user_poi* tempP3 = NULL;
    while(p != NULL){
        while(p2 != NULL){
            if(p->upid == p2->upid){
                while(p3 != NULL){
                    if(p->upid == p3->upid){
                        cout << p->upid << "  ";
                        tempP3 = p3;
                        break;
                    }
                    p3 = p3->next;
                }
                tempP2 = p2;
                break;
            }
            p2 = p2->next;
        }
        p2 = tempP2;
        p3 = tempP3;
        p = p->next;
    }
    cout << endl << "DONE" << endl;

	return 1;
}

/**
* @brief Calculate the distance between locations
*
* @param lid The location's id
* @param pid1 The id of the 1st POI
* @param pid1 The id of the 2nd POI
* @param pid1 The id of the 3rd POI
*
* @return true on success
*         false on failure
*/
int sightseeing_distance(int lid, int pid1, int pid2, int pid3) {
    location* temp = locations_list;
    while(temp != NULL && temp->lid != lid){
        temp = temp->next;
    }

    poi* P[3];
    int i = 0;
    poi* temp2 = temp->poi_list;
    while(temp2 != NULL){
        if(temp2->pid == pid1 || temp2->pid == pid2 || temp2->pid == pid3){
            P[i] = temp2;
            i++;
        }
        temp2 = temp2->next;
    }

    int j,k,z;
    for(i = 0; i < 3; i++){
        if(P[i]->pid == pid1){
            j = i;
        }
        if(P[i]->pid == pid2){
            k = i;
        }
        if(P[i]->pid == pid3){
            z = i;
        }
    }

    int sum = 0;
    poi* p;
    if(j < k){
        p = P[j];
        while(p->next != NULL && p->next != P[k]){
            sum += p->next->distance;
            p = p->next;
            if(p->next == P[k]){
                sum += p->next->distance;
            }
        }
    }
    else{
        p = P[j];
        while(p->prev != NULL && p->prev != P[k]){
            sum += p->prev->distance;
            p = p->prev;
            if(p->prev == P[k]){
                sum += p->prev->distance;
            }
        }
    }

    if(k < z){
        p = P[k];
        while(p->next != NULL && p->next != P[z]){
            sum += p->next->distance;
            p = p->next;
            if(p->next == P[z]){
                sum += p->next->distance;
            }
        }
    }
    else{
        p = P[k];
        while(p->prev != NULL && p->prev != P[z]){
            sum += p->prev->distance;
            p = p->prev;
            if(p->prev == P[z]){
                sum += p->prev->distance;
            }
        }
    }
    cout << "    Total distance: " << sum << endl << "DONE" << endl;

	return 1;
}

/**
* @brief Print all locations
*
* @return true on success
*         false on failure
*/
int print_locations() {
    int i = 1;
    location* temp = locations_list;
    cout << "LOCATIONS:" << endl;
    while(temp != NULL){
        poi* temp2 = temp->poi_list;
        cout << "    ";
        cout << "Location" << i << " = ";
        while(temp2 != NULL){
            cout << temp2->pid << ":" << temp2->type << ":" << temp2->distance;
            temp2 = temp2->next;
            if(temp2 != NULL){
                cout << ",";
            }
        }
        cout << endl;
        i++;
        temp = temp->next;
    }
    cout <<"DONE"<<endl;

	return 1;
}

/**
* @brief Print all users
*
* @return true on success
*         false on failure
*/
int print_users() {
    int i = 1;
    user* temp = users_list;
    while(temp != users_sentinel){
        user_poi* temp2 = temp->interesting_poi;
        cout << "    ";
        cout << "User" << i << ": ";
        while(temp2 != NULL){
            cout << temp2->upid;
            temp2 = temp2->next;
            if(temp2 != NULL){
                cout << ",";
            }
        }
        cout << endl;
        i++;
        temp = temp->next;
    }
    cout <<"DONE"<<endl;

	return 1;
}

/**
* @brief Search for user
*
* @param uid The id of the user we are looking for
*
* @return true on success
*         false on failure
*/
int search_user(int uid) {
    user* temp = users_list;
    while(temp != users_sentinel && temp->uid != uid){
        temp = temp->next;
    }
    user_poi* temp2 = temp->interesting_poi;
    cout << "    ";
    cout << "Interesting_poi: ";
    while(temp2 != NULL){
        cout << temp2->upid;
        temp2 = temp2->next;
        if(temp2 != NULL){
            cout << ",";
        }
    }
    cout << endl;
    cout <<"DONE"<<endl;

	return 1;
}

int free_world() {
    location* temp = locations_list;
    while(temp != NULL){
        location* temp4;
        poi* temp2 = temp->poi_list;
        while(temp2 != NULL){
            poi* temp3;
            temp3 = temp2;
            delete temp3;
            temp2 = temp2->next;
        }
        temp4 = temp;
        delete temp4;
        temp = temp->next;
    }
    delete locations_list;

    user* temp5 = users_list;
    while(temp5 != users_sentinel){
        user* temp6;
        user_poi* temp7 = temp5->interesting_poi;
        while(temp7 != NULL){
            user_poi* temp8;
            temp8 = temp7;
            delete temp8;
            temp7 = temp7->next;
        }
        temp6 = temp5;
        delete temp6;
        temp5 = temp5->next;
    }
    delete users_list;
    delete users_sentinel;

    cout << endl << "All dynamically allocated memory has been freed" << endl;

	return 1;
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
				fprintf(stderr, "%c %d %d %d %d failed\n", event, pid, type, distance, lid);
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
		 * G <uid1> <uid2> <uid3> */
		case 'G':
		{
			int uid1, uid2, uid3;
			sscanf(buff, "%c %d %d %d", &event, &uid1, &uid2, &uid3);
			DPRINT("%c %d %d %d\n", event, uid1, uid2, uid3);

			if ( group_users(uid1, uid2, uid3) ) {
				DPRINT("%c %d %d %d succeeded\n", event, uid1, uid2, uid3);
			} else {
				fprintf(stderr, "%c %d %d %dfailed\n", event, uid1, uid2, uid3);
			}

			break;
		}

		/* Sightseeing distance
		 * B <lid> <pid1> <pid2> <pid3> */
		case 'B':
		{
			int lid;
			int pid1, pid2, pid3;
			sscanf(buff, "%c %d %d %d %d\n", &event, &lid, &pid1, &pid2, &pid3);
			DPRINT("%c %d %d %d %d\n", event, lid, pid1, pid2, pid3);

			if ( sightseeing_distance(lid, pid1, pid2, pid3) ) {
				DPRINT("%c %d %d %d %d succeeded\n", event, lid, pid1, pid2, pid3);
			} else {
				fprintf(stderr, "%c %d %d %d %d failed\n", event, lid, pid1, pid2, pid3);
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
