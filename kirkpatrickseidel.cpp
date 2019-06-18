//CONTAINS THE DEFINITIONS OF FUNCTIONS FOR UPPER BRIDGE AND LOWER BRIDGE
#include "kshull.h"

vector<Point> KS(vector<Point> points, int n)
{
	Point pUMax = maxXCoordinate(points,1);
	Point pUMin = minXCoordinate(points,1);
	Point pLMax = maxXCoordinate(points,0);
	Point pLMin = minXCoordinate(points,0);

	cout<<"pUMax "<<pUMax.describe()<<endl;
	cout<<"pUMin "<<pUMin.describe()<<endl;
	cout<<"pLMax "<<pLMax.describe()<<endl;
	cout<<"pLMin "<<pLMin.describe()<<endl;

	
	/*UHULL WILL HAVE UPPER HULL POINTS IN CLOCKWISE ORDER*/
	cout<<"UPPER HULL CALCULATING..."<<endl;
	vector<Point> uHull = upperHull(pUMin,pUMax,points);
	
	/*LHULL WILL HAVE LOWER HULL POINTS IN CLOCKWISE ORDER*/
	cout<<"LOWER HULL CALCULATING..."<<endl;
	vector<Point> lHull = lowerHull(pLMin,pLMax,points);
	/*RESULT_HULL WILL HAVE ALL HULL POINTS IN CLOCKWISE ORDER*/
	vector<Point> result_hull;
	/*INSERT THE UPPER HULL AS IS*/
	for(int i=0;i<uHull.size();i++)
		result_hull.push_back(uHull[i]);
	
	/*TO INSERT THE LOWER HULL WE NEED TO CHECK ITS FIRST AND LAST POINTS FOR DUPLICATION*/
	for(int i=0;i<lHull.size();i++)
	{
		
		if((i==0 || i==(lHull.size()-1)) && lHull[i].notContainedIn(result_hull))
		{
			
			result_hull.push_back(lHull[i]);
		}
		else if(i!=0 && i!=(lHull.size()-1))
			result_hull.push_back(lHull[i]);
	}
	
	return result_hull;
	/*RETURN THE ANSWER - CLOCKWISE ORDER OF POINTS*/
	
	
}

int main()
{
	int n;
	double x,y;
	cout<<"Welcome to KIRKPATRICK-SEIDEL - The Ultimate Convex Hull"<<endl;
	cout<<"Enter number of points"<<endl;
	cin>>n;

	if(n==1)
		{	cout<<"NOT POSSIBLE WITH 1 POINT"<<endl;
			return 0;
		}

	srand(time(NULL)); //MAKE IT DIFFER ON EVERY RUN
	
	/*
	n=6;
	Point points[] = {{4.308152,3.274154},
	{1.713476,0.282781},
	{2.180473,0.907713},
	{4.060953,2.811898},
	{3.970560,3.843996},
	{0.672234,0.645498}};
                      
    vector<Point> S(points,points+n);
    */
    
    /*
    Point points[] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}, 
                      {1, 0}, {2, 0}};
    */
    
    vector<Point> S = initialize_input(n);
    
    

    
    vector<Point>KSHull = KS(S,n);
    ofstream op_points;
    op_points.open("output_points.txt");

    cout<<"FINAL ULTIMATE HULL "<<endl; 
    for(int i=0;i<KSHull.size();i++)
    	{
    		cout<<KSHull[i].describe()<<endl;
    		op_points<<KSHull[i].describe()<<endl;
    	}

    op_points.close();
	visualize("vis_op.py");
   
	return 0;
}