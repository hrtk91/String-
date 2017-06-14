#pragma once
#include <iostream>
#include <functional>
#include <vector>

class String
{
public:
	String();
	String(int, char);
	String(const char*);
	String(const char*, const char*);
	String(const String&);
	~String();

	// �����񂪋󂩂ǂ�����Ԃ��܂��B
	bool IsEmpty() const;
	// �i�[����Ă��镶����̃T�C�Y��Ԃ��܂��B
	int Size() const;
	// �m�ۂ���Ă��郁�����̈�̕Ԃ��܂��B
	int Capacity() const;
	// �ŏ��̕����v�f��Ԃ��܂��B
	char GetFront() const;
	// �Ō�̕����v�f��Ԃ��܂��B
	char GetBack() const;
	// char�z��ɂ��ĕԂ��܂��B
	const char* ToCharArray() const;
	// �w�肳�ꂽ�������������A�ŏ��Ɍ��������v�f�ԍ���Ԃ��܂��B
	int Find(char) const;
	// �w�肳�ꂽ��������������A�ŏ��Ɍ�������������̐擪�ԍ���Ԃ��܂��B
	int Find(const String&) const;
	// �i�[����Ă��镶�����������܂��B
	void Clear();
	// �w�肳�ꂽ�o�C�g���̃��������m�ۂ��ĕێ����܂��B
	void Reserve(int);
	// �w�肳�ꂽ���������m�ۂł���悤�Ƀ��������m�ۂ��܂��B
	void Resize(int, char ch = ' ');
	// �Ō���̕����v�f��Ԃ��A�z�񂩂�폜���܂��B
	char PopBack();
	// �Ō���Ɏw�肳�ꂽ�����v�f��ǉ����܂��B
	void PushBack(char);
	// �w�肳�ꂽ�C���f�b�N�X�ɕ������i�[���܂��B
	void Insert(int index, char ch);
	// �w�肳�ꂽ�C���f�b�N�X�̕������������܂��B
	void Erase(int index);

	char operator[](int) const;
	String& operator=(const String& str);
	String& operator+=(char ch);
	String& operator+=(const String& str);
	String& operator+(const String& str);
	friend bool operator==(const String&, const String&);
	friend std::ostream& operator<<(std::ostream&, const String&);
private:
	char *_data;
	int _size;
	int _allocSize;
	String& _Concatenate(const String&);
};
