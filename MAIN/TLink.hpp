 // TLink.hpp - ���������� ������ TLink, ������������ ���� �����
 //             ���� ����� (���� � ����� ����� ���� ������ ����)

# ifndef __TLINK_HPP
# define __TLINK_HPP 1

# include "const.hpp"

// // // // // // // // // // // // // // // // // // // // // // // //

  class TLink
    {
      private:

	byte **LinkPtr; //  ��������� �� ������ �������� ��������������
                        //  � ����� ����
        int NumWires;   //  ���-�� �������� �������������� � ����� ����

	byte PreviousLevel;  // ���������� ��������� �����
	byte CurrentLevel;   // ������� ��������� �����

      public:
        int Error;      // ��������� �� ������ ��� �������������
                        // (����. ���� ������)

	int LevelChangeFlag;  // ���� ��������������� � 1, ���� ����������
			      // ��������� ����� ���� �� ����� ��������

    	TLink(int _NumWires);
        ~TLink();

        //  ��������� Init ��������� ������������� �����
        void Init(byte **LinksPtr);

        //  ��������� Transmit ������������ ��������������� �������
        //  � ����� � ����� ���� , �� �� ������
        void Transmit(void);

    } ;

# endif  // __TLINK_HPP
