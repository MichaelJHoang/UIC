#include <iostream>
#include "inst_none.h"
using namespace std;


const int matrixSize = 100;
const int blockingFactor = 50;
int a[matrixSize][matrixSize];
int b[matrixSize][matrixSize];
int c[matrixSize][matrixSize];

int main()
{
        int i, j, k;
        for (i=0; i < matrixSize; i++)
        for (j=0; j < matrixSize; j++) {
        b[i][j] = i + j; c[i][j] = i - j; a[i][j] = 0;
        }

        //OBVIOUS 
        for (i = 0; i < matrixSize; i++)
        {
                for (j = 0; j < matrixSize; j++)
                {
                        for (k = 0; k < matrixSize; k++) {
                                INST_R(b[i][k]);
                                cout << "INST_R b[" << i << "]["<<k<<"]\n";
                                INST_R(c[k][j]);
                                cout << "INST_R c[" << k << "]["<<j<<"]\n";
                                INST_R(a[i][j]);
                        //      a[i][j] += b[i][k]*c[k][j];
                                INST_W(a[i][j]);
                                cout << "INST_W a[" << i << "]["<<j<<"]\n";
                                a[i][j] += b[i][k]*c[k][j];
                        }
                }
        }
/**     
for (i=0; i < matrixSize; i++) {
for (j=0; j < matrixSize; j++) cerr << a[i][j] << ' ';
cerr << endl;
}**/
        return 0;
}
