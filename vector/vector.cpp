#include<iostream>
#include<assert.h>
#include"vector.h"
using namespace std;



int main()
{
	//���ܲ���
	vectors<int>vec;
	vec.push_back(666);
	vectors<int>v(8, 8);
	vec.assign(v.begin(), v.begin() + 4);//������ԭ�����滻�ɵ������ڵ�Ԫ�أ����ı�Ԫ�ش�С��������ǰ������СҲ�ı�������С
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
