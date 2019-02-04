//---------------------------------------------------------------------------
#ifndef IViewSaveParamBd85H
#define IViewSaveParamBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
class IViewSaveParamBd85
{ // Интерфейс: без данных, все методы чисто виртуальные
public:
    virtual void SetVerPoText(const char * text) = 0;
    virtual void SetFileName(const char * fileName) = 0;
    virtual char * GetFileName() = 0;
    virtual void SetFileNameEnabled(bool enabled) = 0;    
    virtual void SetFileHeader(const char * fileHeader) = 0;
    virtual void SetFileHeaderEnabled(bool enabled) = 0;
    virtual void SetTimeText(const char * text) = 0;
    virtual void SetTimeEnabled(bool enabled) = 0;
    virtual void SetNumberText(const char * text) = 0;
    virtual void SetNumberEnabled(bool enabled) = 0;
    virtual void SetDelayText(const char * text) = 0;
    virtual void SetDelayEnabled(bool enabled) = 0;
    virtual void SetButtonOkText(const char * text) = 0;
    virtual void SetButtonCancelEnabled(bool enabled) = 0;
    virtual void SetErrorText(const char * text) = 0;
    virtual void SetSummTimeText(const char * text) = 0;
    virtual void SetCurrTimeText(const char * text) = 0;
    virtual void SetInfoText(const char * text) = 0;
    virtual void SetMiddleScalingText(const char * text) = 0;
    virtual void SetTotalScalingText(const char * text) = 0;
    virtual void WrapShow() = 0;
    virtual void Destroy() = 0;
    virtual ActionEvent<>& EventFormClose() = 0;
    virtual ActionEvent<const char*>& EventEditFileNameChange() = 0;
    virtual ActionEvent<const char*>& EventEditFileHeaderChange() = 0;
    virtual ActionEvent<const char*>& EventEditTimeChange() = 0;
    virtual ActionEvent<const char*>& EventEditNumberChange() = 0;
    virtual ActionEvent<const char*>& EventEditDelayChange() = 0;
    virtual ActionEvent<>& EventButtonOkClick() = 0;
    virtual ActionEvent<>& EventButtonCancelClick() = 0;
    virtual void WrapClose() = 0;
};
//---------------------------------------------------------------------------
#endif
