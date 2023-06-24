#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const string &file_name) {
    ifstream fin(file_name);
    if (fin.fail()) {
        throw "File couldn't be opened";
    }
    // actual head_
    head_ = nullptr;
    // head_ of current row
    row_node *curr_head = nullptr;
    // row counter for error checking
    int row = 0;
    fin >> num_rows_ >> num_columns_;
    if (fin.fail()){
        throw "Invalid number of rows or number of columns";
    }
    string line;
    getline(fin, line);
    while (getline(fin, line)) {
        int col = 0, val;
        stringstream ss(line);
        // if this is the first row
        if (head_ == nullptr) {
            head_ = curr_head = new row_node;
        } else {
            curr_head->down = new row_node;
            curr_head = curr_head->down;
        }
        // pointer at last cell added in this row
        cell_node *curr_cell = nullptr;
        while (ss >> val) {
            if (val != 0) {
                cell_node *new_cell = new cell_node;
                new_cell->value = val;
                new_cell->column = col;
                // if first cell in this row
                if (curr_cell == nullptr)
                    curr_head->cell = curr_cell = new_cell;
                else {
                    curr_cell->right = new_cell;
                    curr_cell->right->left = curr_cell;
                    curr_cell = curr_cell->right;
                }
            }
            col++;
            if (col > num_columns_) {
                throw "Too many columns in row " + to_string(row);
            }
        }
        row++;
        if (row > num_rows_) {
            throw "Too many rows";
        }
        if (col < num_columns_) {
            throw "Not enough columns in row " + to_string(row);
        }
    }
    if (row < num_rows_) {
        throw "Not enough rows";
    }
}

SparseMatrix::~SparseMatrix() {
    while (head_ != nullptr) {
        cell_node *cell = head_->cell;
        while (cell != nullptr) {
            cell_node *t = cell->right;
            delete cell;
            cell = t;
        }
        row_node *t = head_->down;
        delete head_;
        head_ = t;
    }
}

ostream &operator<<(ostream &out, const SparseMatrix & rhs) {
    int rows = 0;
    row_node * head = rhs.head_;
    while (head != nullptr) {
        // To know how many zeros to print between cells
        int col = -1;
        cell_node *cell = head->cell;
        while (cell != nullptr) {
            col++;
            // until we get to this cell's column, print zeros
            while (col < cell->column) {
                out << "0 ";
                col++;
            }
            out << cell->value << " ";
            col = cell->column;
            cell = cell->right;
        }
        // If there are more zeros after the last cell in the row,
        // print them
        while (col < rhs.num_columns_ - 1) {
            out << "0 ";
            col++;
        }
        out << endl;
        head = head->down;
        rows++;
    }
    // If there are rows with no cells at all, print zeros for them
    while (rows < rhs.num_rows_) {
        for (int i = 0; i < rhs.num_columns_; i++) {
            out << "0 ";
        }
        out << endl;
        rows++;
    }
    return out;
}

SparseMatrix::SparseMatrix(SparseMatrix&& rhs) {
    head_ = rhs.head_;
    rhs.head_ = nullptr;
    num_rows_ = rhs.num_rows_;
    num_columns_ = rhs.num_columns_;
}

SparseMatrix::SparseMatrix(row_node *head, int num_rows, int num_columns): head_(head), num_rows_(num_rows), num_columns_(num_columns) {}

SparseMatrix::SparseMatrix(const SparseMatrix &rhs): head_(nullptr), num_columns_(rhs.num_columns_), num_rows_(rhs.num_rows_) {
    copy(rhs, head_, num_rows_, num_columns_);
}

SparseMatrix &SparseMatrix::operator=(const SparseMatrix & rhs) {
    if (&rhs != this)
        copy(rhs, head_, num_rows_, num_columns_);
    return *this;
}

void SparseMatrix::copy(const SparseMatrix& rhs, row_node *&head, int &num_rows, int &num_columns) {
    num_rows = rhs.num_rows_;
    num_columns = rhs.num_columns_;
    if (rhs.num_rows_ == 0 || rhs.num_columns_ == 0) return;
    row_node* curr = head = new row_node;
    row_node* other_head = rhs.head_;
    while(other_head!= nullptr){
        cell_node* rhs_cell = other_head->cell;
        cell_node* my_cell = nullptr;
        while (rhs_cell!=nullptr){
            cell_node * new_cell = new cell_node(rhs_cell->column, rhs_cell->value);
            if (my_cell == nullptr) my_cell = curr->cell = new_cell;
            else{
                my_cell->right = new_cell;
                my_cell->right->left = my_cell;
                my_cell = my_cell->right;
            }
            rhs_cell = rhs_cell->right;
        }
        if (other_head->down!=nullptr){
            curr->down = new row_node;
            curr = curr->down;
        }
        other_head = other_head->down;
    }
}

void toVector(const SparseMatrix & SM, vector<vector<int> > & matrix)
{
    
    matrix = vector<vector<int> >(SM.getRowSize(), vector<int>(SM.getColumnSize(), 0));
    row_node * row_head = SM.getHead();
    for(int i=0; i<SM.getRowSize(); i++){
        cell_node* cell_head = row_head -> cell;
        while(cell_head){
            
            int val = cell_head->value;
            int col = cell_head->column;
            matrix[i][col] = val;
            cell_head = cell_head -> right;
        }
        row_head = row_head -> down;
    }
}


void print_mat(vector<vector<int> > & mat){
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat[i].size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}



void row_col_mult(vector<vector<int> > & lhs, vector<vector<int> > & rhs, vector<vector<int> > & result, int row, int col){
    result[row][col] = 0;
    for(int i=0; i<lhs[row].size(); i++)
    {
        result[row][col] += lhs[row][i] * rhs[i][col];
    }
}





SparseMatrix SparseMatrix::mat_mul(const SparseMatrix& rhs) const
{
    vector<vector<int> > matrixLHS, matrixRHS;
    toVector(*this, matrixLHS);
    toVector(rhs, matrixRHS);
    
    
    vector<vector<int> > result(
        matrixLHS.size(),
        std::vector<int>(matrixRHS[0].size()));
    
    
    vector<thread> threads;
    for(int i = 0; i < result.size(); i++)
    {
        for(int j = 0; j < result[0].size(); j++)
        {
            // void row_col_mult(vector<vector<int> > & lhs, vector<vector<int> > & rhs, vector<vector<int> > & result, int row, int col){
            threads.push_back(thread(row_col_mult, std::ref(matrixLHS), std::ref(matrixRHS), std::ref(result), i, j));
        }
    }

    for (auto& th : threads) 
        th.join();

    print_mat(result);
    // convert result to sparse again

    row_node* row_head = NULL;
    row_node* row_tail = NULL;

    for(int i=0; i<result.size(); i++){
        row_node * new_row = new row_node();
        if(!row_head){
            row_head = new_row;
            row_tail = new_row;
        }
        else{
            row_tail->down = new_row;
            row_tail = row_tail->down;
        }
        cell_node * cell_head = NULL;
        cell_node * cell_tail = NULL;
        for(int j=0; j<result[i].size(); j++){
            
            if(result[i][j] != 0){
                cell_node * new_cell = new cell_node(j, result[i][j]);
                if(!cell_head){
                    cell_head = new_cell;
                    cell_tail = new_cell;
                }
                else{
                    cell_tail->right = new_cell;
                    cell_tail = cell_tail->right;
                }
            }
        }
        new_row->cell = cell_head;
    }
    SparseMatrix res_sparse(row_head, result.size(), result[0].size());

    return res_sparse;
}
