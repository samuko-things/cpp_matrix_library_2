// #include "matrix_lib.h"

// template<size_t R, size_t C>
// void Matrix::copy(matrix (&destinationMatrix)[R][C], matrix (&sourceMatrix)[R][C]){
//     for (int r = 0; r < R; r += 1) {
//         for (int c = 0; c < C; c += 1) {
//             destinationMatrix[r][c] = sourceMatrix[r][c];
//         }
//     }
// }

// template<size_t R, size_t C>
// void Matrix::print(matrix (&sourceMatrix)[R][C]){
//     cout << R << " by " << C << " Matrix" << endl;
//     for (int r = 0; r < R; r += 1) {
//         for (int c = 0; c < C; c += 1) {
//         cout << sourceMatrix[r][c] << "\t";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }