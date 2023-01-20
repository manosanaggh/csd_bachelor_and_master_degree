#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 
#include <fstream>
#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/queuing_mutex.h>
using namespace std;
using namespace tbb;

struct Point 
{ 
    int x; 
    int y;
    Point(int x, int y) 
    { 
        this->x = x; 
        this->y = y; 
    } 
    Point() 
    { 
        x = 0; 
        y = 0; 
    } 
}; 

struct Node 
{ 
    Point pos; 
    double X;
	double Y;
	double Vx;
	double Vy;
	double M;
	int S;
	double weight_center_x;
	double weight_center_y;
	double sum_m;
    string subtree;
    double smallest_length;
	
    Node(Point pos, double X, double Y, double Vx, double Vy, double M, int S, double weight_center_x, double weight_center_y, double sum_m) 
    { 
        this->pos = pos; 
        this->X = X;
		this->Y = Y;
		this->Vx = Vx;
		this->Vy = Vy;
		this->M = M;
		this->S = S; 
		this->weight_center_x = weight_center_x;
		this->weight_center_y = weight_center_y;
		this->sum_m = sum_m;
        subtree = "";
    } 
    Node() 
    { 
        X = 0;
		Y = 0;
		Vx = 0;
		Vy = 0;
		M = 0;
		S = 0; 
		weight_center_x = 0;
		weight_center_y = 0;
		sum_m = 0;
    } 
	
	void toString(){
		cout << this->X << " ";
		cout <<  this->Y << " ";
		cout <<  this->Vx << " ";
		cout <<  this->Vy << " ";
		cout <<  this->M << " ";
		cout <<  this->S << " ";
		cout <<  this->weight_center_x << " ";
		cout <<  this->weight_center_y << " ";
		cout <<  this->sum_m << " ";
		cout << this->subtree << endl;
	}
};

class Quad 
{ 
    // Hold details of the boundary of this node 
    Point topLeft; 
    Point botRight; 
  
    // Contains details of node 
    Node *n; 
  
    // Children of this tree 
    Quad *topLeftTree; 
    Quad *topRightTree; 
    Quad *botLeftTree; 
    Quad *botRightTree; 
  
public: 
    Quad() 
    { 
        topLeft = Point(0, 0); 
        botRight = Point(0, 0); 
        n = NULL; 
        topLeftTree  = NULL; 
        topRightTree = NULL; 
        botLeftTree  = NULL; 
        botRightTree = NULL; 
    } 
    Quad(Point topL, Point botR) 
    { 
        n = NULL; 
        topLeftTree  = NULL; 
        topRightTree = NULL; 
        botLeftTree  = NULL; 
        botRightTree = NULL; 
        topLeft = topL; 
        botRight = botR; 
    } 
    void insert(Node*); 
    Node* search(Point); 
    bool inBoundary(Point);
};

double plus_R, minus_R, temp_R;
bool gi = false;
void Quad::insert(Node *node) 
{ 
    if(!gi){
        temp_R = plus_R;
        gi = true;
    }
    else temp_R = temp_R / 2;

    if (node == NULL) 
        return; 
  
    // Current quad cannot contain it 
    if (!inBoundary(node->pos)) 
        return; 
  
    // We are at a quad of unit area 
    // We cannot subdivide this quad further 
    if (abs(topLeft.x - botRight.x) <= 1 && 
        abs(topLeft.y - botRight.y) <= 1) 
    { 
        if (n == NULL) 
            n = node; 
        n->smallest_length = temp_R;
        gi = false;
        return; 
    } 
  
    if ((topLeft.x + botRight.x) / 2 >= node->pos.x) 
    { 
        // Indicates topLeftTree 
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) 
        { 
            if (topLeftTree == NULL) 
                topLeftTree = new Quad( 
                    Point(topLeft.x, topLeft.y), 
                    Point((topLeft.x + botRight.x) / 2, 
                        (topLeft.y + botRight.y) / 2)); 
            topLeftTree->insert(node); 
        } 
  
        // Indicates botLeftTree 
        else
        { 
            if (botLeftTree == NULL) 
                botLeftTree = new Quad( 
                    Point(topLeft.x, 
                        (topLeft.y + botRight.y) / 2), 
                    Point((topLeft.x + botRight.x) / 2, 
                        botRight.y)); 
            botLeftTree->insert(node); 
        } 
    } 
    else
    { 
        // Indicates topRightTree 
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) 
        { 
            if (topRightTree == NULL) 
                topRightTree = new Quad( 
                    Point((topLeft.x + botRight.x) / 2, 
                        topLeft.y), 
                    Point(botRight.x, 
                        (topLeft.y + botRight.y) / 2)); 
            topRightTree->insert(node); 
        } 
  
        // Indicates botRightTree 
        else
        { 
            if (botRightTree == NULL) 
                botRightTree = new Quad( 
                    Point((topLeft.x + botRight.x) / 2, 
                        (topLeft.y + botRight.y) / 2), 
                    Point(botRight.x, botRight.y)); 
            botRightTree->insert(node); 
        } 
    } 
} 

