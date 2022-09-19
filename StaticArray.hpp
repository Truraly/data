/*
* ��̬����
* ����: Truraly
* ����: ���ݽṹСʵ��
* ��ݵ���: #include"StaticArray.hpp"
* ��ϸ���ܼ�README.md
* ��������Ҫ��Ϣ�����ҹ��µ�лл
* ��Щ�ط��������˵�ע��û�ģ����ø��ˣ����ⲻ��
*/

#pragma once
#include<string.h>// ���ӻ��Ҳ���NULL
#include<iostream>// ���������
using namespace std;



template<class ElemType>
class StArray {
public:
	// ����ͷָ��
	ElemType* elem;
	// ��ǰԪ������
	// ע��long long ���ԼΪ9*10^18�������ᱨ��
	long long length;
	// �������ռ�
	long long listsize;


	// �������м���Ԫ��
	// ���ز���Ԫ�ص��±�
	// ������һ��Ԫ�أ��򷵻����һ��Ԫ���±�
	// �������������һ��Ԫ�غ�����ᳬ�������ݲ��Ϸ����᷵��-1
	long long add(
		ElemType ele, 
		long long i = -1, // ����λ�ã�Ĭ���ڶ�β
		long long num=1 // ����������Ĭ��Ϊ1
	);

	// ͨ���±�ɾ��Ԫ��
	bool delElem(long long i);

	// ���ҵ� st ������������Ԫ��
	long long find(
		ElemType ele, 
		long long st, 
		bool f=true // ��������Ĭ����������
	);

	// ���ҵ�1������������Ԫ��
	long long find(
		ElemType ele,  
		bool f = true // ��������Ĭ����������
	);

	// ͨ���±����,Խ�緵��NULL
	ElemType operator[](long long i);

	// ����һ����������/����(false)��,
	// �����±�Ϊstart��end��Ԫ�غϲ���������
	// ���������С�Ĳ��ֽ��ᱻ��ȥ
	bool merge(
		StArray arr, // Ŀ������
		long long start=0, // ��ʼԪ���±�,Ĭ��Ϊ0
		long long end=-1, // ����Ԫ���±�,Ĭ��Ϊ����β��
		bool b_sx=true // ����˳��Ĭ��Ϊ����false�����鵹������
	);

	// ���������±��start��end��Ԫ������(����)
	bool sort(
		long long start, // ��ʼԪ���±�
		long long end, // ����Ԫ���±�
		bool k = true // ����˳��Ĭ��Ϊ����
	);

	// �������Ԫ��
	bool print(
		string s="", // ��������ǰ�������
		string x = "", // ������Ԫ���м������
		string e = "" // ������ĩβ�����֣������Զ����У�
	);

	// ��������
	~StArray() { delete elem; }
	// Ĭ�Ϲ��캯��,�ᴴ��һ���޷�ʹ�õ�����
	StArray();
	// ��ʼ���������ܷ���i��Ԫ�ص�����
	StArray(long long i);
	// ��¡���캯��
	StArray(StArray& arr);
};





// ----------------����ʵ��-----------
// ͨ��λ��ɾ��
template<class ElemType>
bool StArray<ElemType>::delElem(long long i) {
	// ֱ�Ӹ���
	// ���ݲ��Ϸ�
	if (i < 0 || i >= length) { return false; }
	// �ƶ�λ��
	for (long long j = i; j < length - 1; j++) {
		elem[j] = elem[j + 1];
	}
	length--;
	return true;
}


// ���������,Ĭ�ϲ���β��,�����±�
// ����ָ������λ�ã���������
template<class ElemType>
long long StArray<ElemType>::add(ElemType ele, long long i, long long num) {
	// ����
	if (length > listsize - num || num < 0) { return -1; }
	// ������
	if (i == -1) {
		// ֱ���ں������
		for (long long j = 0; j < num; j++) {
			elem[length] = ele;
			length++;
		}
		// ���ز�������һ����
		return length - 1;
	}
	// �м����
	else {
		// ���ݲ��Ϸ�
		if (i > length) { return -1; }
		// Ԫ�غ���
		for (long long j = length - 1; j >= i; j--) {
			elem[j + num] = elem[j];
		}
		// ����Ԫ��
		long long wz;// ��¼δ֪
		for (wz = i; wz < i + num; wz++) {
			elem[wz] = ele;
			length++;
		}
		// �������һ��λ��
		return wz - 1;
	}
}



