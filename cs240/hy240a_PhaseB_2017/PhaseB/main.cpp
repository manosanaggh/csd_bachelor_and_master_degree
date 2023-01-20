/************************************************************//**
 * @file   main.c                                      		*
 * @author Nikolaos Batsaras <batsaras@csd.uoc.gr>  		*
 *                                                    		*
 * @brief Main function for the needs of cs-240b project 2017   *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
using namespace std;

#include "troy.h"

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
 * @brief Optional function to initialize data structures that
 * need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    registration_hashtable = (soldier**)malloc(max_soldiers_g*sizeof(soldier));
    my_combat.combat_s = (c_soldier*)malloc(sizeof(c_soldier));
    return 1;
}

int h(int k){
    return k%max_soldiers_g;
}

/**
 * @brief Register soldier
 *
 * @param sid The soldier's id
 * @param gid The general's id who orders the soldier
 *
 * @return 1 on success
 *         0 on failure
 */
int register_soldier(int sid, int gid) {
    int pos;

    pos = h(sid);
    soldier *new_soldier = (soldier*)malloc(sizeof(soldier));
    new_soldier->sid = sid;
    new_soldier->gid = gid;
    if(registration_hashtable[pos] == NULL) registration_hashtable[pos] = new_soldier;
    else{
        new_soldier->next = registration_hashtable[pos];
        registration_hashtable[pos] = new_soldier;
    }

    soldier *print_soldiers;
    cout << "    ";
    cout << "Soldiers Hash Table:" << endl;
    for(int i = 0; i < max_soldiers_g; i++){
        print_soldiers = registration_hashtable[i];
        int h = 0;
        while(print_soldiers != NULL){
            h++;
            cout << print_soldiers->sid;
            cout << ":";
            cout << print_soldiers->gid;
            print_soldiers = print_soldiers->next;
            cout << "  ";
        }
        if(h > 0) cout << endl;
    }
    cout << endl << "DONE" << endl;
    return 1;
}

/**
 * @brief General or King joins the battlefield
 *
 * @param gid The general's id
 *
 * @return 1 on success
 *         0 on failure
 */
int add_general(int gid) {
    general *temp;
    temp = (general*)malloc(sizeof(general));
    temp->gid = gid;
    temp->soldiers_S = (TREE_soldier*)malloc(sizeof(TREE_soldier));
    temp->soldiers_R = temp->soldiers_S;
    temp->combats_no = 0;
    temp->next = generals_list;
    generals_list = temp;

    general *temp2 = generals_list;
    cout << "    ";
    cout << "Generals = ";
    while(temp2 != NULL){
        cout << temp2->gid;
        temp2 = temp2->next;
        if(temp2 != NULL) cout << ",";
    }
    cout << endl << "DONE" << endl;

    return 1;
}

TREE_soldier *Insert(TREE_soldier *node,int sid, TREE_soldier *sentinel){
   TREE_soldier* P;
   TREE_soldier* Prev = sentinel;
   TREE_soldier* Q;

   P = node;
   while(P != sentinel){
        if(P->sid == sid) return node;
        Prev = P;
        if(sid < P->sid) P = P->lc;
        else P = P->rc;
   }

   Q = (TREE_soldier*)malloc(sizeof(TREE_soldier));
   Q->sid = sid;
   Q->lc = Q->rc = sentinel;
   Q->p = Prev;

   if(Prev == sentinel) return Q;
   else if (sid < Prev->sid) Prev->lc = Q;
   else Prev->rc = Q;
   return node;
}

void PrintTreeSoldier(TREE_soldier *node, TREE_soldier *sentinel){
    if(node == sentinel) return;
    PrintTreeSoldier(node->lc,sentinel);
    cout << node->sid << "  ";
    PrintTreeSoldier(node->rc,sentinel);
}

