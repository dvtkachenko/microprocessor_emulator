 // TTranslator.hpp  -  ���������� ������ - ����������� �����
 //   ������� ��������� :
 //     - ��� ����� �����
 //   �������� ��������� :
 //     - ������� ���������� �� ������� ������ TModelItem:
 //       - ������� �����������
 //       - ������� ��������� ���������
 //     - ������� ��������� ���� ModelLinkParameters
 //       (��������� ����� ���� "����� �������� - ����� ����")

# ifndef __TTRANS_HPP
# define __TTRANS_HPP 1

# include "const.hpp"
# include "..\service\TQueue.hpp"
# include "TModItem.hpp"
# include <stdio.h>
# include <windows.h>
# include <vcl\forms.hpp>

# define BUFFER_SIZE       4096
# define NAME_ELEMENT_LENGHT  10

# define STRING_CONTINUE   0x5C    //  '\'

# define NOTUSED_PARTITION  0
# define ELEMENTS_PARTITION 1
# define WIRES_PARTITION    2

# define EMPTY_STRING       1
# define NOT_EMPTY_STRING   0

//# define LINK_STRING        1
//# define ELEMENT_STRING     2

# define FILE_NAME_ERROR           1
# define OUT_OF_MEMORY             2
# define INVALID_END_OF_FILE       3
# define INVALID_HEADER_STRING     4
# define LOGIC_ERROR               5

# define ERROR_LOADING_DLL         6
# define ERROR_READING_ITEMS_LIB   7

  typedef BOOL (WINAPI *PROCPTR) (TModelItem**,int,TComponent *);

  typedef struct DescribeElement
    {
      char NameElement[NAME_ELEMENT_LENGHT+1];
      char NameDLL[9];
    } DescribeElement;

  // ���������� �����
  class TTranslator
    {
      private:
        // ������� ���� ��������� � ��������������� �� ��������� DLL
        TQueue *QueueDescribe;
        // ������� ���������� ID ���� ����������� DLL
        TQueue *QueueDLL;

        char PathToDLL[MAX_PATH];
	    char *FileNameBuffer;
	    char *BufferString;
	    int Flag;
     	FILE *FileHandle;
    	//
    	int EmptyString(char *string); // ���������� EMPTY_STRING ���� ������
				       // �� �������� ������ ����� ��������
				       // � ENTER
    	//
        bool FindDLL(char *NameModel,char *FileNameDLL);
        bool LoadDLL(char *FileNameDLL,TModelItem **Model,int NumberElement);
        void FreeAllDLL(void);
        void ReadItemsLib(void); // ������ ���� �������� ���������� ���������
    	void ReadOneSchemeComponent(void);
    	void MakeOneBusLink(TQueue *WiresQueue);
    	void MakeOneElement(TQueue *GenerQueue,TQueue *ItemsQueue);
    	int Error;      // ��������� �� ������ ��� �������������
			// (����. ���� ������)
    	int ErrorCode;  // ��������� �� ��� ������, ���� ��� ����

      public:
    	//
    	int GetError() { return Error; };
    	int GetErrorCode() { return ErrorCode; };
    	// ������� �����
    	// ��������� �� �������� ������� ���������� �� ������� ������� ���������
    	void Translate(TQueue *GenerQueue,TQueue *ItemsQueue,TQueue *WiresQueue);

     	// �����������
    	TTranslator(const char *FileName);

    	// ����������
    	~TTranslator(void);
    };

# endif  // __TTRANS_HPP
