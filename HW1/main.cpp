 //
//  main.cpp
//  atakan.demirelhw1.cpp
//
//  Created by Atakan Demirel on 7.10.2022.
//

// return code 1: filename error
// return code 2: file content error

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h> //used for stol(), to_string()

using namespace std;

//checks if correct file is opened
bool fileError(const string filename, ifstream & file)
{
    file.open(filename.c_str());
    if (file.fail())
    {
        return true;
    }
    return false;
}

//forms vector from rhs and returns false if invalid
bool RHS2vec(ifstream & RHSfile, vector<int> & rhs)
{
    int num, row, column, count = 0;
    
    while(!RHSfile.eof())
    {
        if (RHSfile >> num)
        {
            if (count == 0)
            {
                row = num;
                count++;
                continue;
            }
            else if (count == 1)
            {
                column = num;
                count++;
                continue;
            }
            else
            {
                if (num >= 1 && num <= 9)
                {
                    rhs.push_back(num);
                }
                else
                {
                    return false;
                }
                
            }
        }
    }
    return rhs.size() == row && column == 1;
}

//prev. func. w/o checking n <= 9
bool RES2vec(ifstream & RESfile, vector<int> & res)
{
    int num, row, column, count = 0;
    
    while(!RESfile.eof())
    {
        if (RESfile >> num)
        {
            if (count == 0)
            {
                row = num;
                count++;
                continue;
            }
            if (count == 1)
            {
                column = num;
                count++;
                continue;
            }
            if (num >= 1)
            {
                res.push_back(num);
            }
            else
            {
                return false;
            }
        }
    }
    return res.size() == row && column == 1;
}

//forms 2D vector from txt file and returns false if invalid
//
bool txt2matrix(ifstream & LHSfile, vector<vector<int>> & LHSmatrix)
{
    int num, row, column, count = 0;
    
    while(!LHSfile.eof())
    {
        if (LHSfile >> num)
        {
            if (count == 0)
            {
                row = num;
                count++;
                continue;
            }
            if (count == 1)
            {
                column = num;
                count++;
                continue;
            }
            
            count++;
            if (count == 4) //invalid if file still continues after given row & column numbers
            {
                return false;
            }
            vector<int> lineVec;
            for(int i = 0; i < row; i++)
            {
                for(int k = 0; k < column; k++)
                {
                    if ((num >= 1 && num <= 9) || num == -1)
                    {
                        lineVec.push_back(num);
                        LHSfile >> num;
                    }
                    else
                    {
                        return false;
                    }
                }
                LHSmatrix.push_back(lineVec);
                lineVec.clear();
            }
        }
    }
    return row == LHSmatrix.size() && column == LHSmatrix[0].size();
}

void sort(const vector<int> RHSvec, const vector<vector<int>> LHSvec,
               const vector<int> RESvec, vector<vector<int>> & outvec, vector<int> & RESfinal)
{
    unsigned int sum;
    vector<int> outlines; //row and column part of outfile
    for(int i = 0; i < LHSvec.size(); i++)
    {
        bool unknown = false;
        sum = 0;
        for (int k = 0; k < LHSvec[0].size(); k++)
        {
            int product = LHSvec[i][k] * RHSvec[k];
            if (product > 0)
            {
                sum += product;
            }
            else // add row and column to vector if
            {
                unknown = true; //there is a -1 in row
                outlines.push_back(i);
                outlines.push_back(k);
                outlines.push_back(-product);
                outvec.push_back(outlines);
                outlines.clear();
            }
        }
        if (unknown) // only the corresponding result of rows that have a -1 are added
        {
            RESfinal.push_back(RESvec[i] - sum);
            unknown = false;
        }
    }
}

