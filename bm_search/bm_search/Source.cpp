#include <iostream>
using namespace std;

const int N = 256; // количество возможных символов


class String
{
	char* text_;
	int length_;

	int* createSymbolTable_(const String& word);
	void enterAnswer_(int firstSymbol, int endSymbol);

public:
	String(const char* Text);
	~String() { delete text_; };


	int bmSearch(const String& word);
};

String::String(const char* Text)
{
	for (length_ = 0; Text[length_] != '\0'; length_++);
	text_ = new char[length_];
	for (int i = 0; i < length_; i++) text_[i] = Text[i];
}

int String::bmSearch(const String& word)
{
	int* symbolTable = this->createSymbolTable_(word);
	
	int i = word.length_ - 1, j = word.length_ - 1;
	while (true)
	{
		if ((i < length_) && (j >= 0))
		{
			int k = i;
			j = word.length_ - 1;

			bool flag = true;
			while (flag)
			{
				if (j < 0) flag = false;
				else
				{
					if (text_[k] == word.text_[j]) { j--; k--; }
					else
					{
						i = i + symbolTable[text_[i] + 127];
						j = word.length_ - 1;
						flag = false;
					}
				}
				
			}
			
		}
		else
		{
			if (j >= 0)
			{
				cout << "String in text not found.\n";
				return -1;
			}
			else
			{
				this->enterAnswer_(i + 1 - word.length_, i);
				return (i + 1 - word.length_);
			}
		}
		
	}
}


int* String::createSymbolTable_(const String& word)
{
	int* Table = new int[N];

	for (int i = 0; i < N; i++) Table[i] = word.length_;

	for (int i = 0; i < (word.length_ - 1); i++) Table[word.text_[i] + 127] = word.length_ - 1 - i;

	return Table;
}


void String::enterAnswer_(int firstSymbol, int endSymbol)
{
	cout << "String in text find:\n";
	for (int i = 0; i < length_; i++)
	{
		if (i == firstSymbol) cout << '|';
		cout << text_[i] ;
		if (i == endSymbol) cout << '|';
	}
}


int main()
{
	String text("nranirarararararainininin");
	String word("rain");

	return text.bmSearch(word);
}