//
//  ActivityBST.cpp
//  atakan.demirel_Demirel_Atakan
//
//  Created by Atakan Demirel on 24.11.2022.
//

#include "ActivityBST.h"
#include <iostream>
using namespace std;

ActivityBST::ActivityBST()
{
    root = nullptr;
}

void ActivityBST::deepCopyHelper(tree_node* node, ActivityBST& newCal, const ActivityBST &copy)
{
    if (node == NULL)
        return;
    deepCopyHelper(node -> left, newCal, copy);
    newCal.add(node -> time, node -> activity);
    deepCopyHelper(node -> right, newCal, copy);
}

ActivityBST::ActivityBST(const ActivityBST& copy)
{
    root = nullptr;
    tree_node* node = copy.root;
    deepCopyHelper(node, *this, copy);
}

void delete_tree(tree_node *root)
{
    if (root == NULL)
        return;
    
    delete_tree(root -> left);
    delete_tree(root -> right);
    delete root;
}

ActivityBST::~ActivityBST()
{
    delete_tree(root);
}

string fill_with_zeros(int num_zeros, const string& input){
    unsigned long zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}

string number_to_time(int number){
    if (number >2359 || number < 0) return "ERROR";
    return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2, to_string(number%100));
}

bool not_legal_time(string timestamp)
{
    short int hour = stoi(timestamp.substr(0,2));
    short int minute = stoi(timestamp.substr(3,2));
    return (hour < 0 || minute < 0 || hour > 23 || minute > 59);
}

void end_of_tree(tree_node *&leaf, int time)
{
    while (leaf -> right != nullptr && leaf -> left != nullptr)
    {
        if (time < leaf -> time)
        {
            leaf = leaf -> left;
        }
        else
        {
            leaf = leaf -> right;
        }
    }
}

void ActivityBST::add(int time, const string & activity)
{
    string timestamp = number_to_time(time);
    if (timestamp == "ERROR" || not_legal_time(timestamp))
    {
        return;
    }
    if (root == nullptr)
    {
        root = new tree_node(time, activity);
        return;
    }
    
    tree_node * leaf = root;
    while (true)
    {
        end_of_tree(leaf, time);
        if (leaf -> right == nullptr && leaf -> left == nullptr)
        {
            if (time == leaf -> time)   break;
            if (time > leaf -> time)
            {
                tree_node * last = new tree_node(time, activity);
                leaf -> right = last;
                last -> parent = leaf;
                break;
            }
            else
            {
                tree_node * last = new tree_node(time, activity);
                leaf -> left = last;
                last -> parent = leaf;
                break;
            }
        }
        else if (leaf -> right == nullptr)
        {
            if (time == leaf -> time)   break;
            if (time > leaf -> time)
            {
                tree_node * last = new tree_node(time, activity);
                leaf -> right = last;
                last -> parent = leaf;
                break;
            }
            else
            {
                leaf = leaf -> left;
                continue;
            }
        }
        else if (leaf -> left == nullptr)
        {
            if (time == leaf -> time)   break;
            if (time < leaf -> time)
            {
                tree_node * last = new tree_node(time, activity);
                leaf -> left = last;
                last -> parent = leaf;
                break;
            }
            else
            {
                leaf = leaf -> right;
                continue;
            }
        }
        if (time == leaf -> time)   break;
            
        tree_node * last = new tree_node(time, activity);
        if (time < leaf -> time)
        {
            leaf -> left = last;
            last -> parent = leaf;
        }
        else
        {
            leaf -> right = last;
            last -> parent = leaf;
        }
    }
    return;
}

ActivityBST & ActivityBST::operator = (const ActivityBST & rhs) //deep copy
{
    delete_tree(this -> root);
    ActivityBST res(rhs);
    return *this;
}

ActivityBST ActivityBST::operator += (const ActivityBST & rhs)
{
    if (rhs.root == nullptr)
        return *this;
    deepCopyHelper(rhs.root, *this, rhs);
    return *this;
}

ActivityBST ActivityBST::operator + (const ActivityBST & rhs) const
{
    ActivityBST final;
    final += *this;
    final += rhs;
    return final;
}

void print_all_activities(tree_node *root, ostream & out)
{
    if (root == NULL)
        return;
    
    print_all_activities(root -> left, out);
    out << "[" << number_to_time(root -> time) << "] - " << root -> activity << "\n";
    print_all_activities(root -> right, out);
}

ostream & operator << (ostream & out, const ActivityBST & calendar)
{
    print_all_activities(calendar.root, out);
    return out;
}
