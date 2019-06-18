#include "coreclass.h"

/*
Time complexity of JARVIS MARCH is OUTPUT and INPUT dependent
O(nh)
where n = number of points given in input
h = number of points which end up being part of hull
*/
vector<Point> jarvisMarch(ConvexHull C)
{
	//result_hull WILL CONTAIN FINAL RESULT IN CLOCKWISE DIRECTION
	vector<Point> result_hull;	
	
	//FIND THE LEFTMOST BOTTOMMOST POINT
	int anchor = C.findAnchor();

	/*DEBUG
	cout<<"Anchor point is "<<C.points[anchor].describe()<<endl;
	*/

	//START THE LOOPING PROCESS
	int hull_point_idx = anchor;
	do
	{
		/*DEBUG
		cout<<"Adding "<<C.points[hull_point_idx].x<<" "<<C.points[hull_point_idx].y<<" to the hull"<<endl;
		*/

		//ADD THE CURRENT POINT
		result_hull.push_back(C.points[hull_point_idx]);

		//FIND THE MOST COUNTER-CLOCK POINT WRT CURRENT POINT
		int next = (hull_point_idx+1)%C.n;

		/*DEBUG
		cout<<"Initial candidate is "<<C.points[next].describe()<<endl;
		*/

		for(int i=0;i<C.n;i++)
		{
			/*DEBUG
			cout<<"Comparing ";
			cout<<C.points[next].describe()<<" and ";
			cout<<C.points[i].describe()<<endl;
			*/

			//IF I POINT IS MORE CLOCKWISE THAN NEXT POINT - WE REPLACE NEXT WITH I
			if(C.points[hull_point_idx].orientation(C.points[next],C.points[i]) == 2)
			{
				/*DEBUG
				cout<<"Replacing candidate as "<<C.points[i].describe()<<endl;
				*/

				next=i; //visualisation here
			}

		}
		hull_point_idx = next;
	}while(hull_point_idx!=anchor);

	return result_hull;

}

int main()
{
	int n;
	double x,y;
	cout<<"Welcome to JARVIS MARCH"<<endl;
	//cout<<"Enter number of points"<<endl;
	/*cin>>n;
	Point* points =(Point *)malloc(n*sizeof(Point));
	for(int i=0;i<n;i++)
	{
		cin>>x>>y;
		points[i].set_coordinates(x,y);
	}
	*/

	//INPUT = NUMBER OF POINTS
	//RANDOM GENERATION OF 2D POINTS AND SAVING IN FILE POINTS.TXT
	//PLOT THE SCATTERPLOT OF THE SAME
	//RUN THE ALGORITHM
	//SAVE INTERMEDIATE STEPS IN INTERIM.TXT
	//RUN PYTHON SCRIPT GENERATING PNGs
	//SAVE RESULT IN A FILE RESULTS.TXT
	//GENERATE FINAL PNG
	//MAKE INTO GIF AND SHOW
	//SHOW RUN TIME

	n=20;
	Point points[] = {{3.683809,3.969229},
{4.759163,2.824421},
{3.290079,3.023519},
{0.839728,2.658862},
{1.423967,4.229531},
{3.982798,4.714136},
{0.109364,0.444681},
{3.121435,0.290089},
{1.840088,0.473203},
{1.179784,0.110289},
{2.743007,2.110615},
{3.935332,1.533621},
{0.526064,2.309780},
{2.224322,3.035483},
{0.885938,4.933882},
{3.648590,4.569747},
{3.903111,3.407753},
{2.394168,2.193190},
{1.431271,3.233896},
{4.852052,2.855238}};

    ConvexHull C (points,n); 
    cout<<"CONVEX HULL OBJECT CREATED"<<endl;                 
	vector<Point> result_hull = jarvisMarch(C); 

	for(int i=0;i<result_hull.size();i++)
    	cout<<result_hull[i].x<<" "<<result_hull[i].y<<endl;

	return 0;
}