//
//  ActivityBST.hpp
//  atakan.demirel_Demirel_Atakan
//
//  Created by Atakan Demirel on 24.11.2022.
//

#ifndef ActivityBST_h
#define ActivityBST_h

#include <stdio.h>
#include <string>

using namespace std;

struct tree_node {
    int time;
    string activity;
    tree_node *right;
    tree_node *left;
    tree_node *parent;
    tree_node(int t, const string &a) : time(t), activity(a),
                                        right(nullptr), left(nullptr),
                                        parent(nullptr) {}
};

class ActivityBST
{
private:
    tree_node* root;
    
public:
    //ActivityBST(tree_node* ptr = nullptr): root(ptr){}
    ActivityBST();
    ActivityBST(const ActivityBST& copy);
    ~ActivityBST();
    
    void add(int time, const string & activity);
    
    void deepCopyHelper(tree_node* root, ActivityBST& newCal, const ActivityBST &copy);
    
    ActivityBST & operator = (const ActivityBST & calendar);
    ActivityBST operator + (const ActivityBST & rhs) const;
    ActivityBST operator += (const ActivityBST & calendar);
    friend ostream & operator << (ostream & out, const ActivityBST & calendar);
};


#endif /* ActivityBST_h */
