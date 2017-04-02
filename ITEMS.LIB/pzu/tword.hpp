 // TWord.hpp  -  ���������� ������ TPzu ������������� �������� -
 //		 ���������� ���

# ifndef __TWORD_HPP
# define __TWORD_HPP 1

# include "..\..\main\TModItem.hpp"

  // ����� ����������� ���� ����� ������ (8 - 128) ���
  class TWord
    {
      private:
	//
	int WordLength;

      public:
	//
	int Error;

	byte *Word;     // ����� ������

	// �����������
	TWord(int Length);

	// ����������
	~TWord();
	//
	void Clear(void); // ��������� �������� ����� ������
	void Read(byte *ptr);      // ��������� ������ �� ������
	void Write(byte *ptr);     // ��������� ������ � ������

    } ;

 //---------------------------------------------------------------------------

# endif  // __TWORD_HPP
