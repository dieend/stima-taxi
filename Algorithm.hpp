#pragma once
#include <list>
#include <vector>
#define INF 1000000000
class Algorithm
{
public:
	typedef std::vector<std::vector< std::list<int>* > >* RouteContainer;
	static RouteContainer computeFloydWarshall(double** distance, int n);
	~Algorithm(void);
private:
	static std::list<int>* Path(const std::vector<std::vector<int> >&,int,int);
};
