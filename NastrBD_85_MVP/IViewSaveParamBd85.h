//---------------------------------------------------------------------------
#ifndef IViewSaveParamBd85H
#define IViewSaveParamBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class IViewSaveParamBd85
{ // Интерфейс: без данных, все методы чисто виртуальные
public:
    virtual void SetVerPoText(const char * text) = 0;
    virtual void SetFileName(const char * fileName) = 0;
    virtual void SetFileNameEnabled(bool enabled) = 0;    
    virtual void SetFileHeader(const char * fileHeader) = 0;
    virtual void SetFileHeaderEnabled(bool enabled) = 0;
    virtual void SetTimeText(const char * text) = 0;
    virtual void SetTimeEnabled(bool enabled) = 0;
    virtual void SetNumberText(const char * text) = 0;
    virtual void SetNumberEnabled(bool enabled) = 0;
    virtual void SetDelayText(const char * text) = 0;
    virtual void SetDelayEnabled(bool enabled) = 0;
    virtual void WrapShow() = 0;
    virtual void Destroy() = 0;
    virtual ActionEvent<>& EventFormClose() = 0;
};
//---------------------------------------------------------------------------
#endif
