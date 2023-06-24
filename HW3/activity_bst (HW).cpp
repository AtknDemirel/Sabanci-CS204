//
//  main.cpp
//  atakan.demirel_Demirel_Atakan_3
//
//  Created by Atakan Demirel on 7.11.2022.
//

#include <iostream>
#include "activity_bst.h"
using namespace std;

//given func
string fill_with_zeros(int num_zeros, const string& input){
unsigned long zeros_to_add = num_zeros - input.length();
if (zeros_to_add < 0) zeros_to_add = 0;
return string(zeros_to_add, '0') + input;
}

//given func
string number_to_time(int number){
if (number >2359 || number < 0) return "ERROR";
return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2, to_string(number%100));
}

//given func
bool not_legal_time(string timestamp)
{
    short int hour = stoi(timestamp.substr(0,2));
    short int minute = stoi(timestamp.substr(3,2));
    return (hour < 0 || minute < 0 || hour > 23 || minute > 59);
}

//traverses to node where the new node will be added
void traverse_tree(tree_node *&leaf, int time)
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


// Add an activity with name 'activity' and time 'time'
void add_activity(tree_node *&root, int time, const string &activity)
{
    string timestamp = number_to_time(time);
    if (timestamp == "ERROR" || not_legal_time(timestamp))
    {
        cout << "ERROR! Could not add activity '" << activity << "' due to illegal time value" << "\n";
        return;
    }
    
    if (root == nullptr)
    {
        root = new tree_node(time, activity);
        cout << "Added activity '" << activity << "' at " << timestamp << "\n";
        return;
    }
    
    tree_node * leaf = root;
    while (true)
    {
        traverse_tree(leaf, time);
        if (leaf -> right == nullptr && leaf -> left == nullptr)
        {
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
    
    cout << "Added activity '" << activity << "' at " << timestamp << "\n";
    return;
}

// Print the name of the activity occurring at time 'time'
void print_activity(tree_node *root, int time)
{
    string timestamp = number_to_time(time);
    if (not_legal_time(timestamp))
    {
        cout << "ERROR! Could not print activity at specific time due to illegal time" << "\n";
        return;
    }
    
    tree_node * leaf = root;
    int difference, smallest;
    string activity;
    if (root == nullptr)
    {
        cout << "Time: " << timestamp << ", Activity: free" << "\n";
        return;
    }
    while (leaf -> left != nullptr)
    {
        leaf = leaf -> left;
    }
    if (leaf -> time > time)
    {
        cout << "Time: " << timestamp << ", Activity: free" << "\n";
        return;
    }
    
    //prints activity with the smallest positive difference
    leaf = root;
    difference = time - leaf -> time;
    if (difference < 0)
    {
        smallest = 2400;
    }
    else
    {
        smallest = difference;
        activity = leaf -> activity;
    }
    
    while (!(leaf -> right == nullptr && leaf -> left == nullptr))
    {
        if (leaf -> time == time)
        {
            cout << "Time: " << timestamp << ", Activity: " << leaf -> activity << "\n";
            return;
        }
        else if (time < leaf -> time)
        {
            if (leaf -> left == nullptr)
            {
                cout << "Time: " << timestamp << ", Activity: " << activity << "\n";
                return;
            }
            else
            {
                leaf = leaf -> left;
                difference = time - leaf -> time;
                if (difference >= 0 && difference < smallest)
                {
                    activity = leaf -> activity;
                    smallest = difference;
                }
            }
        }
        else if (time > leaf -> time)
        {
            if (leaf -> right == nullptr)
            {
                cout << "Time: " << timestamp << ", Activity: " << activity << "\n";
                return;
            }
            else
            {
                leaf = leaf -> right;
                difference = time - leaf -> time;
                if (difference >= 0 && difference < smallest)
                {
                    activity = leaf -> activity;
                    smallest = difference;
                }
            }
        }
    }
    cout << "Time: " << timestamp << ", Activity: " << activity << "\n";
}


// Print the duration of the activity occurring at time 'time'
void print_activity_and_duration(tree_node *root, int time)
{
    string timestamp = number_to_time(time);
    
    if (timestamp == "ERROR" || not_legal_time(timestamp))
    {
        cout << "ERROR! Could not check due to illegal time value" << "\n";
        return;
    };
    
    tree_node * leaf = root;
    tree_node * target = root;
    int difference, smallest, start = 0, end = 2400;
    string activity;
    
    if (root == nullptr)
    {
        cout << "Time period: [00:00 - 00:00]: free" << "\n";
        return;
    }
    while (leaf -> left != nullptr)
    {
        leaf = leaf -> left;
    }
    if (leaf -> time > time)
    {
        start = 0;
        end = leaf -> time;
        cout << "Time period: " << "[" << number_to_time(start) << " - " << number_to_time(end) << "]: free" << "\n";
        return;
    }
    
    leaf = root;
    difference = time - leaf -> time;
    if (difference < 0)
    {
        smallest = 2400;
    }
    else
    {
        smallest = difference;
        activity = leaf -> activity;
    }
    
    while (!(leaf -> right == nullptr && leaf -> left == nullptr))
    {
        if (leaf -> time == time)
        {
            target = leaf;
            start = leaf -> time;
            smallest = 0;
            break;
        }
        else if (time < leaf -> time)
        {
            if (leaf -> left == nullptr)
            {
                break;
            }
            else
            {
                leaf = leaf -> left;
                difference = time - leaf -> time;
                if (difference >= 0 && difference < smallest)
                {
                    target = leaf;
                    start = leaf -> time;
                    smallest = difference;
                }
            }
        }
        else if (time > leaf -> time)
        {
            if (leaf -> right == nullptr)
            {
                break;
            }
            else
            {
                leaf = leaf -> right;
                difference = time - leaf -> time;
                if (difference >= 0 && difference < smallest)
                {
                    target = leaf;
                    start = leaf -> time;
                    smallest = difference;
                }
            }
        }
    }
    bool after = false;
    leaf = target;
    
    while (leaf -> parent != nullptr)
    {
        leaf = leaf -> parent;
        if (leaf -> time > time)
        {
            after = true;
            end = leaf -> time;
            break;
        }
    }
    
    if (target -> right != nullptr)
    {
        after = true;
        leaf = target -> right;
        while (leaf -> left != nullptr)
        {
            leaf = leaf -> left;
        }
        if (leaf -> time < end)
        {
            end = leaf -> time;
        }
    }
    if (after)
    {
        cout << "Time period: " << "[" << number_to_time(target -> time) << " - " << number_to_time(end) << "]: "
        << target -> activity << "\n";
    }
    else
    {
        cout << "Time period: " << "[" << number_to_time(target -> time) << " - 00:00]: "<< target -> activity << "\n";
    }
}



// Print the duration of every occurrence of activity 'activity'
void print_single_activity(tree_node *root, const string &activity)
{
    // special case in case user wants to know free time
    if (activity == "free")
    {
        if (root == nullptr)
        {
            cout << "Time period: [00:00 - 00:00]: free" << "\n";
            return;
        }
        else
        {
            tree_node * node = root;
            while(node -> left != nullptr)
            {
                node = node -> left;
            }
            if (node -> time != 0)
            {
                cout << "Time period: " << "[00:00 - " << number_to_time(node -> time) << "]: free" << "\n";
                return;
            }
            else
                return;
        }
    }
    
    if (root == NULL)
        return;
 
    print_single_activity(root->left, activity);
 
    if (root -> activity == activity)
        print_activity_and_duration(root, root -> time);
 
    print_single_activity(root -> right, activity);
}

// Print the starting time of every activity
void print_all_activities(tree_node *root)
{
    if (root == NULL)
        return;
    
    print_all_activities(root -> left);
    
    cout << "[" << number_to_time(root -> time) << "] - " << root -> activity << "\n";
    
    print_all_activities(root -> right);
}

// Delete the tree pointed at by `root`
void delete_tree(tree_node *root)
{
    if (root == NULL)
        return;
    
    delete_tree(root -> left); // deletes left subtree
    delete_tree(root -> right); // deletes right subtree
    delete root; // deletes particular node
}
