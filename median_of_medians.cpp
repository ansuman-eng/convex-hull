#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findMedian(vector<int> vec)
{
	//This entire function is O(1)
	int median;
	size_t size = vec.size();
	sort(vec.begin(),vec.end()); //O(1), since the size of vec is atmost 5
	median = vec[(size/2)];
	return median;
}

int findMedianOfMedians(vector<vector<int> > values)
{
	vector<int> medians;
	for(int i=0; i<values.size(); i++)
	{
		int m = findMedian(values[i]);
		medians.push_back(m);
	}

	return findMedian(medians);
}
void print2D(vector<vector<int> > vec2D)
{
	cout<<endl<<endl<<"Printing 2D vector : "<<endl;
    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[i].size(); j++) {
            cout<<vec2D[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void selectionByMedianOfMedians(const vector<int> values, int k)
{
	//Divide list into n/5 lists of 5 elements each
	vector<vector<int> > vec2D;
	int count = 0;
	while(count < values.size())
	{
		int countRow=0;
		vector<int> row;
		while(countRow<5 && count<values.size())
		{
			row.push_back(values[count]);
			count+=1;
			countRow+=1;
		}
		vec2D.push_back(row);
	}
	
	print2D(vec2D);

	//Find a pivot for splits
	int m = findMedianOfMedians(vec2D);

}



int main()
{
	int values[] = {2,3,5,4,1,12,11,13,16,7,8,6,10,9,17,15,19,20,18,23,21,22,25,24,14};
	vector<int> vec(values, values+25);
	cout<<"Given array is : "<<endl;
	for(int i=0; i < vec.size(); i++)
	{
		cout<<vec[i]<<" ";
	}
	cout<<endl;
	selectionByMedianOfMedians(vec, vec.size()/2);
	return 0;
}