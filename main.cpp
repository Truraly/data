
//#include"StaticArray.hpp"
#include"DynamicArray.hpp"
using namespace std;

bool pr(string aa,DArray<int>& arr,int k) {
	cout << aa<<"容器"<<k<<"大小为：" << arr.capacity() << endl;
	cout << "\n( " << arr.size() << " ) " << arr.print("当前元素为( ", " , ", " )") << endl;

	return true;
}

int main() {
	// 创建一个默认容器
	DArray<int> test1;
	pr("\n创建一个默认容器\n",test1, 1);
	// 创建一个指定大小容器
	DArray<int> test2(15);
	pr("\n创建一个指定大小容器\n",test2, 2);
	// 创建一个指定增长倍率容器
	DArray<int> test3(10,3);
	pr("\n创建一个指定增长倍率容\n",test3, 3);
	// 增加内容
	
	test1.push_back(3,  5);
	test1.push_back(1);
	test1.push_back(5);
	test1.push_back(43);
	test1.push_back(8);
	test1.addElem(99, 2, 3);
	test1.push_back(2, 4);
	pr("\n增加内容\n",test1, 1);
	//test3.push_back(3, 11);
	//pr(test3, 3);
	
	//pr(test1, 1);
	
	test1.sort(3);
	pr("\n排序\n",test1, 1);
	test2.merge(test1);
	pr("\n合并\n", test2, 2);
	test2.clear();
	pr("\nclear 2\n",test2, 2);
	cout << "判断是否为空" << test1.empty()<< endl;
	test1.resize(10);
	pr("\n重新设定大小\n", test1, 1);
	test1.resize(15,114);
	pr("\n重新设定大小,并填充数字\n", test1, 1);
	test1.changeAddSize(3);
	test1.push_back(32, 4);
	pr("\n修改默认扩容倍率\n", test1, 1);
	test1.reserveSpace(100);
	pr("\n预留空间\n", test1, 1);
	test1.autoArrange(1.5);
	pr("\n调整空间\n", test1, 1);
	cout << "通过下标访问(2)" << test1[2] << endl;
	cout << "通过函数访问(2)" << test1.at(2) << endl;
	cout << "访问第一个元素" << test1.front() << endl;
	cout << "访问最后一个元素" << test1.back() << endl;
	cout << "寻找元素（2）" << test1.find(2) << endl;
	cout << "反向寻找元素（2）" << test1.find(2,false) << endl;
	cout << "寻找元素（第二个2）" << test1.find(2,2,true) << endl;
	test1.swap(test2);
	pr("交换容器", test2, 2);
	cout << "弹出最后一个元素" << test2.pop_back() << endl;
	pr("弹出最后一个元素", test2, 2);
	test2.delElem(1);
	pr("删除元素", test2, 2);
	test2.delElem(2,4);
	pr("删除一段元素", test2, 2);
	DArray<int> test4(test2);
	pr("拷贝构造", test4, 4);
	system("pause");
	
	return 0;
}