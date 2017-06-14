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

	// 文字列が空かどうかを返します。
	bool IsEmpty() const;
	// 格納されている文字列のサイズを返します。
	int Size() const;
	// 確保されているメモリ領域の返します。
	int Capacity() const;
	// 最初の文字要素を返します。
	char GetFront() const;
	// 最後の文字要素を返します。
	char GetBack() const;
	// char配列にして返します。
	const char* ToCharArray() const;
	// 指定された文字を検索し、最初に見つかった要素番号を返します。
	int Find(char) const;
	// 指定された文字列を検索し、最初に見つかった文字列の先頭番号を返します。
	int Find(const String&) const;
	// 格納されている文字を消去します。
	void Clear();
	// 指定されたバイト分のメモリを確保して保持します。
	void Reserve(int);
	// 指定された文字数を確保できるようにメモリを確保します。
	void Resize(int, char ch = ' ');
	// 最後尾の文字要素を返し、配列から削除します。
	char PopBack();
	// 最後尾に指定された文字要素を追加します。
	void PushBack(char);
	// 指定されたインデックスに文字を格納します。
	void Insert(int index, char ch);
	// 指定されたインデックスの文字を消去します。
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
