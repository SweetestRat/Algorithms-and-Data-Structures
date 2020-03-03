#include <iostream>
#include <fstream>

using namespace std;

int main()
{
 ifstream fin ("input.txt");
 ofstream fout ("output.txt");

  if(!fin)
  {
    fout << "NO";
  }

 int matrixsize;
 fin >> matrixsize;

 int matrix[matrixsize][matrixsize];
 int count = 0;

  for(int i = 0; i < matrixsize; ++i)
 {
   for(int j = 0; j < matrixsize; ++j)
   {
     fin >> matrix[i][j];
     if(matrix[i][j] == 0)
     count += 1;
   }
 }

 if(count == matrixsize * matrixsize)
 {
     fout << "NO";
 }

 int countdiagonal = 0;
 int countsymmetry = 0;

 for(int i = 0; i < matrixsize; ++i)
 {
     for(int j = 0; j < matrixsize; ++j)
     {
         if(i == j)
         {
             if(matrix[i][j] != 0)
             {
                 countdiagonal += 1;
             }
         }
         else if (i != j)
         {
             if (matrix[i][j] != matrix[j][i])
             {
                 countsymmetry += 1;
             }
         }

     }
 }

 if(countdiagonal > 0 || countsymmetry > 0)
     fout << "NO";
 else
     fout << "YES";

 fin.close();
 fout.close();
return 0;
}
