
//vector로 구현

//#include<iostream>
//#include<vector>
//#include<algorithm>
//
//using namespace std;
//
//int main() {
//	vector<pair <int, string> >v;
//	v.push_back(pair<int, string>(90, "박하늘"));
//	v.push_back(pair<int, string>(23, "이꼴등"));
//	v.push_back(pair<int, string>(44, "중중중"));
//
//	sort(v.begin(), v.end());
//
//	for (int i = 0; i < v.size(); i++) {
//		cout << v[i].second << ' ';
//	}
//
//	return 0;
//}
//







//#include<iostream>
//#include<vector>
//#include<algorithm>
//
//using namespace std;
//
//bool compare(pair<string, pair<int, int>> a,  pair<string, pair<int, int>> b) {
//	if (a.second.first == b.second.first) {
//		return a.second.first > b.second.first;
//	}
//	else
//	{
//		return a.second.second > b.second.second;
//
//	}
//}
//
//int main() {
//	vector<pair<string, pair<int, int>>> v;
//	v.push_back(pair<string, pair<int, int>> ("박창헌",pair<int,int>(26, 100)) );
//	v.push_back(pair<string, pair<int, int>>("박창윤", pair<int, int>(23, 101)));
//	v.push_back(pair<string, pair<int, int>>("이신영", pair<int, int>(53, 99)));
//	v.push_back(pair<string, pair<int, int>>("박정배", pair<int, int>(52, 99)));
//
//
//	sort(v.begin(), v.end(), compare);
//
//	for (int i = 0; i < v.size(); i++) {
//		cout << v[i].first << ' ';
//	}
//
//}
