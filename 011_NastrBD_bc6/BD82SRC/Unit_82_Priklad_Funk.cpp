//---------------------------------------------------------------------------
#pragma hdrstop
#include "Unit_82_Priklad_Funk.h"
//---------------------------------------------------------------------------
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
int ReadSchetaFromBuffer(char * buffer,int maxLength, int * Int_3_Arr)
{
  int sum = 0;
  bool bflag1; // ������� ��������� true - �����, false - ������ ������
  bool bflag2 = false; // ���������� ��������� (�� ����� ��� i = 0, �.�. false)
  int iflag = 0; // ���������� ����� � ������

  Int_3_Arr[1-1] = 0; // ������� ������� (���� 0 - ���� � ����� ��������� �� ���������)
  for ( int i = 0; i < maxLength; i++ )
  {
    if ( '0' <= buffer[i] && buffer[i] <= '9' )
    {
      sum *= 10;
      sum += (buffer[i] - '0');
      bflag1 = true;
    }
    else
    { // ������ ������ ������ (� �������� 0) �� �������� ������
      // �� �������� �������� � �� �������� �������� ���������
      if ( (i == 0) && (buffer[i] != ' ') && (buffer[i] != '\t') && buffer[i] != '-' )
      {
        return Int_3_Arr[1-1];
      }
      bflag1 = false;
    }
    // ===>>
    if ( (bflag2 == true) && (bflag1 == false) ) // ���� ���� �����
    {
      iflag++;
      if ( iflag == 1 )
      {
        Int_3_Arr[2-1] = sum; // ������������ ��� ��� ����
        Int_3_Arr[1-1] = 1; // ������� ������� (���� 1 - ���� ��������, ����� ��������� ���)        
        sum = 0;
      }
      else if ( iflag == 2 )
      {
        Int_3_Arr[3-1] = Int_3_Arr[2-1]; // ��� ����� ���������
        Int_3_Arr[2-1] = sum; // ��� ����
        Int_3_Arr[1-1] = 2; // ������� ������� (���� 2 - ���� � ����� ��������� ���������)
        return Int_3_Arr[1-1];
      }
    }
    // <<===
    if ( buffer[i] == '\0' ) // ����� ������
    {
      return Int_3_Arr[1-1];
    }
    if ( buffer[i] == '-' && buffer[i+1] == '1' ) // -1 �.�. ������ �����
    {
      Int_3_Arr[1-1] = 3;
      return Int_3_Arr[1-1];
    }
    bflag2 = bflag1;
  }
  return Int_3_Arr[1-1];
}
//---------------------------------------------------------------------------
void AprocSP(
    t_IN_mas X, // ������� ������ ���������
    t_IN_mas Y, // ������� ������ �������
    int NP, // ���������� ����� � �������
    int PD, // ������� ��������
    t_OUT_mas MK, // �������� ������ ������������� ��������
    int &DP, // ������� ��������
    float &EI // ����������� ������������
    )
{
  Aproc(X, Y, NP, 1, PD, 1, MK, DP, EI);
}
//---------------------------------------------------------------------------
void Aproc(
    t_IN_mas X, // ������� ������ ���������
    t_IN_mas Y, // ������� ������ �������
    int NP, // ���������� ����� � �������
    bool SW, // ������.��� ��� ��.�.
    int PD, // ������� ��������
    float SK, // ��������.������
    t_OUT_mas MK, // �������� ������ ������������� ��������
    int &DP, // ������� ��������
    float &EI // ����������� ������������
    )
{
  int h;
  int i, j, k, l, m, j1, k1;
  int n, n1;
  float e, e1;
  float r, f, u, s;
  dmas d;
  qmas a,c;
  omas b,g;
  bool boolean = true;

  h = NP; // ���������� �����
  n = 1;
  if ( SW != 0 )
  {
    n = PD; // ������� ��������
  }
  else
  {
    e1 = SK; // ���
  }
  do
  {
    n = n + 1;
    for ( j = 0; j <= 2 * n - 1; j++ )
    {
      if ( j < n + 1 )
      {
        b[j] = 0;
      }
      d[j] = 0;
    }
    for ( i = 1; i <= h; i++ )
    {
      r = Y[i];
      f = 1;
      for ( j = 1; j <= 2 * n - 1; j++ )
      {
        if ( j < n + 1 )
        {
          b[j] = b[j] + r;
          r = r * X[i];
        } // if ( j < n + 1)
        d[j] = d[j] + f;
        f = f * X[i];
      } // for j
    } // for i
    for ( i = 1; i <= n; i++ )
    {
      k = i;
      for ( j = 1; j <= n; j++ )
      {
        a[i][j] = d[k];
        k = k + 1;
      }
    }
    n1 = n - 1;
    for ( k = 1; k <= n1; k++ )
    {
      if ( fabs( a[k][k] ) >0 )
      {
        goto M230;
      }
      k1 = k + 1;
      for ( m = k1; m <= n; m++ )
      {
        if ( fabs( a[m][k] ) != 0 )
        {
          for ( l = 1; l <= n; l++ )
          {
            u = a[k][l];
            a[k][l] = a[m][l];
            a[m][l] = u;
          }
        }
      }
      u = b[k];
      b[k] = b[m];
      b[m] = u;
M230:
      g[k] = b[k] / a[k][k];
      k1 = k + 1;
      for ( i = k1; i <= n; i++ )
      {
        b[i] = b[i] - a[i][k] * g[k];
        for ( j1 = k; j1 <= n; j1++ )
        {
          j = n - j1 + k;
          c[k][j] = a[k][j] / a[k][k];
          a[i][j] = a[i][j] - a[i][k] * c[k][j];
        }
      }
    }
    m = n;
    MK[m] = b[m] / a[m][m];
M290:
    m = m - 1;
    s = 0;
    for ( l = m; l <= n1; l++ )
    {
      s = s + c[m][l+1] * MK[l+1];
    }
    MK[m] = g[m] - s;
    if( m > 1 )
    {
      goto M290;
    }
    e = 0;
    for ( i = 1; i <= h; i++ )
    {
      s = Y[i];
      r = 1;
      for ( j = 1; j <= n; j++ )
      {
        s = s - r * MK[j];
        r = r * X[i];
      }
      e = e + s * s;
    }
    e = sqrt( e / h );
    if ( SW == 1 )
    {
      boolean = false;
    }
    if ( e <= e1 )
    {
      boolean = false;
    }
  } while ( ( n < h ) && ( boolean ) ); // end do while

  DP = n - 1;
  EI = e;
}
//---------------------------------------------------------------------------    
