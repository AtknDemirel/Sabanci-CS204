#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "sparse_matrix_2d_linked_list.h"
using namespace std;

bool structure_is_okay(row_node* head, int num_rows, int num_columns){
    int rows = 0;
    while(head!=nullptr){
        if (rows >= num_rows){
            cout << "Too many rows!\n";
            return false;
        }
        cell_node* cell = head->cell;
        if (cell != nullptr){
            if (cell->left != nullptr){
                cout << "Bad first node!\n";
                return false;
            }
            while (cell!= nullptr){
                if (cell->right != nullptr){
                    if (cell->right->left != cell){
                        cout << "Bad connection!\n";
                        return false;
                    }
                    if (cell->right->column <= cell->column){
                        cout << "Columns should be increasing in a row!\n";
                        return false;
                    }
                }
                if (cell->value ==0){
                    cout << "You can't store zeros in cells!\n";
                    return false;
                }
                if (cell->column >= num_columns){
                    cout << "Too many columns at row " << rows << "!\n";
                    return false;
                }
                cell = cell->right;
            }
        }
        head = head->down;
        rows++;
    }
    if (rows < num_rows){
        cout << "Too few rows!\n";
        return false;
    }
    return true;
}

int main() {
    /////// Timing data ///////
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> total_time;
    //////////////////////////
    string filename1, filename2;
    int m1_rows, m1_cols, m2_rows, m2_cols;
    cout << "Matrix 1 filename: ";
    cin >>filename1;

    cout << "Matrix 2 filename: ";
    cin >>filename2;

    row_node* m1 = read_matrix(filename1, m1_rows, m1_cols);
    structure_is_okay(m1, m1_rows, m1_cols);

    row_node* m2 = read_matrix(filename2, m2_rows, m2_cols);
    structure_is_okay(m2, m2_rows, m2_cols);

    cout << "m1\n";
    print_matrix(m1, m1_rows, m1_cols);

    cout << "m2\n";
    print_matrix(m2, m2_rows, m2_cols);

    if (m1_rows == m2_rows && m1_cols == m2_cols){
        start = chrono::system_clock::now();
        row_node* m3 = add_matrices(m1, m2, m1_rows, m1_cols);
        end = chrono::system_clock::now();
        total_time = end - start;
        cout << "Time to add matrices: " << total_time.count() << " seconds\n";

        structure_is_okay(m3, m2_rows, m2_cols);

        cout << "m3\n";
        print_matrix(m3, m2_rows, m2_cols);
        delete_matrix(m3);
    }
    start = chrono::system_clock::now();
    bool symmetric = is_symmetric(m1, m1_cols, m1_rows);
    end = chrono::system_clock::now();
    total_time = end - start;
    cout << "Time to check if m1 is symmetric: " << total_time.count() << " seconds\n";

    if (symmetric)
        cout << "Matrix m1 is symmetric.\n";
    else
        cout << "Matrix m1 is not symmetric.\n";

    start = chrono::system_clock::now();
    symmetric = is_symmetric(m2, m2_cols, m2_rows);
    end = chrono::system_clock::now();
    total_time = end - start;
    cout << "Time to check if m2 is symmetric: " << total_time.count() << " seconds\n";

    if (symmetric)
        cout << "Matrix m2 is symmetric.\n";
    else
        cout << "Matrix m2 is not symmetric.\n";

    start = chrono::system_clock::now();
//    row_node* m1_transpose = transpose(m1, m1_rows, m1_cols);
//    structure_is_okay(m1_transpose, m1_cols, m1_rows);
    end = chrono::system_clock::now();
    total_time = end - start;
//    cout << "Time to transpose m1: " << total_time.count() << " seconds\n";
//    cout << "m1 transposed\n";
//    print_matrix(m1_transpose, m1_cols, m1_rows);
//    delete_matrix(m1_transpose);

    start = chrono::system_clock::now();
//    row_node* m2_transpose = transpose(m2, m2_rows, m2_cols);
//    structure_is_okay(m2_transpose, m2_cols, m2_rows);
    end = chrono::system_clock::now();
    total_time = end - start;
//    cout << "Time to transpose m2: " << total_time.count() << " seconds\n";
//    cout << "m2 transposed\n";
//    print_matrix(m2_transpose, m2_cols, m2_rows);
//    delete_matrix(m2_transpose);

    delete_matrix(m1);
    delete_matrix(m2);
    return 0;
}