/**
 * @brief Distribute soldiers to the camps
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute() {
    soldier *list_i;
    general *g_list;
    int search_sid;

    for(int i = 0; i < max_soldiers_g; i++){
        list_i = registration_hashtable[i];
        while(list_i != NULL){
            search_sid = list_i->sid;
            g_list = generals_list;
            while(g_list != NULL){
                if(g_list->gid == list_i->gid){
                    g_list->soldiers_R = Insert(g_list->soldiers_R,search_sid,g_list->soldiers_S);
                    break;
                }
                g_list = g_list->next;
            }
            list_i = list_i->next;
        }
    }

    g_list = generals_list;
    cout << "    ";
    cout << "GENERALS: " << endl;
    while(g_list != NULL){
        cout << "    ";
        cout << g_list->gid;
        cout << ": ";
        PrintTreeSoldier(g_list->soldiers_R,g_list->soldiers_S);
        cout << endl;
        g_list = g_list->next;
    }
    cout << endl << "DONE" << endl;
    return 1;
}

void InOrderM(TREE_soldier *node, TREE_soldier *sentinel,TREE_soldier **A, int &i){
    if(node == sentinel) return;
    InOrderM(node->lc, sentinel, A, i);
    if(i == 0) *A = (TREE_soldier*)malloc(sizeof(TREE_soldier));
    else { size_t sz = ((i*sizeof(TREE_soldier))+sizeof(TREE_soldier));
    *A = (TREE_soldier*)realloc(*A,sz);}
    (*A)[i] = *node;
    i++;
    InOrderM(node->rc, sentinel, A, i);
}

/**
 * @brief General resigns from battlefield
 *
 * @param gid1 The id of general that resigns
 * @param gid2 The id of the general that will
 *
 * @return 1 on success
 *         0 on failure
 */
int general_resign(int gid1, int gid2) {
    TREE_soldier *A1;
    TREE_soldier *forPatroklos;
    int i = 0;
    general *patroklos = generals_list;
    general *axileas = generals_list;
    general *del_prev;
    general *g_list;

	    while(patroklos != NULL && patroklos->gid != gid2){
            patroklos = patroklos->next;
            if(patroklos == NULL) {cout << "O strathgos den uparxei" << endl; return 0;}
	    }

	    while(axileas != NULL && axileas->gid != gid1){
            del_prev = axileas;
            axileas = axileas->next;
            if(axileas == NULL) {cout << "O strathgos den uparxei" << endl; return 0;}
	    }

	    InOrderM(axileas->soldiers_R, axileas->soldiers_S, &A1, i);

	    forPatroklos = (TREE_soldier*)malloc(i*sizeof(TREE_soldier));

	    for(int m = 0; m < i; m++){
            forPatroklos[m] = A1[m];
	    }

	    for(int m = 0; m < i; m++){
            patroklos->soldiers_R = Insert(patroklos->soldiers_R,forPatroklos[m].sid,patroklos->soldiers_S);
	    }
	    del_prev->next = axileas->next;
	    delete axileas;

    g_list = generals_list;
    cout << "    ";
    cout << "GENERALS:" << endl;
    while(g_list != NULL){
        cout << "    ";
        cout << g_list->gid;
        cout << ": ";
        PrintTreeSoldier(g_list->soldiers_R,g_list->soldiers_S);
        cout << endl;
        g_list = g_list->next;
    }
    cout << endl << "DONE" << endl;
    return 1;
}

c_soldier *InsertP(c_soldier *node,int sid, int gid){
   c_soldier* P;
   c_soldier* Prev = NULL;
   c_soldier* Q;

   P = node;
   while(P != NULL){
        if(P->sid == sid) return node;
        Prev = P;
        if(sid < P->sid) P = P->lc;
        else P = P->rc;
   }

   Q = (c_soldier*)malloc(sizeof(c_soldier));
   Q->sid = sid;
   Q->alive = 1;
   Q->gid = gid;
   Q->lc = Q->rc = NULL;
   my_combat.soldier_cnt++;

   if(Prev == NULL) return Q;
   else if (sid < Prev->sid) Prev->lc = Q;
   else Prev->rc = Q;
   return node;
}

void InOrderP1(TREE_soldier *node_1, TREE_soldier *node_2,TREE_soldier *sentinel_1, TREE_soldier *sentinel_2,int gid1, int gid2,int state){
                   if(node_1 == sentinel_1 || node_2 == sentinel_2) return;
                       if(state == 0){
                            InOrderP1(node_1->lc,node_2,sentinel_1,sentinel_2,gid1,gid2,state);
                            my_combat.combat_s = InsertP(my_combat.combat_s,node_1->sid,gid1);
                            state = 1;
                            InOrderP1(node_1->rc,node_2,sentinel_1,sentinel_2,gid1,gid2,state);
                       }
                       else{
                            InOrderP1(node_1,node_2->rc,sentinel_1,sentinel_2,gid1,gid2,state);
                            my_combat.combat_s = InsertP(my_combat.combat_s,node_2->sid,gid2);
                            state = 0;
                            InOrderP1(node_1,node_2->lc,sentinel_1,sentinel_2,gid1,gid2,state);
                       }
}

void PrintCombatSoldiers(c_soldier *node){
    if(node == NULL) return;
    PrintCombatSoldiers(node->lc);
    cout << node->sid << "  ";
    PrintCombatSoldiers(node->rc);
}

