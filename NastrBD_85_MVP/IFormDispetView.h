//---------------------------------------------------------------------------
#ifndef IFormDispetViewH
#define IFormDispetViewH
//---------------------------------------------------------------------------
class IFormDispetView
{
public:
  virtual const char * GetProgrammVersion() = 0;
  virtual void WrapShow() = 0; 
};
//---------------------------------------------------------------------------
#endif
