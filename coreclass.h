#include <bits/stdc++.h>
using namespace std;
/*
1. Write a function for taking input of points
2. Both manually, and from a file
*/
double eps = 0.00001;
bool deq(double a, double b)
{
	return (abs(a-b)<eps);
}
bool dlt(double a, double b)
{
	return !deq(a,b) && a<b;
}
bool dgt(double a, double b)
{
	return !deq(a,b) && a>b;
}
bool dle(double a, double b)
{
	return deq(a,b) || dlt(a,b);
}
bool dge(double a, double b)
{
	return deq(a,b) || dgt(a,b);
}
class Point
{
	
	public:
		double x,y;
		void set_coordinates(double x_coor, double y_coor)
		{
			x=x_coor;
			y=y_coor;
		}
		bool liesBelow(Point p)
		{
			return dlt(p.y,y);
		}
		bool liesLeft(Point p)
		{
			return dlt(p.x,x);
		}
		bool sameX(Point p)
		{
			return deq(p.x,x);
		}
		bool sameY(Point p)
		{
			return deq(p.y,y);
		}
		double euclidDist(Point p)
		{
			return ((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
		}
		int orientation(Point q, Point r) 
		{ 
		    double val = (q.y - y) * (r.x - q.x) - 
		              (q.x - x) * (r.y - q.y); 
		  
		    if (deq(val,0)) return 0;  // colinear 
		    return (dgt(val,0))? 1: 2; // 1 = clockwise, 2 = counter-clockwise
		}
		string describe()
		{

			string s = "";
			s+= to_string(x);
			s+= " ";
			s+= to_string(y);
			return s;
		}
		bool Equal(Point q)
		{
			return ((deq(x,q.x))&&(deq(y,q.y)));
		}

		bool notContainedIn(vector<Point> S)
		{
			int i=0;
			for(i=0;i<S.size();i++)
			{
				if(deq(S[i].x,x) && deq(S[i].y,y))
					break;
			}
			return (i==S.size());
		}
};

class Line
{
	public:
		Point Pleft, Pright;
		//SLOPE WILL BE VALID FOR LINES WITH DISSIMILAR X COORDINATES OF END POINTS
		double slope;
		Line(Point p, Point q)
		{
			//THE RESPONSIBILITY TO ARRANGE POINTS IN CORRECT ORDER
			//IS OF THE CONSTRUCTOR.
			if(dle(p.x,q.x))
			{
				Pleft = p;
				Pright = q;
			}
			else
			{
				Pleft = q;
				Pright = p;
			}

			if(!deq(Pleft.x,Pright.x))
				slope = (Pright.y - Pleft.y)/(Pright.x - Pleft.x);
		}
		bool liesOpposite(Point p, Point q)
		{
			/*IF THE LINE IS VERTICAL*/
			if(deq(Pleft.x,Pright.x))
			{
				return (((p.x-Pleft.x)*(q.x-Pleft.x))<0);
			}
			/* LET THE LINE EQUATION BE Y=MX+C */
			else
			{
				double M = slope;
				double C = (Pleft.y - M*Pleft.x);
				return dlt(((p.y - M*p.x - C)*(q.y - M*q.x - C)),0);
			}
			
		}
		bool slopeExists()
		{
			return (!deq(Pleft.x,Pright.x));
		}
};
class ConvexHull
{
	
	public:
		vector<Point> points;
		stack<Point> result_stack;
		int n;
		ConvexHull(Point* input_points, int num)
		{
			n=num;
			for(int i=0;i<n;i++)
				points.push_back(input_points[i]);
			
		}
		ConvexHull(vector<Point> input_points, int num)
		{
			n=num;
			points=input_points;
		}
		//FIND THE LEFTMOST BOTTOMMOST POINT IN THE SET OF INPUT POINTS

		int findAnchor()
		{
			int anchor = 0;
			for(int i = 1; i<n; i++)
				if(points[anchor].liesLeft(points[i]))
					anchor=i;
				else if(points[anchor].sameX(points[i]) && points[anchor].liesBelow(points[i]))
					anchor=i;
			return anchor;
		}

		//FIND THE POINT NEXT TO TOP IN THE GRAHAM STACK
		Point stackNextToTop()
		{
			Point stackTop = result_stack.top();
			result_stack.pop();
			Point stackNextTop = result_stack.top();
			result_stack.push(stackTop);
			return stackNextTop;
		}

		//WRAPPER FOR TOP OF STACK
		Point stackTop()
		{
			return result_stack.top();
		}

		//WRAPPER FOR POPPING OUT OF STACK
		void stackPop()
		{
			result_stack.pop();
		}
		//WRAPPER FOR PUSHING INTO STACK
		void stackPush(Point p)
		{
			result_stack.push(p);
		}
		//SIMPLE FUNCTION TO SWAP TWO POINTS
		void swap(Point &p1, Point &p2)
		{
			Point temp = p1;
			p1 = p2;
			p2 = temp;
		}

		//A SIMPLE RECURSIVE MERGE SORT ROUTINE
		void sortPoints(Point temp[], int low, int high)
		{
			
			//Time complexity : O(nlogn), Space complexity : O(n)
			/*
			Sorting puts points in increasing order of clockwise measure
			So from start to finish - it is a clockwise order
			Whenever the clockwise measure is same - put closer point first
			*/

			if(low>=high)
				return;
			int mid = low + (high-low)/2;
			sortPoints(temp,low,mid);
			sortPoints(temp,mid+1,high);
			int i=low, j=mid+1, k=low;
			
			//Merging step 
			while(i<=mid && j<=high)
			{
				if(deq(points[0].orientation(points[i],points[j]),0))
				{
					if(dle(points[0].euclidDist(points[i]),points[0].euclidDist(points[j])))
						temp[k++]=points[i++];
					else
						temp[k++]=points[j++];
				}
				else if(deq(points[0].orientation(points[i],points[j]),1))
					temp[k++]=points[i++];
				else
					temp[k++]=points[j++];

			}

			while(i<=mid)
				temp[k++]=points[i++];

			while(j<=high)
				temp[k++]=points[j++];

			for(k=low;k<=high;k++)
				points[k]=temp[k];

		}

		void sortClockwise()
		{
			Point* temp = (Point *)malloc(n*sizeof(Point));	
			sortPoints(temp,1,n-1);
		}

		void initiateStack()
		{				
			result_stack.push(points[0]);
			result_stack.push(points[1]);
		}

};

//THIS WILL BE REPLACED BY THE MEDIAN OF MEDIANS ALGORITHM
double kthLargest(vector<double> S, int idx)
{
	vector<double> temp;
	for(int i=0;i<S.size();i++)
		temp.push_back(S[i]);
	sort(temp.begin(), temp.end());
	reverse(temp.begin(), temp.end());
	
	
	return temp[idx];
}

void PRINT(vector<Point> S)
{
	for(int i=0;i<S.size();i++)
		cout<<S[i].describe()<<endl;
	cout<<endl;
}

void visualize(string filename)
{
	
	string command = "python ";
	command += filename;
	system(command.c_str());
}

vector<Point> initialize_input(int n)
{
	vector<Point> S;
	float a = 5; /*GENERATE POINTS BETWEEN 0 and 5*/
    ofstream init_points;
    init_points.open("input_points.txt");
    for(int i=0;i<n;i++)
    {
    	Point P;
    	P.x = (float)rand()/(float)(RAND_MAX/a);
    	P.y = (float)rand()/(float)(RAND_MAX/a);
    	cout<<P.describe()<<endl;
    	init_points<<P.describe()<<endl;
    	S.push_back(P);
    }                                
    init_points.close();
    visualize("vis_ip.py");
    return S;
}