/**
 * @brief Prepare for battle
 *
 * @param gid1 The id of the first general
 * @param gid2 The id of the second general
 *
 * @return 1 on success
 *         0 on failure
 */
int prepare_battle(int gid1, int gid2) {
    general *first_general = generals_list;
    general *second_general = generals_list;

	    while(second_general != NULL && second_general->gid != gid2){
            second_general = second_general->next;
            if(second_general == NULL) {cout << "O strathgos den uparxei" << endl; return 0;}
	    }

	    while(first_general != NULL && first_general->gid != gid1){
            first_general = first_general->next;
            if(first_general == NULL) {cout << "O strathgos den uparxei" << endl; return 0;}
	    }

	    first_general->combats_no++;
	    second_general->combats_no++;

	    InOrderP1(first_general->soldiers_R, second_general->soldiers_R, first_general->soldiers_S, second_general->soldiers_S, gid1, gid2, 0);

    cout << "    ";
    cout << "Combat soldiers: ";
    PrintCombatSoldiers(my_combat.combat_s);
    cout << endl << "DONE" << endl;

    return 1;
}

void InOrderB(c_soldier *node, int res, int &count){
    if(node == NULL) return;
    InOrderB(node->lc,res,count);
    if(count < res){
        node->alive = 0;
        count++;
    }
    InOrderB(node->rc,res,count);
}

void InOrderBPrint(c_soldier *node){
    if(node == NULL) return;
    InOrderBPrint(node->lc);
    cout << node->sid << ":" << node->alive << "  ";
    InOrderBPrint(node->rc);
}

void InOrderBstream(c_soldier *node, char *stream, int i){
    if(node == NULL) return;
    if(i == 6 && node->lc != NULL && node->rc != NULL) i = 0;
    if(stream[i] == '0'){
        InOrderBstream(node->lc, stream, i);
    }
    node->alive = 0;
    i++;
    if(stream[i] == '1'){
        InOrderBstream(node->rc, stream, i);
    }
}

/**
 * @brief Battle
 *
 * @param god_favor
 * @param bit_stream A sequence of bits
 * @param bitsno The number of bits in the sequence
 *
 * @return 1 on success
 *         0 on failure
 */
int battle(int god_favor, char *bit_stream, int bitsno) {
    if(god_favor == 0){
             float res = ((float)(my_combat.soldier_cnt)*(40))/100;
            int border = (int) res;
            int count = 0;
            cout << border << endl;
            InOrderB(my_combat.combat_s, border, count);
    }
    else{
        c_soldier *combat_soldiers = my_combat.combat_s;
            InOrderBstream(combat_soldiers, bit_stream, 0);
    }
    cout << "    Combat soldiers: ";
    c_soldier *combat_soldiers = my_combat.combat_s;
    InOrderBPrint(combat_soldiers);
    cout << endl << "DONE" << endl;
    return 1;
}

c_soldier * minValueNode(c_soldier * node)
{
    c_soldier * current = node;

    while (current->lc != NULL)
        current = current->lc;

    return current;
}

TREE_soldier * minValueNode2(TREE_soldier * node, TREE_soldier * sentinel)
{
    TREE_soldier * current = node;

    while (current->lc != sentinel)
        current = current->lc;

    return current;
}

c_soldier *deleteNode(c_soldier *root, int sid)
{
    if (root == NULL) return root;

    if (sid < root->sid)
        root->lc = deleteNode(root->lc, sid);
    else if (sid > root->sid)
        root->rc = deleteNode(root->rc, sid);
    else
    {
        if (root->lc == NULL)
        {
            c_soldier *temp = root->rc;
            delete root;
            return temp;
        }
        else if (root->rc == NULL)
        {
            c_soldier *temp = root->lc;
            delete root;
            return temp;
        }

        c_soldier *temp = minValueNode(root->rc);

        root->sid = temp->sid;

        root->rc = deleteNode(root->rc, temp->sid);
    }
    return root;
}

TREE_soldier *deleteNode2(TREE_soldier *root, int sid, TREE_soldier *sentinel)
{
    if (root == sentinel) return root;
    if (sid < root->sid)
        root->lc = deleteNode2(root->lc, sid,sentinel);
    else if (sid > root->sid)
        root->rc = deleteNode2(root->rc, sid,sentinel);
    else
    {
        if (root->lc == sentinel)
        {
            TREE_soldier *temp = root->rc;
            delete root;
            return temp;
        }
        else if (root->rc == sentinel)
        {
            TREE_soldier *temp = root->lc;
            delete root;
            return temp;
        }

        TREE_soldier *temp = minValueNode2(root->rc,sentinel);

        root->sid = temp->sid;

        root->rc = deleteNode2(root->rc, temp->sid,sentinel);
    }
    return root;
}

