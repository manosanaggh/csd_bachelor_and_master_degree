/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package java_threading;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

/**
 *
 * @author Manos
 */
public class ask3_java_one_thread extends Thread {
    static List_node head;
    static int count_sim = 1;
    static int number_of_simulations;

    static void insert_list_node(double X, double Y, double Vx, double Vy, double M, int S){
        List_node new_node = new List_node();
        new_node.X = X;
        new_node.Y = Y;
        new_node.Vx = Vx;
        new_node.Vy = Vy;
        new_node.M = M;
        new_node.S = S;
        new_node.next = null;
        if(head == null){
                head = new_node;
        }
        else{
                List_node temp = head;
                while(temp.next != null){
                        temp = temp.next;
                }
                temp.next = new_node;
        }
    } 

    public void run(){
        while(count_sim <= number_of_simulations){
            FileReader fr;
            BufferedReader br;
            FileWriter fw;
            BufferedWriter bw;
            String s; 
            int numB = 0; 
            int p1 = 1;
            int p2 = 1;
            int i = 0;
            double X;
            double Y;
            double Vx;
            double Vy;
            double M;
            int S; 
            String[] result;
            String[] result2;
            Point[] points = null;
            
            head = null;
            
            Quad center = null;
            
            try
            {
                fr=new FileReader("java_threading/output.txt");
                br=new BufferedReader(fr);

                while((s=br.readLine()) != null)
                {
                  if(i == 0){
                      result = s.split(" ");
                      numB = Integer.parseInt(result[0]);
                      points = new Point[numB];
                      for(int k = 0; k < numB; k++){
                            points[k] = new Point(k+1,k+1);
                      }
                      center = new Quad(new Point(0,0), points[numB-1]);
                      i++;
                      System.out.println(numB);
                  }
                  else if(i == 1){
                      result = s.split(",");
                      result2 = result[0].split(" ");
                      center.minus_R = Double.parseDouble(result2[0]);
                      System.out.print(center.minus_R + " ");
                      center.plus_R = -center.minus_R;
                      System.out.println(center.plus_R);
                      i++;
                  }
                  else{
                      result = s.split(" ");
                      if(p1 <= numB){
                          X = Double.parseDouble(result[0]);
                          Y = Double.parseDouble(result[1]);
                          Vx = Double.parseDouble(result[2]);
                          Vy = Double.parseDouble(result[3]);
                          M = Double.parseDouble(result[4]);
                          S = Integer.parseInt(result[5]);
                          insert_list_node(X, Y, Vx, Vy, M, S);
                          p1++;
                      }
                  }                          
                }
                br.close();
            }
            catch(FileNotFoundException e)
            {
                System.out.println("File was not found!");
            }
            catch(IOException e)    
            { 
                System.out.println("No file found!");
            }

            
            Node[] K = new Node[numB];
            int k = 0;
            
            List_node temp = head; 
            double prev_x = 0;
            double prev_Vx = 0;
            double prev_y = 0;
            double prev_Vy = 0;
            int prev_S = 0;
            double prev_m = 0;
            double sum_m = 0;
            double x = 0;
            double y = 0;
            while(temp != null){
                if(k == 1){
                    sum_m = prev_m + temp.M;
                    x = ((prev_x * prev_m) + (temp.X * temp.M)) / sum_m;
                    y = ((prev_y * prev_m) + (temp.Y * temp.M)) / sum_m;
                    Node a = new Node(points[0],prev_x,prev_y,prev_Vx,prev_Vy,prev_m,prev_S, x, y, sum_m);
                    Node b = a;	
                    K[0] = b;
                    p2++;
                    Node c = new Node(points[k],temp.X,temp.Y,temp.Vx,temp.Vy,temp.M,temp.S, x, y, sum_m);
                    Node d = c;	
                    K[k] = d;
                    p2++;
                }
                if(k > 1){
                    sum_m = prev_m + temp.M;
                    x = ((prev_x * prev_m) + (temp.X * temp.M)) / sum_m;
                    y = ((prev_y * prev_m) + (temp.Y * temp.M)) / sum_m;
                    Node c = new Node(points[k],temp.X,temp.Y,temp.Vx,temp.Vy,temp.M,temp.S, x, y, sum_m);
                    Node d = c;	
                    K[k] = d;
                    p2++;
                } 
                prev_x = temp.X;
                prev_y = temp.Y;
                prev_m = temp.M;
                prev_Vx = temp.Vx;
                prev_Vy = temp.Vy;
                prev_S = temp.S;
                k++;
                temp = temp.next;
            }
            
            System.out.println("----------------------------------");
            
            for(int m = 0; m < numB; m++){
                center.insert((K[m]));
            }

            for(int m = 1; m < p2; m++){center.search(points[m-1]);}

            for(int m = 1; m < p2; m++){
                if(center.search(points[m-1]) == null){System.out.println(m-1);}
                double w_x = center.search(points[m-1]).weight_center_x;
                double w_y = center.search(points[m-1]).weight_center_y;
                for(int n = m + 1; n < p2; n++){
                    double x1 = center.search(points[n-1]).X;
                    double y1 = center.search(points[n-1]).Y;
                    double d = sqrt(pow(w_x - x1, 2) + pow(w_y - y1, 2));

                    if(d > center.search(points[n-1]).smallest_length && !center.search(points[n-1]).subtree.equals(center.search(points[m-1]).subtree)){
                        double SF = 0;
                        for(int q = 1; q < p2; q++){
                            if(center.search(points[q-1]).subtree.equals(center.search(points[m-1]).subtree)){
                                double G = 6.67 * pow(10,-11);
                                double F = (G * (center.search(points[q-1]).M * center.search(points[n-1]).M)) / pow(d, 2); 
                                double Fx = (F * (center.search(points[q-1]).X - center.search(points[n-1]).X)) / d; 
                                double Fy = (F * (center.search(points[q-1]).Y - center.search(points[n-1]).Y)) / d;
                                double ax = Fx / (center.search(points[q-1]).M + center.search(points[n-1]).M);
                                double ay = Fy / (center.search(points[q-1]).M + center.search(points[n-1]).M);
                                center.search(points[q-1]).Vx = center.search(points[q-1]).Vx + ax;
                                center.search(points[q-1]).Vy = center.search(points[q-1]).Vy + ay;
                                center.search(points[n-1]).Vx = center.search(points[n-1]).Vx + ax;
                                center.search(points[n-1]).Vy = center.search(points[n-1]).Vy + ay;
                                center.search(points[q-1]).X = center.search(points[q-1]).X + center.search(points[q-1]).Vx;
                                center.search(points[q-1]).Y = center.search(points[q-1]).Y + center.search(points[q-1]).Vy;
                                center.search(points[n-1]).X = center.search(points[n-1]).X + center.search(points[n-1]).Vx;
                                center.search(points[n-1]).Y = center.search(points[n-1]).Y + center.search(points[n-1]).Vy;
                                SF += F;
                            }
                        }
                        System.out.println("SF_1 = " + SF);
                    }
                    else if(d < center.search(points[n-1]).smallest_length || center.search(points[n-1]).subtree.equals(center.search(points[m-1]).subtree)){
                        int l = 1;
                        double SF = 0;
                        for(int q = 1; q < p2; q++){
                            if(center.search(points[q-1]).subtree.equals(center.search(points[m-1]).subtree)){
                                double G = 6.67 * pow(10,-11);
                                double F = (G * (center.search(points[q-1]).M * center.search(points[n-1]).M)) / pow(d, 2); 
                                double Fx = (F * (center.search(points[q-1]).X - center.search(points[n-1]).X)) / d; 
                                double Fy = (F * (center.search(points[q-1]).Y - center.search(points[n-1]).Y)) / d;
                                double ax = Fx / (center.search(points[q-1]).M + center.search(points[n-1]).M);
                                double ay = Fy / (center.search(points[q-1]).M + center.search(points[n-1]).M);
                                center.search(points[q-1]).Vx = center.search(points[q-1]).Vx + ax;
                                center.search(points[q-1]).Vy = center.search(points[q-1]).Vy + ay;
                                center.search(points[n-1]).Vx = center.search(points[n-1]).Vx + ax;
                                center.search(points[n-1]).Vy = center.search(points[n-1]).Vy + ay;
                                center.search(points[q-1]).X = center.search(points[q-1]).X + center.search(points[q-1]).Vx;
                                center.search(points[q-1]).Y = center.search(points[q-1]).Y + center.search(points[q-1]).Vy;
                                center.search(points[n-1]).X = center.search(points[n-1]).X + center.search(points[n-1]).Vx;
                                center.search(points[n-1]).Y = center.search(points[n-1]).Y + center.search(points[n-1]).Vy;
                                SF += F;
                                l++;
                            }
                        }
                        System.out.println("SF_2 = " + SF);
                    }
                }
            }

            try
            {
                fw=new FileWriter("java_threading/output.txt", true);
                bw=new BufferedWriter(fw);

                bw.write("\n"+numB+"\n");
                bw.write(center.minus_R + " " + center.plus_R + "," + center.plus_R + " " + center.plus_R + "," + center.plus_R 
                        + " " + center.minus_R + "," + center.minus_R + " " + center.minus_R + "\n");
                
                for(int m = 1; m < p2; m++){
                    bw.write(center.search(points[m-1]).X + " " + center.search(points[m-1]).Y + " " + center.search(points[m-1]).Vx + " " + center.search(points[m-1]).Vy
                            + " " + center.search(points[m-1]).M + " " + center.search(points[m-1]).S + "\n"); 
                }                

                bw.close();
            }
            catch(FileNotFoundException e)
            {
                System.out.println("Error1!");
            }
            catch(IOException e)    
            {
                System.out.println("Error2!");
            }
            count_sim++;
        } 
    }
    
    public static void main(String[] args){
        Thread t1 = new ask3_java_one_thread();
        number_of_simulations = Integer.parseInt(args[0]);
        t1.start();
    }
}

