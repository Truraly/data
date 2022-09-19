# 写在前面

作者：Truraly

这个是我的数据结构小实践，有不少地方都有问题，不过现在的水平处理不了（开摆）

## 注意事项

- 由于未知类型转换会出现问题，所以暂时不支持使用非常见类型，以及自定义类型
- 位序初始为0
- 通常来讲，输入数据有误会返回false/-1

# 静态顺序表 StArray

- 类名：`StArray`

## 注意事项

- 

## 头文件引用：

```C++
#include"StaticArray.hpp"
```

## 类声明

```C++
template<class ElemType>
class StArray {
public:
	// 数组头指针
	ElemType* elem;
	// 当前元素数量
	// 注意long long 最大约为9*10^18，超过会报错
	long long length;
	// 数组最大空间
	long long listsize;


	// 像数组中加入元素
	// 返回插入元素的下标
	// 若插入一组元素，则返回最后一个元素下标
	// 数组已满或插入一组元素后数组会超，或数据不合法，会返回-1
	long long add(
		ElemType ele, 
		long long i = -1, // 插入位置，默认在队尾
		long long num=1 // 插入数量，默认为1
	);

	// 通过下标删除元素
	bool delElem(long long i);

	// 查找第 st 个满足条件的元素
	long long find(
		ElemType ele, 
		long long st, 
		bool f=true // 搜索方向，默认正向搜索
	);

	// 查找第1个满足条件的元素
	long long find(
		ElemType ele,  
		bool f = true // 搜索方向，默认正向搜索
	);

	// 通过下标访问,越界返回NULL
	ElemType operator[](long long i);

	// 将另一个数组正序/倒叙(false)后,
	// 将其下标为start到end的元素合并到本数组
	// 超出数组大小的部分将会被舍去
	bool merge(
		StArray arr, // 目标数组
		long long start=0, // 开始元素下标,默认为0
		long long end=-1, // 结束元素下标,默认为数组尾部
		bool b_sx=true // 插入顺序，默认为正序，false则将数组倒叙后插入
	);

	// 对容器内下标从start到end的元素排序(快排)
	bool sort(
		long long start, // 开始元素下标
		long long end, // 结束元素下标
		bool k = true // 排序顺序，默认为正序
	);

	// 遍历输出元素
	bool print(
		string s="", // 加入在最前面的文字
		string x = "", // 加入在元素中间的文字
		string e = "" // 加入在末尾的文字（不会自动换行）
	);

	// 析构函数
	~StArray() { delete elem; }
	// 默认构造函数,会创建一个无法使用的数组
	StArray();
	// 初始化，创建能放置i个元素的数组
	StArray(long long i);
	// 克隆构造函数
	StArray(StArray& arr);
};
```

## 示例使用方法：

```C++
	// 新建长度为30的数组
	StArry<int>test1(30);

	// 添加一些元素
	test1.add(1);
	test1.add(3);
	test1.add(5);
	test1.add(2);
	test1.add(1);
	test1.add(9);

	// 在下标为2的地方插入数字(11)
	test1.add(11, 2);

	// 在下标为6的地方加入3个(33)
	test1.add(33, 6,3);

	// 正序排序
	cout << test1.sort(0, test1.length) <<  endl;// p

	// 逆序部分排序( 1 ~ length-2 )
	cout << test1.sort(1, test1.length-2,false) << endl;

	// 删除下标为0的元素
	test1.delElem(0);

	// 删除值为33的元素，输出是否成功删除
	cout << test1.delElem(test1.find(33)) << endl;
	cout << test1.delElem(test1.find(33)) << endl;
	cout << test1.delElem(test1.find(33)) << endl;
	cout << test1.delElem(test1.find(33)) << endl;
	cout << test1.delElem(test1.find(33)) << endl;

	// 加入数字(5)
	test1.add(5);

	// 尾删数字(5)
	cout << test1.delElem(test1.find(5,false)) << endl;
	
	// 下标访问[2]
	cout  << test1[2] << endl;

	// 合并数组
	test1.merge(test2);

	// 部分合并数组(下标为2~3的元素)
	test1.merge(test2,2,3);

	// 克隆构造
	StArry<int>test3(test1);
	
	// 部分合并数组(反向下标从3到7)
	test1.merge(test3,3,7,false);

	// 格式化输出数组
	test1.print("输出数组: "," - ","\n");
```

# 动态顺序表 

- 类名：`DArray`

## 注意事项

- 删除和添加时会向近的方向移动数据，比如删除第二个元素，会将左边的元素（1个）向右移动
- 多余的空间不会被自动清除，需要手动操作

## 头文件快速引用：

```C++
#include"DynamicArray.hpp"
```

## 类声明：

