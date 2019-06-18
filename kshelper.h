#include "coreclass.h"

vector<Line> makePairs(vector<Point> S)
{
	vector<Point> temp_S;
	vector<Line> pairs;
	//COPY INTO A TEMPORARY STORAGE TO HELP WITH THE PAIRING
	for(int i=0;i<S.size();i++)
	{
		temp_S.push_back(S[i]);
	}
	//MAKE RANDOM PAIRINGS
	while(temp_S.size()>0)
	{
		//EACH ITERATION OF THIS LOOP MAKES 1 PAIRING
		int idx1, idx2;

		//PICK FIRST POINT RANDOMLY AND TAKE IT OUT
		idx1 = rand()%(temp_S.size());
		Point p = temp_S[idx1];
		temp_S.erase(temp_S.begin()+idx1);

		//PICK SECOND POINT RANDOMLY AND TAKE IT OUT
		idx2 = rand()%(temp_S.size());
		Point q = temp_S[idx2];
		temp_S.erase(temp_S.begin()+idx2);

		//PUT INTO PAIRS IN THE CORRECT ORDER
		cout<<p.describe()<<" "<<q.describe()<<" PAIRED."<<endl;
		Line L_temp(p,q);
		pairs.push_back(L_temp);

	}

	return pairs;
}

vector<Point> noSlopeCandidates(vector<Line> pairs, int upper)
{
	/*IF THERE IS A PAIR OF POINTS FOR WHICH SLOPE DOESN'T EXIST,
	ONLY ONE WILL BE ADDED TO THE CANDIDATES - UPPER IN CASE OF UPPER
	BRIDGE AND LOWER IN CASE OF LOWER BRIDGE

	AN INTEGER PARAMETER UPPER, TO LET US KNOW WHETHER ITS UPPER BRIDGE CONSTRUCTION
	OR LOWER BRIDGE CONSTRUCTION. HELPS AVOID REDUNDANCY
	*/

	vector<Point> candidates;

	for(int i=0;i<pairs.size();i++)
	{
		if(!pairs[i].slopeExists())
		{
			if(upper==1)
			{
				if(dgt(pairs[i].Pleft.y,pairs[i].Pright.y))
					candidates.push_back(pairs[i].Pleft);
				else
					candidates.push_back(pairs[i].Pright);
			}
			else
			{
				if(dlt(pairs[i].Pleft.y,pairs[i].Pright.y))
					candidates.push_back(pairs[i].Pleft);
				else
					candidates.push_back(pairs[i].Pright);
			}
		}

	}

	return candidates;
}

vector<double> findSlopes(vector<Line> pairs)
{
	/*ALL THE PAIRS WILL VALID SLOPES WILL HAVE THEIR SLOPES CALCULATED
	AND RETURNED*/

	vector<double> slopes;
	for(int i=0;i<pairs.size();i++)
	{
		if(pairs[i].slopeExists())
		{
			cout<<pairs[i].slope<<endl;
			slopes.push_back(pairs[i].slope);
		}	
	}

	return slopes;
}

void disAggregrate(vector<Line>&SMALL,vector<Line>&EQUAL,vector<Line>&LARGE,vector<Line> pairs, double K)
{
	for(int i=0;i<pairs.size();i++)
	{
		if(pairs[i].slopeExists())
		{
			if(dlt(pairs[i].slope,K))
				SMALL.push_back(pairs[i]);

			else if(dgt(pairs[i].slope, K))
				LARGE.push_back(pairs[i]);

			else
				EQUAL.push_back(pairs[i]);
		}
	}
}

