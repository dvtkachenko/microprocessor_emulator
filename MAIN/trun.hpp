 // TRun.hpp - ���������� ������� TKvantLevel,TMikroTaktLevel,TTaktLevel,
 //            TRun, ����������� ��������� ��������

# ifndef __TRUN_HPP
# define __TRUN_HPP 1

# include "main\const.hpp"
# include "main\TScheme.hpp"
# include "main\TLink.hpp"
# include "service\TQueue.hpp"

// // // // // // // // // // // // // // // // // // // // // // // //

  class TKvantLevel
    {
      private:

      public:
    	//
    	TScheme *Scheme;  // ��������� �� ������������ �����
    	int TraceFlag;    // ���� ����������� �� ������ ������
    	//
    	TKvantLevel();
    	~TKvantLevel();
    	void SetScheme(TScheme *SchemePtr);
    	void __fastcall Run(void);
    } ;

// // // // // // // // // // // // // // // // // // // // // // // //

  class TMikroTaktLevel : public TKvantLevel
    {
      private:
    	//
    	byte Cur,Prev;

      public:
        int Enable;     // ���� ���������� ���������� �� ������ ������
                        // ����-�� � ������ ���������� � ������������
                        // ����� �����������(�.�. ��� ���������� ������������
                        // �������� ��������� �������������)

    	int TraceFlag;  // ���� ����������� �� ������ ������
    	//
    	TMikroTaktLevel();
    	~TMikroTaktLevel();
    	void __fastcall Run(void);
    	void SetScheme(TScheme *SchemePtr)
          {
    	    TKvantLevel::SetScheme(SchemePtr);
    	  };
    } ;


// // // // // // // // // // // // // // // // // // // // // // // //

  class TTaktLevel : public TMikroTaktLevel
    {
      private:

      public:
        int Enable;     // ���� ���������� ���������� �� ������ ������
                        // ����-�� � ������ ���������� � ������������
                        // ����� �����������(�.�. ��� ���������� ������������
                        // �������� ��������� �������������)

    	int TraceFlag;  // ���� ����������� �� ������ ������
    	//
    	TTaktLevel();
    	~TTaktLevel();
    	void __fastcall Run(void);
    } ;

// // // // // // // // // // // // // // // // // // // // // // // //

  class TRun : public TTaktLevel
    {
      private:

      public:
        int Enable;     // ���� ���������� ���������� �� ������ ������
                        // ����-�� � ������ ���������� � ������������
                        // ����� �����������(�.�. ��� ���������� ������������
                        // �������� ��������� �������������)

//    	int TraceFlag;  // ���� ����������� �� ������ ������
    	//
    	TRun();
    	~TRun();
    	void SetScheme(TScheme *SchemePtr);
    	void SetTraceLevel(int NumLevel);
    	int GetTraceLevel(void);
    	void __fastcall Run(void) throw(const char*);
    } ;

extern TRun *RunScheme;

# endif  // __TRUN_HPP