```C++
// 指定发生错误时返回的ElemType类型的值，默认为NULL
# define _ERROR_ NULL;
template<class ElemType>
class DArray {
private:
	// 数组头指针
	ElemType* elem;
	// 当前最小下标
	long long begin;
	// 当前最大下标
	long long end;
	// 数组最大空间下标
	long long listsize;
	// 扩容倍率
	double addsize;
public:
	// 判断容器是否为空
	inline bool empty();
	// 容器的容量
	inline long long capacity();
	// 获取容器内元素数量
	inline long long size();
	// 获取剩余容量
	inline long long surplus();
	// 重新指定容器的长度为num
	// 如果容器变短，则末尾超出容器长度的元素被删除。
	// 会将数据移动到开头
	bool resize(int num);
	// 重新指定容器的长度为num
	// 若容器变长，则以[elem]填充新位置（后面空的空间将会被放上可以访问的数据）
	// 如果容器变短，则末尾超出容器长度的元素被删除。
	// 会将数据移动到开头
	bool resize(int num, ElemType elem);


	// 修改自动扩容幅度
	bool changeAddSize(double i);
	// 预留空间
	bool reserveSpace(long long i);
	// 自动整理,将剩余空间调整为目前的k倍
	bool autoArrange(double k);
	
	// 通过下标访问访问不到返回_ERROR_
	ElemType operator[](long long i);
	// 访问对应下标的元素的指针
	// 如果没有会返回NULL指针，相对于[]访问能减少出错
	ElemType* at(long long i);
	// 返回容器中第一个数据元素，容器为空则返回_ERROR_
	ElemType front();
	// 返回容器中最后一个数据元素，容器为空则返回_ERROR_
	ElemType back();
	// 查找第 st 个满足条件的元素的下标，找不到返回-1
	long long find(
		ElemType ele,
		long long st,
		bool f  // 搜索方向，默认正向搜索
	);

	// 查找第1个满足条件的元素的下标
	long long find(
		ElemType ele,
		bool f = true // 搜索方向，默认正向搜索
	);


	// 排序
	bool sort(
		long long start=-1 ,// 开始排序位置
		long long end=-1,// 结束排序位置
		bool sx=true// 顺序or逆序
	);
	// 互换容器
	bool swap(DArray& arr);
	// 遍历输出
	bool print(
		string s = "", // 加入在最前面的文字
		string x = "", // 加入在元素中间的文字
		string e = "" ,// 加入在末尾的文字（不会自动换行）
		bool sx=true// 输出顺序
	);

	// 合并
	bool merge(
		DArray& arr,
		bool del = false// 是否删除传入的对象
	);
	// 插入元素
	long long addElem(
		ElemType ele,
		long long i=-1,// 插入位置
		long long num=1// 插入数量
	);
	// 尾部加入元素，addElem的一种简便形式
	bool push_back(
		ElemType ele,
		long long i=1// 插入数量
	);

	
	// 弹出最后一个元素，容器为空则返回_ERROR_
	ElemType pop_back();
	// 通过下标删除
	bool delElem(long long i);
	// 删除区间（含边界）
	bool delElem(
		long long begain, // 开始元素下标
		long long end// 结束元素下标
	);
	// 清空容器
	bool clear();

	// 构造函数
	DArray(long long size = -1, double addsize = -1);
	// 拷贝构造
	DArray(const DArray& arr);
	// 析构函数
	~DArray() { delete elem; }

};
```

## 示例使用方法：

```C++
	// 创建一个默认容器
	DArray<int> test1;

	// 创建一个指定大小容器
	DArray<int> test2(15);

	// 创建一个指定增长倍率容器
	DArray<int> test3(10,3);

	// 增加内容
	test1.push_back(3,  5);
	test1.push_back(1);
	test1.push_back(5);
	test1.push_back(43);
	test1.push_back(8);
	test1.addElem(99, 2, 3);
	test1.push_back(2, 4);

	// 排序
	test1.sort(3);

	// 合并
	test2.merge(test1);

	// 清空
	test2.clear();
	
	cout << "判断是否为空" << test1.empty()<< endl;

	// 重新设定容器大小
	test1.resize(10);

	// 重新设定大小,并填充数字
	test1.resize(15,114);

	// 修改默认扩容倍率
	test1.changeAddSize(3);

	// 预留空间
	test1.reserveSpace(100);

	// 调整空间
	test1.autoArrange(1.5);

	cout << "通过下标访问(2)" << test1[2] << endl;
	cout << "通过函数访问(2)" << test1.at(2) << endl;
	cout << "访问第一个元素" << test1.front() << endl;
	cout << "访问最后一个元素" << test1.back() << endl;
	cout << "寻找元素（2）" << test1.find(2) << endl;
	cout << "反向寻找元素（2）" << test1.find(2,false) << endl;
	cout << "寻找元素（第二个2）" << test1.find(2,2,true) << endl;

	// 交换容器
	test1.swap(test2);

	cout << "弹出最后一个元素" << test2.pop_back() << endl;

	// 删除元素
	test2.delElem(1);

	// 删除一段元素
	test2.delElem(2,4);

	// 拷贝构造
	DArray<int> test4(test2);
```