string str;
Node* Quad::search(Point p) 
{ 
    // Current quad cannot contain it 
    if (!inBoundary(p)) 
        return NULL; 
  
    // We are at a quad of unit length 
    // We cannot subdivide this quad further 
    if (n != NULL){ 
        if(n->subtree.compare("") == 0){
             n->subtree = str;
        }
        return n; 
    }
  
    if ((topLeft.x + botRight.x) / 2 >= p.x) 
    { 
        // Indicates topLeftTree 
        if ((topLeft.y + botRight.y) / 2 >= p.y) 
        { 
            if (topLeftTree == NULL) 
                return NULL; 
            str = "topLeftTree";
            return topLeftTree->search(p); 
        } 
  
        // Indicates botLeftTree 
        else
        { 
            if (botLeftTree == NULL) 
                return NULL; 
            str = "botLeftTree";
            return botLeftTree->search(p); 
        } 
    } 
    else
    { 
        // Indicates topRightTree 
        if ((topLeft.y + botRight.y) / 2 >= p.y) 
        { 
            if (topRightTree == NULL) 
                return NULL; 
            str = "topRightTree";
            return topRightTree->search(p); 
        } 
  
        // Indicates botRightTree 
        else
        { 
            if (botRightTree == NULL) 
                return NULL; 
            str = "botRightTree";
            return botRightTree->search(p); 
        } 
    } 
}; 

bool Quad::inBoundary(Point p) 
{ 
    return (p.x >= topLeft.x && 
        p.x <= botRight.x && 
        p.y >= topLeft.y && 
        p.y <= botRight.y); 
}

struct list_node{
    double X;
	double Y;
	double Vx;
	double Vy;
	double M;
	int S; 
	list_node *next;
};

list_node *head  = NULL;

list_node *insert_list_node(double X, double Y, double Vx, double Vy, double M, int S){
	list_node *new_node = (list_node*)malloc(sizeof(list_node));
	new_node->X = X;
	new_node->Y = Y;
	new_node->Vx = Vx;
	new_node->Vy = Vy;
	new_node->M = M;
	new_node->S = S;
	new_node->next = NULL;
	if(head == NULL){
		head = new_node;
	}
	else{
		list_node *temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = new_node;
	}
	return head;
}

