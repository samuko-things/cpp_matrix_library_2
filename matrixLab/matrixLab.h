#ifndef MATRIXLAB_h
#define MATRIXLAB_h
#endif

#include <iostream>
#include <math.h>
using namespace std;


const int R_SIZE = 5;
const int C_SIZE = 5;


class Matrix{
    public:
        int rowSize(){
            return row;
        }

        int colSize(){
            return col;
        }

        void writeSize(int r, int c){
            __CLEAR();
            row = r;
            col = c;
        }

        void writeElement(int r_pos, int c_pos, float val){
            if(r_pos<row && c_pos<col){
                data[r_pos][c_pos] = val;
            }
            else{
                cout << "no element exixst at this location" << endl;
            }
        }

        float readElement(int r_pos, int c_pos){
            if(r_pos<row && c_pos<col){
                return data[r_pos][c_pos];
            }
            else{
                cout << "no element exixst at this location" << endl;
                return 0;
            }
        }

        Matrix round(int dp){
            Matrix rounded_matrix;
            rounded_matrix.row = row;
            rounded_matrix.col = col;
            for (int r = 0; r < row; r += 1) {
                    for (int c = 0; c < col; c += 1) {
                        rounded_matrix.data[r][c] = round_dp(data[r][c], dp);
                    }
            }
            return rounded_matrix;
        }

        
        // copy c/c++ array into the matrix object
        template<size_t R, size_t C>
        void copyArray(float (&sourceArray)[R][C]) {
            __CLEAR();
            row = R; col = C;
            for (int r = 0; r < R; r += 1) {
                    for (int c = 0; c < C; c += 1) {
                        data[r][c] = sourceArray[r][c];
                    }
            } 
        }

        // print the matrix
        void print() {
            cout << row << " by " << col << " Matrix" << endl;
            for (int r = 0; r < row; r += 1) {
                for (int c = 0; c < col; c += 1) {
                    cout << data[r][c] << '\t';
                }
                cout << endl;
            }
            cout << endl;
        }

        // transpose the matrix
        Matrix Transpose() {     
            Matrix transposed_matrix;         
            transposed_matrix.row = col; transposed_matrix.col = row;
            for (int r = 0; r < col; r += 1) {
                for (int c = 0; c < row; c += 1) {
                    transposed_matrix.data[r][c] = data[c][r];
                }
            }
            return transposed_matrix;
        }

        Matrix scale(float scalar) {
            Matrix scaled_matrix;
            scaled_matrix.row = row; scaled_matrix.col = col;
            for (int r = 0; r < row; r += 1) {
                for (int c = 0; c < col; c += 1) {
                    scaled_matrix.data[r][c] = data[r][c] * scalar;
                }
            }

            return scaled_matrix;
        }

        Matrix scaleDiv(float scalar) {
            Matrix scaled_matrix;
            scaled_matrix.row = row; scaled_matrix.col = col;
            for (int r = 0; r < row; r += 1) {
                for (int c = 0; c < col; c += 1) {
                    scaled_matrix.data[r][c] = data[r][c] / scalar;
                }
            }

            return scaled_matrix;
        }

        

        float det() {
            if(row == col){
                if (row ==1){
                    det1();
                }
            
                else {
                    float d=0;
                    Matrix minor;
                    for (int c=0; c<col; c+=1){
                        minor = minorElement(0,c);
                        if(c==0 || (c%2)==0) d+=(data[0][c]*minor.det());
                        else d-=(data[0][c]*minor.det());
                    }
                    return d;
                }

            
            }

            else {
                cout << "invalid matrix determinant operation" << endl;
                return 0;
            }   
        }


        Matrix inverse(){
            Matrix inverse_matrix;
            if(row == col){
                float d = det();
                inverse_matrix = minorMatrix();
                inverse_matrix = inverse_matrix.cofactorMatrix();
                inverse_matrix = inverse_matrix.adjointMatrix();
                inverse_matrix = inverse_matrix.scaleDiv(d);
            }
            else{
                cout << "wrong matrix size or dimension" << endl;
            }

           return inverse_matrix; 
        }

private:
        int row, col;
        float data[R_SIZE][C_SIZE];

        float round_dp(float val, int dp){
            float rounded_val = (int)((val*pow(10,dp))+0.5);
            return (float)rounded_val/pow(10,dp);
        }

        // clear the whole matrix object
        void __CLEAR() {
            row = 0;col = 0;
            for (int r = 0; r < R_SIZE; r += 1) {
                for (int c = 0; c < C_SIZE; c += 1) {
                    data[r][c] = 0;
                }
            }
        }
        
        float det1() {
            if(row == col){
                float d=0;
                d = data[0][0];
                return d;
            }  
        }


