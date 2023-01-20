/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package java_threading;

/**
 *
 * @author Manos
 */
public class Node {
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
    String subtree;
    double smallest_length;
	
    Node(Point pos, double X, double Y, double Vx, double Vy, double M, int S, double weight_center_x, double weight_center_y, double sum_m) 
    { 
        this.pos = pos; 
        this.X = X;
        this.Y = Y;
        this.Vx = Vx;
        this.Vy = Vy;
        this.M = M;
        this.S = S; 
        this.weight_center_x = weight_center_x;
        this.weight_center_y = weight_center_y;
        this.sum_m = sum_m;
        subtree = "";
    }     
}
