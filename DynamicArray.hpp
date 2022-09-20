/*
* 动态数组
* 作者: Truraly
* 介绍 : 数据结构小实践
* 快捷导入 : #include"DynamicArray.hpp"
* 注意事项 :
	1. 由于未知类型转换会出现问题，所以暂时不支持使用非常见类型，以及自定义类型
	2. 位序初始为0
	3. 通常来讲，输入数据有误会返回false/-1
	4. 删除和添加时会向近的方向移动数据，比如删除第二个元素，会将左边的元素（1个）向右移动
	5. 多余的空间不会被自动清除，需要手动操作

* 我其实很想直接封装STL
* 一开始写急了，没规划，后面还得重新规划
* 
*/
#pragma once
#include<string.h>// 不加会找不到NULL
#include<iostream>// 输入输出流
#include<stdlib.h>
using namespace std;


# define _ERROR_ NULL;// 指定发生错误时返回的ElemType类型的值，默认为NULL
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
	// 若为-1则单纯为了排序
	bool resize(int num=-1);
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

// 判断容器是否为空
template<class ElemType>
bool DArray<ElemType>::empty() {
	return end < 0 || begin < 0 || end < begin;
}
// 容器的容量
template<class ElemType>
long long DArray<ElemType>::capacity(){
	return this->listsize + 1;
}
// 获取容器内元素数量
template<class ElemType>
long long DArray<ElemType>::size() {
	if (this->end < 0 || this->begin < 0 || this->end < this->begin) { return 0; }
	return this->end-this->begin+1;
}
// 获取剩余容量
template<class ElemType>
inline long long  DArray<ElemType>::surplus() {
	if (this->end < 0 || this->begin < 0 || this->end < this->begin) { return this->listsize+1; }
	return this->listsize-this->end+this->begin;
}
// 重新指定容器的长度为num，如果容器变短，则末尾超出容器长度的元素被删除。
template<class ElemType>
bool DArray<ElemType>::resize(int num) {
	// 数据修改
	if (num == -1) { num = listsize + 1; }
	// 数据不合法
	if (num < 0) { return false; }
	// 开辟空间,如果等大就对原来的数组做处理
	ElemType* ne = (num == listsize + 1?this->elem: (ElemType*)malloc(num *sizeof(ElemType)));
	//ElemType* ne = new ElemType[num];
	if (num >= this->size()) {
		// 把前面空白的删掉搬过去
		for (long long i = 0; i < num; i++) {
			ne[i] = i > this->end-this->begin ? (ElemType)0 : this->elem[i-this->begin];
		}
		this->end = this->size()-1;
		this->begin = 0;
	}
	else {
		// 有些搬不过去了
		for (long long i = 0; i < num; i++) {
			ne[i] = this->elem[i - this->begin];
		}
		this->begin = 0;
		this->end = num - 1;
	}


	if (!(num == listsize + 1||num == -1)) {
		//ElemType* de = this->elem;
		free(this->elem);
		this->elem = ne;
		this->listsize = num-1;
		//delete[] de;
		//if (de == NULL) {  }
		// cout <<"de =" << de[1] << endl;
	}
	return true;
}
// 重新指定容器的长度为num
// 若容器变长，则以[elem]填充新位置
// 如果容器变短，则末尾超出容器长度的元素被删除。
template<class ElemType>
bool DArray<ElemType>::resize(int num, ElemType elem) {
	// 数据不合法
	if (num < 0) { return false; }
	// 与当前大小相同
	if (num == listsize + 1) {
		// 前面有空白
		if (this->begin > 0) {
			for (long long i = 0; i < num; i++) {
				this->elem[i] = i > this->end - this->begin ? elem : this->elem[i - this->begin];
			}
		}
		// 前面没空白
		else {
			for (long long j = this->end + 1; j < num; j++) {
				this->elem[j] = elem;
			}
		}
		return true; 
	}
	// 开辟空间
	ElemType* ne = new ElemType[num];
	// 
	for (long long i = 0; i < num; i++) {
		ne[i] = i > this->end - this->begin ? elem : this->elem[i - this->begin];
	}
	delete this->elem;
	this->elem = ne;
	this->end = num - 1;
	this->begin = 0;
	this->listsize = num;
	return true;

}


// 修改自动扩容幅度
template<class ElemType>
bool DArray<ElemType>::changeAddSize(double i) {
	// 数据不合法
	if (i <=1) { return false; }
	this->addsize = i;
	return true;
}
// 预留空间
template<class ElemType>
bool DArray<ElemType>::reserveSpace(long long i){
	// 数据不合法
	if (i < 0) { return false; }
	// 大小足够
	if (this->surplus() >= i) { return true; }
	else {
		return this->resize(this->size()+i);
	}
	return true;
}
// 调整大小
template<class ElemType>
bool DArray<ElemType>::autoArrange(double k) {
	// 数据不合法
	if (k <= 1) { return false; }
	// 
	long long mb = this->size() * k;
	if (this->listsize == mb) { return true; }
	else {
		return this->resize(mb);
	}
	return true;
}

