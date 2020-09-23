//#pragma once
//#include "Searcher.h"
//#include <queue>
//
//class CommonSearcher : public Searcher
//{
//public:
//	CommonSearcher(): m_evaluatedNodes(0){}
//
////Abstraction
//public:
//	virtual Solution search(const Searchable& s) = 0;
//	virtual int getNumberOfNodesEvaluated() { return m_evaluatedNodes; };
//
////Additional implementation
//public:
//	const State& popOpenList() { m_evaluatedNodes++; return m_openList.top(); }
//
//private:
//	int m_evaluatedNodes;
//	std::priority_queue<State> m_openList;
//};
//
