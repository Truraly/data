/*
* 静态数组
* 作者: Truraly
* 介绍: 数据结构小实践
* 快捷导入: #include"StaticArray.hpp"
* 详细介绍见README.md
* 我累了我要休息，帮我关下灯谢谢
* 有些地方东西改了但注释没改，懒得改了，问题不大
*/

#pragma once
#include<string.h>// 不加会找不到NULL
#include<iostream>// 输入输出流
using namespace std;



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





// ----------------函数实现-----------
// 通过位序删除
template<class ElemType>
bool StArray<ElemType>::delElem(long long i) {
	// 直接覆盖
	// 数据不合法
	if (i < 0 || i >= length) { return false; }
	// 移动位置
	for (long long j = i; j < length - 1; j++) {
		elem[j] = elem[j + 1];
	}
	length--;
	return true;
}


// 在数组插入,默认插入尾部,返回下标
// 可以指定插入位置，插入数量
template<class ElemType>
long long StArray<ElemType>::add(ElemType ele, long long i, long long num) {
	// 满了
	if (length > listsize - num || num < 0) { return -1; }
	// 最后插入
	if (i == -1) {
		// 直接在后面加上
		for (long long j = 0; j < num; j++) {
			elem[length] = ele;
			length++;
		}
		// 返回插入的最后一个点
		return length - 1;
	}
	// 中间插入
	else {
		// 数据不合法
		if (i > length) { return -1; }
		// 元素后移
		for (long long j = length - 1; j >= i; j--) {
			elem[j + num] = elem[j];
		}
		// 插入元素
		long long wz;// 记录未知
		for (wz = i; wz < i + num; wz++) {
			elem[wz] = ele;
			length++;
		}
		// 返回最后一个位置
		return wz - 1;
	}
}



// 通过下标访问,会越界
template<class ElemType>
ElemType  StArray<ElemType>::operator[](long long i) {
	// 异常则返回第一个元素
	if (i < 0 || i >= length) { return NULL; }
	return elem[i];
}


template<class ElemType>
long long StArray<ElemType>::find(ElemType ele, bool f ) {
	return this->find(ele, 1, f);
}
// 查找第一个满足条件的元素，false反向
template<class ElemType>
long long StArray<ElemType>::find(ElemType key, long long st, bool f) {
	// 数据不合法
	if (st < 1) { return -2; }
	// 正向查找
	if (f) {
		for (long long j = 0; j < length; j++) {
			if (elem[j] == key) {
				if (st > 1) { st--; }
				else { return j; }
			}
		}
		return -1;
	}
	// 逆向查找
	else {
		for (long long j = length - 1; j >= 0; j--) {
			if (elem[j] == key) {
				if (st > 1) { st--; }
				else { return j; }
			}
		}
		return -1;
	}
}


// 合并2个数组
template<class ElemType>
bool StArray<ElemType>::merge(StArray arr, long long start, long long end, bool b_sx) {
	if (start < 0) { return false; }
	if (end < 0) { end = arr.length - 1; }
	// 数据不合法
	if (start > arr.length - 1 || end > arr.length - 1 || start > end) { return false; }
	// 正向截取
	if (b_sx) {
		for (long long j = start; j <= end && this->length < listsize; j++) {
			if (!this->add(arr.elem[j])) { return false; }
		}
		return true;
	}
	// 反向截取
	else {
		for (long long j = arr.length - 1 - start; j >= arr.length - 1 - end && this->length < this->listsize; j--) {
			if (!add(arr.elem[j])) { return false; }
		}
		return true;
	}
}

// 对容器内的元素排序,默认正序
template<class ElemType>
bool StArray<ElemType>::sort(long long start, long long end, bool k) {
	// 输入不合法
	if (!( 0<= start && start <= end && end <= this->length)) { return false; }
	if (start == end) { return true; }
	// 顺序
	if (k) {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = start;
			i_min = end;
			// 寻找第一个比key大的
			while (elem[start] >= elem[i_max]) {
				i_max++;
				if (i_max >= end) { break; }
			}
			while (elem[start] <= elem[i_min]) {
				i_min--;
				if (i_min <= start) { break; }
			}
			// 跳出
			if (i_min <= i_max) { break; }
			ElemType temp = elem[i_max];
			elem[i_max] = elem[i_min];
			elem[i_min] = temp;
		}
		ElemType temp = elem[start];
		elem[start] = elem[i_min];
		elem[i_min] = temp;
		sort(0, i_min - 1, k);
		sort(i_max, end, k);
		return true;
	}
	// 逆序
	else {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = end;
			i_min = start;
			// 在右边寻找第一个比key大的
			while (elem[i_max]<=elem[end]) {
				i_max--;
				if (i_max <= start) { break; }
			}
			// 在左边寻找第一个比key小的
			while (elem[end] <= elem[i_min]) {
				i_min++;
				if (i_min >= end) { break; }
			}
			// 跳出
			if (i_min >= i_max)  break; 
			ElemType temp = elem[i_max];
			elem[i_max] = elem[i_min];
			elem[i_min] = temp;
		}
		ElemType temp = elem[end];
		elem[end] = elem[i_min];
		elem[i_min] = temp;
		sort(start, i_max, k);
		sort(i_min + 1, end, k);
		return true;
	}
	return true;
}





// 初始化
template<class ElemType>
StArray<ElemType>::StArray(long long i, long long n, ElemType init) {
	if (i < 0 || i>9000000000000000000||n>i||n<0) {
		elem = NULL;
		length = -1;
		listsize = -1;
		return;
	}
	else {
		elem = new ElemType[i];
		length = n;
		listsize = i;
		// 数组值初始化
		for (long long j = 0; j < i; j++) {
			elem[j] = j<n?init:(ElemType)0;
		}

	}
}

template<class ElemType>
StArray<ElemType>::StArray(long long i) {
	if (i < 0 || i>9000000000000000000) {
		elem = NULL;
		length = -1;
		listsize = -1;
	}
	else {
		elem = new ElemType[i];
		length = 0;
		listsize = i;
		// 数组值初始化
		for (long long j = 0; j < i; j++) {
			elem[j] = (ElemType)0;// 强制转换
		}
	}
}
// 克隆
template<class ElemType>
StArray<ElemType>::StArray(StArray<ElemType>& arr) {
	this->elem = new ElemType[arr.listsize];
	this->listsize = arr.listsize;
	this->length = arr.length;
	// 复制元素
	for (long long j = 0; j < arr.length; j++) {
		elem[j] = arr.elem[j];
	}
}

// 默认构造函数
template<class ElemType>
StArray<ElemType>::StArray() {
	elem = NULL;
	length = -1;
	listsize = -1;
}





// 遍历输出
template<class ElemType>
bool StArray<ElemType>::print(string s,string x, string e) {
	
	cout << s;
	if (length == 0) { cout << "数组为空"; }
	for (long long j = 0; j < length; j++) {
		cout << elem[j] << (j+1>=length?"":x);
	}
	cout << e;
	return true;
}