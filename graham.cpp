#include "coreclass.h"
using namespace std;

vector<Point> grahamScan(ConvexHull C)
{
	/*VISUALISATION CODE*/
	ofstream op_points,comp_points;
	op_points.open("output_points.txt",ios::app);
	/*VISUALISATION CODE ENDS*/

	//FIND ANCHOR
	int anchor = C.findAnchor();
	
	//REPLACE ANCHOR WITH FIRST POINT
	C.swap(C.points[0],C.points[anchor]);
	
	//DEBUGGING
	cout<<"ANCHOR "<<C.points[0].x<<" "<<C.points[0].y<<endl;
	

	//SORT IN A CLOCKWISE MANNER
	C.sortClockwise();
	
	/*DEBUGGING
	for(int i=1;i<C.n;i++)
		cout<<C.points[i].x<<" "<<C.points[i].y<<endl;
	*/

	//CREATE STACK
	C.initiateStack();
	
	int cand = 2;
	while(cand<C.n)
	{
		/*while we get a counterclockwise orientation of point next to stack top,
		stack top and the candidate point - in that order -keep popping off points
		*/
		
		/*VIZ CODE STARTS*/
		comp_points.open("graham_compare.txt");
		cout<<C.stackNextToTop().describe()<<endl;
		cout<<C.stackTop().describe()<<endl;
		cout<<C.points[cand].describe()<<endl;

		comp_points<<C.stackNextToTop().describe()<<endl;
		comp_points<<C.stackTop().describe()<<endl;
		comp_points<<C.points[cand].describe()<<endl;
		visualize("graham_compare.py");
		/*VIZ CODE ENDS*/

		while(C.stackNextToTop().orientation(C.stackTop(), C.points[cand])==2)
			C.stackPop();
		//Now push the candidate and increment to consider next point
		C.stackPush(C.points[cand]);
		cand+=1;
	}

	//return C.graham_hull;
	vector<Point> result_hull;

	while(!C.result_stack.empty())
	{
		Point point = C.result_stack.top();
		C.result_stack.pop();
		result_hull.push_back(point);
	
	}

	reverse(result_hull.begin(), result_hull.end());
	return result_hull;

}

int main()
{
	int n;
	

	cout<<"Welcome to GRAHAM SCAN"<<endl;
	cout<<"Enter the number of points"<<endl;
	cin>>n;



	vector<Point> S = initialize_input(n);
    ConvexHull C(S,n);
   

    cout<<"CONVEX HULL OBJECT CREATED"<<endl;
    vector<Point> result_hull = grahamScan(C); 

    for(int i=0;i<result_hull.size();i++)
    	cout<<result_hull[i].x<<" "<<result_hull[i].y<<endl;
    
	return 0;
}