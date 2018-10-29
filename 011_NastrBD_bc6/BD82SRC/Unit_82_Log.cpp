//---------------------------------------------------------------------------
#pragma hdrstop
#include "Unit_82_Log.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//==\\#include <dir.h>
#include <vcl.h>
#include <stdio.h>
AnsiString LogPath = "";
AnsiString FileNameConst =
    "\\\\fileserver\\change\\Podr-56\\Дорофеев Игорь Александрович (DIA)\\Logs\\";
AnsiString FileName = "";
//---------------------------------------------------------------------------
void WriteLog_DIA(char * chString)
{
/*
  return; // Быстрый вылет :-)
  //
  char lpBuffer[MAX_COMPUTERNAME_LENGTH + 1];
  char lpOemBuffer[MAX_COMPUTERNAME_LENGTH + 1];
  DWORD nSize = MAX_COMPUTERNAME_LENGTH;
  GetComputerName(
      &lpBuffer[0], // address of name buffer
      &nSize // address of size of name buffer
      );
  if ( !CharToOem(
           lpBuffer, // pointer to string to translate
           lpOemBuffer ) // pointer to translated string
      )
  {
    strcpy(lpOemBuffer, lpBuffer);
  }

  FileName = FileNameConst;
  FileName += lpOemBuffer;
  FileName += "_" + ExtractFileName( Application->ExeName );
  FileName += ".log";
  int nLogFile = -1;

  if ( FileExists( FileName ) )
  {
    nLogFile = FileOpen( FileName, fmOpenWrite | fmShareDenyWrite );
  }
  else
  {
    nLogFile = FileCreate(FileName);
  }
  if ( -1 != nLogFile )
  {
    TDateTime dateTime; // = Time();
    // Set file pointer to the end of file.
    FileSeek( nLogFile, 0, 2 );
    char acBuffer[1024] = {0};
    sprintf(acBuffer, "%s\t%s\r\n",
        ((AnsiString)dateTime.CurrentDateTime()).c_str(),
        chString);
    FileWrite(nLogFile, ( void * )acBuffer, strlen(acBuffer));
    FileClose(nLogFile);
  }
  else
  {
    //==\\strcpy(text_buf[num_lines], "Ошибка доступа к файлу: ");
    //==\\strcat(text_buf[num_lines++], FileName.c_str());
  }
*/
}
//---------------------------------------------------------------------------