// 通过下标访问
template<class ElemType>
ElemType DArray<ElemType>::operator[](long long i) {
	// 数据不合法
	if (i < 0 || i >= this->size()) { return _ERROR_; }
	return this->elem[this->begin + i];
}
// 访问对应下标的元素的指针，方便查错
template<class ElemType>
ElemType* DArray<ElemType>::at(long long i) {
	if (i < 0 || i >= this->size()) { return NULL; }
	return &this->elem[this->begin + i];
}
//返回容器中第一个数据元素
template<class ElemType>
ElemType DArray<ElemType>::front() {
	if (this->size() == 0) { return _ERROR_; }
	return elem[begin];
}
//返回容器中最后一个数据元素
template<class ElemType>
ElemType DArray<ElemType>::back() {
	if (this->size() == 0) { return _ERROR_; }
	return elem[end];
}

// 查找第 st 个满足条件的元素的下标
template<class ElemType>
long long DArray<ElemType>::find(ElemType key, long long st, bool f) {
	if (this->size() <= 0) { return -1; }
	for (long long j = (f ? begin : end); (f ? j <= end : j >= begin); (f ? j++ : j--)) {
		if (elem[j] == key) {
			if (st > 1) {
				st--;
			}
			else {
				return j;
			}
		}
	}
	return -2;
}

// 查找第1个满足条件的元素的下标
template<class ElemType>
long long DArray<ElemType>::find(ElemType ele, bool f) {
	return this->find(ele, 1, f);
}


// 排序
template<class ElemType>
bool DArray<ElemType>::sort(long long start, long long end_, bool k) {
	if (start == -1) { start = this->begin; }
	if (end_ == -1) { end_ = this->end; }
	// 输入不合法

	if (!(0 <= start && start <= end_ && end_ < this->size())) { return false; }
	// 不用排序
	if (start == end_) { return true; }
	// 容器为空
	if (this->empty()) { return false; }
	start +=this-> begin;
	end_ += this->begin;
	// 顺序
	if (k) {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = start;
			i_min = end_;
			// 寻找第一个比key大的
			while (this->elem[start] >= this->elem[i_max]) {
				i_max++;
				if (i_max >= end_) { break; }
			}
			while (this->elem[start] <= this->elem[i_min]) {
				i_min--;
				if (i_min <= start) { break; }
			}
			// 跳出
			if (i_min <= i_max) { break; }
			ElemType temp = this->elem[i_max];
			this->elem[i_max] = this->elem[i_min];
			this->elem[i_min] = temp;
		}
		ElemType temp = this->elem[start];
		this->elem[start] = this->elem[i_min];
		this->elem[i_min] = temp;
		this->sort(start, i_min - 1, k);
		this->sort(i_max, end_, k);
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
			while (this->elem[i_max] <= this->elem[end]) {
				i_max--;
				if (i_max <= start) { break; }
			}
			// 在左边寻找第一个比key小的
			while (this->elem[end] <= this->elem[i_min]) {
				i_min++;
				if (i_min >= end) { break; }
			}
			// 跳出
			if (i_min >= i_max)  break;
			ElemType temp = this->elem[i_max];
			this->elem[i_max] = this->elem[i_min];
			this->elem[i_min] = temp;
		}
		ElemType temp = elem[end];
		this->elem[end] = this->elem[i_min];
		this->elem[i_min] = temp;
		this->sort(start, i_max, k);
		this->sort(i_min + 1, end, k);
		return true;
	}
	return true;

}

// 互换容器
template<class ElemType>
bool DArray<ElemType>::swap(DArray& arr) {
	// 定义中间变量
	ElemType* temp_elem = this->elem;
	long long temp_begin = this->begin;
	long long temp_end = this->end;
	long long temp_listsize = this->listsize;
	long long temp_addszie = this->addsize;
	//
	this->elem = arr.elem;
	this->begin = arr.begin;
	this->end = arr.end;
	this->listsize = arr.listsize;
	this->addsize = arr.addsize;
	//
	arr.elem = temp_elem;
	arr.begin = temp_begin;
	arr.end = temp_end;
	arr.listsize = temp_listsize;
	arr.addsize = temp_addszie;
	return true;
}


// 遍历输出
template<class ElemType>
bool DArray<ElemType>::print(string s, string b, string c,bool sx) {
	cout << s;
	if (this->size() == 0) { cout << "数组为空"; return false; }
	for (long long j = (sx ? begin : end); (sx ? j <= end : j >= begin); (sx ? j++ : j--)) {
		cout << elem[j] << (j<=begin&& !sx||j>=end&&sx? "" : b);
	}
	cout << c;
	return true;
}