// ͨ���±����,��Խ��
template<class ElemType>
ElemType  StArray<ElemType>::operator[](long long i) {
	// �쳣�򷵻ص�һ��Ԫ��
	if (i < 0 || i >= length) { return NULL; }
	return elem[i];
}


template<class ElemType>
long long StArray<ElemType>::find(ElemType ele, bool f ) {
	return this->find(ele, 1, f);
}
// ���ҵ�һ������������Ԫ�أ�false����
template<class ElemType>
long long StArray<ElemType>::find(ElemType key, long long st, bool f) {
	// ���ݲ��Ϸ�
	if (st < 1) { return -2; }
	// �������
	if (f) {
		for (long long j = 0; j < length; j++) {
			if (elem[j] == key) {
				if (st > 1) { st--; }
				else { return j; }
			}
		}
		return -1;
	}
	// �������
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


// �ϲ�2������
template<class ElemType>
bool StArray<ElemType>::merge(StArray arr, long long start, long long end, bool b_sx) {
	if (start < 0) { return false; }
	if (end < 0) { end = arr.length - 1; }
	// ���ݲ��Ϸ�
	if (start > arr.length - 1 || end > arr.length - 1 || start > end) { return false; }
	// �����ȡ
	if (b_sx) {
		for (long long j = start; j <= end && this->length < listsize; j++) {
			if (!this->add(arr.elem[j])) { return false; }
		}
		return true;
	}
	// �����ȡ
	else {
		for (long long j = arr.length - 1 - start; j >= arr.length - 1 - end && this->length < this->listsize; j--) {
			if (!add(arr.elem[j])) { return false; }
		}
		return true;
	}
}

// �������ڵ�Ԫ������,Ĭ������
template<class ElemType>
bool StArray<ElemType>::sort(long long start, long long end, bool k) {
	// ���벻�Ϸ�
	if (!( 0<= start && start <= end && end <= this->length)) { return false; }
	if (start == end) { return true; }
	// ˳��
	if (k) {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = start;
			i_min = end;
			// Ѱ�ҵ�һ����key���
			while (elem[start] >= elem[i_max]) {
				i_max++;
				if (i_max >= end) { break; }
			}
			while (elem[start] <= elem[i_min]) {
				i_min--;
				if (i_min <= start) { break; }
			}
			// ����
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
	// ����
	else {
		long long i_max;
		long long i_min;
		while (1) {
			i_max = end;
			i_min = start;
			// ���ұ�Ѱ�ҵ�һ����key���
			while (elem[i_max]<=elem[end]) {
				i_max--;
				if (i_max <= start) { break; }
			}
			// �����Ѱ�ҵ�һ����keyС��
			while (elem[end] <= elem[i_min]) {
				i_min++;
				if (i_min >= end) { break; }
			}
			// ����
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





// ��ʼ��
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
		// ����ֵ��ʼ��
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
		// ����ֵ��ʼ��
		for (long long j = 0; j < i; j++) {
			elem[j] = (ElemType)0;// ǿ��ת��
		}
	}
}
// ��¡
template<class ElemType>
StArray<ElemType>::StArray(StArray<ElemType>& arr) {
	this->elem = new ElemType[arr.listsize];
	this->listsize = arr.listsize;
	this->length = arr.length;
	// ����Ԫ��
	for (long long j = 0; j < arr.length; j++) {
		elem[j] = arr.elem[j];
	}
}

// Ĭ�Ϲ��캯��
template<class ElemType>
StArray<ElemType>::StArray() {
	elem = NULL;
	length = -1;
	listsize = -1;
}





// �������
template<class ElemType>
bool StArray<ElemType>::print(string s,string x, string e) {
	
	cout << s;
	if (length == 0) { cout << "����Ϊ��"; }
	for (long long j = 0; j < length; j++) {
		cout << elem[j] << (j+1>=length?"":x);
	}
	cout << e;
	return true;
}