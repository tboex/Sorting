#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void randomizeArray(int* arr, const int size, const int maxNum)
{
   int temp = 0;
   for(int i = 0; i < size; i++)
   {
      temp = rand() % maxNum;
      arr[i] = temp;
   }
}

int main(int argc, char* argv[])
{
   int size = 0;
   int maxNum = 0;
   if(argc > 1)
   {
      static const size_t npos = -1;
      string filename(argv[1]);
      size_t pos = filename.rfind(".txt");
      if(pos != npos)
      {
         ofstream ofile(argv[1]);
	 cout <<"\nEnter array size: \033[1;32m";
         cin >> size;
         cout <<"\033[0mEnter maximum number size: \033[1;32m";
         cin >> maxNum;
         cout <<"\033[0m";

         int arr[size];
         cout <<"\033[1;36mRandomizing\033[0m"<<endl;
         auto t1 = chrono::high_resolution_clock::now();
         randomizeArray(arr,size,maxNum);
         auto t2 = chrono::high_resolution_clock::now();
         cout <<"\033[1;32mFinished\033[0m-\033[1;32m[OUTPUT FILE]\033[0m->\033[1;33m"<<argv[1]<<"\033[0m"<<endl;
	 cout << "\033[1;36mGenerator\033[0m- " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "\033[0m milliseconds" << endl;
         for(int i = 0; i < size; i++)
         {
            ofile <<arr[i]<<"\n";
         }
      }else{
         cout << "\033[1;31m"<<filename<<"\033[0m-\033[1;31mNot a valid file name\033[0m" <<endl;
      }
   }
   return 0;
}
