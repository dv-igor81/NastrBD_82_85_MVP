//---------------------------------------------------------------------------
#ifndef Utilites_For_EditH
#define Utilites_For_EditH
//---------------------------------------------------------------------------
#include <StdCtrls.hpp> // TEdit
//---------------------------------------------------------------------------
// Дата создания класса: 24.01.2018
class EditHelper
{
public:
  EditHelper();
  ~EditHelper();
  static int ConvertToInt(
    TEdit * edit,
    int min,
    int max,
    int & errorCode);
  static int ConvertToInt(
    TEdit * edit,
    int min,
    int & errorCode);
protected:
private:
};
//---------------------------------------------------------------------------
#endif
