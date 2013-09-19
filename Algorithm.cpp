#include "Algorithm.hpp"

//dist must be INF if infinite
static double** dist = NULL;
Algorithm::RouteContainer Algorithm::computeFloydWarshall(double** distance, int n)
{
	if (dist != distance) {
		delete dist;
		dist = distance;
	}
	dist = distance;
	std::vector<std::vector<int> > next(n,std::vector<int>(n,-1));
	for (int k=0 ;k < n; k++) {
		for (int i=0; i< n; i++) {
			for (int j=0; j<n; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = k;
				}
			}
		}
	}
	std::vector<std::vector< std::list<int>* > >* ret = new std::vector<std::vector< std::list<int>* > > (n, std::vector< std::list<int>* >(n, NULL) );
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			std::list<int>* tmp = new std::list<int>;
			std::list<int>* first= new std::list<int>(1,i);
			std::list<int>* mid = Algorithm::Path(next, i, j);
			std::list<int>* last = new std::list<int>(1,j);
			tmp->insert(tmp->end(), first->begin(), first->end());
			delete first;
			tmp->insert(tmp->end(), mid->begin(), mid->end());
			delete mid;
			tmp->insert(tmp->end(), last->begin(), last->end());
			delete last;

			(*ret)[i][j] = tmp;
		}
	}
	return ret;
}
std::list<int>* Algorithm::Path(const std::vector<std::vector<int> >& next, int i, int j) {
	std::list<int>* ret = NULL;
	if (dist[i][j] == INF) {
			// no path
	} else {
		int intermediate = next[i][j];
		ret = new std::list<int>;
		if (next[i][j] == -1) {
		} else {
			std::list<int>* first= Algorithm::Path(next,i,intermediate);
			std::list<int>* mid = new std::list<int>(1,intermediate);
			std::list<int>* last = Algorithm::Path(next,intermediate,j);
			ret->insert(ret->end(), first->begin(), first->end());
			delete first;
			ret->insert(ret->end(), mid->begin(), mid->end());
			delete mid;
			ret->insert(ret->end(), last->begin(), last->end());
			delete last;
		}
	}
	return ret;
}
Algorithm::~Algorithm(void)
{
}
