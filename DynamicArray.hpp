/*
* ��̬����
* ����: Truraly
* ���� : ���ݽṹСʵ��
* ��ݵ��� : #include"DynamicArray.hpp"
* ע������ :
	1. ����δ֪����ת����������⣬������ʱ��֧��ʹ�÷ǳ������ͣ��Լ��Զ�������
	2. λ���ʼΪ0
	3. ͨ��������������������᷵��false/-1
	4. ɾ�������ʱ������ķ����ƶ����ݣ�����ɾ���ڶ���Ԫ�أ��Ὣ��ߵ�Ԫ�أ�1���������ƶ�
	5. ����Ŀռ䲻�ᱻ�Զ��������Ҫ�ֶ�����

* ����ʵ����ֱ�ӷ�װSTL
* һ��ʼд���ˣ�û�滮�����滹�����¹滮
* 
*/
#pragma once
#include<string.h>// ���ӻ��Ҳ���NULL
#include<iostream>// ���������
#include<stdlib.h>
using namespace std;


# define _ERROR_ NULL;// ָ����������ʱ���ص�ElemType���͵�ֵ��Ĭ��ΪNULL
template<class ElemType>
class DArray {
private:
	// ����ͷָ��
	ElemType* elem;
	// ��ǰ��С�±�
	long long begin;
	// ��ǰ����±�
	long long end;
	// �������ռ��±�
	long long listsize;
	// ���ݱ���
	double addsize;
public:
	// �ж������Ƿ�Ϊ��
	inline bool empty();
	// ����������
	inline long long capacity();
	// ��ȡ������Ԫ������
	inline long long size();
	// ��ȡʣ������
	inline long long surplus();
	// ����ָ�������ĳ���Ϊnum
	// ���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
	// �Ὣ�����ƶ�����ͷ
	// ��Ϊ-1�򵥴�Ϊ������
	bool resize(int num=-1);
	// ����ָ�������ĳ���Ϊnum
	// �������䳤������[elem]�����λ�ã�����յĿռ佫�ᱻ���Ͽ��Է��ʵ����ݣ�
	// ���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
	// �Ὣ�����ƶ�����ͷ
	bool resize(int num, ElemType elem);


	// �޸��Զ����ݷ���
	bool changeAddSize(double i);
	// Ԥ���ռ�
	bool reserveSpace(long long i);
	// �Զ�����,��ʣ��ռ����ΪĿǰ��k��
	bool autoArrange(double k);
	
	// ͨ���±���ʷ��ʲ�������_ERROR_
	ElemType operator[](long long i);
	// ���ʶ�Ӧ�±��Ԫ�ص�ָ��
	// ���û�л᷵��NULLָ�룬�����[]�����ܼ��ٳ���
	ElemType* at(long long i);
	// ���������е�һ������Ԫ�أ�����Ϊ���򷵻�_ERROR_
	ElemType front();
	// �������������һ������Ԫ�أ�����Ϊ���򷵻�_ERROR_
	ElemType back();
	// ���ҵ� st ������������Ԫ�ص��±꣬�Ҳ�������-1
	long long find(
		ElemType ele,
		long long st,
		bool f  // ��������Ĭ����������
	);

	// ���ҵ�1������������Ԫ�ص��±�
	long long find(
		ElemType ele,
		bool f = true // ��������Ĭ����������
	);


	// ����
	bool sort(
		long long start=-1 ,// ��ʼ����λ��
		long long end=-1,// ��������λ��
		bool sx=true// ˳��or����
	);
	// ��������
	bool swap(DArray& arr);
	// �������
	bool print(
		string s = "", // ��������ǰ�������
		string x = "", // ������Ԫ���м������
		string e = "" ,// ������ĩβ�����֣������Զ����У�
		bool sx=true// ���˳��
	);

	// �ϲ�
	bool merge(
		DArray& arr,
		bool del = false// �Ƿ�ɾ������Ķ���
	);
	// ����Ԫ��
	long long addElem(
		ElemType ele,
		long long i=-1,// ����λ��
		long long num=1// ��������
	);
	// β������Ԫ�أ�addElem��һ�ּ����ʽ
	bool push_back(
		ElemType ele,
		long long i=1// ��������
	);

	
	// �������һ��Ԫ�أ�����Ϊ���򷵻�_ERROR_
	ElemType pop_back();
	// ͨ���±�ɾ��
	bool delElem(long long i);
	// ɾ�����䣨���߽磩
	bool delElem(
		long long begain, // ��ʼԪ���±�
		long long end// ����Ԫ���±�
	);
	// �������
	bool clear();

	// ���캯��
	DArray(long long size = -1, double addsize = -1);
	// ��������
	DArray(const DArray& arr);
	// ��������
	~DArray() { delete elem; }

};