        Matrix minorElement(int pos_r, int pos_c) {
            Matrix minor;
            minor.row = row-1;
            minor.col = col-1;

            int minor_r = 0, minor_c = 0;

            for(int r=0; r<row; r+=1){

                for(int c=0; c<col; c+=1){
                    if((r==pos_r) || (c==pos_c)) {
                        continue;
                    }
                    else {
                        minor.data[minor_r][minor_c] = data[r][c];
                        minor_c+=1;
                        if(minor_c>=minor.col) minor_c = 0;
                    }
                }

                if(r==pos_r) {
                        continue;
                }
                else {
                    minor_r+=1;
                    if(minor_r>=minor.row) minor_r = 0;
                } 
            }

           return minor;  
        }



        Matrix minorMatrix(){
            Matrix minor_element;
            Matrix minor_matrix;
            minor_matrix.row = row;
            minor_matrix.col = col;

            int minor_r = 0, minor_c = 0;

            for(int r=0; r<row; r+=1){
                for(int c=0; c<col; c+=1){
                    minor_element = minorElement(r,c);	
                    minor_matrix.data[r][c] = minor_element.det();
                }
		    }

           return minor_matrix; 
        }


        Matrix cofactorMatrix(){
            Matrix cofactor_matrix;
            cofactor_matrix.row = row;
            cofactor_matrix.col = col;

            for(int r=0; r<row; r+=1){
                for(int c=0; c<col; c+=1){
                    if((r+c)==0 || ((r+c)%2)==0) cofactor_matrix.data[r][c] = data[r][c];
                    else cofactor_matrix.data[r][c] = -1*data[r][c];
                }
            }
           return cofactor_matrix; 
        }


        Matrix adjointMatrix(){
            Matrix adjoint_matrix;
            adjoint_matrix = Transpose();
           return adjoint_matrix; 
        }
    
};




//////////////////////////// vector class ////////////////////////////////////
class Vector{
    public:
};
///////////////////////////////////////////////////////////////////////////////





////////////////////////  matrices and vector operations ///////////////////////////////////////
class MatrixOperations{
    public:
        Matrix add(Matrix matrix1, Matrix matrix2) {
            Matrix add_matrix;
            if((matrix1.rowSize() == matrix2.rowSize()) && (matrix1.colSize() == matrix2.colSize())){
                int new_row = matrix1.rowSize();
		        int new_col = matrix1.colSize();
                add_matrix.writeSize(new_row, new_col);

                float val;

                for (int r = 0; r < new_row; r += 1) {
                    for (int c = 0; c < new_col; c += 1) {
                        val = matrix1.readElement(r,c) + matrix2.readElement(r,c);
                        add_matrix.writeElement(r,c,val);
                        val = 0;
                    }
                }
                return add_matrix;
            }
            else{
                cout << "ERROR: cannot add matrices, cross check their sizes" << endl;
                return add_matrix;
            }
        }



        Matrix subtract(Matrix matrix1, Matrix matrix2) {
            Matrix sub_matrix;
            if((matrix1.rowSize() == matrix2.rowSize()) && (matrix1.colSize() == matrix2.colSize())){
                int new_row = matrix1.rowSize();
		        int new_col = matrix1.colSize();
                sub_matrix.writeSize(new_row, new_col);

                float val;

                for (int r = 0; r < new_row; r += 1) {
                    for (int c = 0; c < new_col; c += 1) {
                        val = matrix1.readElement(r,c) - matrix2.readElement(r,c);
                        sub_matrix.writeElement(r,c,val);
                        val = 0;
                    }
                }
                return sub_matrix;
            }
            else{
                cout << "ERROR: cannot substract matrices, cross check their sizes" << endl;
                return sub_matrix;
            }
        }

        
        Matrix dotProd(Matrix matrix1, Matrix matrix2) {
            Matrix prod_matrix;
            if(matrix1.colSize() == matrix2.rowSize()){
                int new_row = matrix1.rowSize();
		        int new_col = matrix2.colSize();
                prod_matrix.writeSize(new_row, new_col);

                Matrix T_matrix2;
                T_matrix2 = matrix2.Transpose();
                float val = 0;
                int loop = T_matrix2.colSize();

                for (int r=0; r<new_row; r+=1) {
                    for (int c=0; c<new_col; c+=1) {
                        for (int count = 0; count < loop; count += 1) {
                            val += matrix1.readElement(r,count) * T_matrix2.readElement(c,count);
                        }
                        prod_matrix.writeElement(r,c,val);
                        val = 0;
                    }
                }
                return prod_matrix;
            }
            else{
                cout << "cannot multiply matrices, cross check their sizes" << endl;
                return prod_matrix;
            }
        }	
        
};

MatrixOperations mat;
//////////////////////////////////////////////////////////////////////////////////////////////////////