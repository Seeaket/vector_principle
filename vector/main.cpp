#include<iostream>
#include<assert.h>
#include"vector.h"
using namespace std;



int main()
{
	//功能测试
	vectors<int>vec;
	vec.push_back(666);
	vectors<int>v(8, 8);
	vec.assign(v.begin(), v.begin() + 4);//将所有原数都替换成迭代器内的元素，并改变元素大小，超出当前容器大小也改变容器大小
	cout << vec.capacity() << endl;
	vec.insert(vec.begin(),3, 4);
	vectors<int>vs(1,1);
	vs.push_back(2);
	vs.push_back(3);
	for (auto i : vs)
	{
		cout << i << " ";
	}
	cout << endl <<vec.front() << endl;
	cout <<vec.back() << endl;
	vec.insert(vec.begin(), vs.begin(), vs.begin() + 2);
	vec.erase(vec.begin(),vec.begin()+3);
	for (int i = 0; i < vec.size();i++)
	{
		vec.at(i) = 0;
		cout << vec.at(i) << " ";
	}
	return 0;
}