// �ж������Ƿ�Ϊ��
template<class ElemType>
bool DArray<ElemType>::empty() {
	return end < 0 || begin < 0 || end < begin;
}
// ����������
template<class ElemType>
long long DArray<ElemType>::capacity(){
	return this->listsize + 1;
}
// ��ȡ������Ԫ������
template<class ElemType>
long long DArray<ElemType>::size() {
	if (this->end < 0 || this->begin < 0 || this->end < this->begin) { return 0; }
	return this->end-this->begin+1;
}
// ��ȡʣ������
template<class ElemType>
inline long long  DArray<ElemType>::surplus() {
	if (this->end < 0 || this->begin < 0 || this->end < this->begin) { return this->listsize+1; }
	return this->listsize-this->end+this->begin;
}
// ����ָ�������ĳ���Ϊnum�����������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
template<class ElemType>
bool DArray<ElemType>::resize(int num) {
	// �����޸�
	if (num == -1) { num = listsize + 1; }
	// ���ݲ��Ϸ�
	if (num < 0) { return false; }
	// ���ٿռ�,����ȴ�Ͷ�ԭ��������������
	ElemType* ne = (num == listsize + 1?this->elem: (ElemType*)malloc(num *sizeof(ElemType)));
	//ElemType* ne = new ElemType[num];
	if (num >= this->size()) {
		// ��ǰ��հ׵�ɾ�����ȥ
		for (long long i = 0; i < num; i++) {
			ne[i] = i > this->end-this->begin ? (ElemType)0 : this->elem[i-this->begin];
		}
		this->end = this->size()-1;
		this->begin = 0;
	}
	else {
		// ��Щ�᲻��ȥ��
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
// ����ָ�������ĳ���Ϊnum
// �������䳤������[elem]�����λ��
// ���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
template<class ElemType>
bool DArray<ElemType>::resize(int num, ElemType elem) {
	// ���ݲ��Ϸ�
	if (num < 0) { return false; }
	// �뵱ǰ��С��ͬ
	if (num == listsize + 1) {
		// ǰ���пհ�
		if (this->begin > 0) {
			for (long long i = 0; i < num; i++) {
				this->elem[i] = i > this->end - this->begin ? elem : this->elem[i - this->begin];
			}
		}
		// ǰ��û�հ�
		else {
			for (long long j = this->end + 1; j < num; j++) {
				this->elem[j] = elem;
			}
		}
		return true; 
	}
	// ���ٿռ�
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


// �޸��Զ����ݷ���
template<class ElemType>
bool DArray<ElemType>::changeAddSize(double i) {
	// ���ݲ��Ϸ�
	if (i <=1) { return false; }
	this->addsize = i;
	return true;
}
// Ԥ���ռ�
template<class ElemType>
bool DArray<ElemType>::reserveSpace(long long i){
	// ���ݲ��Ϸ�
	if (i < 0) { return false; }
	// ��С�㹻
	if (this->surplus() >= i) { return true; }
	else {
		return this->resize(this->size()+i);
	}
	return true;
}
// ������С
template<class ElemType>
bool DArray<ElemType>::autoArrange(double k) {
	// ���ݲ��Ϸ�
	if (k <= 1) { return false; }
	// 
	long long mb = this->size() * k;
	if (this->listsize == mb) { return true; }
	else {
		return this->resize(mb);
	}
	return true;
}

// ͨ���±����
template<class ElemType>
ElemType DArray<ElemType>::operator[](long long i) {
	// ���ݲ��Ϸ�
	if (i < 0 || i >= this->size()) { return _ERROR_; }
	return this->elem[this->begin + i];
}
// ���ʶ�Ӧ�±��Ԫ�ص�ָ�룬������
template<class ElemType>
ElemType* DArray<ElemType>::at(long long i) {
	if (i < 0 || i >= this->size()) { return NULL; }
	return &this->elem[this->begin + i];
}
//���������е�һ������Ԫ��
template<class ElemType>
ElemType DArray<ElemType>::front() {
	if (this->size() == 0) { return _ERROR_; }
	return elem[begin];
}
//�������������һ������Ԫ��
template<class ElemType>
ElemType DArray<ElemType>::back() {
	if (this->size() == 0) { return _ERROR_; }
	return elem[end];
}

// ���ҵ� st ������������Ԫ�ص��±�
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

// ���ҵ�1������������Ԫ�ص��±�
template<class ElemType>
long long DArray<ElemType>::find(ElemType ele, bool f) {
	return this->find(ele, 1, f);
}


// ����
template<class ElemType>
bool DArray<ElemType>::sort(long long start, long long end_, bool k) {
	if (start == -1) { start = this->begin; }
	if (end_ == -1) { end_ = this->end; }
	// ���벻�Ϸ�

	if (!(0 <= start && start <= end_ && end_ < this->size())) { return false; }
	// ��������
	if (start == end_) { return true; }
	// ����Ϊ��
	if (this->empty()) { return false; }
	start +=this-> begin;
	end_ += this->begin;
	// ˳��
	if (k) {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = start;
			i_min = end_;
			// Ѱ�ҵ�һ����key���
			while (this->elem[start] >= this->elem[i_max]) {
				i_max++;
				if (i_max >= end_) { break; }
			}
			while (this->elem[start] <= this->elem[i_min]) {
				i_min--;
				if (i_min <= start) { break; }
			}
			// ����
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
	// ����
	else {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = end;
			i_min = start;
			// ���ұ�Ѱ�ҵ�һ����key���
			while (this->elem[i_max] <= this->elem[end]) {
				i_max--;
				if (i_max <= start) { break; }
			}
			// �����Ѱ�ҵ�һ����keyС��
			while (this->elem[end] <= this->elem[i_min]) {
				i_min++;
				if (i_min >= end) { break; }
			}
			// ����
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

// ��������
template<class ElemType>
bool DArray<ElemType>::swap(DArray& arr) {
	// �����м����
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


// �������
template<class ElemType>
bool DArray<ElemType>::print(string s, string b, string c,bool sx) {
	cout << s;
	if (this->size() == 0) { cout << "����Ϊ��"; return false; }
	for (long long j = (sx ? begin : end); (sx ? j <= end : j >= begin); (sx ? j++ : j--)) {
		cout << elem[j] << (j<=begin&& !sx||j>=end&&sx? "" : b);
	}
	cout << c;
	return true;
}


// �������
template<class ElemType>
bool DArray<ElemType>::clear() {
	// ������
	this->begin = -1;
	this->end = -1;
	return true;
}





// �ϲ�
template<class ElemType>
bool DArray<ElemType>::merge(DArray<ElemType>& arr,bool del) {
	if (arr.size() < 1) { return false; }
	for (long long j = arr.begin; j <= arr.end; j++) {
		if (!this->addElem(arr.elem[j])) {
			// ����
			return true;
		}
	}
	if (del) {
		arr.~DArray();// ɾ������Ķ���
	}
	return true;
}









// ����Ԫ��
template<class ElemType>
long long DArray<ElemType>::addElem(ElemType ele, long long i, long long num ) {
	// �����޸�
	if (i == -1) { i =(this->size()==0?0: this->end + 1) ; }
	if (i < -1 || num < 1||i>this->size()) { return false; }
	// ����
	if (this->surplus()<=0) {
		this->autoArrange(this->addsize);
	}

	// ���������ƶ�
	if (this->begin - i < this->end - i && this->begin>0) {
	
		
		for (long long j = this->begin; j <= i; j++) {
			this->elem[j -1] = this->elem[j];
		}
		this->elem[i] = ele;
		num--;
		this->begin --;
		
	}
	// ������
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


// β������Ԫ��
template<class ElemType>
bool DArray<ElemType>::push_back(ElemType ele, long long i) {
	if (i <= 0) { return false; }
	// ����
	if (this->surplus() <= 0) {
		this->autoArrange(this->addsize);
	}
	// ��ǰ��
	if (this->listsize - this->end < i) {
		this->resize();
	}

	for (; i > 0 && this->surplus() > 0; (this->size() == 0 ? this->end = 0 : this->end++), i--) {
		
		this->elem[end + 1] = ele;
	}
	if (i > 0) { return this->push_back(ele, i); }
	return true;
}


// �������һ��Ԫ��
template<class ElemType>
ElemType DArray<ElemType>::pop_back() {
	if (this->size() == 0) {return _ERROR_;}
	this->end--;
	return this->elem[end+1];
}

// ͨ���±�ɾ��
template<class ElemType>
bool DArray<ElemType>::delElem(long long i) {\
	// ���ݲ��Ϸ�
	if (i < 0 || i >= this->size()) { return false; }
	// ����β��
	if (this->size() / i < 2) {
		for (long long j = i; j < this->end; j++) {
			this->elem[j] = this->elem[j + 1];
		}
		this->end--;
	}
	// ����ͷ��
	else {
		for (long long j = i; j > this->begin; j--) {
			this->elem[j] = this->elem[j - 1];
		}
		this->begin++;
	}
	return true;
}
// ɾ������
template<class ElemType>
bool DArray<ElemType>::delElem(long long d_begin, long long d_end) {
	// ���ݲ��Ϸ�
	if (!(0 <= d_begin && d_begin <= d_end && d_end < this->size())) { return false; }
	long long L = d_end - d_begin + 1;
	// ����β��
	if ((d_begin - this->begin) >= (this->end - d_end)) {
		for (long long j = d_end; j <= this->end;j++) {
			this->elem[j - L] = this->elem[j];
		}
		this->end -= L;
	}
	// ����ͷ��
	else {
		for (long long j = d_begin - 1;  j >= this->begin; j--) {
			this->elem[j + L] = this->elem[j];
		}
		this->begin += L;
	}
	return true;
}



// ���캯��
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
// ��������
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