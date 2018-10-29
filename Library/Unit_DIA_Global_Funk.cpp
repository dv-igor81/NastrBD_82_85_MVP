//---------------------------------------------------------------------------
//#include <vcl.h>
//#pragma hdrstop
#include "Unit_DIA_Global_Funk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// ���������� ����������
find_t find;
godnost_t godnost1;
godnost_t godnost2;
godnost_t godnost3;
godnost_t gst;
godnost_t gst_Sdvig;
StrParam_t StrParam1;
//---------------------------------------------------------------------------
// ���������� ����, � ������ �������� ���������� ������
// ��� ������, ��� ��������� �������� �������� ������ (������� � �������)
int dia_atof( float * fVar, char * chStr ) // chStr to float
{
  float Rezult; // ���������
  float Simvol; // ������� �����
  int iFlagSostoyaniya; // ���� ���������
  int NSim; // ������� ���������� ������� � ������
  bool bFlagZnak; // ���� ����� �����
  bool bFlagZnakExp; // ���� ����� ���������� �����
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
      // ��� ��������������:
          // ��������� � 0
      // ��� ������ ������� � ��� ���������
          // �����, ���� ������ ����������� �������
      // ��� ���������:
          // ���������� �������, ������� ����, ����� (�������), ����� (+-)
  // iFlagSostoyaniya == 1 ---
      // ��� ��������������:
          // ��������� � 0, ���� ��������� � 5
      // ��� ������ ������� � ��� ���������
          // ������ ������� �����
      // ��� ���������:
          // ������� ����, ����� (�������), ������� ���������� (e ��� E)
  // iFlagSostoyaniya == 2 ---
      // ��� ��������������:
          // ��������� � 1, ���� ��������� � 3
      // ��� ������ ������� � ��� ���������
          // ������ ������� ���������� (e, E)
      // ��� ���������:
          // ������ �����, ������ ����� (+-)
  // iFlagSostoyaniya == 3 ---
      // ��� ��������������:
          // ��������� � 1, ���� ��������� � 6
      // ��� ������ ������� � ��� ���������
          // ������ ������� ����� (�������), ���� ���� ��������� � 1,
          // ���� ������ ������� �����, ���� ���� ��������� � 6
      // ��� ���������:
          // ������ �����, ���������� (e, E)
  // iFlagSostoyaniya == 4 ---
      // ��� ��������������:
          // ��������� � 2
      // ��� ������ ������� � ��� ���������
          // ������ ������� ����� (+-)
      // ��� ���������:
          // ������ �����
  // iFlagSostoyaniya == 5 ---
      // ��� ��������������:
          // ��������� � 0
      // ��� ������ ������� � ��� ���������
          // ������ ������� ����� (+-)
      // ��� ���������:
          // ������ ����� (�������), ���� ������ �����
  // iFlagSostoyaniya == 6 ---
      // ��� ��������������:
          // ��������� � 0 ���� ��������� � 5
      // ��� ������ ������� � ��� ���������
          // ������ ������� ����� (�������)
      // ��� ���������:
          // ������ �����

  NSim = diaStrCpy( chString_18, "0123456789-+00., " );
  for ( i = 0; chStr[i] != 0; i++ )
  {
    NSim = FindSimInStr( chStr[i], chString_18 );
    if ( NSim == -1 )
    {
      return i + 1; // ���������� ������, � ������� �������� ������, ������� � �������
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
        // �� ���� ������� �������, ���� ������� ���������� �������, ���� '-' ��� '+'
        if ( ( iFlagSostoyaniya == 0 ) || ( iFlagSostoyaniya == 5 ) )
        {
          iFlagSostoyaniya = 1;
          NSim = diaStrCpy( chString_18, "012345678900eE.,0" );
        }
        else if ( ( iFlagSostoyaniya == 3 ) || ( iFlagSostoyaniya == 6 ) )
        {
          iPorDes--;
          if ( iFlagSostoyaniya == 6 ) // '-' ��� '+', ����� '.' ��� ','
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
    else if ( ( NSim == 10 ) || ( NSim == 11 ) ) // '-' ��� '+'
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
        return 0; // ������� �������� ����������
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
          iFlagSostoyaniya = 6; // ����� ����� �����, ���� ����� ����� �������
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
  if ( iPor > 38 ) // ��� ���� float �����������-���������� ���������� ������� - 38
  {
    return i; // ���������� ������, � ������� �������� ������, ������� � �������  
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
  return 0; // ������� �������� ����������
}
//---------------------------------------------------------------------------
// ���������� ����, � ������ �������� ���������� ������
// ��� ������, ��� ��������� �������� �������� ������ (������� � �������)
int dia_atoi( int * iVar, char * chStr ) // chStr to int
{
  char chString_14[14];
  int Rezult; // ���������
  int Simvol; // ������� �����
  int iFlagSostoyaniya; // ���� ���������
  bool bFlagZnak;
  int NSim; // ������� ���������� ������� � ������
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
      return i + 1; // ���������� ������, � ������� �������� ������, ������� � �������
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
    else if ( ( NSim == 10 ) || ( NSim == 11 ) ) // '-' ��� '+'
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
  return 0; // ������� �������� ����������
}
//---------------------------------------------------------------------------
int GetLengthStr( char * chStr ) // ���������� �����, ��� ����-�������
{
  int i;
  for ( i = 0; chStr[i] != 0; i++ )
  {
  }
  return i;
}
//---------------------------------------------------------------------------
// ���� ������ chSim � ������ chStr, ������� � ������� iFirst,
// ���������� �������� iLast.
// ����������: -1 - �� �����, ����� ������ ���������� ������� � �������
// chStr (������� �� 0)
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
// �������� ����� ������ chStrFrom � ������ chStrTo
// iFirst - ������ ������� ����������� �������
// iLast - ������ ���������� ����������� �������
// ���� iFirst = iLast = 0, �� ���������� ��� ������
int diaStrCpy( char * chStrTo, char * chStrFrom, int iFirst, int iLast )
{
  int i1, i2;
  int iEndLoop;

  if ( KorekArg( chStrFrom, iFirst, & iLast ) == -1 )
  {
    return -1;
  }
  iEndLoop = iLast;

  for ( i1 = 0, i2 = iFirst; i2 <= iEndLoop; i1++, i2++ ) // ������� (chStrFrom[i] != 0) ��� �� ������������
  {
    chStrTo[i1] = chStrFrom[i2];
  }

  chStrTo[i1] = '\0';
  return i1; // ����� ������������� ������, ��� ����� ������������ ����
}
//---------------------------------------------------------------------------
// ���������� ������ N �������� ���� �����, ���� ������ ��������� � ������
// N �������� - ������������ 0, ���� -1 - ������ �� ���������, ���� -2
// - ����� ����� �� ����� ������ N, ���� -3 - ������ ��� ����� N
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
  return 0; // �����
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// ���� ��������� ������ chStrSmall � ������ ������� chStrBig,
// ������� � ������� iFirst, ���������� �������� iLast
// ����������: -1 - �� �����, ����� ������ � ������� chStrBig
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
  if ( iStart == -1 ) // �� ������ ������
  {
    return -1;
  }
  else if ( LenSmall == 1 ) // ����� ������ ������� ���� �� ������ �������
  {
    return iStart;
  }
  if ( iLast != 0 ) // iLast == 0 �� ���������
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
      return i; // �����
    }
  }
  return -1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
float diaBaseExp( int iPor ) // = 10^iPor, ���� iPor <= 32 + 7 (39)
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
  TCHAR buf[2]; // ������ ����� ����������� ����� � ������� ������ �����
                // ������ - ","
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
// ����������� ������ chFrom, �������� ��������� � ������ chTo
// ������� �� ���������� ������� � ������ ������;
// ������� � ������ ����� ������ ����������� ������� ������;
// ��������� ������ ����� �������� � ������:
//        '('; ','; '='; '+'; '-'; '*'; '/'; '%'; "if"; "for";
//        "while"; "//"; "=="; "!="; ">="; "<="; "+="; "-="; "*=";
//        "/="; "%="; "||"; "&&"
// ��������� ������ ����� ��������� � ���������:
//        ')'; '=' '+'; '-'; '*'; '/'; '%'; "//"; "=="; "!="; ">=";
//        "<="; "+="; "-="; "*="; "/="; "%="; "||"; "&&"
void SpaceCPPConvert( godnost_t * godnost_var )
{
  char chTemp[255];
  int iLen;
  int i1, i2;
  int iFS;
  bool bf1; // true - �� ���������� ���������� ������, false - ���������� ������
  int iIdentifik; // = 0 - ��������� ������������ ������� ������, ����� �������
  // �� ����������� �������� ������������������...
  bool bfPrigodnost; // true - ������ �������� ��� ���������� ���������.
  bool bfUchet; // true - ������ ";" ����������� (��������� ����. ��������� ������)


  bfPrigodnost = true;
  bfUchet = true;

  GodRes( godnost_var ); // ������������� ����� ���������


  iLen = GetLengthStr( godnost_var->chOriginal );
  bf1 = true; // ���� ������ ���������� � ����������� ������� - ������ ���
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
      find.chR = '0'; // ������ �����������
      find.StrLek = " 0\t0(0)0,0=0>0<0;0+0"
                    "-0*0/0%0&0|0^0\"0'0{0"
                    "}0#";

      find.iFirst = i1; // ������ ������ � ������ find.StrText
      find.RazLek = true; // ������������ ������ ����������� (true - find.iLast � find.N ������������)
      //==\\find.iLast = i1; // ��������� ������ � ������ find.StrText
      //==\\find.N = 1; // ��������� �� ������ ������� �� ������ find.StrText

      iFS = FindMultiInBig( & find );
      find.RazLek = false; // �� ������������ ������ �����������
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
          ( godnost_var->Prichina == godnost_t::pr_Kavychki ) // �������� ������������� ��� ������� ������� ���� �������
          || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ������� �������� ��� �������
        )
        {
          godnost_var->Kavychki++;
        }
        break;
      case 19: // "'"
        if
        (
          ( godnost_var->Prichina == godnost_t::pr_Appostr ) // �������� ������������� ��� ������� ������� ��� ��������
          || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ������� �������� ��� �������
        )
        {
          godnost_var->Appostr++;
        }
        break;
      case 22: // "#"
        if
        (
          ( godnost_var->Prichina == godnost_t::pr_Reshotka ) // �������� ������������� ��� ������� ������� ��� �������
          || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ������� �������� ��� �������
        )
        {
          godnost_var->Reshotka++;
        }
        break;
      }


      if ( Prigodnost( godnost_var ) == false )
      {
        // �������� ������������� ����������� ���� �������
        // ������� ��� ���������� ��� ����� ������� "/*"
        if ( godnost_var->Prichina != godnost_t::pr_KomOtkr )
        {
          if ( iFS != -2 ) // ���� �� ������ ������� FindMultiInBig (�������� find.iFirst = -1 )
          {
            iFS = -1; // ������ ���������� ������ ������
          }
        }
      }

      switch ( iFS )
      {
      // ��������� ���������� ������ ����� ���������� ���������
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
            bf1 = true; // ������ �� ������� ���������� ��������
            chTemp[i2] = ' ';
            i2++;
          }
        }
        break;
      }
      switch ( iFS )
      {
      case 1: // " "   // �����, �.�. ������� ������ - ���������� ������
      case 2: // "\t"  // �����, �.�. ������� ������ - ���������� ������
        if ( bf1 == false )
        {
          bf1 = true;
          chTemp[i2] = ' ';
          //chTemp[i2] = godnost_var->chOriginal[i1];
          i2++;
        }
        break;
      // ��������� ���������� ������ ����� ��������� ��������
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
        chTemp[i2] = godnost_var->chOriginal[i1]; // ����������� ���� ������
        i2++;
        bf1 = false; // ����� ���� �������� ��� ������
        // �������� ���������� ������ ����� �������� � ��������� �� 3 �� 17
        if ( bf1 == false )
        {
          bf1 = true; // ������ �� ������� ���������� ��������
          chTemp[i2] = ' ';
          i2++;
        }
        break;
      // ����������� ��������� ������� �� ����� ������� �� ����� �� �����
      case 4: // ")"
      case 18: // "\""
      case 19: // "'"
      case 20: // "{"
      case 21: // "}"
      case -1: // �� ����� �� ������ �� ��������� ��������
        bf1 = false; // ���������, ��� ������� ������ - �� ����������
        chTemp[i2] = godnost_var->chOriginal[i1];
        i2++;
        break;
      case -2: // ������ �������
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
    find.RazLek = true; // ������������ ������ ����������� (true - find.iLast � find.N ������������)
    //==\\find.iLast = ...; // ��������� ������ � ������ find.StrText
    //==\\find.N = ...; // ��������� �� �������� �� find.N �������� � ������ find.StrText
    find.RazLek = true; // ������������ ������ �����������

    find.chR = ':'; // ������ �����������
    find.StrLek = "if:/*:*/:->:++:--:()://:==:!=:" 
                  ">=:<=:&&:||:+=:-=:*=:/=:%=:|=:"
                  "&=:^=:<<:>>:\\\":while:for:\\\\:do";

    iFS = FindMultiInBig( & find );
    switch ( iFS )
    {
    case 2: // "/*"
      if ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ������� �������� ��� �������
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
        ( godnost_var->Prichina == godnost_t::pr_SlashTwo ) // �������� ������������� ��� ������� ������� ���� ��� ������ �����
        || ( godnost_var->Prichina == godnost_t::pr_NetPrichin ) // ������� �������� ��� �������
      )
      {
        godnost_var->SlashTwo++;
      }
      break;
    }

    if ( iFS >= 0 ) // ������� ���� �� �������
    {
      if ( Prigodnost( godnost_var ) == false )
      {
        if ( godnost_var->Prichina != godnost_t::pr_KomOtkr )
        {
          iFS = -3; // �� ��������� ������� ��� ������� ����� �� �������.
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
        iFS = -3; // �� ��������� ������� ��� ������� ����� �� �������.
      }
      break;
    }

    switch ( iFS ) // �������� ���������� ������� �����
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
        chTemp[i2] = ' '; // ���������� ������ �����
        i2++;
        bf1 = true; // ������ �� ������� ���������� ��������
      }
      break;
    }
    switch ( iFS ) // ����������� ��������������
    {
    case 1: // "if"
    case 2: // "/*"
    case 3: // "*/"
    case 4: // "->" // �� ����� ������� �� ����� �� �����
    case 5: // "++" // �� ����� ������� �� ����� �� �����
    case 6: // "--" // �� ����� ������� �� ����� �� �����
    case 7: // "()" // �� ����� ������� �� ����� �� �����
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
      bf1 = false; // ���������, ��� ����� ���� ������� ��������� ������� ������
      break;
    case -3: // ���� �� ���������� ������� ��� ���������� ���������.
      iIdentifik = 2;
      i2 += diaStrCpy( &chTemp[i2], find.chKontrol );
      i1 += find.pereskok;
      break;
    }
    switch ( iFS ) // �������� ���������� ������� �����
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
        bf1 = true; // ������ �� ������� ���������� ��������
        chTemp[i2] = ' '; // ���������� ������ �����
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
// ����������� ������ chFrom, �������� ��������� � ������ chTo
// ����� �������� ������� ������ ������� iSp ��������
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
// �������� ���� �������� skobkiCount, kavCount � koment;
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
// �������� ������ chStr �� iSdvig �������� �����
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
// ������� ���������� ������� �����
// ���������� ���������� �������� ��������
int StrDelSpace( char * chStr )
{
  char chTemp[255];
  int iFS;
  int i1, i2;
  bool bf1; // true - �� ���������� ���������� ������, false - ���������� ������
  int iLen;
  //int iRet;

  //iRet = 0;
  iLen = GetLengthStr( chStr );
  bf1 = true; // ���� ������ ���������� � ����������� ������� - ������ ���
  for ( i1 = 0, i2 = 0; i1 < iLen; i1++ )
  {
    // === �������� ������ ���������� ��������
    iFS = FindSimInStr( chStr[i1], " \t" );
    if ( iFS != -1 ) // �����, �.�. ������� ������ - ���������� ������
    {
      if ( bf1 == false )
      {
        chStr[i2] = chStr[i1];
        i2++;
      }
    }
    else if ( iFS == -1 ) // �� �����, �.�. ������� ������ - �� ����������
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
// ��������� ������ chSim � ������ chTo �� ������� Index
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
// ��������� ������ chSim � ������ chTo �� ������� Index
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
// �������� � ��������� ������� ���������� (����������)
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
    * iLast = GetLengthStr( chStr ) - 1; // �������� �� ������ ���� ���� ����������
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
// ������ chStrMulti ������� �� ��������� �������� ��������, ������� N ������
// �������� ������ "if==()" ����� ����������� ��� ������������ ��������
// ("if", "==", "()") � ������� N = 2 � �������� 1, 2 � 3 ��������������.
// ���� ���� �� ��������, ������ N (�������� chStrMulti) � ������ chStrBig,
// ������� � ������� iFirst, ���������� �������� iLast (�� 0 �� �����-1)
// ����������: -1 - �� ����� ���� ����������� ������� ���������, ����� �����
// ��������� (�� 1 �� ����� / N).
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
  char * chStrMulti; // ������ � ���������
  char * chStrBig; // ������, � ������� ������ �����
  int iFirst;
  int iLast;
  int N;
  int iLenMulti; // ����� ������ � ���������
  int iLenBig; // ����� ������ � �������, � ������� ������ ��� �������
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
  find->bOtdelLeft = false; // ���� �� ���� �������� �� ������� ������� ������ ���� �������� �����
  find->bOtdelRight = false; // ���� �� ���� �������� �� ������� ������ ������ ���� �������� ������

  chSimvol = find->chR;
  iLenMulti = GetLengthStr( chStrMulti );
  iLenBig = GetLengthStr( chStrBig ); //==\\ �������
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
    iLast = -1; // �������� �� ���������
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

    if ( find->RazLek == true ) // ������������ ����������� �������
    {
      I1 = i2 + 2;
      I2 = FindSimInStr( chSimvol, chStrMulti, I1 ) - 1;
      {
        if ( I2 < 0 )
        {
          I2 = iLenMulti - 1;
          if ( vyhod == 0 )
          {
            vyhod = 1; // ����� ����������� �������� ����
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
        //==\\iFirst = iTemp + 1; // ������
        if ( iTemp >= 0 )
        {
          iFirst = iTemp + 1; //==\\ �������
          find->Count++;
        }
      }
      while ( iTemp >= 0 );
    }
    if ( iTemp != -1 )
    {
      diaStrCpy( find->chKontrol, chStrSmall ); // ������� �������
      if ( iFirst == 0 ) // ������� ������� �������
      {
        find->bOtdelLeft = true; // ������� �������� ������� ������
      }
      else
      {
        iTemp = FindSimInStr( chStrBig[iFirst - 1], " \t);" );
        if ( iTemp >= 0 )
        {
          find->bOtdelLeft = true; // ������� �������� �������� �����
        }
      }
      if ( iFirst + find->pereskok + 1 == iLenBig ) // ������� ������� ������
      {
        find->bOtdelRight = true; // ������� �������� ������ ������
      }
      else if ( iFirst + find->pereskok + 1 < iLenBig )
      {
        iTemp = FindSimInStr( chStrBig[iFirst + find->pereskok + 1], " \t(" );
        if ( iTemp >= 0 )
        {
          find->bOtdelRight = true; // ������� �������� �������� ������
        }
      }
      else if ( iFirst + find->pereskok + 1 > iLenBig )
      {
        find->bOtdelRight = find->bOtdelRight; // ������!!! ����� �������� ���� �� ������
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
  find->pereskok = 0; // ������� �� �������

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
// ���� �������
// true - ��������� ������ ";", false - �� ��������� ��� �.�. �� ������
// "("������")"
bool Uchet( godnost_t * godnost_var )
{
  int DeltaSkoba;

  DeltaSkoba = godnost_var->SkobaOtkr - godnost_var->SkobaZakr;
  if ( ( DeltaSkoba % 2 ) == 1 )
  {
    // ������ �� ������������
    godnost_var->SkobaOtkr = 1;
    godnost_var->SkobaZakr = 0;
    return false;
  }
  else if ( ( DeltaSkoba % 2 ) == 0 )
  {
    // ������ �� ������������
    godnost_var->SkobaOtkr = 0;
    godnost_var->SkobaZakr = 0;
  }
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// ����������� ������� ���� ��������������� ������� ��� ���������� ���������
// true - ��������, false - ���
//     - ��������� ����� �� ������� ������ ������� "�������";
//     - ��������� ����� �� ������� ������ ���������� '�������';
//     - ��������� ����� �� ������� ������ ����������� /*�������*/;
//     - ��������� ����� �� ������� ����� ���������� //�������;
//     - ��������� ����� �� ������� ����� #�������.
bool Prigodnost( godnost_t * godnost_var )
{
  //     - ��������� ����� �� ������� ������ ������� "�������";
  int DeltaKom;
  if ( ( godnost_var->Kavychki % 2 ) == 1 )
  {
    godnost_var->Kavychki = 1; // ������ �� ������������
    godnost_var->Prichina = godnost_t::pr_Kavychki;
    return false;
  }
  else if ( ( godnost_var->Kavychki % 2 ) == 0 )
  {
    godnost_var->Kavychki = 0; // ������ �� ������������
  }
  //     - ��������� ����� �� ������� ������ ���������� '�������';
  if ( ( godnost_var->Appostr % 2 ) == 1 )
  {
    godnost_var->Appostr = 1; // ������ �� ������������
    godnost_var->Prichina = godnost_t::pr_Appostr;
    return false;
  }
  else if ( ( godnost_var->Appostr % 2 ) == 0 )
  {
    godnost_var->Appostr = 0; // ������ �� ������������
  }  
  //     - ��������� ����� �� ������� ������ ����������� /*�������*/
  DeltaKom = godnost_var->KomOtkr - godnost_var->KomZakr;
  if ( ( DeltaKom % 2 ) == 1 )
  {
    // ������ �� ������������
    godnost_var->KomOtkr = 1;
    godnost_var->KomZakr = 0;
    godnost_var->Prichina = godnost_t::pr_KomOtkr;
    return false;
  }
  else if ( ( DeltaKom % 2 ) == 0 )
  {
    // ������ �� ������������
    godnost_var->KomOtkr = 0;
    godnost_var->KomZakr = 0;
  }
  //     - ��������� ����� �� ������� ����� ���������� //�������
  if ( godnost_var->SlashTwo > 0 )
  {
    godnost_var->Prichina = godnost_t::pr_SlashTwo;
    return false;
  }
  //     - ��������� ����� �� ������� ����� #�������
  if ( godnost_var->Reshotka > 0 )
  {
    godnost_var->Prichina = godnost_t::pr_Reshotka;
    return false;
  }
  //     - ��������� ����� �� ������� ������ (������)
  godnost_var->Prichina = godnost_t::pr_NetPrichin;
  return true;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// ������ N ��������� ������ ��� ���������, ���� �� �� ��������������
// � �� ��������� ������ ������.
bool Proverka( int N, godnost_t * godnost_var ) // �������� �����������
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

    if ( godnost_var->Yes[i] != -1 ) // ���� � ������ ������ ������, � �������� �������� ��������������
    {
      if ( ( ( N + iNet ) >= godnost_var->Net[i] ) && ( ( N + iYes ) < godnost_var->Yes[i] ) )
      {
        return false;
      }
    }
    else // ��� ������� � �������� �������������� ��������
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
bool Proverka2( int N, godnost_t * godnost_var ) // �������� ����������� 2
{
  int i;
  int iNet;
  int iYes;  

  iNet = 2;
  iYes = 0;
  for ( i = 0; i < godnost_var->CountSkoba; i++ )
  {
    if ( godnost_var->SkobkaYes[i] != -1 ) // ���� � ������ ������ ������, � �������� �������� ��������������
    {
      if ( ( N >= ( godnost_var->SkobkaNet[i] - iNet ) ) && ( N < ( godnost_var->SkobkaYes[i] - iYes ) ) )
      {
        return false;
      }
    }
    else // ��� ������� � �������� �������������� ��������
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
// �� �� �����, ��� � "FindSmallInBig()", �� � ���������, �� �����������
// �.�. �������, ��������������� ���� �������, �������� �� ������ ����
// /* ������ ����������� */
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
  bool iRP; // ��������� ��������
  bool iRP2; // ��������� �������� 2
  do
  {
    iFS = FindSmallInBig( chLeksem, chStrBig, iFirst, iLast );
    iFirst = iFS + 1;
    iRP = Proverka( iFS /*+ iSumIndex*/, godnost_var );
    iRP2 = Proverka2( iFS /*+ iSumIndex*/, godnost_var );
    if ( iRP == true ) // ������� ��������� ��� �������� �������
    {
      if ( CmpNFirst( chLeksem, ";", 1 ) == 0 ) // ���� ��� ";"
      {
        if ( iRP2 == true ) // ��� �� � �������
        {
          Uspeh = true;
          break;
        }
      }
      else // ����� �������, ����� ";"
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
// ����� ������ �� ���������� ������ ��������� ��� ���������, ������� �
// ������� iFirst
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
        iDSim = i; // ������ ��������� ��������� ������
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
  godnost_var->Obmen[0] = iDSim; // ������ ������� ���������� �������
  godnost_var->Obmen[1] = iDSimNSp; // ������ ������� ���������� ������������� �������
  return bfDSimNSp;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// ���� ������ �������� �� iSdvig �������� �����, ���� ������ ���
// � ��������� ������, ���� godnost_t
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
    if ( godnost_var->Yes[i] != -1 ) // ���� � ������ ������ ������, � �������� �������� ��������������
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
    if ( godnost_var->SkobkaYes[i] != -1 ) // ���� � ������ ������ ������, � �������� �������� ��������������
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
// ���� � ������� Pos ����������� N ��������, ��� ���� ������.
// ������������ ��������: true - ������� ���������, false - �� �������
bool Korrektor2( int iPos, int Sdvig, godnost_t * godnost_var )
{
  int i;
  int iNet;
  if ( Proverka( iPos, godnost_var ) == false ) // �� ������ �����������
  { // (��� ������ ������)
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
// ������� ����������� �����
void DiaStrCpy( p_StrParam_t pVar )
{
  int i; // ������� �����
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
    pVar->bRezult = false; // �������
  }
  if ( iLenDest >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // �������
  }
  if ( pVar->iKolSimv < 0 )
  {
    pVar->bRezult = false; // �������  
  }
  if ( pVar->iDestFirst < 0 )
  {
    pVar->bRezult = false; // �������
  }
  if (  pVar->iDestFirst >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // �������  
  }
  if ( pVar->iSrcFirst < 0 )
  {
    pVar->bRezult = false; // �������
  }
  if (  pVar->iSrcFirst >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // �������
  }
  if ( pVar->iDestFirst + pVar->iKolSimv >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // �������
  }
  if ( pVar->iSrcFirst + pVar->iKolSimv >= StrParam_t::MaxLen )
  {
    pVar->bRezult = false; // �������
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
    // ����� ������� ������� chLeft, ��������������� ��������� ������
      // �������� ����� ����� ��� ����� ������
    iFirst = 0;
    iPosLeft = -1;
    while ( iFirst < iLenSrc )
    {
      iFindSimvol = FindSmallInBig( pVar->chLeft, pVar->chSrc, iFirst );
      if ( iFindSimvol != -1 )
      {
        iPosLeft = iFindSimvol;
        if ( pVar->bRevers == false ) // ������� ������� ����� ������ ���������
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
    // ����� ������� ������� chRight, ��������������� ��������� ������
      // �������� ����� ����� ��� ����� ������
    iFirst = 0;
    iPosRight = -1;
    while ( iFirst < iLenSrc )
    {
      iFindSimvol = FindSmallInBig( pVar->chRight, pVar->chSrc, iFirst );
      if ( iFindSimvol != -1 )
      {
        iPosRight = iFindSimvol;
        if ( pVar->bRevers == false ) // ������� ������� ����� ������ ���������
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
    // ���������, ������� �� �������
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

    // ���������, ���������� �� ����� ����� ����
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

  // ����������� �����, ����������� ����� ���������
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
// ������� ������ �����
void DiaFindReplace( p_StrParam_t pVar )
{
  char chTemp[StrParam_t::MaxLen];
  int i; // ������� �����
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
    if ( iFindSimvol != -1 ) // ���� ������� �������
    {
      // ����������� ����� ������ �� �������� chLeft
      pVar->iSrcFirst = iFirst;
      pVar->iDestFirst = iDestBegin;
      pVar->iKolSimv = iFindSimvol - iFirst;
      DiaStrCpy( pVar );

      // ����������� � ������ ���������� chRight
      iDestBegin += pVar->iKolSimv;
      pVar->chSrc = pVar->chRight;
      pVar->iSrcFirst = 0;
      pVar->iDestFirst = iDestBegin;
      pVar->iKolSimv = iLenRight;
      DiaStrCpy( pVar );

      // ������������� � ������ � ���������� ����� ������
      iDestBegin += pVar->iKolSimv;
      iFirst = iFindSimvol + iLenLeft;
      pVar->chSrc = pchSrc;
    }
    else
    {
      // ����������� ����� ������ �� � �����
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
// ��������� ������� � ���������� ����� � "�������"
char ToBigBukva( char Bukva )
{
  unsigned char uchBigBukva;
  unsigned char uchBukva;
  char BigBukva;

  //==\\uchBukva = static_cast<unsigned char>( Bukva );
  uchBukva = ( unsigned char )( Bukva );

  // ����������� �����
  uchBigBukva = uchBukva;

  // ������� ���� �� "�" �� "�", ��� ����� "�"
  if ( uchBukva >= 224 ) // && ( uchBukva <= 255 ) - ������ �������
  {
    uchBigBukva = uchBukva - 32;
  }
  // ������� ����� "�"
  if ( uchBukva == 184 )
  {
    uchBigBukva = 168;
  }
  // ������� ���� �� "a" �� "z"
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
// ��������� ������� � ���������� ����� � "���������"
char ToSmallBukva( char Bukva )
{
  unsigned char uchSmallBukva;
  unsigned char uchBukva;
  char SmallBukva;

  //==\\uchBukva = static_cast<unsigned char>( Bukva );
  uchBukva = ( unsigned char )( Bukva );

  // ����������� �����
  uchSmallBukva = uchBukva;

  // ������� ���� �� "�" �� "�", ��� ����� "�"
  if ( ( uchBukva >= 192 ) && ( uchBukva <= 223 ) )
  {
    uchSmallBukva = uchBukva + 32;
  }
  // ������� ����� "�"
  if ( uchBukva == 168 )
  {
    uchSmallBukva = 184;
  }
  // ������� ���� �� "A" �� "Z"
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
  sPath = ExtractFileDrive( chPath ); // "C:" ( ��� "D:" - ��������� ���� )
  sPath += asDirName; // asDirName = "\\VNIIA Ppograms\\Tabulyatziya" - ��������;
  if ( DirectoryExists( sPath.c_str() ) == false )
  {
    if ( ForceDirectories( sPath.c_str() ) == false )
    {
      // � ������� �� CreateDir ������� ForceDirectories ������ ���
      // ��������� � ���������� ������� ���������, ���� ���� �������������
      // �������� �� ����������
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
  sPath = ExtractFileDrive( chPath ); // "C:" ( ��� "D:" - ��������� ���� )
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
  sPath = ExtractFileDrive( chPath ); // "C:" ( ��� "D:" - ��������� ���� )
  return sPath;
}
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---