int main(int argc, char** argv){
    int number_of_simulations = atoi(argv[1]);
    static queuing_mutex m;
    
    task_scheduler_init init(4);
    parallel_for(blocked_range<size_t>(0, number_of_simulations, 1),
    [=](const blocked_range<size_t>& r) -> void{
    //for(int count_sim = 1; count_sim <= number_of_simulations; count_sim++){
        for(size_t count_sim = r.begin(); count_sim != r.end(); count_sim++ ){
            queuing_mutex::scoped_lock lock(m);
            int numB; 
            int p1 = 1;
            int p2 = 1;
            fstream fp("output.txt", ios::in | ios::out);
            int i = 0;
            double X;
            double Y;
            double Vx;
            double Vy;
            double M;
            int S; 
            string s;
            vector<string> result;
            vector<string> result2;
            head = NULL;
            
            while(getline(fp, s)){
                if(i == 0){
                    boost::split(result, s, boost::is_any_of(" "));
                    numB = atoi(result[0].c_str());
                    i++;
                    printf("%d\n",numB);
                }
                else if(i == 1){
                    boost::split(result, s, boost::is_any_of(","));
                    boost::split(result2, result[0], boost::is_any_of(" "));
                    minus_R = atof(result2[0].c_str());
                    cout << minus_R << " ";
                    plus_R = -minus_R;
                    cout << plus_R << endl;
                    i++;
                }
                else{
                    boost::split(result, s, boost::is_any_of(" "));
                    if(p1 <= numB){
                        X = atof(result[0].c_str());
                        Y = atof(result[1].c_str());
                        Vx = atof(result[2].c_str());
                        Vy = atof(result[3].c_str());
                        M = atof(result[4].c_str());
                        S = atoi(result[5].c_str());
                        head = insert_list_node(X, Y, Vx, Vy, M, S);
                        p1++;
                    }
                }
            }
            Node K[numB];
            int k = 0;
            Quad center(Point(0, 0), Point(numB, numB));
            
            list_node *temp = head; 
            double prev_x;
            double prev_Vx;
            double prev_y;
            double prev_Vy;
            int prev_S;
            double prev_m;
            double sum_m;
            double x;
            double y;
            while(temp != NULL){
                if(k == 1){
                    sum_m = prev_m + temp->M;
                    x = ((prev_x * prev_m) + (temp->X * temp->M)) / sum_m;
                    y = ((prev_y * prev_m) + (temp->Y * temp->M)) / sum_m;
                    Node *a = new Node(Point(p2,p2),prev_x,prev_y,prev_Vx,prev_Vy,prev_m,prev_S, x, y, sum_m);
                    Node b = *a;	
                    K[0] = b;
                    p2++;
                    Node *c = new Node(Point(p2,p2),temp->X,temp->Y,temp->Vx,temp->Vy,temp->M,temp->S, x, y, sum_m);
                    Node d = *c;	
                    K[k] = d;
                    p2++;
                }
                if(k > 1){
                    sum_m = prev_m + temp->M;
                    x = ((prev_x * prev_m) + (temp->X * temp->M)) / sum_m;
                    y = ((prev_y * prev_m) + (temp->Y * temp->M)) / sum_m;
                    Node *c = new Node(Point(p2,p2),temp->X,temp->Y,temp->Vx,temp->Vy,temp->M,temp->S, x, y, sum_m);
                    Node d = *c;	
                    K[k] = d;
                    p2++;
                } 
                prev_x = temp->X;
                prev_y = temp->Y;
                prev_m = temp->M;
                prev_Vx = temp->Vx;
                prev_Vy = temp->Vy;
                prev_S = temp->S;
                k++;
                temp = temp->next;
            }
            
            cout << "----------------------------------" << endl;
            
            for(int m = 0; m < numB; m++){
                center.insert(&(K[m]));
            }

            for(int m = 1; m < p2; m++){center.search(Point(m,m));}

            for(int m = 1; m < p2; m++){
                double w_x = center.search(Point(m,m))->weight_center_x;
                double w_y = center.search(Point(m,m))->weight_center_y;
                for(int n = m + 1; n < p2; n++){
                    double x = center.search(Point(n,n))->X;
                    double y = center.search(Point(n,n))->Y;
                    double d = sqrt(pow(w_x - x, 2) + pow(w_y - y, 2));

                    if(d > center.search(Point(n,n))->smallest_length && center.search(Point(n,n))->subtree.compare(center.search(Point(m,m))->subtree) != 0){
                        double SF = 0;
                        for(int q = 1; q < p2; q++){
                            if(center.search(Point(q,q))->subtree.compare(center.search(Point(m,m))->subtree) == 0){
                                double G = 6.67 * pow(10,-11);
                                double F = (G * (center.search(Point(q,q))->M * center.search(Point(n,n))->M)) / pow(d, 2); 
                                double Fx = (F * (center.search(Point(q,q))->X - center.search(Point(n,n))->X)) / d; 
                                double Fy = (F * (center.search(Point(q,q))->Y - center.search(Point(n,n))->Y)) / d;
                                double ax = Fx / (center.search(Point(q,q))->M + center.search(Point(n,n))->M);
                                double ay = Fy / (center.search(Point(q,q))->M + center.search(Point(n,n))->M);
                                center.search(Point(q,q))->Vx = center.search(Point(q,q))->Vx + ax;
                                center.search(Point(q,q))->Vy = center.search(Point(q,q))->Vy + ay;
                                center.search(Point(n,n))->Vx = center.search(Point(n,n))->Vx + ax;
                                center.search(Point(n,n))->Vy = center.search(Point(n,n))->Vy + ay;
                                center.search(Point(q,q))->X = center.search(Point(q,q))->X + center.search(Point(q,q))->Vx;
                                center.search(Point(q,q))->Y = center.search(Point(q,q))->Y + center.search(Point(q,q))->Vy;
                                center.search(Point(n,n))->X = center.search(Point(n,n))->X + center.search(Point(n,n))->Vx;
                                center.search(Point(n,n))->Y = center.search(Point(n,n))->Y + center.search(Point(n,n))->Vy;
                                SF += F;
                            }
                        }
                        cout << "SF_1 = " << SF << endl;
                    }
                    else if(d < center.search(Point(n,n))->smallest_length || center.search(Point(n,n))->subtree.compare(center.search(Point(m,m))->subtree) == 0){
                        int l = 1;
                        double SF = 0;
                        for(int q = 1; q < p2; q++){
                            if(center.search(Point(q,q))->subtree.compare(center.search(Point(m,m))->subtree) == 0 && l <= 4){
                                double G = 6.67 * pow(10,-11);
                                double F = (G * (center.search(Point(q,q))->M * center.search(Point(n,n))->M)) / pow(d, 2); 
                                double Fx = (F * (center.search(Point(q,q))->X - center.search(Point(n,n))->X)) / d; 
                                double Fy = (F * (center.search(Point(q,q))->Y - center.search(Point(n,n))->Y)) / d;
                                double ax = Fx / (center.search(Point(q,q))->M + center.search(Point(n,n))->M);
                                double ay = Fy / (center.search(Point(q,q))->M + center.search(Point(n,n))->M);
                                center.search(Point(q,q))->Vx = center.search(Point(q,q))->Vx + ax;
                                center.search(Point(q,q))->Vy = center.search(Point(q,q))->Vy + ay;
                                center.search(Point(n,n))->Vx = center.search(Point(n,n))->Vx + ax;
                                center.search(Point(n,n))->Vy = center.search(Point(n,n))->Vy + ay;
                                center.search(Point(q,q))->X = center.search(Point(q,q))->X + center.search(Point(q,q))->Vx;
                                center.search(Point(q,q))->Y = center.search(Point(q,q))->Y + center.search(Point(q,q))->Vy;
                                center.search(Point(n,n))->X = center.search(Point(n,n))->X + center.search(Point(n,n))->Vx;
                                center.search(Point(n,n))->Y = center.search(Point(n,n))->Y + center.search(Point(n,n))->Vy;
                                SF += F;
                                l++;
                            }
                        }
                        cout << "SF_2 = " << SF << endl;
                    }
                }
            }

            fp.clear();

            fp << endl << numB << endl;
            fp << minus_R << " " << plus_R << "," << plus_R << " " << plus_R << "," << plus_R << " " << minus_R << "," << minus_R << " " << minus_R << endl;

            for(int m = 1; m < p2; m++){
                fp << center.search(Point(m,m))->X << " " << center.search(Point(m,m))->Y << " " << center.search(Point(m,m))->Vx << " " << center.search(Point(m,m))->Vy <<
                " " << center.search(Point(m,m))->M << " " << center.search(Point(m,m))->S << endl; 
            }
            lock.release();
        }
    }
    );
	return 0;
}
