//
//  main.cpp
//  atakan.demirel_Demirel_Atakan_2.cpp
//
//  Created by Atakan Demirel on 25.10.2022.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cctype> //functions to remove whitespace when reading from txt
#include "sparse_matrix_2d_linked_list.h"


using namespace std;

row_node* read_matrix(const string& filename, int& num_rows, int& num_columns)
{
    ifstream matrix;
    matrix.open(filename.c_str());
    
    string line;
    getline(matrix, line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end()); //removes whitespace
    num_rows = int(line.at(0)) - int('0');
    num_columns = int(line.at(1)) - int('0');
    
    int val;
    unsigned int row = 0;
    
    row_node * row_nd = new row_node();
    row_node * head = row_nd;
    while (getline(matrix, line))
    {

        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end()); //removes whitespace
        
        bool not_empty = false;
        for (int l = 0; l < line.length(); l++)
        {
            if (line.at(l) != '0')
            {
                not_empty = true;
                break;
            }
        }
        
        if (not_empty)
        {
            cell_node * cell_nd = new cell_node();
            row_nd -> cell = cell_nd;
            bool negative = false;
            int column = -1;
            
            for (int i = 0; i < line.length(); i++)
            {
                column++;
                if (line.at(i) == '-')
                {
                    negative = true;
                    column -= 1;
                    continue;
                }
                if(line.at(i) != '0')
                {
                    val = int(line.at(i)) - int('0');
                    if (negative)
                    {
                        val *= -1;
                    }
                    cell_nd -> value = val;
                    cell_nd -> column = column;
                    string remaining = line.substr(i + 1, line.length());
                    bool last = true;
                    for (int p = 0; p < remaining.length(); p++)
                    {
                        if (remaining.at(p) != '0')
                        {
                            last = false;
                            break;
                        }
                    }
                    if (last)
                    {
                        cell_nd -> right = NULL;
                        break;
                    }
                    else
                    {
                        cell_node * cell_next = new cell_node();
                        cell_nd -> right = cell_next;
                        cell_next -> left = cell_nd;
                        cell_nd = cell_next;
                    }
                }
                negative = false;
            }
        }
        
        if (row < num_rows - 1)
        {
            row_node * row_new = new row_node();
            row_nd -> down = row_new;
            row_nd = row_new;
        }
        else
        {
            row_nd -> down = NULL;
        }
        row++;
    }
    return head;
}

void print_matrix(row_node* head, int num_rows, int num_columns)
{
    row_node* traverser = head;
    cell_node* cn;
    
    for (int row = 0; row < num_rows; row++)
    {
        cn = traverser -> cell;
        for (int column = 0; column < num_columns; column++)
        {
            if (cn == NULL)
            {
                cout << "0 ";
                continue;
            }
            if (cn -> column > column)
            {
                cout << "0 ";
                continue;
            }
            if (cn -> column == column)
            {
                cout << cn -> value << " ";
                cn = cn -> right;
            }
        }
        cout << "\n";
        traverser = traverser -> down;
    }
}

// deletes the data of the matrix pointed at by `head`
void delete_matrix(row_node* head)
{
    row_node* traverser = head;
    row_node* dummy_traverser = nullptr;
    cell_node * cn = head -> cell;
    
    while (traverser -> down != NULL)
    {
        while (cn -> right != NULL)
        {
            cn = cn -> right;
            delete cn -> left;
        }
        delete cn;
        
        dummy_traverser = traverser -> down;
        delete traverser;
        traverser = dummy_traverser;
        cn = traverser -> cell;
    }
    while (cn -> right != NULL)
    {cn = cn -> right; delete cn -> left;}
    delete traverser;
    delete cn;
    
    
}

// Adds two matrices, one pointed at by `left` and the other pointed at by `right`.
// Both matrices will have `num_rows` rows, and `num_columns` columns.
row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns)
{
    row_node* row_res = new row_node();
    row_node* head = row_res;
    cell_node* cn_left, * cn_right;
    
    for (int row = 0; row < num_rows; row++)
    {
        bool left_empty = false;
        bool right_empty = false;
        cn_left = left -> cell;
        if (cn_left == NULL)
        {
            left_empty = true;
        }
        
        cn_right = right -> cell;
        if (cn_right == NULL)
        {
            right_empty = true;
        }
        
        cell_node* cn_res = new cell_node();
        row_res -> cell = cn_res;
        int sum = 0;
        bool non_zero_left, non_zero_right, go_right, go_left;
        for (int column = 0; column < num_columns; column++)
        {
            sum = 0;
            non_zero_left = false;
            non_zero_right = false;
            go_right = false;
            go_left = false;
            
            if (cn_left != NULL && cn_left -> column == column)
            {
                sum += cn_left -> value;
                
                if (cn_left -> right != NULL)
                {
                    go_left = true;
                }
                non_zero_left = true;
            }
            if (cn_right != NULL && cn_right -> column == column)
            {
                sum += cn_right -> value;
                if (cn_right -> right != NULL)
                {
                    go_right = true;
                }
                non_zero_right = true;
            }
            if (non_zero_left || non_zero_right)
            {
                cn_res -> column = column;
                cn_res -> value = sum;
                if ((!left_empty && cn_left -> right != NULL) ||
                    (!right_empty && cn_right -> right != NULL))
                {
                    cell_node* cn_next = new cell_node();
                    cn_res -> right = cn_next;
                    cn_next -> left = cn_res;
                    cn_res = cn_next;
                }
            }
            if(go_left)
            {
                cn_left = cn_left -> right;
            }
            if(go_right)
            {
                cn_right = cn_right -> right;
            }
        }
        if (row < num_rows - 1)
        {
            row_node* row_next = new row_node();
            row_res -> down = row_next;
            row_res = row_next;
            left = left -> down;
            right = right -> down;
        }
        else
        {
            row_res -> down = NULL;
        }
    }
    return head;
}

// Checks if the matrix pointed at by `head` with `num_rows` rows and `num_column` columns
// is symmetric or not.
bool is_symmetric(row_node* head, int num_rows, int num_columns)
{
    cell_node * cn_linear = new cell_node();
    cell_node * cn_vertical = new cell_node();
    row_node * rw_linear = head;
    row_node * rw_vertical = head;
    
    if (num_rows == 1 && num_columns == 1)
    {
        return true;
    }
    return false;
}

// Generate a new sparse matrix that is the transpose of the matrix pointed at by
// `head` with `num_rows` rows and `num_columns` columns
row_node* transpose(row_node* head, int num_rows, int num_columns)
{
    return head;
}
