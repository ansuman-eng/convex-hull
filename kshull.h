#include "ksbridge.h"

vector<Point> Hull(Point pmin, Point pmax, vector<Point> T, int upper)
{

	/*HANDLE THE RECURSION TERMINATION CASE HERE ONLY*/
	if(T.size()==2)
	{
		vector<Point> hull;
		
		hull.push_back(T[0]);
		hull.push_back(T[1]);
		
		if(dle(T[0].x,T[1].x))
			return hull;
		else
			reverse(hull.begin(),hull.end());	
			return hull;

	}

	/*FIND OUT THE DIVIDING LINE*/
	vector<double> x_coord;
	for(int i=0;i<T.size();i++)
		{	cout<<(double)T[i].x<<endl;
			x_coord.push_back(T[i].x);
		}
	cout<<pmin.describe()<<endl;
	cout<<pmax.describe()<<endl;
	double median_x = kthLargest(x_coord,x_coord.size()/2);
	cout<<"MEDIAN X IS "<<median_x<<endl;
	

	/*GENERATE TLEFT AND TRIGHT*/
	vector<Point> Tleft,Tright;

	for(int i=0;i<T.size();i++)
		if(dle(T[i].x,median_x))
			Tleft.push_back(T[i]);
		else
			Tright.push_back(T[i]);

	//cout<<Tleft.size()<<endl;
	//cout<<Tright.size()<<endl;
	

	/*FIND THE BRIDGE LINE*/
	Line uBridge = Bridge(T,median_x,upper);
	cout<<"BRIDGE"<<endl;
	cout<<uBridge.Pleft.describe()<<endl;
	cout<<uBridge.Pright.describe()<<endl;
	cout<<"BRIDGE ENDS"<<endl;
	/*FIND OUT LEFT AND RIGHT BRIDGE POINTS*/
	Point leftBridgePoint = uBridge.Pleft;
	Point rightBridgePoint = uBridge.Pright;

	/*CREATE SIDES OF QUADRILATERAL*/
	Line leftLine(leftBridgePoint,pmin);

	
	Line rightLine(rightBridgePoint,pmax);


	vector<Point> leftRecur;
	vector<Point> rightRecur;

	/*IF PMIN AND LEFTBRIDGE POINTS ARE SAME, THEN LEFT PORTION FOR HULL
	IS DONE*/	
	
	if(!pmin.Equal(leftBridgePoint))
	{

		vector<Point> Tleftnew;

		Tleftnew.push_back(leftBridgePoint);
		Tleftnew.push_back(pmin);

		/*UPDATE TLEFT TO CONTAIN THOSE POINTS WHICH ARE LEFT OF LEFTLINE
		FOR THAT, SIMPLY CHECK IF RIGHT BRIDGE POINT AND THE POINT IN CONSIDERATION
		LIE ON OPPOSITE SIDES OF THE LINE
		*/

		for(int i=0;i<Tleft.size();i++)
		{
			if(leftLine.liesOpposite(rightBridgePoint,Tleft[i]))
				Tleftnew.push_back(Tleft[i]);
		}

		leftRecur = Hull(pmin,leftBridgePoint,Tleftnew,upper);

	}

	else
	{
		leftRecur.push_back(pmin);
	}

	/*IF PMAX AND RIGHTBRIDGE POINTS ARE SAME, THEN RIGHT PORTION FOR  HULL
	IS DONE*/	

	if(!pmax.Equal(rightBridgePoint))
	{
		vector<Point> Trightnew;

		Trightnew.push_back(rightBridgePoint);
		Trightnew.push_back(pmax);

		/*UPDATE TRIGHT TO CONTAIN THOSE POINTS WHICH ARE RIGHT OF RIGHTLINE
		CHECK IF LEFT BRIDGE POINT AND POINT IN CONSIDERATION LIE ON OPPOSITE SIDES
		OF LINE
		*/
	
		for(int i=0;i<Tright.size();i++)
		{
			if(rightLine.liesOpposite(leftBridgePoint,Tright[i]))
				Trightnew.push_back(Tright[i]);
		}

		rightRecur = Hull(rightBridgePoint,pmax,Trightnew,upper);
	}
	else
	{
		rightRecur.push_back(pmax);
	}
	
	
	vector<Point> hull = leftRecur;
	hull.insert(hull.end(),rightRecur.begin(),rightRecur.end());
	return hull;

}

/*WRAPPER FUNCTION*/
vector<Point> upperHull(Point pmin, Point pmax, vector<Point>T)
{
	return Hull(pmin,pmax,T,1);
}
/*WRAPPER FUNCTION*/
vector<Point> lowerHull(Point pmin, Point pmax, vector<Point>T)
{
	vector<Point>lHull = Hull(pmin,pmax,T,0);
	reverse(lHull.begin(),lHull.end());
	return lHull;
}