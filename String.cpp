#include "String.h"

std::ostream& operator << (std::ostream& stream, const String& str)
{
	stream << str.ToCharArray();
	return stream;
}
bool operator==(const String& left, const String& right)
{
	if (left.Size() != right.Size())
	{
		return false;
	}

	const char* ltemp = left.ToCharArray();
	const char* rtemp = right.ToCharArray();
	for (int i = 0; i < left.Size(); i++)
	{
		if (ltemp[i] != rtemp[i])
		{
			return false;
		}
	}
	return true;
}


String::String()
{
	this->_size = 0;
	this->_allocSize = 8;
	this->_data = new char[this->_allocSize];
	memset(this->_data, '\0', this->_allocSize);
}
String::String(int size, char c)
{
	this->_size = size;
	this->_allocSize = size + 1;
	this->_data = new char[this->_allocSize];

	int i;
	for (i = 0; i < this->_size; i++)
	{
		this->_data[i] = c;
	}
	this->_data[i] = '\0';
}
/// <summary>指定された文字列で初期化</summary>
String::String(const char* src)
{
	// 引数の文字数を数える
	int i = 0;
	this->_size = 0;
	while (src[i++] != '\0');
	this->_size = i - 1;

	// メモリ領域を文字数+1確保
	this->_allocSize = i;
	this->_data = new char[this->_allocSize];

	// 文字列をコピーし最後尾にnull文字追加
	for (i = 0; src[i] != '\0'; i++)
	{
		this->_data[i] = src[i];
	}
	this->_data[i] = '\0';
}
/// <summary>6.
String::String(const char* first, const char *last)
{
	// 引数の文字数を数える
	int i = 0;
	this->_size = 0;
	while (first[i++] != last[0]);
	this->_size = i - 1;

	// メモリ領域を文字数+1確保
	this->_allocSize = i;
	this->_data = new char[this->_allocSize];

	// 文字列をコピーし最後尾にnull文字追加
	for (i = 0; first[i] != last[0]; i++)
	{
		this->_data[i] = first[i];
	}
	this->_data[i] = '\0';
}
/// 7.
String::String(const String &str)
{
	this->_size = str._size;
	this->_allocSize = str._allocSize;
	this->_data = new char[this->_allocSize];
	
	int i = 0;
	for (i = 0; str._data[i] != '\0'; i++)
	{
		this->_data[i] = str._data[i];
	}
	this->_data[i] = '\0';
}
String::~String()
{
	delete[] this->_data;
}
bool String::IsEmpty() const
{
	return (this->_size <= 0) ? true : false;
}
int String::Size() const
{
	return this->_size;
}
int String::Capacity() const
{
	return this->_allocSize - 1;
}
char String::GetFront() const
{
	if (this->Size() > 0)
	{
		return this->_data[0];
	}
	else
	{
		return '\0';
	}
}
char String::GetBack() const
{
	if (this->IsEmpty() == false)
	{
		return this->_data[this->Size() - 1];
	}
	else
	{
		return '\0';
	}
}
char String::operator[](int index) const
{
	if (0 <= index && index <= this->Size() && this->IsEmpty() == false)
	{
		return this->_data[index];
	}
	else
	{
		throw std::range_error("添字が無効です。");
	}
}
const char* String::ToCharArray() const
{
	return this->_data;
}
int String::Find(char ch) const
{
	int result = -1;

	for (int i = 0; i < this->_size; i++)
	{
		if (this->_data[i] == ch)
		{
			result = i;
			break;
		}
	}

	return result;
}
int String::Find(const String& str) const
{
	int result = -1;
	std::function<bool(const char*, const char*, int)> reclusive = [&reclusive](const char* str, const char* source, int sourceSize) -> bool {
		if (str[0] == source[0])
		{
			if (str[1] == '\0')
			{
				return true;
			}
			else
			{
				if (sourceSize > 0)
				{
					return reclusive(&str[1], &source[1], sourceSize-1);
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	};

	for(int i = 0; i < this->Size(); i++)
	{
		if (str[0] == this->_data[i])
		{
			bool res = reclusive(str.ToCharArray(), &this->_data[i], this->Size() - i);
			if (res == true)
			{
				result = i;
				break;
			}
		}
	}

	return result;
}
void String::Clear()
{
	this->_size = 0;
	this->_data[0] = '\0';
}
void String::Reserve(int capacity)
{
	if (capacity < 0)
	{
		throw std::range_error("マイナス値を入れないでください。");
	}
	// 指定されたキャパシティが今より大きければ拡張
	if (capacity > this->Capacity())
	{
		// 新しい領域を確保してnull文字で初期化
		int allocsize = capacity + 64;
		char* reserve = new char[allocsize];
		memset(reserve, '\0', allocsize);

		// 元のデータを新しい領域にコピーする
		int i;
		for (i = 0; i < this->Size(); i++)
		{
			reserve[i] = this->_data[i];
		}

		// 古い領域を消して新しい領域に差し替え
		delete[] this->_data;
		this->_data = reserve;
		// アロックサイズを刷新
		this->_allocSize = allocsize;
	}
}
void String::Resize(int size, char ch)
{
	if (size < 0)
	{
		throw std::range_error("マイナス値は入れないでください。");
	}
	// 指定されたサイズが今より大きければ拡張
	if (size > this->Capacity())
	{
		this->Reserve(size);
		// 拡張した文字数分chを格納しておく
		for (int i = this->Size(); i <= this->Capacity(); i++)
		{
			this->_data[i] = ch;
		}
		this->_size = size;
		this->_data[size] = '\0';
	}
	// 小さければ拡張せず文字列末尾となるインデックスにnull文字セット
	else
	{
		this->_size = size;
	}
	this->_data[size] = '\0';
}
char String::PopBack()
{
	// 文字列末尾のインデックスを取得
	int index = this->Size() - 1;
	// 文字列がないならなにもしない
	if (index < 0)
	{
		throw std::range_error("文字がありません。");
	}
	
	char ret = this->_data[index];
	this->_data[index] = '\0';
	this->_size--;

	return ret;
}
void String::PushBack(char ch)
{
	// キャパシティが足りてないなら増やす
	if (this->Capacity() <= this->Size())
	{
		this->Reserve(this->Size() + 1);
	}
	// 末尾に文字を追加し、サイズをインクリメント
	this->_data[this->Size()] = ch;
	this->_data[this->Size() + 1] = '\0';
	this->_size++;
}
void String::Insert(int index, char ch)
{
	// 引数チェック
	if (index < 0 || this->Size() < index)
	{
		throw std::range_error("引数indexが無効です。");
	}
	
	// 一文字分文字列サイズを大きくする
	this->Resize(this->Size() + 1);

	// 指定されたインデックスまでの文字列を後ろに寄せる
	for(int i = this->Size(); i > index; i--)
	{
		this->_data[i] = this->_data[i - 1];
	}
	// 指定のインデックスに文字を挿入
	this->_data[index] = ch;
	this->_data[this->Size()] = '\0';
}
void String::Erase(int index)
{
	if (index < 0 || index >= this->Size())
	{
		throw std::range_error("引数が無効です。");
	}

	for (int i = index; i < this->Size(); i++)
	{
		this->_data[i] = this->_data[i + 1];
	}
	this->_data[this->Size()] = '\0';
	this->_size--;
}
String& String::operator=(const String& str)
{
	const char* temp = str.ToCharArray();
	this->Resize(str.Size());
	for (int i = 0; i < str.Size(); i++)
	{
		this->_data[i] = str[i];
	}
	this->_data[str.Size()] = '\0';
	return *this;
}
String& String::operator+=(char ch)
{
	this->PushBack(ch);
	return *this;
}
String& String::operator+=(const String& str)
{
	return this->_Concatenate(str);
}
String& String::operator+(const String& str)
{
	return this->_Concatenate(str);
}
String& String::_Concatenate(const String& str)
{
	const char* temp = str.ToCharArray();
	for (int i = 0; i < str.Size(); i++)
	{
		this->PushBack(temp[i]);
	}
	return *this;
}
