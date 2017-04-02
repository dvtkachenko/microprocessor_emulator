 // TRun.hpp - ќбъ€вление классов TKvantLevel,TMikroTaktLevel,TTaktLevel,
 //            TRun, реализующих алгоритмы эмул€ции

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
    	TScheme *Scheme;  // указатель на моделируемую схему
    	int TraceFlag;    // флаг трассировки на данном уровне
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
        int Enable;     // флаг разрешени€ выполнени€ на данном уровне
                        // прим-с€ в случае отсутстви€ в моделируемой
                        // схеме генераторов(т.к. нет генератора относительно
                        // которого выполн€ть моделирование)

    	int TraceFlag;  // флаг трассировки на данном уровне
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
        int Enable;     // флаг разрешени€ выполнени€ на данном уровне
                        // прим-с€ в случае отсутстви€ в моделируемой
                        // схеме генераторов(т.к. нет генератора относительно
                        // которого выполн€ть моделирование)

    	int TraceFlag;  // флаг трассировки на данном уровне
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
        int Enable;     // флаг разрешени€ выполнени€ на данном уровне
                        // прим-с€ в случае отсутстви€ в моделируемой
                        // схеме генераторов(т.к. нет генератора относительно
                        // которого выполн€ть моделирование)

//    	int TraceFlag;  // флаг трассировки на данном уровне
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
