#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void print(int* arr, int n)
{
   for(int i = 0; i < n; i++)
   {
      cout << arr[i] << ",";
   }
   cout << endl;
}

int getMax(int* arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int* arr, int size, int exp)
{
    int output[size];
    int i, count[10] = {0};
    for (i = 0; i < size; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }
    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (i = size - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }
}

void radixsort(int* arr, const int size)
{
    int m = getMax(arr, size);
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        countSort(arr, size, exp);
    }
}

int main(int argc, char* argv[])
{
   vector<int> myvec;
   int sz = 0;
   if(argc > 1)
   {
      //Checks if input is a file
      static const size_t npos = -1;
      string filename(argv[1]);
      size_t pos = filename.rfind(".txt");
      if(pos != npos)
      {
        cout <<"\n\033[1;32mReading File\033[0m-" <<"\033[1;32m[INPUT FILE]\033[0m->"<<"\033[1;33m"<<argv[1]<<"\033[0m"<<endl;
        int conv = 0;
        string line;
        string finalFile = "sorted-"+(string)argv[1];
        ifstream myfile(argv[1]);
        ofstream ofile(finalFile);
        if(myfile.is_open())
        {
           while(getline(myfile,line))
           {
              conv = atoi(line.c_str());
              myvec.push_back(conv);
           }
           int* arr =myvec.data();
           sz = sizeof(arr)/sizeof(arr[0]);
           cout << "Finished Reading File" << endl;
           myfile.close();
           cout << "\033[1;36mSorting...\033[0m" <<endl;
   	   auto t1 = chrono::high_resolution_clock::now();
           radixsort(arr, myvec.size());
 	   auto t2 = chrono::high_resolution_clock::now();
           for(int i = 0; i <myvec.size(); i++)
           {
              ofile << arr[i] << endl;
           }
           //FINISHED SORTING
           cout << "\033[1;32mFinished Sort\033[0m-" << "\033[1;32m[OUTPUT FILE]\033[0m->\033[1;33m"<<finalFile <<"\033[0m\n"<<endl;
	   cout << "\033[1;36mRadix sort\033[0m- " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "\033[0m milliseconds" << endl;
        }else{
           cout << "\033[1;31mUnable to open file: " <<argv[1] <<"\033[0m" << endl;
        }
      }else{
         cout <<"\033[1;31m"<<argv[1] << "\033[0m-\033[1;31minvalid filetype \033[0m\n" <<endl;
         cout << "Please enter a .txt file" << endl;
      }
   }//If input file exists it is now put into a vector (myvec)
}
