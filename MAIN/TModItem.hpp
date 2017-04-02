 // TModelItem.hpp - ќбъ€вление абстрактного  класса моделируемого
 //                  элемента TModelItem
# ifndef __TMODELITEM_H
# define __TMODELITEM_H 1

# include "const.hpp"
# include <alloc.h>
# include <vcl\forms.hpp>

  class TModelItem
    {
      private:
        byte NumParameters;   // число параметров инициализации элемента

      public:
        TForm *ModelForm;
        int Error;            // указывает на ошибку при инициализации
                              // (напр. мало пам€ти)
        byte *Parameters;     // указатель на массив выводов элемента

    	int NumberElement;    // номер элемента в схеме
    	int Visible;          // указывает €вл€етс€ ли
			      // моделируемый элемент видимым или нет

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

    	// загружает параметры из Parameters во внутренние переменные
    	virtual void LoadParam(void) {};
    	// выгружает параметры из внутренних переменных в Parameters
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

  // класс исключительной ситуации
  // предназначен дл€ генерации при наличии
  // неопределенного уровн€ на входах элементов
  // может генерироватьс€ в результате работы метода Run()
  class UndefLevelError 
    {
      int ErrorCode;
    };

# endif  // __TMODELITEM_H
