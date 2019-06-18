#include "kshelper.h"

using namespace std;

Line Bridge(vector<Point> S, double a, int upper)
{
	//WHERE THERE ARE TWO POINTS, LINE JOINING THEM IS THE BRIDGE
	if(S.size()==2)
	{
		Line L_temp(S[0],S[1]);
		return L_temp;
	}

	//DECLARATIONS
	vector<Point> candidates, temp_S;
	vector<Line> pairs, SMALL, EQUAL, LARGE;
	vector<double> slopes;


	candidates = handleOddPoint(S);
	pairs = makePairs(S);

	//4//
	vector<Point> extraCandidates = noSlopeCandidates(pairs,upper);
	/*cout<<"EXTRA CANDIDATES"<<endl;
	for(int i=0;i<extraCandidates.size();i++)
		cout<<extraCandidates[i].describe()<<endl;
	*/
	candidates.insert(candidates.end(), extraCandidates.begin(), extraCandidates.end());
	//cout<<"SLOPES"<<endl;
	slopes = findSlopes(pairs);
	

	//5//
	double K = kthLargest(slopes, slopes.size()/2);
	cout<<"MEDIAN SLOPE "<<K<<endl;

	//6//	
	disAggregrate(SMALL,EQUAL,LARGE,pairs,K);

	//7 - FIND POINTS WITH MAX Y INTERCEPT//
	vector<Point> S_cand;
	S_cand.insert(S_cand.end(), S.begin(), S.end());
	S_cand.insert(S_cand.end(), candidates.begin(), candidates.end());
	
	vector<Point> MAX;
	if(upper==1)
		MAX = maxYIntercept(S_cand,K);
	else
		MAX = minYIntercept(S_cand,K);
	
	cout<<"POINTS IN MAX"<<endl;
	for(int i=0;i<MAX.size();i++)
		cout<<MAX[i].describe()<<endl;
	
	Point pointK = minXCoordinate(MAX,1);
	Point pointM = maxXCoordinate(MAX,1);	

	//8//
	

	if(dle(pointK.x,a) && dgt(pointM.x,a))
	{
		Line bridgeL(pointK,pointM);
		return bridgeL;
	}
	
	//9 - ALL POINTS ON LEFT//
	else if(dle(pointM.x,a))
	{
		if(upper==1)
		{
			PopulateCand(LARGE,candidates,0,1);
			PopulateCand(EQUAL,candidates,0,1);
			PopulateCand(SMALL,candidates,1,1);
		}
		else
		{
			PopulateCand(LARGE,candidates,1,1);
			PopulateCand(EQUAL,candidates,0,1);
			PopulateCand(SMALL,candidates,0,1);
		}
	
	}

	//10 - ALL POINTS ON RIGHT//
	else if(dgt(pointK.x,a))
	{
		
		if(upper==1)
		{
			PopulateCand(SMALL,candidates,1,0);
			PopulateCand(EQUAL,candidates,1,0);
			PopulateCand(LARGE,candidates,1,1);
		}
		else
		{
			PopulateCand(LARGE,candidates,1,0);
			PopulateCand(EQUAL,candidates,1,0);
			PopulateCand(SMALL,candidates,1,1);
		}

	}

	/*
	cout<<"CANDIDATES"<<endl;
	for(int i=0;i<candidates.size();i++)
		cout<<candidates[i].describe()<<endl;
	*/
	return Bridge(candidates, a, upper);

}
