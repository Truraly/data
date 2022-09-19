# 写在前面

作者：Truraly

这个是我的数据结构小实践，有不少地方都有问题，不过现在的水平处理不了（开摆）





# 静态顺序表 StArray

- 类名：`StArray`

## 注意事项

- 由于未知类型转换会出现问题，所以暂时不支持使用非常见类型，以及自定义类型
- 位序初始为0

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



## 头文件快速引用：



## 类声明：

```C++

```



## 示例使用方法：