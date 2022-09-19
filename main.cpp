
//#include"StaticArray.hpp"
#include"DynamicArray.hpp"
using namespace std;

bool pr(string aa,DArray<int>& arr,int k) {
	cout << aa<<"����"<<k<<"��СΪ��" << arr.capacity() << endl;
	cout << "\n( " << arr.size() << " ) " << arr.print("��ǰԪ��Ϊ( ", " , ", " )") << endl;

	return true;
}

int main() {
	// ����һ��Ĭ������
	DArray<int> test1;
	pr("\n����һ��Ĭ������\n",test1, 1);
	// ����һ��ָ����С����
	DArray<int> test2(15);
	pr("\n����һ��ָ����С����\n",test2, 2);
	// ����һ��ָ��������������
	DArray<int> test3(10,3);
	pr("\n����һ��ָ������������\n",test3, 3);
	// ��������
	
	test1.push_back(3,  5);
	test1.push_back(1);
	test1.push_back(5);
	test1.push_back(43);
	test1.push_back(8);
	test1.addElem(99, 2, 3);
	test1.push_back(2, 4);
	pr("\n��������\n",test1, 1);
	//test3.push_back(3, 11);
	//pr(test3, 3);
	
	//pr(test1, 1);
	
	test1.sort(3);
	pr("\n����\n",test1, 1);
	test2.merge(test1);
	pr("\n�ϲ�\n", test2, 2);
	test2.clear();
	pr("\nclear 2\n",test2, 2);
	cout << "�ж��Ƿ�Ϊ��" << test1.empty()<< endl;
	test1.resize(10);
	pr("\n�����趨��С\n", test1, 1);
	test1.resize(15,114);
	pr("\n�����趨��С,���������\n", test1, 1);
	test1.changeAddSize(3);
	test1.push_back(32, 4);
	pr("\n�޸�Ĭ�����ݱ���\n", test1, 1);
	test1.reserveSpace(100);
	pr("\nԤ���ռ�\n", test1, 1);
	test1.autoArrange(1.5);
	pr("\n�����ռ�\n", test1, 1);
	cout << "ͨ���±����(2)" << test1[2] << endl;
	cout << "ͨ����������(2)" << test1.at(2) << endl;
	cout << "���ʵ�һ��Ԫ��" << test1.front() << endl;
	cout << "�������һ��Ԫ��" << test1.back() << endl;
	cout << "Ѱ��Ԫ�أ�2��" << test1.find(2) << endl;
	cout << "����Ѱ��Ԫ�أ�2��" << test1.find(2,false) << endl;
	cout << "Ѱ��Ԫ�أ��ڶ���2��" << test1.find(2,2,true) << endl;
	test1.swap(test2);
	pr("��������", test2, 2);
	cout << "�������һ��Ԫ��" << test2.pop_back() << endl;
	pr("�������һ��Ԫ��", test2, 2);
	test2.delElem(1);
	pr("ɾ��Ԫ��", test2, 2);
	test2.delElem(2,4);
	pr("ɾ��һ��Ԫ��", test2, 2);
	DArray<int> test4(test2);
	pr("��������", test4, 4);
	system("pause");
	
	return 0;
}