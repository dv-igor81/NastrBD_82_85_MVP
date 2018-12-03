//---------------------------------------------------------------------------
#ifndef ModelSaveParamBd85H
#define ModelSaveParamBd85H
//---------------------------------------------------------------------------
#include "ViewModelSaveParamBd85.h"
#include "IAllProtokolS.h"
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
//class
class ModelSaveParamBd85
{
public:
    ModelSaveParamBd85(
        IAllProtokolS * allProtokol,
        ViewModelSaveParamBd85 * vmSaveParam,
        ConnectBdProt * connectBdProt );
        
    ~ModelSaveParamBd85();

    AnsiString FileName;
    AnsiString FileHeader;
    
    int m_nT; // Время измерения, (с)
    int m_nN; // Количество изменений
    int m_nZ; // Задержка (мин)

    bool StartStopWork();
    int GetSummTime();

private:
    IAllProtokolS * _allProtokol;
    ViewModelSaveParamBd85 * _vmSaveParam;
    ConnectBdProt * _connectBdProt;

    void CreateActions(); // Создать делегаты
    void DestroyActions(); // Освободить память, от делегатов

    bool _isWork;

    //===>> Делегаты
    ActionSelf<> * as_OprosIter;
    void OprosIter();
    ActionSelf<const char*> * as_DisplayErrors;
    void DisplayErrors(const char * text);
    //<<===

    void StartWork();
    void StopWork();
    void ClearParam();
    void Calculate();

    unsigned char _ssp;

    unsigned short _scaling; // Счёт за подинтервал (200 мс для 9-битного, 250 для ModBus)
    unsigned int _intervalQuantity; // Считаем количество подинтервалов, для интервала (секунды)
    unsigned int _intervalCounter;  // Счётчик подинтервалов (0,1,2,3 или 0,1,2,3,4) 
    unsigned int _scalingCounterTmp; // Для секундного счёта
    unsigned int _scalingCounter; // Для секундного счёта
    unsigned int _currTimeScaling; // Текущее время

};
//---------------------------------------------------------------------------
#endif
