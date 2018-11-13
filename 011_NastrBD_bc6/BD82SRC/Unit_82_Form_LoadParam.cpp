//---------------------------------------------------------------------------
#include <vcl.h>
#include <Inifiles.hpp>
#pragma hdrstop

#include "Unit_82_Form_LoadParam.h"
#include "Unit_82_Form_Start.h"

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*extern*/ const char * IniFileName = "DIA_BD82.ini";
TForm_LoadParam *Form_LoadParam;
//---------------------------------------------------------------------------
__fastcall TForm_LoadParam::TForm_LoadParam(TComponent* Owner)
        : TForm(Owner)
{
  m_pParams = new std::list< std::list< Param > >;
  m_nN = -1;
}
//---------------------------------------------------------------------------
int GetString(int hFile, AnsiString* pstrBuffer)
{
  char buff[1024] = {0};
  char * p = buff;

  int n = 0;
  int len = 0;

  // Trim leading whitespaces.
  do
  {
    n = FileRead(hFile, p, 1);
  } while ( (0 != n) && (' ' == *p) );
  // Read line.
  while ( 0 != n )
  {
    if ('\r' == *p)
    {
      // Read '\n'.
      n = FileRead(hFile, p, 1);
      break;
    }
    if ('\n' == *p)
    {
      break;
    }
    len++;
    p++;
    n = FileRead(hFile, p, 1);
  }
  *p = '\0';
  if ( 0 != len )
  {
    pstrBuffer->printf("%s", buff);
  }
  return len;
}
//---------------------------------------------------------------------------
void TForm_LoadParam::GetParams(std::list<Param> & params)
{
  std::list< std::list<Param> >::iterator i;
  std::list< Param >::iterator j;

  if ( (NULL != m_pParams) && (!m_pParams->empty()) )
  {
    for ( i = m_pParams->begin(); i != m_pParams->end(); i++ )
    {
      if ( !i->empty() )
      {
        if ( i->front().m_nN == m_nN )
        {
          break;
        }
      }
    }
    if ( i != m_pParams->end() )
    {
      std::copy( i->begin(), i->end(), std::back_inserter(params) );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_LoadParam::Button_BrowseClick(TObject *Sender)
{
  if ( OpenDialog->Execute() )
  {
    Edit_LogFileName->Text = OpenDialog->FileName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_LoadParam::Button_ReadClick(TObject *Sender)
{
  AnsiString strFileName = Edit_LogFileName->Text;
  int nLogFile = -1;

  if ( FileExists( Edit_LogFileName->Text.c_str() ) )
  {
    nLogFile = FileOpen(strFileName, fmOpenRead);
    if ( -1 != nLogFile )
    {
      // Cleaning up.
      m_pParams->clear();
      ListView_DetectionUnits1->Items->Clear();

      // Trim first line (header).
      AnsiString line;
      int k = GetString(nLogFile, &line);
      if ( 0 != k )
      {
        do
        {
          k = GetString(nLogFile, &line);
          if ( 0 != k )
          {
            ProcessLine(line);
          }
        }
        while (0 != k);
      } // end if ( 0 != k )
      FileClose(nLogFile);
      // Process results.
      if ( !m_pParams->empty() )
      {
        for ( std::list< std::list< Param > >::iterator i = m_pParams->begin();
            i != m_pParams->end(); i++)
        {
          // Add front.
          TListItem * pli = ListView_DetectionUnits1->Items->Add();
          if ( NULL != pli )
          {
            pli->Caption = IntToStr( i->front().m_nN );
          }
        }
        Button_Ok->Enabled = true;
      }
      else
      {
        Button_Ok->Enabled = false;
      }
    }
    else // if ( -1 != nLogFile )
    {
      ShowMessage("Ошибка доступа к файлу: " + strFileName);
    }
  }
  else
  {
    ShowMessage("Файл: " + strFileName + " не существует");
  }
}
//---------------------------------------------------------------------------
int TForm_LoadParam::ProcessLine(AnsiString strLine)
{

  int n = 0;
  char szDateTime[16] = {0};
  int tCode = 0;
  float tValue = 0;
  int pwmPulseLengthCode = 0;
  int pwmCycleTimeCode = 0;
  int vValue = 0;
  int ledCode = 0;
  char szComment[512] = {0};

  sscanf(strLine.c_str(), "%d%s%d%f%d%d%d%d%s",
      &n, // №БД
      szDateTime, // Дата
      &tCode, // Т (Код)
      &tValue, // Т (градусы)
      &pwmPulseLengthCode, // U
      &pwmCycleTimeCode, // U (Код) ----------- Вносить в строку "ПЕРИОД ШИМ минимальный"
      &vValue, // U (Изм)
      &ledCode, // Св (Код)
      szComment // Комментарий
      );


      Param param = Param(
      n,
      StrToDate(szDateTime),
      tCode,
      tValue,
      pwmPulseLengthCode,
      pwmCycleTimeCode,
      vValue,
      ledCode,
      AnsiString(szComment)
      );

  std::list< std::list< Param > >::iterator i; // list<> ** i;
  std::list< Param >::iterator j; // list<> * j;
  if ( NULL != m_pParams )
  {
    for ( i = m_pParams->begin(); i != m_pParams->end(); i++ )
    {
      for ( j = i->begin(); j != i->end(); j++ )
      {
        if ( j->m_nN == param.m_nN )
        {
          goto exit;
        }
      }
    }
    exit:
    if ( i == m_pParams->end() )
    {
      // New list.
      std::list<Param> params;
      params.push_back(param);
      m_pParams->push_back(params);
    }
    else
    {
      // Existing list.
      i->push_back(param);
    }
  }
  return 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadParam::ListView_DetectionUnits1Click(
      TObject *Sender)
{
  std::list< std::list< Param > >::iterator i;
  std::list< Param >::iterator j;

  // ДИА 04.09.2015 ===>>
  //==\\int DiaShim; //m_nPwmCycleTimeCode
  //==\\int DiaShim_Min;
  DiaShim = 0;
  DiaShim_Min = 0;
  // ДИА 04.09.2015 <<===


  if ( NULL != m_pParams && !m_pParams->empty() )
  {
    TListItem * pli = ListView_DetectionUnits1->Selected;
    if ( NULL != pli )
    {
      // Cleaing up.
      ListView_DetectionUnits2->Items->Clear();
      //
      for ( i = m_pParams->begin(); i != m_pParams->end(); i++ )
      {
        if ( !i->empty() )
        {
          // Save detection unit number;
          m_nN = i->front().m_nN;
          //
          if ( pli->Caption == IntToStr(m_nN) )
          {
            break;
          }
        }
      }
      if ( i != m_pParams->end() )
      {
        for ( j = i->begin(); j != i->end(); j++ )
        {
          TListItem * pli = ListView_DetectionUnits2->Items->Add();
          if ( NULL != pli )
          {
            pli->Caption = FloatToStrF( j->m_fltTValue, ffFixed , 8, 1 );
            pli->Checked = j->m_xChecked;
            pli->SubItems->Add( IntToStr( j->m_nTCode ) );
            pli->SubItems->Add( IntToStr( j->m_nLedCode ) );
            // ДИА 04.09.2015 ===>>
            if ( j == i->begin() )
            {
              DiaShim_Min = j->m_nPwmCycleTimeCode;  //m_nPwmCycleTimeCode
            }
            else
            {
              DiaShim = j->m_nPwmCycleTimeCode;
              if ( DiaShim < DiaShim_Min )
              {
                DiaShim_Min = DiaShim;
              }
            }
            // ДИА 04.09.2015 <<===
          }
        }
      }
      else
      {
        // Empty.
        m_nN = -1;
      }
    }
  }
  // ДИА 04.09.2015 ===>>
  //==\\Form_82_Start->Edit_2_Col2_Row9->Text = IntToStr( DiaShim_Min );
  //==\\FlagGrafik = true;
  // ДИА 04.09.2015 <<===
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadParam::ListView_DetectionUnits2Click(
      TObject *Sender)
{
  std::list<std::list<Param> >::iterator i;
  std::list<Param>::iterator j;

  if ( NULL != m_pParams && !m_pParams->empty() )
  {
    for ( i = m_pParams->begin(); i != m_pParams->end(); i++ )
    {
      if ( !i->empty() )
      {
        if ( i->front().m_nN == m_nN )
        {
          break;
        }
      }
    }
    if ( i != m_pParams->end() )
    {
      j = i->begin();
      for ( int n = 0; (n < ListView_DetectionUnits2->Items->Count) && (j != i->end()); n++, j++ )
      {
        j->m_xChecked = ListView_DetectionUnits2->Items->Item[n]->Checked;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_LoadParam::FormShow(TObject *Sender)
{
  // приведённый ниже код здесь не нужен!!! т.к. форма присутствует не одна
  //if( FormDispet != 0 )
  //{
  //  FormDispet->DiaGetWinHandle( this->Handle );
  //}
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadParam::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  AnsiString m_strLogFileName; // Имя файла журнала.
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    IniFile->WriteInteger( "Form LoadParam Settings", "FormLoadParamWidth", Form_LoadParam->Width );
    IniFile->WriteInteger( "Form LoadParam Settings", "FormLoadParamHeight", Form_LoadParam->Height );
    IniFile->WriteInteger( "Form LoadParam Settings", "FormLoadParamLeft", Form_LoadParam->Left );
    IniFile->WriteInteger( "Form LoadParam Settings", "FormLoadParamTop", Form_LoadParam->Top );
    IniFile->WriteString( "Form LoadParam Settings",  "Form_LoadParam_Edit_LogFileName_Text", Form_LoadParam->Edit_LogFileName->Text );
    // Именно "Form ARCH Settings" а не "Form LoadParam Settings"
    IniFile->WriteString( "Form ARCH Settings", "LogFileName", Form_LoadParam->Edit_LogFileName->Text );
    m_strLogFileName = IniFile->ReadString( "Form ARCH Settings", "LogFileName", "NastrBD.log" );
    delete IniFile;
  }
  catch(...) // любое исключение
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm_LoadParam::FormCreate(TObject *Sender)
{
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    Form_LoadParam->Width = IniFile->ReadInteger( "Form LoadParam Settings", "FormLoadParamWidth", Form_LoadParam->Width );
    Form_LoadParam->Height = IniFile->ReadInteger( "Form LoadParam Settings", "FormLoadParamHeight", Form_LoadParam->Height );
    Form_LoadParam->Left =  IniFile->ReadInteger( "Form LoadParam Settings", "FormLoadParamLeft", Form_LoadParam->Left );
    Form_LoadParam->Top = IniFile->ReadInteger( "Form LoadParam Settings", "FormLoadParamTop", Form_LoadParam->Top );
    Form_LoadParam->Edit_LogFileName->Text = IniFile->ReadString( "Form LoadParam Settings", "Form_LoadParam_Edit_LogFileName_Text",
      Form_LoadParam->Edit_LogFileName->Text );
    delete IniFile;
  }
  catch(...) // Любое исключение
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------