void InOrderU(c_soldier *battle_tree){
    if(battle_tree == NULL) return;
    InOrderU(battle_tree->lc);
    if(battle_tree->alive == 0){
        int gid_gen = battle_tree->gid;
        int sid_hash = battle_tree->sid;
        my_combat.combat_s = deleteNode(my_combat.combat_s, sid_hash);
        general *g_list = generals_list;
        while(g_list != NULL && g_list->gid != gid_gen) g_list = g_list->next;
        if(g_list != NULL && g_list->gid == gid_gen) g_list->soldiers_R = deleteNode2(g_list->soldiers_R, sid_hash, g_list->soldiers_S);
        for(int i = 0; i < max_soldiers_g; i++){
            soldier *chain = registration_hashtable[i];
            soldier *prev;
            while(chain != NULL && chain->sid != sid_hash){prev = chain; chain = chain->next;}
            if(chain != NULL && chain->sid == sid_hash){
                prev->next = chain->next;
                delete chain;
            }
        }
        cout << "ok" << endl;
    }
    InOrderU(battle_tree->rc);

}

/**
 * @brief Cease fire
 *
 * @return 1 on success
 *         0 on failure
 */
int cease_fire() {
    c_soldier *battle_tree = my_combat.combat_s;
    InOrderU(my_combat.combat_s);
    general *g_list = generals_list;
    cout << "    ";
    cout << "GENERALS LIST:" << endl;
    while(g_list != NULL){
        cout << "    ";
        cout << g_list->gid;
        cout << ": ";
        PrintTreeSoldier(g_list->soldiers_R,g_list->soldiers_S);
        cout << endl;
        g_list = g_list->next;
    }
    cout << endl;
    soldier *print_soldiers;
    cout << "    ";
    cout << "SOLDIERS HASH TABLE:" << endl;
    for(int i = 0; i < max_soldiers_g; i++){
        print_soldiers = registration_hashtable[i];
        int h = 0;
        while(print_soldiers != NULL){
            h++;
            cout << print_soldiers->sid;
            cout << ":";
            cout << print_soldiers->gid;
            print_soldiers = print_soldiers->next;
            cout << "  ";
        }
        if(h > 0) cout << endl;
    }
    cout << endl << "DONE" << endl;
    return 1;
}

void InorderPrint(TREE_soldier *ts, TREE_soldier *sentinel){
    if(ts == sentinel) return;
    InorderPrint(ts->lc,sentinel);
    cout << ts->sid << "  ";
    InorderPrint(ts->rc,sentinel);
}

/**
 * @brief Print general's soldiers
 *
 * @param gid The id of the general
 *
 * @return 1 on success
 *         0 on failure
 */
int print_generals_soldiers(int gid) {
    general *g_list = generals_list;
    while(g_list != NULL && g_list->gid != gid) g_list = g_list->next;
    cout << "    ";
    cout << "Soldier Tree = ";
    InorderPrint(g_list->soldiers_R, g_list->soldiers_S);
    cout << endl << "DONE" << endl;
    return 1;
}

/**
 * @brief Print generals
 *
 * @return 1 on success
 *         0 on failure
 */
int print_generals() {
    general *g_list = generals_list;
    cout << "    ";
    cout << "GENERALS:" << endl;
    while(g_list != NULL){
        cout << "    ";
        cout << g_list->gid;
        cout << ": ";
        PrintTreeSoldier(g_list->soldiers_R,g_list->soldiers_S);
        cout << endl;
        g_list = g_list->next;
    }
    cout << endl << "DONE" << endl;
    return 1;
}

/**
 * @brief Print registration hashtable
 *
 * @return 1 on success
 *         0 on failure
 */
