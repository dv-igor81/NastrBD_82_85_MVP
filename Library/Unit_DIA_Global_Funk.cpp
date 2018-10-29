//---------------------------------------------------------------------------
//#include <vcl.h>
//#pragma hdrstop
#include "Unit_DIA_Global_Funk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// Глобальные переменные
find_t find;
godnost_t godnost1;
godnost_t godnost2;
godnost_t godnost3;
godnost_t gst;
godnost_t gst_Sdvig;
StrParam_t StrParam1;
//---------------------------------------------------------------------------
// Возвращает НУЛЬ, в случеа удачного завершения работы
// или символ, при обработке которого произшла ошибка (начиная с единицы)
int dia_atof( float * fVar, char * chStr ) // chStr to float
{
  float Rezult; // Резутьтат
  float Simvol; // Текущая цифра
  int iFlagSostoyaniya; // Флаг состояния
  int NSim; // Позиция найденного символа в строке
  bool bFlagZnak; // Флаг знака числа
  bool bFlagZnakExp; // Флаг знака экспоненты числа
  int iPorDes;
  int iPorExp;
  int iPor;
  float fPor;
  char chString_18[18];

  Rezult = 0.0;
  iFlagSostoyaniya = 0;
  bFlagZnak = false;
  bFlagZnakExp = false;
  iPorDes = 0;
  iPorExp = 0;
  fPor = 1;
  int i;

  // iFlagSostoyaniya == 0 ---
      // Что предшествовало:
          // Состояние № 0
      // Чем вызван переход в это состояние
          // Ничем, либо вводом пробельного символа
      // Что разрешено:
          // Пробельные символы, символы цифр, точки (запятой), знака (+-)
  // iFlagSostoyaniya == 1 ---
      // Что предшествовало:
          // Состояние № 0, либо Состояние № 5
      // Чем вызван переход в это состояние
          // Вводом символа цифры
      // Что разрешено:
          // Символы цифр, точки (запятой), символы экспоненты (e или E)
  // iFlagSostoyaniya == 2 ---
      // Что предшествовало:
          // Состояние № 1, либо Состояние № 3
      // Чем вызван переход в это состояние
          // Вводом символа експоненты (e, E)
      // Что разрешено:
          // Символ цифры, символ знака (+-)
  // iFlagSostoyaniya == 3 ---
      // Что предшествовало:
          // Состояние № 1, либо Состояние № 6
      // Чем вызван переход в это состояние
          // Вводом символа точки (запятой), если было Состояние № 1,
          // либо вводом символа цифры, если было Состояние № 6
      // Что разрешено:
          // Символ цифры, експоненты (e, E)
  // iFlagSostoyaniya == 4 ---
      // Что предшествовало:
          // Состояние № 2
      // Чем вызван переход в это состояние
          // Вводом символа знака (+-)
      // Что разрешено:
          // Символ цифры
  // iFlagSostoyaniya == 5 ---
      // Что предшествовало:
          // Состояние № 0
      // Чем вызван переход в это состояние
          // Вводом символа знака (+-)
      // Что разрешено:
          // Символ точки (запятой), либо символ цифры
  // iFlagSostoyaniya == 6 ---
      // Что предшествовало:
          // Состояние № 0 либо Состояние № 5
      // Чем вызван переход в это состояние
          // Вводом символа точки (запятой)
      // Что разрешено:
          // Символ цифры

  NSim = diaStrCpy( chString_18, "0123456789-+00., " );
  for ( i = 0; chStr[i] != 0; i++ )
  {
    NSim = FindSimInStr( chStr[i], chString_18 );
    if ( NSim == -1 )
    {
      return i + 1; // Возвращает символ, в котором произшла ошибка, начиная с единицы
    }
    if ( ( 0 <= NSim ) && ( NSim <= 9 ) )
    {
      if ( ( iFlagSostoyaniya == 0 ) || ( iFlagSostoyaniya == 1 ) ||
           ( iFlagSostoyaniya == 3 ) || ( iFlagSostoyaniya == 5 ) ||
           ( iFlagSostoyaniya == 6 ) )
      {
        Simvol = (float)NSim;
        Rezult *= 10;
        Rezult += Simvol;
        // Не было введено символа, либо введены пробельные символы, либо '-' или '+'
        if ( ( iFlagSostoyaniya == 0 ) || ( iFlagSostoyaniya == 5 ) )
        {
          iFlagSostoyaniya = 1;
          NSim = diaStrCpy( chString_18, "012345678900eE.,0" );
        }
        else if ( ( iFlagSostoyaniya == 3 ) || ( iFlagSostoyaniya == 6 ) )
        {
          iPorDes--;
          if ( iFlagSostoyaniya == 6 ) // '-' или '+', затем '.' или ','
          {
            iFlagSostoyaniya = 3;
            NSim = diaStrCpy( chString_18, "012345678900eE000" );
          }
        }
      }
      else if ( ( iFlagSostoyaniya == 2 ) || iFlagSostoyaniya == 4 )
      {
        iPorExp *= 10;
        iPorExp += NSim;
        if ( ( iFlagSostoyaniya == 2 ) )
        {
          iFlagSostoyaniya = 4;
          NSim = diaStrCpy( chString_18, "01234567890000000" );          
        }
      }
    }
    else if ( ( NSim == 10 ) || ( NSim == 11 ) ) // '-' или '+'
    {
      if ( iFlagSostoyaniya == 0 )
      {
        if ( NSim == 10 ) // '-'
        {
          bFlagZnak = true;
        }
        iFlagSostoyaniya = 5;        
        NSim = diaStrCpy( chString_18, "01234567890000.,0" );
      }
      else if ( iFlagSostoyaniya == 2 )
      {
        if ( NSim == 10 ) // '-'
        {
          bFlagZnakExp = true;
        }
        iFlagSostoyaniya = 4;
        NSim = diaStrCpy( chString_18, "01234567890000000" );
      }
    }
    else if ( ( NSim == 12 ) || ( NSim == 13 ) ) // 'e' 'E'
    {
      if ( Rezult == 0 )
      {
        *fVar = Rezult;
        return 0; // Признак удачного выполнения
      }
      if ( ( iFlagSostoyaniya == 1 ) || ( iFlagSostoyaniya == 3 ) )
      {
        iFlagSostoyaniya = 2;
        NSim = diaStrCpy( chString_18, "0123456789-+00000" );
      }
    }
    else if ( ( NSim == 14 ) || ( NSim == 15 ) ) // '.' ','
    {
      if ( ( iFlagSostoyaniya == 0 ) || ( iFlagSostoyaniya == 1 ) || ( iFlagSostoyaniya == 5 ) )
      {
        if ( ( iFlagSostoyaniya == 5 ) || ( iFlagSostoyaniya == 0 ) )
        {
          iFlagSostoyaniya = 6; // Точка после знака, либо точка после пробела
          NSim = diaStrCpy( chString_18, "01234567890000000" );          
        }
        else
        {
          iFlagSostoyaniya = 3;
          NSim = diaStrCpy( chString_18, "012345678900eE000" );
        }
      }
    }
  } // end for ( int i = 0; ( chStr[i] != 0 ) && ( bFlagLoopExit == false ); i++ )

  if ( bFlagZnakExp == true )
  {
    iPorExp *= -1;  
  }
  iPor = iPorDes + iPorExp;
  if ( iPor < 0 )
  {
    bFlagZnakExp = true;
    iPor *= -1;    
  }
  else
  {
    bFlagZnakExp = false;  
  }
  if ( iPor > 38 ) // для типа float максимально-допустимый показатель степени - 38
  {
    return i; // Возвращает символ, в котором произшла ошибка, начиная с единицы  
  }
  fPor = diaBaseExp( iPor ); // = 10^iPor
  if ( bFlagZnakExp == true )
  {
    Rezult /= fPor;
  }
  else
  {
    Rezult *= fPor;
  }
  //===
  if ( bFlagZnak == true )
  {
    Rezult *= -1;
  }
  *fVar = Rezult;
  return 0; // Признак удачного выполнения
}
//---------------------------------------------------------------------------
// Возвращает НУЛЬ, в случеа удачного завершения работы
// или символ, при обработке которого произшла ошибка (начиная с единицы)
int dia_atoi( int * iVar, char * chStr ) // chStr to int
{
  char chString_14[14];
  int Rezult; // Резутьтат
  int Simvol; // Текущая цифра
  int iFlagSostoyaniya; // Флаг состояния
  bool bFlagZnak;
  int NSim; // Позиция найденного символа в строке
  int i;

  Rezult = 0;
  iFlagSostoyaniya = 0;
  bFlagZnak = false;  
  diaStrCpy( chString_14, "0123456789-+ " );
  for ( i = 0; chStr[i] != 0; i++ )
  {
    NSim = FindSimInStr( chStr[i], chString_14 );
    if ( NSim == -1 )
    {
      return i + 1; // Возвращает символ, в котором произшла ошибка, начиная с единицы
    }
    if ( ( 0 <= NSim ) && ( NSim <= 9 ) )
    {
      if ( ( iFlagSostoyaniya == 0 ) || ( iFlagSostoyaniya == 1 ) )
      {
        if ( iFlagSostoyaniya == 0 )
        {
          iFlagSostoyaniya = 1;
          diaStrCpy( chString_14, "0123456789000" );
        }
        Rezult *= 10;
        Rezult += NSim;
      }
    }
    else if ( ( NSim == 10 ) || ( NSim == 11 ) ) // '-' или '+'
    {
      if ( iFlagSostoyaniya == 0 )
      {
        iFlagSostoyaniya = 1;
        diaStrCpy( chString_14, "0123456789000" );        
      }
      if ( NSim == 10 )
      {
        bFlagZnak = true;
      }
    }
  }
  if ( bFlagZnak == true )
  {
    Rezult *= -1;
  }
  *iVar = Rezult;
  return 0; // Признак удачного выполнения
}
//---------------------------------------------------------------------------
int GetLengthStr( char * chStr ) // Возвращает длину, без нуль-символа
{
  int i;
  for ( i = 0; chStr[i] != 0; i++ )
  {
  }
  return i;
}
//---------------------------------------------------------------------------
// Ищет символ chSim в строке chStr, начиная с индекса iFirst,
// заканчивая индексом iLast.
// Возвращает: -1 - не нашел, иначе индекс найденного символа в массиве
// chStr (начиная от 0)
int FindSimInStr( char chSim, char * chStr, int iFirst, int iLast )
{
  int i;
  int iEndLoop;

  if ( KorekArg( chStr, iFirst, & iLast ) == -1 )
  {
    return -1;
  }
  iEndLoop = iLast;  
    
  for ( i = iFirst; i <= iEndLoop; i++ )
  {
    if ( chStr[i] == chSim )
    {
      return i;
    }
  }
  return -1;
}
//---------------------------------------------------------------------------
// Копирует часть строки chStrFrom в строку chStrTo
// iFirst - индекс первого копируемого символа
// iLast - индекс последнего копируемого символа
// Если iFirst = iLast = 0, то копируется вся строка
int diaStrCpy( char * chStrTo, char * chStrFrom, int iFirst, int iLast )
{
  int i1, i2;
  int iEndLoop;

  if ( KorekArg( chStrFrom, iFirst, & iLast ) == -1 )
  {
    return -1;
  }
  iEndLoop = iLast;

  for ( i1 = 0, i2 = iFirst; i2 <= iEndLoop; i1++, i2++ ) // условие (chStrFrom[i] != 0) тут не используется
  {
    chStrTo[i1] = chStrFrom[i2];
  }

  chStrTo[i1] = '\0';
  return i1; // Длина скопированной строки, без учёта завершающего нуля
}
//---------------------------------------------------------------------------
// Сравнивает первые N символов двух строк, если строки совпадают в первых
// N символах - возвращается 0, если -1 - строки не совпадают, если -2
// - длина одной из строк меньше N, если -3 - ошибка при вводе N
int CmpNFirst( char * chStr1, char * chStr2, int N )
{
  int i;

  if ( N <=0 )
  {
    return -3;
  }
  if ( GetLengthStr( chStr1 ) < N )
  {
    return -2;
  }
  if ( GetLengthStr( chStr2 ) < N )
  {
    return -2;
  }
  for ( i = 0; i < N; i++ )
  {
    if ( chStr1[i] != chStr2[i] )
    {
      return -1;
    }
  }
  return 0; // Удача
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Ищет маленькую строку chStrSmall в строке большой chStrBig,
// начиная с индекса iFirst, заканчивая индексом iLast
// возвращает: -1 - не нашел, иначе индекс в массиве chStrBig
int FindSmallInBig( char * chStrSmall, char * chStrBig, int iFirst, int iLast )
{
  int LenSmall, LenBig, LenRaznost;
  int i;
  int iStart;
  int iStop;

  if ( KorekArg( chStrBig, iFirst, & iLast ) == -1 )
  {
    return -1;
  }

  LenBig = GetLengthStr( chStrBig );
  LenSmall = GetLengthStr( chStrSmall );
  if ( LenBig - 1 < iFirst )
  {
    return -1;
  }
  if ( LenBig - 1 < iLast )
  {
    return -1;
  }  
  if ( LenBig < LenSmall )
  {
    return -1;
  }

  LenRaznost = LenBig - LenSmall;
  iStart = FindSimInStr( chStrSmall[0], chStrBig, iFirst, iLast );
  if ( iStart == -1 ) // Не найден символ
  {
    return -1;
  }
  else if ( LenSmall == 1 ) // Малая строка состоит лишь из одного символа
  {
    return iStart;
  }
  if ( iLast != 0 ) // iLast == 0 по умолчанию
  {
    if ( iStart + LenSmall - 1 > iLast )
    {
      return -1;
    }
    iStop = iLast;
  }
  else
  {
    iStop = LenRaznost;
  }
  for
  (
    i = iStart;
    ( i < iStop ) && ( i >= 0 );
    i = FindSimInStr( chStrSmall[0], chStrBig, i + 1 )
  )
  {
    if ( CmpNFirst( chStrSmall, &chStrBig[i], LenSmall ) == 0 )
    {
      return i; // Удача
    }
  }
  return -1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
float diaBaseExp( int iPor ) // = 10^iPor, если iPor <= 32 + 7 (39)
{
  float fExp[12] = { 1e0, 1e1, 1e2, 1e3,
                     1e4, 1e5, 1e6, 1e7,
                     1e8, 1e16, 1e24, 1e32 };
  float ePor;
  ePor = fExp[ iPor % 8 ];
  if ( ( iPor > 7 ) && ( ( iPor / 8 ) <= 4 ) )
  {
    ePor *= fExp[ (iPor / 8) + 7 ];
  }
  return ePor;
}
//---------------------------------------------------------------------------
//TJPEGImage LoadJPEGFromResource( THandle resHandle, String name )
TGraphic * LoadJPEGFromResource( THandle resHandle, String name )
{
  TGraphic * jpegImage;
  TResourceStream * resStream;

  resStream = new TResourceStream( resHandle, name, RT_RCDATA );
  jpegImage = new TJPEGImage;
  jpegImage->LoadFromStream( resStream );
  resStream->Free();
  return jpegImage;
}
//------------------------------------------------------------------------------
AnsiString Preobraz( AnsiString prov )
{
  TCHAR buf[2]; // узнаем какой разделитель целой и дробной частей числа
                // обычно - ","
  int Err = GetLocaleInfo( LOCALE_SYSTEM_DEFAULT, LOCALE_SDECIMAL, buf, 2 );
  if ( !Err )
  {
    return prov;
  }
  int n;
  if ( buf[0] == ',' )
  {
    n = prov.AnsiPos(".");
    if ( n != 0 )
    {
      prov.Delete( n, 1 );
      prov.Insert( ",", n );
    }
  }
  if ( buf[0] == '.' )
  {
    n = prov.AnsiPos( "," );
    if ( n != 0 )
    {
      prov.Delete( n, 1 );
      prov.Insert( ".", n );
    }
  }
  return prov;
}
//---------------------------------------------------------------------------
void GodRes( godnost_t * godnost_var )
{
  int i;

//godnost_var->

  godnost_var->Reshotka = 0;
  godnost_var->SlashTwo = 0;
  godnost_var->Count = 0;
  godnost_var->CountSkoba = 0;

  for ( i = 0; i < godnost_t::MaxIP; i++ )
  {
    godnost_var->Net[i] = 0;
    godnost_var->Yes[i] = -1;
    godnost_var->SkobkaNet[i] = 0;
    godnost_var->SkobkaYes[i] = -1;
    godnost_var->PrichinaArr[i] = godnost_t::pr_NetPrichin;
  }
}
//---------------------------------------------------------------------------
// Преобразует строку chFrom, сохраняя результат в строке chTo
// Убирает всё пробельные символы в начале строки;
// Убирает в строке более одного пробельного символа подряд;
// Вставляет пробел после символов и лексем:
//        '('; ','; '='; '+'; '-'; '*'; '/'; '%'; "if"; "for";
//        "while"; "//"; "=="; "!="; ">="; "<="; "+="; "-="; "*=";
//        "/="; "%="; "||"; "&&"
// Вставляет пробел перед символами и лексемами:
//        ')'; '=' '+'; '-'; '*'; '/'; '%'; "//"; "=="; "!="; ">=";
//        "<="; "+="; "-="; "*="; "/="; "%="; "||"; "&&"
void SpaceCPPConvert( godnost_t * godnost_var )
{
  char chTemp[255];
  int iLen;
  int i1, i2;
  int iFS;
  bool bf1; // true - не пропускать пробельный символ, false - копировать пробел
  int iIdentifik; // = 0 - разрешено обрабатывать текущий символ, иначе лексема
  // из последующих символов идентифицировалась...
  bool bfPrigodnost; // true - Символ пригоден для дальнейшей обработки.
  bool bfUchet; // true - Символ ";" учитывается (находится спец. функциями поиска)


  bfPrigodnost = true;
  bfUchet = true;

  GodRes( godnost_var ); // Инициализация полей структуры


  iLen = GetLengthStr( godnost_var->chOriginal );
  bf1 = true; // Если строка начинается с пробельного символа - убрать его
  iIdentifik = 0;
  find.StrText = godnost_var->chOriginal;
  find.AllCount = false;
  for ( i1 = -1, i2 = 0; i1 < iLen; i1++ )
  {
    if ( iIdentifik > 0 )
    {
      iIdentifik--;
    }

    if ( iIdentifik == 0 )
    {
      //              01  02   03  04  05  06  07  08  09  10
      //              " " "\t" "(" ")" "," "=" ">" "<" ";" "+"
      //              "-" "*"  "/" "%" "&" "|" "^" "\"" "'" "{"
      //              "}" "#";
      find.chR = '0'; // Символ разделителя
      find.StrLek = " 0\t0(0)0,0=0>0<0;0+0"
                    "-0*0/0%0&0|0^0\"0'0{0"
                    "}0#";

      find.iFirst = i1; // Первый символ в строке find.StrText
      find.RazLek = true; // Использовать символ разделителя (true - find.iLast и find.N игнорируются)
      //==\\find.iLast = i1; // Последний символ в строке find.StrText
      //==\\find.N = 1; // Проверять по одному символу из строки find.StrText

      iFS = FindMultiInBig( & find );
      find.RazLek = false; // НЕ использовать символ разделителя
      switch ( iFS )
      {
      case 3: // "("
        if ( godnost_var->Prichina == godnost_t::pr_NetPrichin )
        {
          godnost_var->SkobaOtkr++;
        }
        break;
      case 4: // ")"
        if ( godnost_var->Prichina == godnost_t::pr_NetPrichin )
        {
          godnost_var->SkobaZakr++;
        }
        break;
      case 18: // "\""
        if
        (
          ( godnost_var->Prichina == godnost_t::pr_Kavychki ) // Причиной непригодности для разбора ЛЕКСЕМЫ были кавычки
          || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ЛЕКСЕМА пригодна для разбора
        )
        {
          godnost_var->Kavychki++;
        }
        break;
      case 19: // "'"
        if
        (
          ( godnost_var->Prichina == godnost_t::pr_Appostr ) // Причиной непригодности для разбора ЛЕКСЕМЫ был апостроф
          || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ЛЕКСЕМА пригодна для разбора
        )
        {
          godnost_var->Appostr++;
        }
        break;
      case 22: // "#"
        if
        (
          ( godnost_var->Prichina == godnost_t::pr_Reshotka ) // Причиной непригодности для разбора ЛЕКСЕМЫ был решетка
          || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ЛЕКСЕМА пригодна для разбора
        )
        {
          godnost_var->Reshotka++;
        }
        break;
      }


      if ( Prigodnost( godnost_var ) == false )
      {
        // Проверка предотвращает копирование того символа
        // который уже скопирован как часть лексемы "/*"
        if ( godnost_var->Prichina != godnost_t::pr_KomOtkr )
        {
          if ( iFS != -2 ) // Если не ошибка функции FindMultiInBig (например find.iFirst = -1 )
          {
            iFS = -1; // Просто копировать данный символ
          }
        }
      }

      switch ( iFS )
      {
      // Поставить пробельный символ перед следующими символами
      case 4: // ")"
      case 6: // "="
      case 7: // ">"
      case 8: // "<"
      case 10: // "+"
      case 11: // "-"
      case 12: // "*"
      case 13: // "/"
      case 14: // "%"
      case 15: // "&"
      case 16: // "|"
      case 17: // "^"
        if ( godnost_var->Prichina != godnost_t::pr_KomOtkr )
        {
          if ( bf1 == false )
          {
            bf1 = true; // Больше не ставить пробельных символов
            chTemp[i2] = ' ';
            i2++;
          }
        }
        break;
      }
      switch ( iFS )
      {
      case 1: // " "   // Нашёл, т.е. текущий символ - пробельный символ
      case 2: // "\t"  // Нашёл, т.е. текущий символ - пробельный символ
        if ( bf1 == false )
        {
          bf1 = true;
          chTemp[i2] = ' ';
          //chTemp[i2] = godnost_var->chOriginal[i1];
          i2++;
        }
        break;
      // Поставить пробельный символ после следующих символов
      case 3: // "("
      case 5: // ","
      case 6: // "="
      case 7: // ">"
      case 8: // "<"
      case 9: // ";"
      case 10: // "+"
      case 11: // "-"
      case 12: // "*"
      case 13: // "/"
      case 14: // "%"
      case 15: // "&"
      case 16: // "|"
      case 17: // "^"
        chTemp[i2] = godnost_var->chOriginal[i1]; // Скопировать этот символ
        i2++;
        bf1 = false; // После этих символов идёт пробел
        // Вставить пробельный символ после символов с индексами от 3 до 17
        if ( bf1 == false )
        {
          bf1 = true; // Больше не ставить пробельных символов
          chTemp[i2] = ' ';
          i2++;
        }
        break;
      // Скопировать следующие символы не ставя пробелы ни перед ни после
      case 4: // ")"
      case 18: // "\""
      case 19: // "'"
      case 20: // "{"
      case 21: // "}"
      case -1: // Не нашел ни одного из указанных символов
        bf1 = false; // Запомнить, что текущий символ - НЕ пробельный
        chTemp[i2] = godnost_var->chOriginal[i1];
        i2++;
        break;
      case -2: // Ошибка функции
        break;
      default:
        break;
      }

      if ( Prigodnost( godnost_var ) == false )
      {
        if ( bfPrigodnost == true )
        {
          bfPrigodnost = false;
          godnost_var->Count++;
          godnost_var->Net[godnost_var->Count - 1] = i2;
          godnost_var->PrichinaArr[godnost_var->Count - 1] = godnost_var->Prichina;
        }
      }
      else
      {
        if ( bfPrigodnost == false )
        {
          bfPrigodnost = true;
          godnost_var->Yes[godnost_var->Count - 1] = i2;
        }
      }
      //=======================================================================
      if ( Uchet( godnost_var ) == false )
      {
        if ( bfUchet == true )
        {
          bfUchet = false;
          godnost_var->CountSkoba++;
          godnost_var->SkobkaNet[godnost_var->CountSkoba - 1] = i2;
        }
      }
      else
      {
        if ( bfUchet == false )
        {
          bfUchet = true;
          godnost_var->SkobkaYes[godnost_var->CountSkoba - 1] = i2;
        }
      }
    } // end if ( iIdentifik == 0 )
    find.iFirst = i1 + 1;
    find.RazLek = true; // Использовать символ разделителя (true - find.iLast и find.N игнорируются)
    //==\\find.iLast = ...; // Последний символ в строке find.StrText
    //==\\find.N = ...; // Проверять по лексемме из find.N символов в строке find.StrText
    find.RazLek = true; // Использовать символ разделителя

    find.chR = ':'; // Символ разделителя
    find.StrLek = "if:/*:*/:->:++:--:()://:==:!=:" 
                  ">=:<=:&&:||:+=:-=:*=:/=:%=:|=:"
                  "&=:^=:<<:>>:\\\":while:for:\\\\:do";

    iFS = FindMultiInBig( & find );
    switch ( iFS )
    {
    case 2: // "/*"
      if ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ЛЕКСЕМА пригодна для разбора
      {
        godnost_var->KomOtkr++;
      }
      break;
    case 3: // "*/"
      if ( godnost_var->Prichina == godnost_t::pr_KomOtkr )
      {
        godnost_var->KomZakr++;
      }
      break;
    case 8: // "//"
      if
      (
        ( godnost_var->Prichina == godnost_t::pr_SlashTwo ) // Причиной непригодности для разбора ЛЕКСЕМЫ была два прямых слеша
        || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ЛЕКСЕМА пригодна для разбора
      )
      {
        godnost_var->SlashTwo++;
      }
      break;
    }

    if ( iFS >= 0 ) // Найдена одна из лексемм
    {
      if ( Prigodnost( godnost_var ) == false )
      {
        if ( godnost_var->Prichina != godnost_t::pr_KomOtkr )
        {
          iFS = -3; // Не пропустим лексему для вставки после неё пробела.
        }
      }
    }

    switch ( iFS )
    {
    case 1: // "if"
    case 26: // "for"
    case 27: // "while"
    case 29: // "do"
      if ( ( find.bOtdelLeft == false ) || ( find.bOtdelRight == false ) )
      {
        iFS = -3; // Не пропустим лексему для вставки после неё пробела.
      }
      break;
    }

    switch ( iFS ) // Вставить пробельные символы перед
    {
    case 3: // "*/"
    case 8: // "//"
    case 9: // "=="
    case 10: // "!="
    case 11: // ">="
    case 12: // "<="
    case 13: // "&&"
    case 14: // "||"
    case 15: // "+="
    case 16: // "-="
    case 17: // "*="
    case 18: // "/="
    case 19: // "%="
    case 20: // "|="
    case 21: // "&="
    case 22: // "^="
    case 23: // "<<"
    case 24: // ">>"
      if ( bf1 == false )
      {
        chTemp[i2] = ' '; // Пробельный символ перед
        i2++;
        bf1 = true; // Больше не ставить пробельных символов
      }
      break;
    }
    switch ( iFS ) // Скопировать идентификаторы
    {
    case 1: // "if"
    case 2: // "/*"
    case 3: // "*/"
    case 4: // "->" // не нужны пробелы ни перед ни после
    case 5: // "++" // не нужны пробелы ни перед ни после
    case 6: // "--" // не нужны пробелы ни перед ни после
    case 7: // "()" // не нужны пробелы ни перед ни после
    case 8: // "//"
    case 9: // "=="
    case 10: // "!="
    case 11: // ">="
    case 12: // "<="
    case 13: // "&&"
    case 14: // "||"
    case 15: // "+="
    case 16: // "-="
    case 17: // "*="
    case 18: // "/="
    case 19: // "%="
    case 20: // "|="
    case 21: // "&="
    case 22: // "^="
    case 23: // "<<"
    case 24: // ">>"
    case 25: // "\\\""
    case 26: // "for"
    case 27: // "while"
    case 28: // "\\\\" (\\)
    case 29: // "do"
      iIdentifik = 2;
      i2 += diaStrCpy( &chTemp[i2], find.chKontrol );
      i1 += find.pereskok;
      bf1 = false; // Запомнить, что после этих лексемм допустимо ставить пробел
      break;
    case -3: // Если не пропустили лексему для дальнейшей обработки.
      iIdentifik = 2;
      i2 += diaStrCpy( &chTemp[i2], find.chKontrol );
      i1 += find.pereskok;
      break;
    }
    switch ( iFS ) // Вставить пробельные символы после
    {
    case 1: // "if"
    case 2: // "/*"
    case 8: // "//"
    case 9: // "=="
    case 10: // "!="
    case 11: // ">="
    case 12: // "<="
    case 13: // "&&"
    case 14: // "||"
    case 15: // "+="
    case 16: // "-="
    case 17: // "*="
    case 18: // "/="
    case 19: // "%="
    case 20: // "|="
    case 21: // "&="
    case 22: // "^="
    case 23: // "<<"
    case 24: // ">>"
    case 26: // "for"
    case 27: // "while"
    case 29: // "do"    
      if ( bf1 == false )
      {
        bf1 = true; // Больше не ставить пробельных символов
        chTemp[i2] = ' '; // Пробельный символ после
        i2++;
      }
      break;
    }

    if ( Prigodnost( godnost_var ) == false )
    {
      if ( bfPrigodnost == true )
      {
        bfPrigodnost = false;
        godnost_var->Count++;
        godnost_var->Net[godnost_var->Count - 1] = i2;
        godnost_var->PrichinaArr[godnost_var->Count - 1] = godnost_var->Prichina;
      }
    }
    else
    {
      if ( bfPrigodnost == false )
      {
        bfPrigodnost = true;
        godnost_var->Yes[godnost_var->Count - 1] = i2;
      }
    }

  } // end for ( i1 = -1, i2 = 0; i1 < iLen; i1++ )
  chTemp[i2] = '\0';
  diaStrCpy( godnost_var->chArrConvert, chTemp );
  diaStrCpy( godnost_var->chConvert, godnost_var->chArrConvert );
}
//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Преобразует строку chFrom, сохраняя результат в строке chTo
// Перед исходной строкой ставит строкой iSp пробелов
void SpaceInsert( char * chTo, char * chFrom, int iSp ) // chTo := chFrom
{
  int i;
  for ( i = 0; i < iSp; i++ )
  {
    chTo[i] = ' ';
  }
  diaStrCpy( &chTo[i], chFrom );
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Обнуляет поля структур skobkiCount, kavCount и koment;
void Obnulenie( godnost_t * godnost_var )
{
  godnost_var->SkobaOtkr = 0;
  godnost_var->SkobaZakr = 0;
  godnost_var->Kavychki = 0;
  godnost_var->Appostr = 0;
  godnost_var->SlashTwo = 0;
  godnost_var->KomOtkr = 0;
  godnost_var->KomZakr = 0;
  godnost_var->Prichina = godnost_t::pr_NetPrichin;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Сдвигает строку chStr на iSdvig символов левее
int StrSdvig( char * chStr, int iSdvig, godnost_t * godnost_var )
{
  int iEndLoop;
  int i;
  int iNet;

  if ( iSdvig < 0 )
  {
    return -1;
  }

  iEndLoop = GetLengthStr( chStr );
  if ( iSdvig > iEndLoop )
  {
    return -1;
  }


  for ( i = 0; i + iSdvig < iEndLoop; i++ )
  {
    chStr[i] = chStr[i + iSdvig];
  }
  chStr[i] = '\0';

  if ( godnost_var != 0 )
  {
    Korrektor( iSdvig, godnost_var );
  }

  return iSdvig;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Удаляет пробельные символы слева
// Возвращает количество удалённых пробелов
int StrDelSpace( char * chStr )
{
  char chTemp[255];
  int iFS;
  int i1, i2;
  bool bf1; // true - не пропускать пробельный символ, false - копировать пробел
  int iLen;
  //int iRet;

  //iRet = 0;
  iLen = GetLengthStr( chStr );
  bf1 = true; // Если строка начинается с пробельного символа - убрать его
  for ( i1 = 0, i2 = 0; i1 < iLen; i1++ )
  {
    // === Удаление лишних пробельных символов
    iFS = FindSimInStr( chStr[i1], " \t" );
    if ( iFS != -1 ) // Нашёл, т.е. текущий символ - пробельный символ
    {
      if ( bf1 == false )
      {
        chStr[i2] = chStr[i1];
        i2++;
      }
    }
    else if ( iFS == -1 ) // Не нашёл, т.е. текущий символ - НЕ пробельный
    {
      bf1 = false;
      chStr[i2] = chStr[i1];
      i2++;
    }
  }
  chStr[i2] = '\0';
  return i1 - i2;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Вставляет символ chSim в строку chTo по индексу Index
int SimvolInsert( char * chTo, int Index, char chSim, godnost_t * godnost_var )
{
  int i;
  const int MaxIndex = 250;
  int LenOld, LenNew;
  char chTemp[255];

  LenOld = GetLengthStr(chTo);
  LenNew = LenOld + 1;
  if ( LenNew > MaxIndex )
  {
    return -1;
  }
  
  if ( godnost_var != 0 )
  {
    if ( Korrektor2( Index, 1, godnost_var ) == false )
    {
      return -1;
    }
  }

  chTo[LenNew + 1] = '\0';
  for ( i = LenOld; i >= Index; i-- )
  {
    chTo[i + 1] = chTo[i];
  }
  chTo[Index] = chSim;
  return Index;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Вставляет символ chSim в строку chTo по индексу Index
int SimvolInsert( char * chTo, int Index, char chSim )
{
  int i;
  int LenOld, LenNew;
  LenOld = GetLengthStr(chTo);
  LenNew = LenOld + 1;

  chTo[LenNew + 1] = '\0';
  for ( i = LenOld; i >= Index; i-- )
  {
    chTo[i + 1] = chTo[i];
  }
  chTo[Index] = chSim;
  return Index;  
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Контроль и коррекция входных параметров (аргументов)
int KorekArg( char * chStr, int iFirst, int * iLast )
{
  int i1, i2;
  int iEndLoop;

  if ( iFirst < 0 )
  {
    return -1;
  }
  if ( * iLast == -1 )
  {
    * iLast = GetLengthStr( chStr ) - 1; // Передача по ссылке ради этой инструкции
  }
  else if ( * iLast < 0 )
  {
    return -1;
  }
  else if ( * iLast < iFirst )
  {
    return -1;
  }
  return 0;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Строка chStrMulti состоиз из множество подстрок символов, длинной N каждая
// например строку "if==()" можно представить как совокупность подстрок
// ("if", "==", "()") с длинной N = 2 и номерами 1, 2 и 3 соответственно.
// Ищет одну из подстрок, длиной N (входящих chStrMulti) в строке chStrBig,
// начиная с индекса iFirst, заканчивая индексом iLast (от 0 до Длина-1)
// возвращает: -1 - не нашел либо некорректны входные параметры, иначе номер
// подстроки (от 1 до Длина / N).
//int FindMultiInBig( char * chStrMulti, char * chStrBig, int iFirst, int iLast, int N, char * chKontrol )
//{
  //int iLenMulti;
  //int iTemp;
  //char chStrSmall[16];

  //if ( KorekArg( chStrBig, iFirst, & iLast ) == -1 )
  //{
  //  return -1;
  //}
  //iLenMulti = GetLengthStr( chStrMulti );
  //if ( ( iLenMulti % N ) != 0 )
  //{
  //  return -1;
  //}

  //for ( iFirst = 0, iLast = N - 1; iLast <= iLenMulti; iFirst += N, iLast += N )
  //{
  //  iTemp = diaStrCpy( chStrSmall, chStrBig, iFirst, iLast );
  //  iTemp = FindSmallInBig( chStrSmall, chStrBig, iFirst, iLast );
  //  if ( iTemp != -1 )
  //  {
  //    diaStrCpy( chKontrol, chStrSmall );
  //    return i1 / N + 1;
  //  }
  //}
  //return -1;
//}
int FindMultiInBig( find_t * find )
{
  char * chStrMulti; // Строка с лексемами
  char * chStrBig; // Строка, в которой ведётся поиск
  int iFirst;
  int iLast;
  int N;
  int iLenMulti; // Длина строки с лексемами
  int iLenBig; // Длина строки с текстом, в котором ищутся эти лексемы
  int iTemp;
  char chStrSmall[16];
  int i1;
  int i2;
  char chSimvol;
  int I1, I2;
  int N1, N2;
  int vyhod;
  int Cnt;

  Cnt = 0;
  chStrMulti = find->StrLek;
  chStrBig = find->StrText;
  iFirst = find->iFirst;
  find->bOtdelLeft = false; // Пока не ясно отделена ли лексема началом строки либо символом слева
  find->bOtdelRight = false; // Пока не ясно отделена ли лексема концом строки либо символом справа

  chSimvol = find->chR;
  iLenMulti = GetLengthStr( chStrMulti );
  iLenBig = GetLengthStr( chStrBig ); //==\\ Вставил
  if ( find->RazLek == false )
  {
    iLast = find->iLast;
    find->pereskok = 0;
    N = find->N;
    if ( ( iLenMulti % N ) != 0 )
    {
      return -2;
    }
    N1 = N;
    N2 = N;
  }
  else
  {
    N1 = 0;
    N2 = FindSimInStr( chSimvol, chStrMulti );
    iLast = -1; // Значение по умолчанию
  }
  if ( KorekArg( chStrBig, iFirst, & iLast ) == -1 )
  {
    return -2;
  }

  find->Count = 0;
  vyhod = 0;
  for ( i1 = 0, i2 = N2 - 1; ( i2 <= iLenMulti ) ; i1 += N1, i2 += N2, Cnt++ )
  {
    if ( vyhod == 2 )
    {
      break;
    }
    if ( vyhod >= 1 )
    {
      vyhod++;
    }

    if ( find->RazLek == true ) // Используется разделитель лексемм
    {
      I1 = i2 + 2;
      I2 = FindSimInStr( chSimvol, chStrMulti, I1 ) - 1;
      {
        if ( I2 < 0 )
        {
          I2 = iLenMulti - 1;
          if ( vyhod == 0 )
          {
            vyhod = 1; // Скоро понадобится прервать цикл
          }
        }
      }
      N1 = I1 - i1;
      N2 = I2 - i2;
      iLast = iFirst + (i2 - i1);
      find->pereskok = (i2 - i1);
    }
    iTemp = diaStrCpy( chStrSmall, chStrMulti, i1, i2 );
    if ( find->AllCount == false )
    {
      iTemp = FindSmallInBig( chStrSmall, chStrBig, iFirst, iLast );
    }
    else // if ( find->AllCount == true )
    {
      do
      {
        iTemp = FindSmallInBig( chStrSmall, chStrBig, iFirst, iLast );
        //==\\iFirst = iTemp + 1; // Удалил
        if ( iTemp >= 0 )
        {
          iFirst = iTemp + 1; //==\\ Вставил
          find->Count++;
        }
      }
      while ( iTemp >= 0 );
    }
    if ( iTemp != -1 )
    {
      diaStrCpy( find->chKontrol, chStrSmall ); // Нашлась лексема
      if ( iFirst == 0 ) // Лексема нашлась вначале
      {
        find->bOtdelLeft = true; // лексема отделена началом строки
      }
      else
      {
        iTemp = FindSimInStr( chStrBig[iFirst - 1], " \t);" );
        if ( iTemp >= 0 )
        {
          find->bOtdelLeft = true; // лексема отделена символом слева
        }
      }
      if ( iFirst + find->pereskok + 1 == iLenBig ) // Лексема нашлась вконце
      {
        find->bOtdelRight = true; // лексема отделена концом строки
      }
      else if ( iFirst + find->pereskok + 1 < iLenBig )
      {
        iTemp = FindSimInStr( chStrBig[iFirst + find->pereskok + 1], " \t(" );
        if ( iTemp >= 0 )
        {
          find->bOtdelRight = true; // лексема отделена символом справа
        }
      }
      else if ( iFirst + find->pereskok + 1 > iLenBig )
      {
        find->bOtdelRight = find->bOtdelRight; // Ошибка!!! такой ситуации быть не должно
      }
      if ( find->RazLek == false )
      {
        return ( i1 / N ) + 1;
      }
      else
      {
        return Cnt + 1;      
      }

    }
  } // end for ( i1 = 0, i2 = N2 - 1; ( i2 <= iLenMulti ) ; i1 += N1, i2 += N2 )
  find->pereskok = 0; // Лексема не найдена

  //==\\if ( find->AllCount == true )
  //==\\{
  //==\\  return iMin;
  //==\\}
  //==\\else
  //==\\{
  //==\\  return -1;
  //==\\}
  return -1;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Учет символа
// true - учитывать символ ";", false - не учитывать его т.к. он внутри
// "("скобок")"
bool Uchet( godnost_t * godnost_var )
{
  int DeltaSkoba;

  DeltaSkoba = godnost_var->SkobaOtkr - godnost_var->SkobaZakr;
  if ( ( DeltaSkoba % 2 ) == 1 )
  {
    // Защита от переполнения
    godnost_var->SkobaOtkr = 1;
    godnost_var->SkobaZakr = 0;
    return false;
  }
  else if ( ( DeltaSkoba % 2 ) == 0 )
  {
    // Защита от переполнения
    godnost_var->SkobaOtkr = 0;
    godnost_var->SkobaZakr = 0;
  }
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Пригодность символа либо многосимвольной лексемы для дальнейшей обработки
// true - пригодна, false - нет
//     - Проверить стоит ли ЛЕКСЕМА внутри кавичек "ЛЕКСЕМА";
//     - Проверить стоит ли ЛЕКСЕМА внутри апострофов 'ЛЕКСЕМА';
//     - Проверить стоит ли ЛЕКСЕМА внутри комментария /*ЛЕКСЕМА*/;
//     - Проверить стоит ли ЛЕКСЕМА после коментария //ЛЕКСЕМА;
//     - Проверить стоит ли ЛЕКСЕМА после #ЛЕКСЕМА.
bool Prigodnost( godnost_t * godnost_var )
{
  //     - Проверить стоит ли ЛЕКСЕМА внутри кавичек "ЛЕКСЕМА";
  int DeltaKom;
  if ( ( godnost_var->Kavychki % 2 ) == 1 )
  {
    godnost_var->Kavychki = 1; // Защита от переполнения
    godnost_var->Prichina = godnost_t::pr_Kavychki;
    return false;
  }
  else if ( ( godnost_var->Kavychki % 2 ) == 0 )
  {
    godnost_var->Kavychki = 0; // Защита от переполнения
  }
  //     - Проверить стоит ли ЛЕКСЕМА внутри апострофов 'ЛЕКСЕМА';
  if ( ( godnost_var->Appostr % 2 ) == 1 )
  {
    godnost_var->Appostr = 1; // Защита от переполнения
    godnost_var->Prichina = godnost_t::pr_Appostr;
    return false;
  }
  else if ( ( godnost_var->Appostr % 2 ) == 0 )
  {
    godnost_var->Appostr = 0; // Защита от переполнения
  }  
  //     - Проверить стоит ли ЛЕКСЕМА внутри комментария /*ЛЕКСЕМА*/
  DeltaKom = godnost_var->KomOtkr - godnost_var->KomZakr;
  if ( ( DeltaKom % 2 ) == 1 )
  {
    // Защита от переполнения
    godnost_var->KomOtkr = 1;
    godnost_var->KomZakr = 0;
    godnost_var->Prichina = godnost_t::pr_KomOtkr;
    return false;
  }
  else if ( ( DeltaKom % 2 ) == 0 )
  {
    // Защита от переполнения
    godnost_var->KomOtkr = 0;
    godnost_var->KomZakr = 0;
  }
  //     - Проверить стоит ли ЛЕКСЕМА после коментария //ЛЕКСЕМА
  if ( godnost_var->SlashTwo > 0 )
  {
    godnost_var->Prichina = godnost_t::pr_SlashTwo;
    return false;
  }
  //     - Проверить стоит ли ЛЕКСЕМА после #ЛЕКСЕМА
  if ( godnost_var->Reshotka > 0 )
  {
    godnost_var->Prichina = godnost_t::pr_Reshotka;
    return false;
  }
  //     - Проверить стоит ли лексема внутри (скобок)
  godnost_var->Prichina = godnost_t::pr_NetPrichin;
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Символ N считается годным для обработке, если он не закоментирован
// и не находится внутри строки.
bool Proverka( int N, godnost_t * godnost_var ) // Проверка пригодности
{
  int i;
  int iNet;
  int iYes;

  for ( i = 0; i < godnost_var->Count; i++ )
  {
    godnost_var->Prichina = static_cast<godnost_t::Prichina_t>(godnost_var->PrichinaArr[i]);
    
    if ( godnost_var->Prichina == godnost_t::pr_SlashTwo )
    {
      iNet = 2;
    }
    if ( godnost_var->Prichina == godnost_t::pr_Reshotka )
    {
      iNet = 1;
    }
    if ( ( godnost_var->Prichina == godnost_t::pr_Kavychki ) || // "\""
    ( godnost_var->Prichina == godnost_t::pr_Appostr ) ) // "'"
    {
      iNet = 1;
      iYes = 0;
    }
    if ( godnost_var->Prichina == godnost_t::pr_KomOtkr ) // "/*"
    {
      iNet = 3;
      iYes = 0;
    }

    if ( godnost_var->Yes[i] != -1 ) // Если в строке найден символ, с которого годность возобновляется
    {
      if ( ( ( N + iNet ) >= godnost_var->Net[i] ) && ( ( N + iYes ) < godnost_var->Yes[i] ) )
      {
        return false;
      }
    }
    else // нет символа с которого возобнавляется годность
    {
      if ( ( N + iNet ) >= godnost_var->Net[i] )
      {
        return false;
      }
    }
  }
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
bool Proverka2( int N, godnost_t * godnost_var ) // Проверка пригодности 2
{
  int i;
  int iNet;
  int iYes;  

  iNet = 2;
  iYes = 0;
  for ( i = 0; i < godnost_var->CountSkoba; i++ )
  {
    if ( godnost_var->SkobkaYes[i] != -1 ) // Если в строке найден символ, с которого годность возобновляется
    {
      if ( ( N >= ( godnost_var->SkobkaNet[i] - iNet ) ) && ( N < ( godnost_var->SkobkaYes[i] - iYes ) ) )
      {
        return false;
      }
    }
    else // нет символа с которого возобнавляется годность
    {
      if ( N >= ( godnost_var->SkobkaNet[i] - iNet ) )
      {
        return false;
      }
    }
  }
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// То же самое, что и "FindSmallInBig()", но с проверкой, на пригодность
// т.е. лексемы, удовлетворяющие этой функции, например не должны быть
// /* ВНУТРИ КОММЕНТАРИЯ */
int FindSmallInBigPrigod( char * chLeksem,
                          char * chStrBig,
                          godnost_t * godnost_var,
                          int iSumIndex,
                          int iFirst,
                          int iLast )
{
  int iFS;
  bool Uspeh;
  Uspeh = false;
  bool iRP; // Результат проверки
  bool iRP2; // Результат проверки 2
  do
  {
    iFS = FindSmallInBig( chLeksem, chStrBig, iFirst, iLast );
    iFirst = iFS + 1;
    iRP = Proverka( iFS /*+ iSumIndex*/, godnost_var );
    iRP2 = Proverka2( iFS /*+ iSumIndex*/, godnost_var );
    if ( iRP == true ) // Нашлась пригодная для обработк лексема
    {
      if ( CmpNFirst( chLeksem, ";", 1 ) == 0 ) // если это ";"
      {
        if ( iRP2 == true ) // Она не в скобках
        {
          Uspeh = true;
          break;
        }
      }
      else // Любая лексема, кроме ";"
      {
        Uspeh = true;
        break;
      }
    }

  } while ( iFS >= 0 );
  if ( Uspeh == true )
  {
    return iFS;
  }
  else
  {
    return -1;
  }
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Найти первый НЕ ПРОБЕЛЬНЫЙ символ доступный для обработки, начиная с
// индекса iFirst
bool FindPrigod( int iFirst, godnost_t * godnost_var )
{
  int iLen;
  bool bfDSim;
  int iDSim;
  bool bfDSimNSp;
  int iDSimNSp;

  godnost_var->Obmen[0] = -2;
  godnost_var->Obmen[1] = -2;
  bfDSim = false;
  bfDSimNSp = false;
  iDSim = -1;
  iDSimNSp = -1;
  iLen = GetLengthStr( godnost_var->chConvert );
  if (  iLen == 0 )
  {
    return false;
  }
  for( int i = iFirst; i < iLen; i++ )
  {
    if ( Proverka( i, godnost_var ) == true )
    {
      if ( bfDSim == false )
      {
        bfDSim = true;
        iDSim = i; // Первый найденный доступный символ
      }
      //if ( ( godnost_var->chConvert[i] != ' ' ) && ( godnost_var->chConvert[i] != '\t' ) )
      if ( ( godnost_var->chConvert[i] != ' ' ) && ( godnost_var->chConvert[i] != '\t' ) ) //
      {
        if ( bfDSimNSp == false )
        {
          bfDSimNSp = true;
          iDSimNSp = i;
        }
      }
    }
  } // END for( int i = iFirst; i < iLen; i++ )
  godnost_var->Obmen[0] = iDSim; // Индекс первого доступного символа
  godnost_var->Obmen[1] = iDSimNSp; // Индекс первого доступного непробельного символа
  return bfDSimNSp;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Если строку сдвинули на iSdvig символов влево, надо учесть это
// в структуре данных, типа godnost_t
void Korrektor( int iSdvig, godnost_t * godnost_var )
{
  int i;
  int iNet;
  int iYes = 0;
  for ( i = 0; i < godnost_var->Count; i++ )
  {
    godnost_var->Prichina = static_cast<godnost_t::Prichina_t>(godnost_var->PrichinaArr[i]);

    if ( godnost_var->Prichina == godnost_t::pr_SlashTwo )
    {
      iNet = 2;
    }
    if ( godnost_var->Prichina == godnost_t::pr_Reshotka )
    {
      iNet = 1;
    }
    if ( ( godnost_var->Prichina == godnost_t::pr_Kavychki ) || // "\""
    ( godnost_var->Prichina == godnost_t::pr_Appostr ) ) // "'"
    {
      iNet = 1;
    }
    if ( godnost_var->Prichina == godnost_t::pr_KomOtkr ) // "/*"
    {
      iNet = 3;
    }
    godnost_var->Net[i] -= iSdvig;
    if ( godnost_var->Net[i] < iNet )
    {
      godnost_var->Net[i] = iNet;
    }
    if ( godnost_var->Yes[i] != -1 ) // Если в строке найден символ, с которого годность возобновляется
    {
      godnost_var->Yes[i] -= iSdvig;
      if ( godnost_var->Yes[i] < iYes )
      {
        godnost_var->Yes[i] = iYes;
      }
    }
  }
  iNet = 1;
  for ( i = 0; i < godnost_var->CountSkoba; i++ )
  {
    godnost_var->SkobkaNet[i] -= iSdvig;
    if ( godnost_var->SkobkaNet[i] < iNet )
    {
      godnost_var->SkobkaNet[i] = iNet;
    }
    if ( godnost_var->SkobkaYes[i] != -1 ) // Если в строке найден символ, с которого годность возобновляется
    {
      godnost_var->SkobkaYes[i] -= iSdvig;
      if ( godnost_var->SkobkaYes[i] < iYes )
      {
        godnost_var->SkobkaYes[i] = iYes;
      }
    }
  }
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Если в позицию Pos вставляются N символов, это надо учесть.
// Возвращаемое значение: true - вставка произошла, false - не удалась
bool Korrektor2( int iPos, int Sdvig, godnost_t * godnost_var )
{
  int i;
  int iNet;
  if ( Proverka( iPos, godnost_var ) == false ) // Мы внутри комментария
  { // (или внутри строки)
    return false;
  }
  for ( i = 0; i < godnost_var->Count; i++ )
  {
    if ( godnost_var->Prichina == godnost_t::pr_SlashTwo )
    {
      iNet = 2;
    }
    if ( godnost_var->Prichina == godnost_t::pr_Reshotka )
    {
      iNet = 1;
    }
    if ( ( godnost_var->Prichina == godnost_t::pr_Kavychki ) || // "\""
    ( godnost_var->Prichina == godnost_t::pr_Appostr ) ) // "'"
    {
      iNet = 1;
    }
    if ( godnost_var->Prichina == godnost_t::pr_KomOtkr ) // "/*"
    {
      iNet = 3;
    }
    if ( ( iPos + iNet ) < godnost_var->Net[i] )
    {
      godnost_var->Net[i] += Sdvig;
      if ( godnost_var->Yes[i] != -1 )
      {
        godnost_var->Yes[i] += Sdvig;      
      }
    }
  }
  iNet = 1;
  for ( i = 0; i < godnost_var->CountSkoba; i++ )
  {
    if ( ( iPos + iNet ) < godnost_var->SkobkaNet[i] )
    {
      godnost_var->SkobkaNet[i] += Sdvig;
      if ( godnost_var->SkobkaYes[i] != -1 )
      {
        godnost_var->SkobkaYes[i] += Sdvig;      
      }
    }
  }  
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Функция копирования строк
void DiaStrCpy( p_StrParam_t pVar )
{
  int i; // Счётчик цикла
  int iStart;
  int iFinish;
  int iDelta;

  int iLenSrc;
  int iLenDest;
  int iLenLeft;
  int iLenRight;
  int iPosLeft;
  int iPosRight;

  int iFirst;
  int iFindSimvol;
  char chBukva;

  if ( pVar->chSrc != 0 )
  {
    iLenSrc = GetLengthStr( pVar->chSrc );
  }
  if ( pVar->chDest != 0 )
  {
    iLenDest = GetLengthStr( pVar->chDest );
  }
  if ( pVar->chLeft != 0 )
  {
    iLenLeft = GetLengthStr( pVar->chLeft );
  }
  if ( pVar->chRight != 0 )
  {
    iLenRight = GetLengthStr( pVar->chRight );
  }

  pVar->bRezult = true;
  if ( iLenSrc >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // Неудача
  }
  if ( iLenDest >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // Неудача
  }
  if ( pVar->iKolSimv < 0 )
  {
    pVar->bRezult = false; // Неудача  
  }
  if ( pVar->iDestFirst < 0 )
  {
    pVar->bRezult = false; // Неудача
  }
  if (  pVar->iDestFirst >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // Неудача  
  }
  if ( pVar->iSrcFirst < 0 )
  {
    pVar->bRezult = false; // Неудача
  }
  if (  pVar->iSrcFirst >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // Неудача
  }
  if ( pVar->iDestFirst + pVar->iKolSimv >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // Неудача
  }
  if ( pVar->iSrcFirst + pVar->iKolSimv >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // Неудача
  }
  
  if ( pVar->bRezult == false )
  {
    if ( pVar->chDest != 0 )
    {
      pVar->chDest[0] = '\0';
    }
    return;
  }

  if ( pVar->bFindLeftRightStr == true )
  {
    // Найти позицию лексемы chLeft, удовлетворяющую критериям поиска
      // например самую левую или самую правую
    iFirst = 0;
    iPosLeft = -1;
    while ( iFirst < iLenSrc )
    {
      iFindSimvol = FindSmallInBig( pVar->chLeft, pVar->chSrc, iFirst );
      if ( iFindSimvol != -1 )
      {
        iPosLeft = iFindSimvol;
        if ( pVar->bRevers == false ) // Вернуть позицию самой первой найденной
        {
          break;
        }
        if ( pVar->bRevers == true )
        {
          iFirst = iFindSimvol + 1;
        }
      }
      if ( iFindSimvol == -1 )
      {
        break;
      }
    }
    // Найти позицию лексемы chRight, удовлетворяющую критериям поиска
      // например самую левую или самую правую
    iFirst = 0;
    iPosRight = -1;
    while ( iFirst < iLenSrc )
    {
      iFindSimvol = FindSmallInBig( pVar->chRight, pVar->chSrc, iFirst );
      if ( iFindSimvol != -1 )
      {
        iPosRight = iFindSimvol;
        if ( pVar->bRevers == false ) // Вернуть позицию самой первой найденной
        {
          break;
        }
        if ( pVar->bRevers == true )
        {
          iFirst = iFindSimvol + 1;
        }
      }
      if ( iFindSimvol == -1 )
      {
        break;
      }
    }
    // Проверить, найдены ли лексемы
    if ( iPosLeft == -1 )
    {
      pVar->bRezult = false;
    }
    if ( iPosRight == -1 )
    {
      pVar->bRezult = false;
    }

    if ( pVar->bRezult == false )
    {
      if ( pVar->chDest != 0 )
      {
        pVar->chDest[0] = '\0';
      }
      return;
    }

    // Проверить, существует ли текст между ними
    if ( iPosLeft + iLenLeft < iPosRight )
    {
      pVar->iKolSimv = iPosRight - iPosLeft - iLenLeft;
      pVar->iKolSimv += iLenRight;
      pVar->iSrcFirst = iPosLeft + iLenLeft;
    }
    else
    {
      pVar->bRezult = false;
    }
  }

  // Скопировать текст, находящийся между лексемами
  iDelta = 1;
  iFinish = pVar->iKolSimv;
  iStart = 0;
  if ( pVar->bRezult == false )
  {
    return;
  }
  for ( i = iStart; i < iFinish; i += iDelta )
  {
    if ( pVar->Zamena == pVar->Net )
    {
      chBukva = pVar->chSrc[pVar->iSrcFirst + i];
    }
    if ( pVar->Zamena == pVar->ToSmall )
    {
      chBukva = ToSmallBukva( pVar->chSrc[pVar->iSrcFirst + i] );
    }
    if ( pVar->Zamena == pVar->ToBig )
    {
      chBukva = ToBigBukva( pVar->chSrc[pVar->iSrcFirst + i] );
    }
    pVar->chDest[pVar->iDestFirst + i] = chBukva;
  }
  if ( pVar->bNullEnd == true )
  {
    pVar->chDest[pVar->iDestFirst + i] = '\0';
  }
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Функция замены строк
void DiaFindReplace( p_StrParam_t pVar )
{
  char chTemp[StrParam_t::MaxLen];
  int i; // Счётчик цикла
  int iDestBegin;
  char * pchSrc;

  int iLenSrc;
  int iLenRight;
  int iLenLeft;

  int iFirst;
  int iFindSimvol;

  pVar->bRezult = true;
  pVar->bNullEnd = true;
  pVar->bFindLeftRightStr = false;
  pchSrc = pVar->chSrc;
  pVar->chDest = chTemp;
  pVar->iSrcFirst = 0;

  iLenSrc = GetLengthStr( pVar->chSrc );
  iLenRight = GetLengthStr( pVar->chRight );
  iLenLeft = GetLengthStr( pVar->chLeft );
  

  iFirst = 0;
  iDestBegin = 0;

  while ( iFirst < iLenSrc )
  {
    iFindSimvol = FindSmallInBig( pVar->chLeft, pVar->chSrc, iFirst );
    if ( iFindSimvol != -1 ) // Если найдена лексема
    {
      // Скопировать часть строки до найденой chLeft
      pVar->iSrcFirst = iFirst;
      pVar->iDestFirst = iDestBegin;
      pVar->iKolSimv = iFindSimvol - iFirst;
      DiaStrCpy( pVar );

      // Скопировать в строку назначения chRight
      iDestBegin += pVar->iKolSimv;
      pVar->chSrc = pVar->chRight;
      pVar->iSrcFirst = 0;
      pVar->iDestFirst = iDestBegin;
      pVar->iKolSimv = iLenRight;
      DiaStrCpy( pVar );

      // Подготовиться к поиску в оставшейся части строки
      iDestBegin += pVar->iKolSimv;
      iFirst = iFindSimvol + iLenLeft;
      pVar->chSrc = pchSrc;
    }
    else
    {
      // Скопировать часть строки до её конца
      pVar->iSrcFirst = iFirst;
      pVar->iDestFirst = iDestBegin;
      pVar->iKolSimv = iLenSrc - iFirst;
      DiaStrCpy( pVar );
      iFirst = iLenSrc;
      break;    
    }
  }
  if ( iFirst != 0 )
  {
    pVar->chDest = pVar->chSrc;
    pVar->chSrc = chTemp;
    pVar->iDestFirst = 0;
    pVar->iSrcFirst = 0;
    pVar->iKolSimv = StrParam_t::MaxLen - 1;
    DiaStrCpy( pVar );
  }
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Переводит русские и английские буквы в "БОЛЬШИЕ"
char ToBigBukva( char Bukva )
{
  unsigned char uchBigBukva;
  unsigned char uchBukva;
  char BigBukva;

  //==\\uchBukva = static_cast<unsigned char>( Bukva );
  uchBukva = ( unsigned char )( Bukva );

  // Копирование буквы
  uchBigBukva = uchBukva;

  // Перевод букв от "а" до "я", без буквы "ё"
  if ( uchBukva >= 224 ) // && ( uchBukva <= 255 ) - всегда истинно
  {
    uchBigBukva = uchBukva - 32;
  }
  // Перевод буквы "ё"
  if ( uchBukva == 184 )
  {
    uchBigBukva = 168;
  }
  // Перевод букв от "a" до "z"
  if ( ( uchBukva >= 97 ) && ( uchBukva <= 122 ) )
  {
    uchBigBukva = uchBukva - 32;
  }
  //==\\BigBukva = static_cast<unsigned char>( uchBigBukva );
  BigBukva = ( unsigned char )( uchBigBukva );
  return BigBukva;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// Переводит русские и английские буквы в "маленькие"
char ToSmallBukva( char Bukva )
{
  unsigned char uchSmallBukva;
  unsigned char uchBukva;
  char SmallBukva;

  //==\\uchBukva = static_cast<unsigned char>( Bukva );
  uchBukva = ( unsigned char )( Bukva );

  // Копирование буквы
  uchSmallBukva = uchBukva;

  // Перевод букв от "А" до "Я", без буквы "Ё"
  if ( ( uchBukva >= 192 ) && ( uchBukva <= 223 ) )
  {
    uchSmallBukva = uchBukva + 32;
  }
  // Перевод буквы "Ё"
  if ( uchBukva == 168 )
  {
    uchSmallBukva = 184;
  }
  // Перевод букв от "A" до "Z"
  if ( ( uchBukva >= 65 ) && ( uchBukva <= 90 ) )
  {
    uchSmallBukva = uchBukva + 32;
  }
  //==\\SmallBukva = static_cast<unsigned char>( uchSmallBukva );
  SmallBukva = ( unsigned char )( uchSmallBukva );
  return SmallBukva;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
bool DiaCreateDir( AnsiString asDirName )
{
  AnsiString sPath;
  char chPath[MAX_PATH];
  GetWindowsDirectory( chPath, MAX_PATH );
  sPath = ExtractFileDrive( chPath ); // "C:" ( или "D:" - системный диск )
  sPath += asDirName; // asDirName = "\\VNIIA Ppograms\\Tabulyatziya" - например;
  if ( DirectoryExists( sPath.c_str() ) == false )
  {
    if ( ForceDirectories( sPath.c_str() ) == false )
    {
      // В отличие от CreateDir функция ForceDirectories создаёт всю
      // указанную её аргументом цепочку каталогов, даже если промежуточные
      // каталоги не существуют
      return false;
    }
  }
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
/*
void DiaDiskBukba( AnsiString * asDiskBukva )
{
  char chPath[MAX_PATH];
  GetWindowsDirectory( chPath, MAX_PATH );
  sPath = ExtractFileDrive( chPath ); // "C:" ( или "D:" - системный диск )
  *asDiskBukva = sPath;
}
*/
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
AnsiString DiaDiskBukba( void )
{
  AnsiString sPath;
  char chPath[MAX_PATH];
  GetWindowsDirectory( chPath, MAX_PATH );
  sPath = ExtractFileDrive( chPath ); // "C:" ( или "D:" - системный диск )
  return sPath;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

