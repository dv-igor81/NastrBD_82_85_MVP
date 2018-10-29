//---------------------------------------------------------------------------
#pragma hdrstop
#include "Unit_82_ClassFunction.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

void Function_t::DIAcopy(char * S, unsigned char var)
{
  for (int i = 0; (i < razmer) && (S != 0) ; i++)
  {
	String[var-1][i] = S[i];
  }
}
//----------------------------------------------------------------------------
void Function_t::DIAcopy2(char * S1, char * S2, unsigned char var1,  unsigned char var2)
{
  int i;
  for (i = 0; (i < razmer) && (i < var1) && (S1 != 0) ; i++)
  {
	massaIstochnika[i] = S1[i];
  }
  massaIstochnika[i] = '\0';
  for (i = 0; (i < razmer) && (i < var2) && (S2 != 0) ; i++)
  {
	tipIctochnika[i] = S2[i];
  }
  tipIctochnika[i] = '\0';
}
//---------------------------------------------------------------------------
char * Function_t::Display(int var)
{
  if (ProgrammState == -1)
  {
    if (7 == var) // Все поля очищены
    {
      ProgrammState = 0;
    }
    return String[var];
  }
  if (ProgrammState == 0)
  {
    DIAcopy("", var); // Очистить строку с номером var
  }
  if ( ProgrammState == 0 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " Нажмите кнопку \"Далее\" для набора начального фона");
  }
  if ( ProgrammState == 1 )
  {
    sprintf(this->arr2, " Идёт набор начального фона Nf1");
  }
  if ( ProgrammState == 3 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " Введите массу и тип источника");
  }
  if ( ProgrammState == 4 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " Идёт набор фона от источника");
  }
  if ( ProgrammState == 7 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " Идёт набор конечного фона Nf2");
  }
  if ( ProgrammState == 8 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " Идёт набор конечного фона Nf2");
  }
  //===
  if ( ProgrammState == 1 || ProgrammState == 4 )
  {
    for (int i = 0; i < 8; i++)
    {
      if (this->bAddrBDArr[i] == true)
      {
      	if ( this->Cprw->bFlagOprosa[i+1] == 0 )
      	{
      	  sprintf(this->String[i],
              "БД: %0.1d, t: %05.01f сек, Сум. счёт: %.05d, Сред. счёт: %06.2f, Призн. неснят. сч: %.02d, Err1: %.02d, Err2: %.02d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->Data.SumSchet[i],
	      this->Cprw->Data.SredSchet[i],
	      this->Cprw->N1[i],
	      this->Cprw->N2[i],
	      this->Cprw->N3[i]
          );
        }
	else
	{
	  sprintf(this->String[i],
              "БД: %0.1d, t: %05.01f сек, Код ошибки связи: %d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->ErrorCode[i]
          );
        }
      }
      else
      {
      	sprintf(this->String[i], "");
      }
    }
    sprintf(this->arr, "dT = %.3d мсек, dTmax = %.4d мсек", this->Cprw->dT, this->Cprw->dTmax);
  }
  if (ProgrammState == 2 || ProgrammState == 5 || ProgrammState == 6 || ProgrammState == 7 || ProgrammState == 8 )
  {
    if ( ProgrammState == 2 )
    {
      ProgrammState = 3; // Теперь запросим ввод источника
    }
    if ( ProgrammState == 5 )
    {
      ProgrammState = 3; // Теперь всё с начала
    }
    if ( ProgrammState == 8 )
    {
      ProgrammState = 0; // Теперь всё с начала
    }


    for ( int i = 0; i < 8; i++ )
    {
      if ( this->bAddrBDArr[i] == true )
      {
	if ( this->Cprw->bFlagOprosa[i+1] == 0 )
	{
	  sprintf(this->String[i],
	      "БД: %0.1d, t: %05.01f сек, Сум. счёт: %.05d, Сред. счёт: %06.2f, Призн. неснят. сч: %.02d, Err1: %.02d, Err2: %.02d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->Data.SumSchet[i],
	      this->Cprw->Data.SredSchet[i],
	      this->Cprw->N1[i],
	      this->Cprw->N2[i],
	      this->Cprw->N3[i] );
        }
	else
	{
	  sprintf(this->String[i],
	      "БД: %0.1d, t: %05.01f сек, Код ошибки связи: %d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->ErrorCode[i] );
        }
      }
      else
      {
	sprintf(this->String[i], "");
      }
    }
    sprintf(this->arr, "dT = %.3d мсек, dTmax = %.4d мсек", this->Cprw->dT, this->Cprw->dTmax);
  }
  if ( var >= 0 )
  {
    return this->String[var];
  }
  else if ( var == -1 )
  {
    return this->arr;
  }
  else if ( var == -2 )
  {
    return this->arr2;
  }
}
//---------------------------------------------------------------------------
unsigned int Function_t::Next(void)
{
  WORD Year, Month, Day; // Переменные для хранения даты
  WORD Hour, Min, Sec, MSec; // Переменные для хранения время
  int length; // Для функции sprintf (длинна)

  this->Cprw->AddrBD = this->AddrBD; // Количество
  if ( ProgrammState == -1 )
  {
    upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
    upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
    upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
    upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
    upravlenie &= ~(1 << 4); // Остановить таймер
    upravlenie |= (1 << 5); // Доступна кнопка "Next"
    upravlenie &= ~(1 << 6); // НЕ Доступна кнопка "End" завершить работу с источниками и перейти к набору конечного фона
    upravlenie |= (1 << 7); // Доступны флажки выбора БД
    return upravlenie;
  }
  if ( ProgrammState == 0 )
  {
    char id[10];
    sprintf(id, "COM%d", ComPortNum);
    for (int i = 0; i < 10; i++)
    {
      this->Cprw->DEVID[i] = (wchar_t)id[i];
    }
    if ( this->Cprw->RSConnect(this->Cprw->DEVID) == 0 ) // Если нет ошибок открытия ком-порта
    {
      upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
      upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
      upravlenie &= ~(1 << 2); // Не Доступно для ввода поле "Адрес БД"
      upravlenie &= ~(1 << 3); // НЕ Доступно для ввода поле "Номер COM-порта"
      upravlenie |= (1 << 4); // Запстить таймер
      upravlenie &= ~(1 << 5); // НЕ Доступна кнопка "Next"
      upravlenie &= ~(1 << 7); // НЕ Доступны флажки выбора БД
      ProgrammState = 1;
      this->Cprw->NomIstoch = 0;
      for (int i = 0; i < 8; i++)
      {
      	this->Cprw->Data.flagGetSerialNum[i] = false;
      	this->Cprw->Data.flagSetTimeInterval[i] = false;
      }
    }
    else
    {
      upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
      upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
      upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
      upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
      upravlenie &= ~(1 << 4); // Остановить таймер
      upravlenie |= (1 << 5); // Доступна кнопка "Next"
      this->Cprw->RSDisConnect();
      sprintf(this->String[0],
    	  "Ошибка при попытке открыть COM-порт "
      );
    }
    return upravlenie;
  }
  if ( ProgrammState == 1 ) // Идет набор фона перед источником
  {
    if ( bFlagPotoka == true )
    {
      this->Cprw->Resume(); // каждые 200 мс. делать запрос
      FormErrorReport->Memo1->Lines->Add(this->Cprw->Str_err);
    }
    else
    {
      this->Cprw->OprosBD_Arr(); // каждые 200 мс. делать запрос
    }
    if ( this->Cprw->t == this->intervZad ) // Если набор фона завершился
    { // в ф-ции Reset происходит обнуление t, поэтому t берётся из класса ComPortReadWrite_t
      upravlenie |= (1 << 0); // Доступно для ввода поле "масса источника"
      upravlenie |= (1 << 1); // Доступно для ввода поле "тип источника"
      upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
      upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
      upravlenie &= ~(1 << 4); // Остановить таймер
      upravlenie |= (1 << 5); // Доступна кнопка "Next"
      this->Cprw->RSDisConnect();
      ProgrammState = 2;
      for (int i = 0; i < 8; i++)
      {
        if (this->bAddrBDArr[i] == true)
	{
	  this->Cprw->DataI.SumSchet[i] = this->Cprw->Data.SumSchet[i];
	  this->Cprw->DataI.SredSchet[i] = this->Cprw->Data.SredSchet[i];
        }
      }
    }
    return upravlenie;
  }
  if ( ProgrammState == 3 ) // Идет набор фона от источника
  {
    char id[10];
    sprintf(id, "COM%d", ComPortNum);
    for ( int i = 0; i < 10; i++ )
    {
      this->Cprw->DEVID[i] = (wchar_t)id[i];
    }
    if ( FlagMassyItipa == false ) // = true если поля ввода не пусты, иначе false
    {
      sprintf(this->arr2, "Введите массу и тип источника");
      return upravlenie;
    }
    if ( this->Cprw->RSConnect(this->Cprw->DEVID) == 0 ) // Если нет ошибок открытия ком-порта
    {
      upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
      upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
      upravlenie &= ~(1 << 2); // Не Доступно для ввода поле "Адрес БД"
      upravlenie &= ~(1 << 3); // НЕ Доступно для ввода поле "Номер COM-порта"
      upravlenie |= (1 << 4); // Запстить таймер
      upravlenie &= ~(1 << 5); // НЕ Доступна кнопка "Next"
      upravlenie &= ~(1 << 6); // НЕ Доступна кнопка "End" завершить работу с источниками и перейти к набору конечного фона
      ProgrammState = 4;
      this->Cprw->NomIstoch++; //
    }
    else
    {
      upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
      upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
      upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
      upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
      upravlenie &= ~(1 << 4); // Остановить таймер
      upravlenie |= (1 << 5); // Доступна кнопка "Next"
      upravlenie |= (1 << 6); // Доступна кнопка "End" завершить работу с источниками и перейти к набору конечного фона
      this->Cprw->RSDisConnect();
      sprintf(this->String[0],
	  "Ошибка при попытке открыть COM-порт "
      );
      ProgrammState = 0;
    }
    return upravlenie;
  }
  if ( ProgrammState == 4 )
  {
    if ( bFlagPotoka == true )
    {
      this->Cprw->Resume(); // каждые 200 мс. делать запрос
    }
    else
    {
      this->Cprw->OprosBD_Arr(); // каждые 200 мс. делать запрос
    }
    if ( this->Cprw->t == this->intervZad ) // Если набор фона завершился
    { // в ф-ции Reset происходит обнуление t, поэтому t берётся из класса ComPortReadWrite_t
      upravlenie |= (1 << 0); // Доступно для ввода поле "масса источника"
      upravlenie |= (1 << 1); // Доступно для ввода поле "тип источника"
      //upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
      upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
      upravlenie &= ~(1 << 4); // Остановить таймер
      upravlenie |= (1 << 5); // Доступна кнопка "Next"
      upravlenie |= (1 << 6); // Доступна кнопка "End" завершить работу с источниками и перейти к набору конечного фона

      this->Cprw->RSDisConnect();
      ProgrammState = 5;
    }
  }
///////////////////////////////////////////////
  if (ProgrammState == 6) // Идет конечный набор фона (без источника)
  {
    char id[10];
    sprintf(id, "COM%d", ComPortNum);
    for (int i = 0; i < 10; i++)
    {
      this->Cprw->DEVID[i] = (wchar_t)id[i];
    }
    if ( /*this->Cprw->RSConnect(this->Cprw->DEVID) == 0*/true ) // Если нет ошибок открытия ком-порта
    {
      upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
      upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
      upravlenie &= ~(1 << 2); // Не Доступно для ввода поле "Адрес БД"
      upravlenie &= ~(1 << 3); // НЕ Доступно для ввода поле "Номер COM-порта"
      upravlenie |= (1 << 4); // Запстить таймер
      upravlenie &= ~(1 << 5); // НЕ Доступна кнопка "Next"
      ProgrammState = 7;
    }
    else
    {
      upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
      upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
      upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
      upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
      upravlenie &= ~(1 << 4); // Остановить таймер
      upravlenie |= (1 << 5); // Доступна кнопка "Next"
      this->Cprw->RSDisConnect();
      sprintf(this->String[0],
          "Ошибка при попытке открыть COM-порт "
      );
      upravlenie |= (1 << 7); // Доступны флажки выбора БД
      ProgrammState = 0;
    }
    return upravlenie;
  }
	//{ // в ф-ции Reset происходит обнуление t, поэтому t берётся из класса ComPortReadWrite_t
  upravlenie &= ~(1 << 0); // НЕ Доступно для ввода поле "масса источника"
  upravlenie &= ~(1 << 1); // НЕ Доступно для ввода поле "тип источника"
  //upravlenie |= (1 << 2); // Доступно для ввода поле "Адрес БД"
  upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
  upravlenie &= ~(1 << 4); // Остановить таймер
  upravlenie |= (1 << 5); // Доступна кнопка "Next"
  upravlenie &= ~(1 << 6); // НЕ Доступна кнопка "End" завершить работу с источниками и перейти к набору конечного фона
  upravlenie |= (1 << 7); // Доступны флажки выбора БД
  //this->Cprw->RSDisConnect();
  ProgrammState = 8;

  DecodeDate(Date(), Year, Month, Day);
  sprintf(forReport, "Дата проведения:%.02d.%.02d.%.04d", Day, Month, Year);
  Form_Report->Memo_Log->Lines->Add(forReport);
  sprintf(forReport, "ПРОВЕРКА ЧУВСТВИТЕЛЬНОСТИ БД (время измерения %dс)", (this->intervZad/1000));
  Form_Report->Memo_Log->Lines->Add(forReport);

  DecodeTime(Time(), Hour, Min, Sec, MSec);
  sprintf(forReport, "Время проведения:%.02d.%.02d.%.02d", Hour, Min, Sec);
  Form_Report->Memo_Log->Lines->Add(forReport);

  if (this->Cprw->Data.AllSerialNum == true) // = true, если все серийные номера получены
  {
    sprintf(forReport, "Имя файла для сохранения логов: %s", this->Cprw->Str_FileNameSerialNum, "");
    Form_Report->Memo_Log->Lines->Add(forReport);
  }
  else
  {
    sprintf(forReport, "Имя файла для сохранения логов выбирается пользователем: серийные номера не прочитаны");
    Form_Report->Memo_Log->Lines->Add(forReport);
  }

  length = sprintf(forReport, "В проверке участвовали:");
  int length2 = length;
  for ( int i = 0; i < 8; i++ )
  {
    if (this->bAddrBDArr[i] == true)
    {
      if ( length2 == length )
      {
        length2 += sprintf( &forReport[length2], "BD%d", AddrBDArr[i] );
      }
      else
      {
        length2 += sprintf( &forReport[length2], ", BD%d", AddrBDArr[i] );
      }
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   Счёт импульсов за время измерения фона");
  length = sprintf(forReport, "   Nf1:   ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d    ", this->Cprw->DataI.SumSchet[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   Начальная скорость счёта фона (имп/с)");
  length = sprintf(forReport, "   nf1:  ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%.2f   ", this->Cprw->DataI.SredSchet[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   Кол-во импульсов фона по анализатору в выделен.зоне");
  length = sprintf(forReport, "     :    ");
  for (int i = 0; i < 8; i++)
  {
    if (this->bAddrBDArr[i] == true)
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Naf[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   Начальная скорость счёта фона по анализатору (имп/с)");
  length = sprintf(forReport, "     :    ");
  for (int i = 0; i < 8; i++)
  {
    if (this->bAddrBDArr[i] == true)
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Naf[i]/(this->intervZad/1000));
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("---------------------------------------------------------------------------------------");

  sprintf(forReport, " Источник №:%d", this->Cprw->NomIstoch);
  Form_Report->Memo_Log->Lines->Add(forReport);
  sprintf(forReport, "   Масса источника,г(АктивнМБк):%s", this->massaIstochnika);
  Form_Report->Memo_Log->Lines->Add(forReport);
  sprintf(forReport, "   Тип источника:%s", this->tipIctochnika);
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   \"Счёт от источника\" Ns( имп )");
  length = sprintf(forReport, "     :  ");
  for (int i = 0; i < 8; i++)
  {
    if (this->bAddrBDArr[i] == true)
    {
      length += sprintf(&forReport[length],
          "%d   ",
	  this->Cprw->Data.SumSchet[i]
      );
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   \"Cкорость счёта от источника\" ns( имп/с)");
  length = sprintf(forReport, "     :  ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length],
	  "%.02f   ",
	  this->Cprw->Data.SredSchet[i]
      );
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   \"Счёт от источника по анализатору\"  Ns ( имп )");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Nai[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   \"Cкорость счёта от источника по анализатору\" ns( имп/с )");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Nai[i]/(this->intervZad/1000));
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   \"Чистая скорость счёта\" ns-nf( имп/с)");
  length = sprintf(forReport, "     :  ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length],
         "%.02f   ",
	 ( this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i] )
      );
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   Значение канала от цезия");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Tceziya[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   Значение канала от светодиода");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Svetodiod[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add( forReport );
  // ===
  Form_Report->Memo_Log->Lines->Add("   Погрешность порогов дискриминации,%  ");
  length = sprintf(forReport, "   Ф :    ");
  int modul;
  double rezult;
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      modul = this->Cprw->DataI.SumSchet[i] - this->Arr_Naf[i];
      if ( modul < 0 )
      {
	modul = modul * -1;
      }
      rezult = (double)modul * 100.0 / this->Cprw->DataI.SumSchet[i];
      length += sprintf(&forReport[length], "%.01f      ", rezult);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  length = sprintf(forReport, "   И :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      modul = this->Cprw->Data.SumSchet[i] - this->Arr_Nai[i];
      if ( modul < 0 )
      {
	modul = modul * -1;
      }
      rezult = (double)modul * 100.0 / this->Cprw->Data.SumSchet[i];
      length += sprintf(&forReport[length], "%.01f      ", rezult);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   Чувствительность (имп/(с*г) или (имп/(с*МБк)) )");
  if ( m != 0 )
  {
    length = sprintf(forReport, "   S :");
    for ( int i = 0; i < 8; i++ )
    {
      if ( this->bAddrBDArr[i] == true )
      {
	length += sprintf(&forReport[length],
	    "%.1f   ",
	    ( ( this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i]) / m )
        );
      }
    }
  }
  else
  {
    Form_Report->Memo_Log->Lines->Add("   S :");
    sprintf(forReport, "      Ошибка: m == 0   ");
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  Form_Report->Memo_Log->Lines->Add("   Погрешность чувствительности (СКО)");
  length = sprintf(forReport, "     :");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      if ( (this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i]) != 0 )
      {
	length += sprintf(&forReport[length],
	    "%.3f   ",
	    ( sqrt( (this->Cprw->Data.SredSchet[i] + this->Cprw->DataI.SredSchet[i]) * (this->intervZad/1000) ) /
	    ( (this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i]) * (this->intervZad/1000) ) )
        );
      }
      else
      {
	length += sprintf(&forReport[length], "Ошибка: деление на ноль    ");
      }
    }
  }
  Form_Report->Memo_Log->Lines->Add( forReport );
  //===
  Form_Report->Memo_Log->Lines->Add("   Количество ошибок связи:"); // N3
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Cprw->N3[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add( forReport );
  // ===
  Form_Report->Memo_Log->Lines->Add("   Количество признаков неснятого счёта:"); // N1
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Cprw->N1[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  Form_Report->Memo_Log->Lines->Add("   Количество пропущенных интервалов:"); // N2
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Cprw->N2[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  Form_Report->Memo_Log->Lines->Add("---------------------------------------------------------------------------------------");
  }
  return upravlenie;
  }
  return upravlenie;
}
//---------------------------------------------------------------------------
Function_t::Function_t( void ) // Конструктор
{
  bFlagPotoka = /*true*/ false; // true - использовать поток, false - не использовать поток
  Cprw = new ComPortReadWrite_t(true, bFlagPotoka); // true - Не запускать поток при выделение памяти
  Cprw->FreeOnTerminate = true; // false - НЕ уничтожаться после завершения
  ProgrammState = -1; // Текущее состояние программы (-1 - при старте)
  this->upravlenie = 0x0F;

  DIAcopy(" Выберите номер COM-порта и количество БД ", 1);
  DIAcopy("", 2);
  DIAcopy("", 3);
  DIAcopy("", 4);
  DIAcopy("", 5);
  DIAcopy("", 6);
  DIAcopy("", 7);
  DIAcopy("", 8);
}
//---------------------------------------------------------------------------
void Function_t::GetParam(char * s, double var)
{
  if ( DIAcpy("t", s) == 0 )
  {
    /*t = var*/;
  }
  else if ( DIAcpy("Ns", s) == 0 )
  {
    Ns = var;
  }
  else if ( DIAcpy("Nf", s) == 0 )
  {
    Nf = var;
  }
  else if ( DIAcpy("Nf1", s) == 0 )
  {
    Nf1 = var;
  }
  else if ( DIAcpy("Nf2", s) == 0 )
  {
    Nf2 = var;
  }
  else if ( DIAcpy("m", s) == 0 )
  {
    m = var;
  }
  else if ( DIAcpy("S", s) == 0 )
  {
    S = var;
  }
}
//---------------------------------------------------------------------------
int Function_t::DIAcpy(char * var1, char * var2)
{
  int i;
  for (i = 0; (i < razmer) && (var2[i] != 0) ; i++)
  {
    if ( var1[i] != var2[i] )
    {
      return -1; // Строки не равны
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
int Function_t::Stop(void)
{
  for ( int i = 0; i < 8; i++ )
  {
    sprintf(this->String[i], "");
  }
  sprintf(this->arr, "");

  ProgrammState = 0;
  upravlenie &= ~(1 << 0); // НЕ доступно для ввода поле "масса источника"
  upravlenie &= ~(1 << 1); // НЕ доступно для ввода поле "тип источника"
  upravlenie |= (1 << 3); // Доступно для ввода поле "Номер COM-порта"
  upravlenie &= ~(1 << 4); // Остановить таймер
  upravlenie |= (1 << 5); // Доступна кнопка "Next"
  upravlenie |= (1 << 7); // Доступны флажки выбора БД
  this->Cprw->RSDisConnect();	// Закрыть COM-порт
  this->Cprw->Reset();

  return upravlenie;
}
//---------------------------------------------------------------------------
int Function_t::EndIstochnik(void)
{
  for ( int i = 0; i < 8; i++ )
  {
    sprintf(this->String[i], "\0\0\0\0\0\0\0\0\0\0\0\0\0");
  }
  upravlenie |= (1 << 4); // Запустить таймер
  upravlenie &= ~(1 << 6); // НЕ Доступна кнопка "End" завершить работу с источниками и перейти к набору конечного фона
  ProgrammState = 6; // Перейти к заключительному этапу - сбору конечного фона
  return upravlenie;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