int print_registration_hashtable() {
    soldier *print_soldiers;
    cout << "     ";
    cout << "Registration list = ";
    for(int i = 0; i < max_soldiers_g; i++){
        print_soldiers = registration_hashtable[i];
        while(print_soldiers != NULL){
            cout << print_soldiers->sid;
            cout << ":";
            cout << print_soldiers->gid;
            print_soldiers = print_soldiers->next;
            cout << "  ";
        }
    }
    cout << endl << "DONE" << endl;
    return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_world() {
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

                /* Maximum soldiers */
            case '0':
                {
                    sscanf(buff, "%c %d", &event, &max_soldiers_g);
                    DPRINT("%c %d\n", event, max_soldiers_g);

                    initialize();

                    break;
                }

                /* Register soldier
                 * R <sid> <gid> */
            case 'R':
                {
                    int sid, gid;

                    sscanf(buff, "%c %d %d", &event, &sid, &gid);
                    DPRINT("%c %d %d\n", event, sid, gid);

                    if ( register_soldier(sid, gid) ) {
                        DPRINT("R %d %d succeeded\n", sid, gid);
                    } else {
                        fprintf(stderr, "R %d %d failed\n", sid, gid);
                    }

                    break;
                }

                /* General or king joins the battlefield
                 * G <gid> */
            case 'G':
                {
                    int gid;

                    sscanf(buff, "%c %d", &event, &gid);
                    DPRINT("%c %d\n", event, gid);

                    if ( add_general(gid) ) {
                        DPRINT("%c %d succeeded\n", event, gid);
                    } else {
                        fprintf(stderr, "%c %d failed\n", event, gid);
                    }

                    break;
                }

                /* Distribute soldier
                 * D */
            case 'D':
                {
                    sscanf(buff, "%c", &event);
                    DPRINT("%c\n", event);

                    if ( distribute() ) {
                        DPRINT("%c succeeded\n", event);
                    } else {
                        fprintf(stderr, "%c failed\n", event);
                    }

                    break;
                }

                /* General resigns from battle
                 * M <gid1> <gid2> */
            case 'M':
                {
                    int gid1, gid2;

                    sscanf(buff, "%c %d %d", &event, &gid1, &gid2);
                    DPRINT("%c %d %d\n", event, gid1, gid2);

                    if ( general_resign(gid1, gid2) ) {
                        DPRINT("%c %d %d succeeded\n", event, gid1, gid2);
                    } else {
                        fprintf(stderr, "%c %d %d failed\n", event, gid1, gid2);
                    }

                    break;
                }

                /* Prepare for battle
                 * P <gid1> <gid2> */
            case 'P':
                {
                    int gid1, gid2;
                    sscanf(buff, "%c %d %d", &event, &gid1, &gid2);
                    DPRINT("%c %d %d\n", event, gid1, gid2);

                    if ( prepare_battle(gid1, gid2) ) {
                        DPRINT("%c %d %d succeeded\n", event, gid1, gid2);
                    } else {
                        fprintf(stderr, "%c %d %d failed\n", event, gid1, gid2);
                    }

                    break;
                }

                /* Battle
                 * B <god_favor> <bit_stream> */
            case 'B':
                {
                    int god_favor;
                    char bit_stream[9];

                    sscanf(buff, "%c %d %s\n", &event, &god_favor, bit_stream);
                    DPRINT("%c %d %s\n", event, god_favor, bit_stream);

                    if ( battle(god_favor, bit_stream, 8) ) {
                        DPRINT("%c %d %s succeeded\n", event, god_favor, bit_stream);
                    } else {
                        fprintf(stderr, "%c %d %s failed\n", event, god_favor, bit_stream);
                    }

                    break;
                }

                /* Cease fire
                 * U */
            case 'U':
                {
                    sscanf(buff, "%c", &event);
                    DPRINT("%c\n", event);

                    if ( cease_fire() ) {
                        DPRINT("%c succeeded\n", event);
                    } else {
                        fprintf(stderr, "%c failed\n", event);
                    }

                    break;
                }

                /* Print general's soldiers
                 * W <gid> */
            case 'W':
                {
                    int gid;

                    sscanf(buff, "%c %d", &event, &gid);
                    DPRINT("%c %d\n", event, gid);

                    if ( print_generals_soldiers(gid) ) {
                        DPRINT("%c %d succeeded\n", event, gid);
                    } else {
                        fprintf(stderr, "%c %d failed\n", event, gid);
                    }

                    break;
                }

                /* Print generals
                 * X */
            case 'X':
                {
                    sscanf(buff, "%c", &event);
                    DPRINT("%c\n", event);

                    if ( print_generals() ) {
                        DPRINT("%c succeeded\n", event);
                    } else {
                        fprintf(stderr, "%c failed\n", event);
                    }

                    break;
                }

                /* Print registration hashtable
                 * Y */
            case 'Y':
                {
                    sscanf(buff, "%c", &event);
                    DPRINT("%c\n", event);

                    if ( print_registration_hashtable() ) {
                        DPRINT("%c succeeded\n", event);
                    } else {
                        fprintf(stderr, "%c failed\n", event);
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

