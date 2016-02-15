#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool checkSorted(int* arr, const int size)
{
   bool val = true;
   for(int i = 0; i< size-1; i++)
   {
      if(arr[i]>arr[i+1])
      {
         val = false;
      }
   }
   return val;
}//Checks if the array is sorted

int main(int argc, char* argv[])
{
   vector<int> myvec;
   bool sorted = false;
   int sz = 0;
   string line="";
   int conv = 0;
   if(argc >1)
   {
      string filename(argv[1]);
      size_t pos = filename.rfind(".txt");
      ifstream myfile(argv[1]);
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
         cout << "\033[1;36mChecking if Sorted...\033[0m" <<endl;
         auto t1 = chrono::high_resolution_clock::now();
	 sorted = checkSorted(arr,sz);
         auto t2 = chrono::high_resolution_clock::now();
	 if(sorted == true)
         {
	    cout <<"Array is Sorted - [\033[1;32mX\033[0m]" <<endl;
         }else{
	    cout <<"Array is Sorted - [ ]" <<endl;
         }
         cout << "\033[1;36mSort Check\033[0m- " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "\033[0m milliseconds" << endl;
      }else{
         cout << "\033[1;31mUnable to open file: " <<argv[1] <<"\033[0m" << endl;
      }
   }else{
      cout <<"\033[1;31mEnter a Valid Filename\033[0m"<<endl;
   }
   return 0;
}