vector<Point> maxYIntercept(vector<Point>S, double K)
{
	double maxY = INT_MIN;
	vector<Point> MAX;
	cout<<"MAXYINTERCEPTTTTTTTTTT"<<endl;
	for(int i=0; i<S.size(); i++)
	{
		
		cout<<S[i].describe()<<endl;
		cout<<S[i].y -K*S[i].x<<endl;
		if(dgt((S[i].y - K*S[i].x),maxY))
		{
			maxY = S[i].y - K*S[i].x;
			MAX.clear();
			MAX.push_back(S[i]);
		}
		else if(deq((S[i].y - K*S[i].x),maxY))
		{
			MAX.push_back(S[i]);
		}
	}
	cout<<"MAXYINTERCEPTTTTTTTTTT"<<endl;
	return MAX;
}

vector<Point> minYIntercept(vector<Point>S, double K)
{
	double minY = INT_MAX;
	vector<Point> MAX;

	for(int i=0; i<S.size(); i++)
	{
		
		if(dlt((S[i].y - K*S[i].x),minY))
		{
			minY = S[i].y - K*S[i].x;
			MAX.clear();
			MAX.push_back(S[i]);
		}
		else if(deq((S[i].y - K*S[i].x),minY))
		{
			MAX.push_back(S[i]);
		}
	}
	
	return MAX;
}


Point minXCoordinate(vector<Point> S, int upper)
{
	double  minX = INT_MAX;
	/* THE BELOW VECTOR WILL CONTAIN ALL 
	POINTS FROM S WITH THE MINIMUM X COORDINATE */
	vector<Point> minXpoints;
	for(int i=0; i<S.size(); i++)
		if(dlt(S[i].x,minX))
		{
			minX = S[i].x;
			minXpoints.clear();
			minXpoints.push_back(S[i]);
		}
		else if(deq(S[i].x,minX))
		{
			minXpoints.push_back(S[i]);
		}

	Point answer_upper, answer_lower;
	double minY = INT_MAX, maxY = INT_MIN;

	for(int i=0;i <minXpoints.size(); i++)
	{
		if(dgt(minXpoints[i].y,maxY))
		{
			maxY = minXpoints[i].y;
			answer_upper = minXpoints[i];
		}
		if(dlt(minXpoints[i].y,minY))
		{
			minY = minXpoints[i].y;
			answer_lower = minXpoints[i];
		}
	}

	if(upper==1)
		return answer_upper;
	else
		return answer_lower;
}

Point maxXCoordinate(vector<Point> S, int upper)
{
	double maxX = INT_MIN;
	/* THE BELOW VECTOR WILL CONTAIN ALL 
	POINTS FROM S WITH THE MAXIMUM X COORDINATE */
	vector<Point> maxXpoints;
	for(int i=0; i<S.size(); i++)
		if(dgt(S[i].x, maxX))
		{
			maxX = S[i].x;
			maxXpoints.clear();
			maxXpoints.push_back(S[i]);
		}
		else if(deq(S[i].x,maxX))
		{
			maxXpoints.push_back(S[i]);
		}

	Point answer_upper, answer_lower;
	double minY = INT_MAX, maxY = INT_MIN;

	for(int i=0;i <maxXpoints.size(); i++)
	{
		if(dgt(maxXpoints[i].y,maxY))
		{
			maxY = maxXpoints[i].y;
			answer_upper = maxXpoints[i];
		}
		if(dlt(maxXpoints[i].y,minY))
		{
			minY = maxXpoints[i].y;
			answer_lower = maxXpoints[i];
		}
	}

	if(upper==1)
		return answer_upper;
	else
		return answer_lower;
}

void PopulateCand(vector<Line> source, vector<Point>&candidates, int left, int right)
{
	for(int i=0;i<source.size();i++)
	{
		if(left==1)
			candidates.push_back(source[i].Pleft);
		if(right==1)
			candidates.push_back(source[i].Pright);
	}
}

vector<Point> handleOddPoint(vector<Point>&S)
{
	vector<Point> candidates;
	if(S.size()%2)
	{
		cout<<S[0].describe()<< " put into candidates"<<endl;
		candidates.push_back(S[0]);
		S.erase(S.begin());
	}
	return candidates;
}