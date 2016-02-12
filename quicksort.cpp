#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void  swap(int i, int j, int *a)
{
   int temp = a[i];
   a[i] = a[j];
   a[j] = temp;
}

void quicksort(int *arr, int left, int right)
{
   int middle = left + (right-left)/2;
   int l = left;
   int r = right;
   int pivot = arr[middle];

   while(left < r || l <right)
   {
      while(arr[l]<pivot)
      {
         l++;
      }
      while(arr[r]>pivot)
      {
         r--;
      }
      if(l<=r)
      {
         swap(l,r,arr);
         l++;
         r--;
      }else
      {
         if(left<r)
         {
            quicksort(arr,left,r);
         }
         if(l<right)
         {
            quicksort(arr,l,right);
         }
         return;
      }
   }
}

int main(int argc, char* argv[])
{
   if(argc > 1)
   {
      //Checks if input is a file
      static const size_t npos = -1;
      string filename(argv[1]);
      size_t pos = filename.rfind(".txt");
      if(pos != npos)
      {
        cout <<"Reading File..." <<endl;
        vector<int> myvec;
        int conv = 0;
        string line;
        ifstream myfile(argv[1]);
        if(myfile.is_open())
        {
           while(getline(myfile,line))
           {
              conv = atoi(line.c_str());
              myvec.push_back(conv);
           }
           cout << "Finished Reading File" << endl;
           myfile.close();
        }else{
           cout << "\033[1;31mUnable to open file: " <<argv[1] <<"\033[0m" << endl;
        }
      }else{
         cout <<"\033[1;31m"<<argv[1] << "\033[0m-\033[1;31minvalid filetype \033[0m\n" <<endl;
         cout << "Please enter a .txt file" << endl;
      }
   }//If input file exists it is now put into a vector (myvec)
}