// 清空容器
template<class ElemType>
bool DArray<ElemType>::clear() {
	// 懒清理
	this->begin = -1;
	this->end = -1;
	return true;
}





// 合并
template<class ElemType>
bool DArray<ElemType>::merge(DArray<ElemType>& arr,bool del) {
	if (arr.size() < 1) { return false; }
	for (long long j = arr.begin; j <= arr.end; j++) {
		if (!this->addElem(arr.elem[j])) {
			// 满了
			return true;
		}
	}
	if (del) {
		arr.~DArray();// 删除传入的对象
	}
	return true;
}









// 插入元素
template<class ElemType>
long long DArray<ElemType>::addElem(ElemType ele, long long i, long long num ) {
	// 数据修改
	if (i == -1) { i =(this->size()==0?0: this->end + 1) ; }
	if (i < -1 || num < 1||i>this->size()) { return false; }
	// 扩容
	if (this->surplus()<=0) {
		this->autoArrange(this->addsize);
	}

	// 优先向左移动
	if (this->begin - i < this->end - i && this->begin>0) {
	
		
		for (long long j = this->begin; j <= i; j++) {
			this->elem[j -1] = this->elem[j];
		}
		this->elem[i] = ele;
		num--;
		this->begin --;
		
	}
	// 向右塞
	else {
		for (long long j = end; j >= i; j--) {
			this->elem[j + 1] = this->elem[j];
		}
		this->elem[i] = ele;
		num--;
		if (this->size() <= 0) 
		{ this->end = 0; }
		else { this->end++; }
	}
	
		

	if (num > 0) { return this->addElem(ele, i,num); }
	//cout << "les = " << les << endl;
	return true;

}


// 尾部加入元素
template<class ElemType>
bool DArray<ElemType>::push_back(ElemType ele, long long i) {
	if (i <= 0) { return false; }
	// 扩容
	if (this->surplus() <= 0) {
		this->autoArrange(this->addsize);
	}
	// 往前移
	if (this->listsize - this->end < i) {
		this->resize();
	}

	for (; i > 0 && this->surplus() > 0; (this->size() == 0 ? this->end = 0 : this->end++), i--) {
		
		this->elem[end + 1] = ele;
	}
	if (i > 0) { return this->push_back(ele, i); }
	return true;
}


// 弹出最后一个元素
template<class ElemType>
ElemType DArray<ElemType>::pop_back() {
	if (this->size() == 0) {return _ERROR_;}
	this->end--;
	return this->elem[end+1];
}

// 通过下标删除
template<class ElemType>
bool DArray<ElemType>::delElem(long long i) {\
	// 数据不合法
	if (i < 0 || i >= this->size()) { return false; }
	// 靠近尾巴
	if (this->size() / i < 2) {
		for (long long j = i; j < this->end; j++) {
			this->elem[j] = this->elem[j + 1];
		}
		this->end--;
	}
	// 靠近头部
	else {
		for (long long j = i; j > this->begin; j--) {
			this->elem[j] = this->elem[j - 1];
		}
		this->begin++;
	}
	return true;
}
// 删除区间
template<class ElemType>
bool DArray<ElemType>::delElem(long long d_begin, long long d_end) {
	// 数据不合法
	if (!(0 <= d_begin && d_begin <= d_end && d_end < this->size())) { return false; }
	long long L = d_end - d_begin + 1;
	// 靠近尾巴
	if ((d_begin - this->begin) >= (this->end - d_end)) {
		for (long long j = d_end; j <= this->end;j++) {
			this->elem[j - L] = this->elem[j];
		}
		this->end -= L;
	}
	// 靠近头部
	else {
		for (long long j = d_begin - 1;  j >= this->begin; j--) {
			this->elem[j + L] = this->elem[j];
		}
		this->begin += L;
	}
	return true;
}



// 构造函数
template<class ElemType>
DArray<ElemType>::DArray(long long size,double addsize) {
	this->listsize = (size <= 0 ? 9 : size-1);
	this->addsize= (addsize <= 1 ? 1.5 : addsize);
	this->begin = 0;
	this->end = -1;
	this->elem =(ElemType*) malloc((listsize + 1) * sizeof(ElemType));
	for (long long j = 0; j < listsize; j++) {
		elem[j] = (ElemType)0;
	}
}
// 拷贝构造
template<class ElemType>
DArray<ElemType>::DArray(const DArray& arr) {
	this->listsize = arr.listsize;
	this->addsize = arr.addsize;
	this->begin = arr.begin;
	this->end = arr.end;
	this->elem = (ElemType*)malloc((arr.listsize + 1) * sizeof(ElemType));
	for (long long j = 0; j < arr.listsize; j++) {
		this->elem[j] = arr.elem[j];
	}
}