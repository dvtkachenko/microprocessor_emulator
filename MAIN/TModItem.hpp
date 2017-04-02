 // TModelItem.hpp - ���������� ������������  ������ �������������
 //                  �������� TModelItem
# ifndef __TMODELITEM_H
# define __TMODELITEM_H 1

# include "const.hpp"
# include <alloc.h>
# include <vcl\forms.hpp>

  class TModelItem
    {
      private:
        byte NumParameters;   // ����� ���������� ������������� ��������

      public:
        TForm *ModelForm;
        int Error;            // ��������� �� ������ ��� �������������
                              // (����. ���� ������)
        byte *Parameters;     // ��������� �� ������ ������� ��������

    	int NumberElement;    // ����� �������� � �����
    	int Visible;          // ��������� �������� ��
			      // ������������ ������� ������� ��� ���

    	TModelItem(int Number)
          {
    	    NumberElement = Number;
            ModelForm = NULL;
    	    Parameters = NULL;
            Error = MY_NO_ERROR;
          };

    	virtual ~TModelItem()
           {
             if (Parameters!=NULL) free(Parameters);
           };

        virtual int  Init(string80 Array[]) { return (MY_NO_ERROR); };
        virtual int  InitPin(void) { return (MY_NO_ERROR); };

    	// ��������� ��������� �� Parameters �� ���������� ����������
    	virtual void LoadParam(void) {};
    	// ��������� ��������� �� ���������� ���������� � Parameters
    	virtual void StoreParam(void) {};
        virtual void Run() {};
    	virtual void Update() {};
    	virtual void Reset() {};

        virtual void Show()
          {
            ModelForm->Show();
            Update();
          }; 
    	
        virtual void SetToNormal()
          {
            ModelForm->Enabled = true;
            if(ModelForm != NULL) ModelForm->WindowState = wsNormal;
          };

    	virtual void SetToMinimized()
          {
            ModelForm->Enabled = false;
            if(ModelForm != NULL) ModelForm->WindowState = wsMinimized;
          };

    	void SetNumParameters(byte NumParam) { NumParameters = NumParam;};
        byte GetNumParameters(void)  { return (NumParameters);};
        //
    	byte *GetParamPtr() { return Parameters; };
    } ;

  // ����� �������������� ��������
  // ������������ ��� ��������� ��� �������
  // ��������������� ������ �� ������ ���������
  // ����� �������������� � ���������� ������ ������ Run()
  class UndefLevelError 
    {
      int ErrorCode;
    };

# endif  // __TMODELITEM_H
