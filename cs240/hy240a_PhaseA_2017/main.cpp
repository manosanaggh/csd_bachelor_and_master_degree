/************************************************************//**
 * @file   main.c                                      			*
 * @author Antonis Papaioannou <papaioan@csd.uoc.gr>  			*
 *                                                    			*
 * @brief Header function for the needs of cs-240a project 2017 *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "troy.h"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */
#include <iostream>
using namespace std;
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
	    my_combat.soldier_cnt = 0;
	    my_combat.combat_s = NULL;
    	return 1;
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
	int register_soldier (int sid, int gid) {
		if(registration_list == NULL){
			registration_sentinel = (soldier*)malloc(sizeof(soldier));
			registration_sentinel->sid = registration_sentinel->gid = -1;
			registration_list = registration_sentinel;
		}
		soldier *temp;
		temp = (soldier*)malloc(sizeof(soldier));
		temp->sid = sid;
		temp->gid = gid;
		temp->next = registration_list;
		registration_list = temp;

		soldier *temp2 = registration_list;
		cout << "    ";
		cout << "Registration list = ";
		while(temp2 != registration_sentinel){
			cout << temp2->sid;
			cout << ":";
			cout << temp2->gid;
			temp2 = temp2->next;
			if(temp2 != registration_sentinel) cout << ",";
		}

		cout << endl << "DONE" << endl;

		return 1;
	}

	/**
	 * @brief General or King joins the battlefield
	 *
     * @param gid The general's id
	 * @return 1 on success
	 *         0 on failure
	 */
	 int add_general(int gid) {
		if(generals_list == NULL){
			general_sentinel = (general*)malloc(sizeof(general));
			general_sentinel->gid = -1;
			generals_list = general_sentinel;
		}
		general *temp;
		temp = (general*)malloc(sizeof(general));
		temp->gid = gid;
		temp->combats_no = 0;
		temp->next = generals_list;
		generals_list = temp;

		general *temp2 = generals_list;
		cout << "    ";
		cout << "Generals = ";
		while(temp2 != general_sentinel){
			cout << temp2->gid;
			temp2 = temp2->next;
			if(temp2 != general_sentinel) cout << ",";
		}
		cout << endl << "DONE" << endl;

		return 1;
	 }


	/**
	 * @brief Distribute soldiers to the camps
     *
	 * @return 1 on success
	 *         0 on failure
	 */
	int distribute() {
	    soldier *reg_list = registration_list;
	    general *temp_list;
	    DDL_soldier *gen_list_ddl;
	    DDL_soldier *temp2;
	    int key_gid;
	    int key_sid;
		cout << "    ";
		cout << "GENERALS :\n";
	    while(reg_list != registration_sentinel){
	        key_gid = reg_list->gid;
                key_sid = reg_list->sid;
            key_gid = reg_list->gid;
            temp_list = generals_list;
            while(temp_list != general_sentinel && temp_list->gid != key_gid){
                temp_list = temp_list->next;
            }
            gen_list_ddl = temp_list->soldiers_head;
            temp2 = NULL;
            key_sid = reg_list->sid;
            while(gen_list_ddl != NULL && gen_list_ddl->sid < key_sid){
                temp2 = gen_list_ddl;
                gen_list_ddl = gen_list_ddl->next;
            }

            DDL_soldier *new_soldier_to_rest = (DDL_soldier*)malloc(sizeof(DDL_soldier));
            new_soldier_to_rest->sid = key_sid;
            if(gen_list_ddl != NULL) new_soldier_to_rest->next = gen_list_ddl;
            else new_soldier_to_rest->next = NULL;

            if(temp2 == NULL){
                temp_list->soldiers_head = new_soldier_to_rest;
                new_soldier_to_rest->prev = NULL;
            }
            else{
                temp2->next = new_soldier_to_rest;
                new_soldier_to_rest->prev = temp2;
            }

            if(new_soldier_to_rest->next != NULL) new_soldier_to_rest->next->prev = new_soldier_to_rest;
            else temp_list->soldiers_tail = new_soldier_to_rest;
            reg_list = reg_list->next;
        }

        temp_list = generals_list;
        while(temp_list != general_sentinel){
            cout << "    ";
            cout << temp_list->gid;
            cout << ": ";
            gen_list_ddl = temp_list->soldiers_head;
            while(gen_list_ddl != NULL){
                cout << gen_list_ddl->sid;
                gen_list_ddl = gen_list_ddl->next;
                if(gen_list_ddl != NULL) cout << ",";
            }
            cout << endl;
            temp_list = temp_list->next;
        }
        cout << endl << "DONE" << endl;

        return 1;
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
	    general *patroklos = generals_list;
	    general *axileas = generals_list;
	    general *del_prev;
	    general *print_head;
	    DDL_soldier *ax_army;
	    DDL_soldier *patr_army;
	    DDL_soldier *patr_army_prev;
	    DDL_soldier *temp_head;

	    while(patroklos != general_sentinel && patroklos->gid != gid2){
            patroklos = patroklos->next;
	    }

	    while(axileas != general_sentinel && axileas->gid != gid1){
            del_prev = axileas;
            axileas = axileas->next;
	    }
	    ax_army = axileas->soldiers_head;
	    temp_head = patroklos->soldiers_head;
	    while(ax_army != NULL){
            patr_army = temp_head;
            while(patr_army != NULL && patr_army->sid < ax_army->sid){
                patr_army_prev = patr_army;
                patr_army = patr_army->next;
            }
            DDL_soldier *new_soldier_to_rest = (DDL_soldier*)malloc(sizeof(DDL_soldier));
            new_soldier_to_rest->sid = ax_army->sid;
            if(patr_army != NULL) new_soldier_to_rest->next = patr_army;
            else new_soldier_to_rest->next = NULL;

                if(patr_army_prev == NULL){
                    patroklos->soldiers_head = new_soldier_to_rest;
                    new_soldier_to_rest->prev = NULL;
                }
                else{
                    patr_army_prev->next = new_soldier_to_rest;
                    new_soldier_to_rest->prev = patr_army_prev;
                }

            if(new_soldier_to_rest->next != NULL) new_soldier_to_rest->next->prev = new_soldier_to_rest;
            else patroklos->soldiers_tail = new_soldier_to_rest;
            temp_head = patroklos->soldiers_head;
            ax_army = ax_army->next;
	    }
	    del_prev->next = axileas->next;
	    delete axileas;

		cout << "    ";
		cout << "GENERALS :\n";
	    print_head = generals_list;
        while(print_head != general_sentinel){
            cout << "    ";
            cout << print_head->gid;
            cout << ": ";
            temp_head = print_head->soldiers_head;
            while(temp_head != NULL){
                cout << temp_head->sid;
                temp_head = temp_head->next;
                if(temp_head != NULL) cout << ",";
            }
            print_head = print_head->next;
            cout << endl;
        }
        cout << endl << "DONE" << endl;

		return 1;
	}

	/**
	 * @brief Prepare for battle
     *
	 * @param gid1 The id of the first general
     * @param gid2 The id of the second general
     * @param gid3 The id of the third general
      *
	 * @return 1 on success
	 *         0 on failure
	 */
	int prepare_battle(int gid1, int gid2, int gid3) {
	    general *gen1 = (general*)malloc(sizeof(general));
	    general *gen2 = (general*)malloc(sizeof(general));
	    general *gen3 = (general*)malloc(sizeof(general));
	    DDL_soldier *gen1_soldiers_h;
	    DDL_soldier *gen2_soldiers_h;
	    DDL_soldier *gen3_soldiers_h;
	    DDL_soldier *gen1_soldiers_t;
	    DDL_soldier *gen2_soldiers_t;
	    DDL_soldier *gen3_soldiers_t;
	    c_soldier *temp1_soldiers_h = NULL;
	    c_soldier *temp2_soldiers_h = NULL;
	    c_soldier *temp3_soldiers_h = NULL;
	    c_soldier *temp1_soldiers_t = NULL;
	    c_soldier *temp2_soldiers_t = NULL;
	    c_soldier *temp3_soldiers_t = NULL;
	    c_soldier *print_p;
	    int state = 1;
	    general *temp_list;
	    temp_list = generals_list;
	    gen1 = gen2 = gen3 = NULL;

	    while(temp_list != general_sentinel){
            if(temp_list->gid == gid1){
                gen1 = temp_list;
            }
            else if(temp_list->gid == gid2){
                gen2 = temp_list;
            }
            else if(temp_list->gid == gid3){
                gen3 = temp_list;
            }
            temp_list = temp_list->next;
	    }

	    if(gen1 != NULL){
            gen1->combats_no++;
            gen1_soldiers_h = gen1->soldiers_head;
            gen1_soldiers_t = gen1->soldiers_tail;
	    }
	    if(gen2 != NULL){
            gen2->combats_no++;
            gen2_soldiers_h = gen2->soldiers_head;
            gen2_soldiers_t = gen2->soldiers_tail;
	    }
	    if(gen3 != NULL){
            gen3->combats_no++;
            gen3_soldiers_h = gen3->soldiers_head;
            gen3_soldiers_t = gen3->soldiers_tail;
	    }

	    if(gen1 != NULL && gen2 != NULL && gen3 != NULL){
            while(gen1_soldiers_h != gen1_soldiers_t &&
                  gen2_soldiers_h != gen2_soldiers_t &&
                  gen3_soldiers_h != gen3_soldiers_t){
                if(gen1_soldiers_h != gen1_soldiers_t){
                    if(state == 1){
                        c_soldier *new_soldier = (c_soldier*)malloc(sizeof(struct c_soldier));
                        new_soldier->alive = 1;
                        new_soldier->gid = gid1;
                        new_soldier->sid = gen1_soldiers_h->sid;
                        my_combat.soldier_cnt++;
                        if(my_combat.combat_s == NULL) my_combat.combat_s = new_soldier;
                        if(temp3_soldiers_h != NULL) temp3_soldiers_h->next = new_soldier;
                        temp1_soldiers_h = new_soldier;
                        gen1_soldiers_h = gen1_soldiers_h->next;
                    }
                    else if(state == 2){
                        c_soldier *new_soldier2 = (c_soldier*)malloc(sizeof(struct c_soldier));
                        new_soldier2->alive = 1;
                        new_soldier2->gid = gid1;
                        new_soldier2->sid = gen1_soldiers_t->sid;
                        my_combat.soldier_cnt++;
                        if(temp3_soldiers_t != NULL) temp3_soldiers_t->next = new_soldier2;
                        temp1_soldiers_t = new_soldier2;
                        gen1_soldiers_t = gen1_soldiers_t->prev;
                    }
                  }

                    if(gen2_soldiers_h != gen2_soldiers_t){
                        if(state == 1){
                            c_soldier *new_soldier3 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier3->alive = 1;
                            new_soldier3->gid = gid2;
                            new_soldier3->sid = gen2_soldiers_h->sid;
                            my_combat.soldier_cnt++;
                            if(temp1_soldiers_h != NULL) temp1_soldiers_h->next = new_soldier3;
                            temp2_soldiers_h = new_soldier3;
                            gen2_soldiers_h = gen2_soldiers_h->next;
                        }
                        else if(state == 2){
                            c_soldier *new_soldier4 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier4->alive = 1;
                            new_soldier4->gid = gid2;
                            new_soldier4->sid = gen2_soldiers_t->sid;
                            my_combat.soldier_cnt++;
                            if(temp1_soldiers_t != NULL) temp1_soldiers_t->next = new_soldier4;
                            temp2_soldiers_t = new_soldier4;
                            gen2_soldiers_t = gen2_soldiers_t->prev;
                        }
                    }

                    if(gen3_soldiers_h != gen3_soldiers_t){
                        if(state == 1){
                            c_soldier *new_soldier5 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier5->alive = 1;
                            new_soldier5->gid = gid3;
                            new_soldier5->sid = gen3_soldiers_h->sid;
                            my_combat.soldier_cnt++;
                            if(temp2_soldiers_h != NULL) temp2_soldiers_h->next = new_soldier5;
                            temp3_soldiers_h = new_soldier5;
                            gen3_soldiers_h = gen3_soldiers_h->next;
                            state = 2;
                        }
                        else if(state == 2){
                            c_soldier *new_soldier6 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier6->alive = 1;
                            new_soldier6->gid = gid3;
                            new_soldier6->sid = gen3_soldiers_t->sid;
                            my_combat.soldier_cnt++;
                            if(temp2_soldiers_t != NULL) temp2_soldiers_t->next = new_soldier6;
                            temp3_soldiers_t = new_soldier6;
                            gen3_soldiers_t = gen3_soldiers_t->prev;
                            state = 1;
                        }
                    }
                  }
	    }
	    else if(gen1 == NULL && gen2 != NULL && gen3 != NULL){
                cout << gen2_soldiers_t->prev->sid << endl;
                cout << gen3_soldiers_t->prev->sid << endl;
            while(gen2_soldiers_h != gen2_soldiers_t ||
                  gen3_soldiers_h != gen3_soldiers_t){
                    if(gen2_soldiers_h != gen2_soldiers_t){
                        if(state == 1){
                            c_soldier *new_soldier3 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier3->alive = 1;
                            new_soldier3->gid = gid2;
                            if(gen2_soldiers_h != NULL) new_soldier3->sid = gen2_soldiers_h->sid;
                            my_combat.soldier_cnt++;
                            if(my_combat.combat_s == NULL) my_combat.combat_s = new_soldier3;
                            if(temp3_soldiers_h != NULL) temp3_soldiers_h->next = new_soldier3;
                            temp2_soldiers_h = new_soldier3;
                            if(gen2_soldiers_h != NULL)gen2_soldiers_h = gen2_soldiers_h->next;
                            if(gen3_soldiers_h == gen3_soldiers_t) state = 2;
                        }
                        else if(state == 2){
                            c_soldier *new_soldier4 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier4->alive = 1;
                            new_soldier4->gid = gid2;
                            if(gen2_soldiers_t != NULL) new_soldier4->sid = gen2_soldiers_t->sid;
                            my_combat.soldier_cnt++;
                            if(temp3_soldiers_t != NULL) temp3_soldiers_t->next = new_soldier4;
                            temp2_soldiers_t = new_soldier4;
                            if(gen2_soldiers_t != NULL)gen2_soldiers_t = gen2_soldiers_t->prev;
                            if(gen3_soldiers_h == gen3_soldiers_t) state = 1;
                        }
                    }

                    if(gen3_soldiers_h != gen3_soldiers_t){
                        if(state == 1){
                            c_soldier *new_soldier5 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier5->alive = 1;
                            new_soldier5->gid = gid3;
                            if(gen3_soldiers_h != NULL)new_soldier5->sid = gen3_soldiers_h->sid;
                            my_combat.soldier_cnt++;
                            if(temp2_soldiers_h != NULL &&
                               gen2_soldiers_h != gen2_soldiers_t) temp2_soldiers_h->next = new_soldier5;
                            else if(temp3_soldiers_t != NULL &&
                                    gen2_soldiers_h == gen2_soldiers_t) temp3_soldiers_t->next = new_soldier5;
                            temp3_soldiers_h = new_soldier5;
                            if(gen3_soldiers_h != NULL) gen3_soldiers_h = gen3_soldiers_h->next;
                            state = 2;
                        }
                        else if(state == 2){
                            c_soldier *new_soldier6 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier6->alive = 1;
                            new_soldier6->gid = gid3;
                            if(gen3_soldiers_t != NULL) new_soldier6->sid = gen3_soldiers_t->sid;
                            my_combat.soldier_cnt++;
                            if(temp2_soldiers_t != NULL &&
                               gen2_soldiers_h != gen2_soldiers_t) temp2_soldiers_t->next = new_soldier6;
                            else if(temp3_soldiers_h != NULL &&
                                    gen2_soldiers_h == gen2_soldiers_t) temp3_soldiers_h->next = new_soldier6;
                            temp3_soldiers_t = new_soldier6;
                            if(gen3_soldiers_t != NULL) gen3_soldiers_t = gen3_soldiers_t->prev;
                            state = 1;
                        }
                    }
                  }
	    }
	    else if(gen1 != NULL && gen2 == NULL && gen3 != NULL){
            while(gen1_soldiers_h != gen1_soldiers_t &&
                  gen3_soldiers_h != gen3_soldiers_t){
                if(gen1_soldiers_h != gen1_soldiers_t){
                    if(state == 1){
                        c_soldier *new_soldier = (c_soldier*)malloc(sizeof(struct c_soldier));
                        new_soldier->alive = 1;
                        new_soldier->gid = gid1;
                        new_soldier->sid = gen1_soldiers_h->sid;
                        my_combat.soldier_cnt++;
                        if(my_combat.combat_s == NULL) my_combat.combat_s = new_soldier;
                        if(temp3_soldiers_h != NULL) temp3_soldiers_h->next = new_soldier;
                        temp1_soldiers_h = new_soldier;
                        gen1_soldiers_h = gen1_soldiers_h->next;
                    }
                    else if(state == 2){
                        c_soldier *new_soldier2 = (c_soldier*)malloc(sizeof(struct c_soldier));
                        new_soldier2->alive = 1;
                        new_soldier2->gid = gid1;
                        new_soldier2->sid = gen1_soldiers_t->sid;
                        my_combat.soldier_cnt++;
                        if(temp3_soldiers_t != NULL) temp3_soldiers_t->next = new_soldier2;
                        temp1_soldiers_t = new_soldier2;
                        gen1_soldiers_t = gen1_soldiers_t->prev;
                    }
                  }

                    if(gen3_soldiers_h != gen3_soldiers_t){
                        if(state == 1){
                            c_soldier *new_soldier5 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier5->alive = 1;
                            new_soldier5->gid = gid3;
                            new_soldier5->sid = gen3_soldiers_h->sid;
                            my_combat.soldier_cnt++;
                            if(temp1_soldiers_h != NULL) temp1_soldiers_h->next = new_soldier5;
                            temp3_soldiers_h = new_soldier5;
                            gen3_soldiers_h = gen3_soldiers_h->next;
                            state = 2;
                        }
                        else if(state == 2){
                            c_soldier *new_soldier6 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier6->alive = 1;
                            new_soldier6->gid = gid3;
                            new_soldier6->sid = gen3_soldiers_t->sid;
                            my_combat.soldier_cnt++;
                            if(temp1_soldiers_t != NULL) temp1_soldiers_t->next = new_soldier6;
                            temp3_soldiers_t = new_soldier6;
                            gen3_soldiers_t = gen3_soldiers_t->prev;
                            state = 1;
                        }
                    }
                  }
	    }
	    else if(gen1 != NULL && gen2 != NULL && gen3 == NULL){
            while(gen1_soldiers_h != gen1_soldiers_t &&
                  gen2_soldiers_h != gen2_soldiers_t){
                if(gen1_soldiers_h != gen1_soldiers_t){
                    if(state == 1){
                        c_soldier *new_soldier = (c_soldier*)malloc(sizeof(struct c_soldier));
                        new_soldier->alive = 1;
                        new_soldier->gid = gid1;
                        new_soldier->sid = gen1_soldiers_h->sid;
                        my_combat.soldier_cnt++;
                        if(my_combat.combat_s == NULL) my_combat.combat_s = new_soldier;
                        if(temp3_soldiers_h != NULL) temp3_soldiers_h->next = new_soldier;
                        temp1_soldiers_h = new_soldier;
                        gen1_soldiers_h = gen1_soldiers_h->next;
                    }
                    else if(state == 2){
                        c_soldier *new_soldier2 = (c_soldier*)malloc(sizeof(struct c_soldier));
                        new_soldier2->alive = 1;
                        new_soldier2->gid = gid1;
                        new_soldier2->sid = gen1_soldiers_t->sid;
                        my_combat.soldier_cnt++;
                        if(temp3_soldiers_t != NULL) temp3_soldiers_t->next = new_soldier2;
                        temp1_soldiers_t = new_soldier2;
                        gen1_soldiers_t = gen1_soldiers_t->prev;
                    }
                  }

                    if(gen2_soldiers_h != gen2_soldiers_t){
                        if(state == 1){
                            c_soldier *new_soldier3 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier3->alive = 1;
                            new_soldier3->gid = gid2;
                            new_soldier3->sid = gen2_soldiers_h->sid;
                            my_combat.soldier_cnt++;
                            if(temp1_soldiers_h != NULL) temp1_soldiers_h->next = new_soldier3;
                            temp2_soldiers_h = new_soldier3;
                            gen2_soldiers_h = gen2_soldiers_h->next;
                            state = 2;
                        }
                        else if(state == 2){
                            c_soldier *new_soldier4 = (c_soldier*)malloc(sizeof(struct c_soldier));
                            new_soldier4->alive = 1;
                            new_soldier4->gid = gid2;
                            new_soldier4->sid = gen2_soldiers_t->sid;
                            my_combat.soldier_cnt++;
                            if(temp1_soldiers_t != NULL) temp1_soldiers_t->next = new_soldier4;
                            temp2_soldiers_t = new_soldier4;
                            gen2_soldiers_t = gen2_soldiers_t->prev;
                            state = 1;
                        }
                    }
                  }
	    }
        cout << "    ";
		cout << "Combat soldiers : ";
	    print_p = my_combat.combat_s;
	    while(print_p != NULL){
            cout << print_p->sid;
            print_p = print_p->next;
            if(print_p != NULL) cout << ", ";
	    }
	    cout << endl << "DONE" << endl;

		return 1;
	}

	/**
	 * @brief Battle
     *
     * @param god_favor
     *
	 * @return 1 on success
	 *         0 on failure
	 */
	int battle(int god_favor) {
	    if(god_favor == 0){
            float res = ((float)(my_combat.soldier_cnt)*(40))/100;
            int border = (int) res;
            c_soldier* combat_soldiers = my_combat.combat_s;
            int i;
            for(i = 0; i < border; i++){
                if(combat_soldiers != NULL){
                    combat_soldiers->alive = 0;
                    combat_soldiers = combat_soldiers->next;
                }
            }
	    }
	    else{
            c_soldier* combat_soldiers = my_combat.combat_s;
            int count = 1;
            int check_count;
            combat_soldiers->alive = 0;
            while(combat_soldiers != NULL){
                if(count%10 == 0){
                   combat_soldiers->alive = 0;
                }
                count++;
                combat_soldiers = combat_soldiers->next;
            }
	    }

        cout << "    ";
		cout << "Combat soldiers : ";
	    c_soldier* print_p = my_combat.combat_s;
	    while(print_p != NULL){
            cout << print_p->sid;
            cout << ":";
            cout << print_p->alive;
            print_p = print_p->next;
            if(print_p != NULL) cout << ", ";
	    }
	    cout << endl << "DONE" << endl;

		return 1;
	}

	/**
	 * @brief Cease fire
     *
	 * @return 1 on success
	 *         0 on failure
	 */
	int cease_fire() {
	    c_soldier *search_dead = my_combat.combat_s;
	    while(search_dead != NULL){
            if(search_dead->alive == 0){
                general *temp_list = generals_list;
                int key_gid = search_dead->gid;
                int key_sid = search_dead->sid;
                while(temp_list != general_sentinel && temp_list->gid != key_gid){
                    temp_list = temp_list->next;
                }
                DDL_soldier *gen_key_soldiers = temp_list->soldiers_head;
                if(gen_key_soldiers != NULL){
                    while(gen_key_soldiers != NULL && gen_key_soldiers->sid != key_sid){
                        gen_key_soldiers = gen_key_soldiers->next;
                        cout << gen_key_soldiers->sid << endl;
                    }
                    if(gen_key_soldiers->prev != NULL) gen_key_soldiers->prev->next = gen_key_soldiers->next;
                    else temp_list->soldiers_head = gen_key_soldiers->next;
                    if(gen_key_soldiers->next != NULL) gen_key_soldiers->next->prev = gen_key_soldiers->prev;
                    soldier *rl = registration_list;
                    soldier *rl_prev = NULL;
                    while(rl != registration_sentinel){
                        rl_prev = rl;
                        if(rl->sid == gen_key_soldiers->sid){
                            soldier *rl_tbd = rl;
                            rl_prev->next = rl->next;
                            delete rl_tbd;
                        }
                        rl = rl->next;
                    }
                }
                delete gen_key_soldiers;
            }
            search_dead = search_dead->next;
	    }
	    my_combat.soldier_cnt = 0;
	    my_combat.combat_s = NULL;

		cout << "    ";
		cout << "GENERALS :\n";
	    general *print_head = generals_list;
	    DDL_soldier *temp_head;
        while(print_head != general_sentinel){
            cout << "    ";
            cout << print_head->gid;
            cout << ": ";
            temp_head = print_head->soldiers_head;
            while(temp_head != NULL){
                cout << temp_head->sid;
                temp_head = temp_head->next;
                if(temp_head != NULL) cout << ",";
            }
            print_head = print_head->next;
            cout << endl;
        }
        cout << endl << "DONE" << endl;

		return 1;
	}

	/**
	 * @brief Trojan Horse
	 *
	 * @return 1 on success
	 *         0 on failure
	 */
	int trojan_horse() {
	    general *trojanHelp[5];
	    general *temp_list = generals_list;
	    for(int i = 0; i < 5; i++){
	        if(temp_list != general_sentinel) trojanHelp[i] = temp_list;
	        temp_list = temp_list->next;
	    }

	    general *min;
	    int min_combats_no = trojanHelp[0]->combats_no;
	    int min_pos;
	    for(int i = 1; i < 5; i++){
            if(trojanHelp[i]->combats_no < min_combats_no){
                min_combats_no = trojanHelp[i]->combats_no;
                min = trojanHelp[i];
                min_pos = i;
            }
	    }
	    temp_list = generals_list;
	    while(temp_list != general_sentinel){
            if(temp_list->combats_no > min->combats_no){
                trojanHelp[min_pos] = temp_list;
                for(int i = 1; i < 5; i++){
                    if(trojanHelp[i]->combats_no < min_combats_no){
                        min_combats_no = trojanHelp[i]->combats_no;
                        min = trojanHelp[i];
                        min_pos = i;
                    }
                }
            }
            temp_list = temp_list->next;
	    }

		cout << "    ";
		cout << "General = ";
	    general *print_head = generals_list;
        while(print_head != general_sentinel){
            cout << print_head->gid;
            cout << ": ";
            cout << print_head->combats_no;
            if(print_head != general_sentinel) cout << ", ";
            print_head = print_head->next;
        }
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
		cout << "    ";
		cout << "GENERALS :\n";
	    general *print_head = generals_list;
	    DDL_soldier *temp_head;
        while(print_head != general_sentinel){
            cout << "    ";
            cout << print_head->gid;
            cout << ": ";
            temp_head = print_head->soldiers_head;
            while(temp_head != NULL){
                cout << temp_head->sid;
                temp_head = temp_head->next;
                if(temp_head != NULL) cout << ",";
            }
            print_head = print_head->next;
            cout << endl;
        }
        cout << endl << "DONE" << endl;
		return 1;
	}

	/**
	 * @brief Print registration list
	 *
	 * @return 1 on success
	 *         0 on failure
	 */
	int print_registration_list() {
		soldier *temp2 = registration_list;
		cout << "    ";
		cout << "Registration list = ";
		while(temp2 != registration_sentinel){
			cout << temp2->sid;
			cout << ":";
			cout << temp2->gid;
			temp2 = temp2->next;
			if(temp2 != registration_sentinel) cout << ",";
		}

		cout << endl << "DONE" << endl;
		return 1;
	}



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

	initialize();

	/* Read input file buff-by-buff and handle the events */
	while ( fgets(buff, BUFFER_SIZE, fin) ) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

		/* Comment */
		case '#':
			break;

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
		 * P <gid1> <gid2> <gid3> */
		case 'P':
		{
			int gid1, gid2, gid3;
			sscanf(buff, "%c %d %d %d", &event, &gid1, &gid2, &gid3);
			DPRINT("%c %d %d %d\n", event, gid1, gid2, gid3);

			if ( prepare_battle(gid1, gid2, gid3) ) {
				DPRINT("%c %d %d %d succeeded\n", event, gid1, gid2, gid3);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n", event, gid1, gid2, gid3);
			}

			break;
		}

		/* Battle
		 * B <god_favor> */
		case 'B':
		{
			int god_favor;
			sscanf(buff, "%c %d\n", &event, &god_favor);
			DPRINT("%c %d\n", event, god_favor);

			if ( battle(god_favor) ) {
				DPRINT("%c %d succeeded\n", event, god_favor);
			} else {
				fprintf(stderr, "%c %d failed\n", event, god_favor);
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

		/* Trojan Horse
		 * T */
		case 'T':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( trojan_horse() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
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

		/* Print registration list
		 * Y */
		case 'Y':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( print_registration_list() ) {
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

