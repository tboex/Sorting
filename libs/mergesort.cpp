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
vector<int> merge(vector<int>&, const vector<int>&, const vector<int>& );
vector<int> mergesort(vector<int>& myvec)
{
   if(myvec.size() == 1)
   {
      return myvec;
   }
   vector<int>::iterator middle = myvec.begin() + (myvec.size()/2);
   vector<int> left(myvec.begin(), middle);
   vector<int> right(middle, myvec.end());
   left = mergesort(left);
   right = mergesort(right);
   return merge(myvec,left,right);
}

vector<int> merge(vector<int>& vec, const vector<int>& left, const vector<int>& right)
{
    vector<int> result;
    unsigned left_it = 0, right_it = 0;
    while(left_it < left.size() && right_it < right.size())
    {
        if(left[left_it] < right[right_it])
        {
            result.push_back(left[left_it]);
            left_it++;
        }else{
            result.push_back(right[right_it]);
            right_it++;
        }
    }
    while(left_it < left.size())
    {
        result.push_back(left[left_it]);
        left_it++;
    }
    while(right_it < right.size())
    {
        result.push_back(right[right_it]);
        right_it++;
    }
   vec = result;
   return vec;
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
           int* tempArr = arr;
           sz = sizeof(arr)/sizeof(arr[0]);
           cout << "Finished Reading File" << endl;
           myfile.close();
           cout << "\033[1;36mSorting...\033[0m" <<endl;
           auto t1 = chrono::high_resolution_clock::now();
	   myvec = mergesort(myvec);
           auto t2 = chrono::high_resolution_clock::now();
           for(int i = 0; i <myvec.size(); i++)
           {
              ofile << myvec[i] << endl;
           }
           //FINISHED SORTING
           cout << "\033[1;32mFinished Sort\033[0m-" << "\033[1;32m[OUTPUT FILE]\033[0m->\033[1;33m"<<finalFile <<"\033[0m\n"<<endl;
	   cout << "\033[1;36mMerge Sort\033[0m- " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "\033[0m milliseconds" << endl;
        }else{
           cout << "\033[1;31mUnable to open file: " <<argv[1] <<"\033[0m" << endl;
        }
      }else{
         cout <<"\033[1;31m"<<argv[1] << "\033[0m-\033[1;31minvalid filetype \033[0m\n" <<endl;
         cout << "Please enter a .txt file" << endl;
      }
   }//If input file exists it is now put into a vector (myvec)
}
