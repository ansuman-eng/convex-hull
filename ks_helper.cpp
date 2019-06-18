/*
void lowerBridge()
{

}
vector<Point> bridgeConcat(vector<Point> P, vector<Point> Q)
{

}

vector<Point> lowerHull(Point pmin, Point pmax, vector<Point>T)
{
	//VERY REPETITIVE
	vector<float> x_coord;
	for(int i=0;i<T.size();i++)
		x_coord.push_back(T[i].x);

	float median_x = kthLargest(x_coord,x_coord.size()/2);
	
	vector<Point> Tleft,Tright;

	for(int i=0;i<T.size();i++)
		if(T[i].x<=median_x)
			Tleft.push_back(T[i]);
		else
			Tright.push_back(T[i]);

	Line uBridge = lowerBridge(T,Tleft,Tright);
	
	//UPDATE Tleft		
	//UPDATE Tright

	return bridgeConcat(lowerHull(pmin,pl,Tleft),lowerHull(pr,pmax,Tright));

}

*/