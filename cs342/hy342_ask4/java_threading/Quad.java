/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package java_threading;

import static java.lang.Math.abs;

/**
 *
 * @author Manos
 */
public class Quad {
    double plus_R, minus_R, temp_R;
    boolean gi = false;
    String str;
    
    // Hold details of the boundary of this node 
    Point topLeft; 
    Point botRight; 
  
    // Contains details of node 
    Node n; 
  
    // Children of this tree 
    Quad topLeftTree; 
    Quad topRightTree; 
    Quad botLeftTree; 
    Quad botRightTree; 
   
    Quad() 
    { 
        topLeft = new Point(0, 0);
        botRight = new Point(0, 0); 
        n = null; 
        topLeftTree  = null; 
        topRightTree = null; 
        botLeftTree  = null; 
        botRightTree = null; 
    } 
    Quad(Point topL, Point botR) 
    { 
        n = null; 
        topLeftTree  = null; 
        topRightTree = null; 
        botLeftTree  = null; 
        botRightTree = null; 
        topLeft = topL; 
        botRight = botR; 
    } 
    
    boolean inBoundary(Point p) 
    { 
        return (p.x >= topLeft.x && 
            p.x <= botRight.x && 
            p.y >= topLeft.y && 
            p.y <= botRight.y); 
    }
    
    void insert(Node node) 
    { 
        if(!gi){
            temp_R = plus_R;
            gi = true;
        }
        else temp_R = temp_R / 2;

        if (node == null) 
            return; 

        // Current quad cannot contain it 
        if (!inBoundary(node.pos)) 
            return; 

        // We are at a quad of unit area 
        // We cannot subdivide this quad further 
        if (abs(topLeft.x - botRight.x) <= 1 && 
            abs(topLeft.y - botRight.y) <= 1) 
        { 
            if (n == null) 
                n = node; 
            n.smallest_length = temp_R;
            gi = false;
            return; 
        } 

        if ((topLeft.x + botRight.x) / 2 >= node.pos.x) 
        { 
            // Indicates topLeftTree 
            if ((topLeft.y + botRight.y) / 2 >= node.pos.y) 
            { 
                if (topLeftTree == null) 
                    topLeftTree = new Quad( 
                        new Point(topLeft.x, topLeft.y), 
                        new Point((topLeft.x + botRight.x) / 2, 
                            (topLeft.y + botRight.y) / 2)); 
                topLeftTree.insert(node); 
            } 

            // Indicates botLeftTree 
            else
            { 
                if (botLeftTree == null) 
                    botLeftTree = new Quad( 
                        new Point(topLeft.x, 
                            (topLeft.y + botRight.y) / 2), 
                        new Point((topLeft.x + botRight.x) / 2, 
                            botRight.y)); 
                botLeftTree.insert(node); 
            } 
        } 
        else
        { 
            // Indicates topRightTree 
            if ((topLeft.y + botRight.y) / 2 >= node.pos.y) 
            { 
                if (topRightTree == null) 
                    topRightTree = new Quad( 
                        new Point((topLeft.x + botRight.x) / 2, 
                            topLeft.y), 
                        new Point(botRight.x, 
                            (topLeft.y + botRight.y) / 2)); 
                topRightTree.insert(node); 
            } 

            // Indicates botRightTree 
            else
            { 
                if (botRightTree == null) 
                    botRightTree = new Quad( 
                        new Point((topLeft.x + botRight.x) / 2, 
                            (topLeft.y + botRight.y) / 2), 
                        new Point(botRight.x, botRight.y)); 
                botRightTree.insert(node); 
            } 
        } 
    }
    

    Node search(Point p) 
    { 
        // Current quad cannot contain it 
        if (!inBoundary(p)) 
            return null; 

        // We are at a quad of unit length 
        // We cannot subdivide this quad further 
        if (n != null){ 
            if(n.subtree == null){
                 n.subtree = str;
            }
            return n; 
        }

        if ((topLeft.x + botRight.x) / 2 >= p.x) 
        { 
            // Indicates topLeftTree 
            if ((topLeft.y + botRight.y) / 2 >= p.y) 
            { 
                if (topLeftTree == null) 
                    return null; 
                str = "topLeftTree";
                return topLeftTree.search(p); 
            } 

            // Indicates botLeftTree 
            else
            { 
                if (botLeftTree == null) 
                    return null; 
                str = "botLeftTree";
                return botLeftTree.search(p); 
            } 
        } 
        else
        { 
            // Indicates topRightTree 
            if ((topLeft.y + botRight.y) / 2 >= p.y) 
            { 
                if (topRightTree == null) 
                    return null; 
                str = "topRightTree";
                return topRightTree.search(p); 
            } 

            // Indicates botRightTree 
            else
            { 
                if (botRightTree == null) 
                    return null; 
                str = "botRightTree";
                return botRightTree.search(p); 
            } 
        } 
    } 
}