//calculates the values missing in lhs
void calculate(vector<vector<int>> & outvec, vector<int> RESfinal)
{
    vector<int> sameRow;
    unsigned int outidxstop, outidxstart, RESidx = 0;
    for (int i = 0; i < outvec.size(); i++)
    {
        outidxstart = i;
        outidxstop = i;
        sameRow.push_back(outvec[i][2]);
        if (i < outvec.size() - 1)
        {
            while (outvec[i][0] == outvec[i + 1][0]) //checks if the next element is in the same row
            {
                i++;
                sameRow.push_back(outvec[i][2]);
                outidxstop = i;
                if (!(i < outvec.size() - 1))
                {
                    break;
                }
            }
        }
        unsigned long intnum, sum = 0;
        string strnum = "";
        for (int z = 0; z < sameRow.size(); z++)
        {
            strnum += "1";
        }
        for (int y = sameRow.size() - 1; y >= 0; y--) //calculates sum for the smallest case
        {
            char coefficient = strnum.at(y);
            sum += (int(coefficient) - int('0')) * sameRow[y];
        }
        while(sum != RESfinal[RESidx])
        {
            sum = 0;
            intnum = stol(strnum);
            intnum++;
            strnum = to_string(intnum);
            if (strnum.find("0") != string::npos)
            {
                continue;
            }
            for (int y = sameRow.size() - 1; y >= 0; y--)
            {
                char coefficient = strnum.at(y);
                sum += (int(coefficient) - int('0')) * sameRow[y];
            }
        }
        sameRow.clear();
        if (outidxstart != outidxstop)
        {
            unsigned int numidx = 0;
            for (int q = outidxstart; q <= outidxstop; q++)
            {
                int unknown = int(strnum.at(numidx)) - int('0');
                outvec[q][2] = unknown;
                numidx++;
            }
        }
        else
        {
            outvec[i][2] = stoi(strnum);
        }
        RESidx++;
    }
}


int main()
{
    //inputting file names
    ifstream LHSfile, RHSfile, RESfile;
    ofstream outfile;
    string LHSname, RHSname, RESname, outname;
    cout << "Enter LHS matrix filename: ";
    cin >> LHSname;
    cout << "Enter RHS matrix filename: ";
    cin >> RHSname;
    cout << "Enter RES filename: ";
    cin >> RESname;
    cout << "Enter output filename: ";
    cin >> outname;
    
    //checking name of output file
    outfile.open(outname.c_str());
    if (outfile.fail())
    {
        cout << "Error! (wrong output file)";
        return 1;
    }
    
    //checking name of opened files
    if (fileError(LHSname, LHSfile) || fileError(RHSname, RHSfile) || fileError(RESname, RESfile))
    {
        cout << "Error! (filename)";
        outfile << "Error";
        return 1;
    }
    
    vector<int> RHSvec;
    
    //returns error if rhs content is faulty
    if (!RHS2vec(RHSfile, RHSvec))
    {
        cout << "Error! (Rhs content)";
        outfile << "Error";
        return 2;
    }
    
    vector<int> RESvec;
    
    //returns error if res content is faulty
    if (!RES2vec(RESfile, RESvec))
    {
        cout << "Error! (Res content)";
        outfile << "Error";
        return 2;
    }
    
    vector<vector<int>> LHSmat;
    
    if (!txt2matrix(LHSfile, LHSmat))
    {
        cout << "Error! (Lhs content)";
        outfile << "Error";
        return 2;
    }
    
    vector<vector<int>> outvector;
    vector<int> RESfinal;
    
    sort(RHSvec, LHSmat, RESvec, outvector, RESfinal);
    
    calculate(outvector, RESfinal);
    
    for (int j = 0; j < outvector.size(); j++)
    {
        for (int p = 0; p < outvector[0].size(); p++)
        {
            outfile << outvector[j][p];
            if (p < outvector[0].size() - 1)
            {
                outfile << " ";
            }
        }
        outfile << "\n";
    }
    
    RESfile.close();
    RHSfile.close();
    LHSfile.close();
    outfile.close();
    
    return 0;
}
