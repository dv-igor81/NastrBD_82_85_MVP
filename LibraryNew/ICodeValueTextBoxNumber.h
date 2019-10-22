//---------------------------------------------------------------------------
#ifndef ICodeValueTextBoxNumberH
#define ICodeValueTextBoxNumberH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
class ICodeValueTextBoxNumber
{
public: // Чисто-виртуальные методы
    // Принять измененный текст, и позицию курсора поля "код"
    virtual void TextBoxCodeChange(const char * text, int pos) = 0;
    // Принять измененный текст, и позицию курсора поля "величина"
    virtual void TextBoxValueChange(const char * text, int pos) = 0;
    // Установить значение "код", и отобразить "код" и "величину" в связанных с объектом полях
    virtual void SetCode(int code) = 0;
    // Установить значение "кода", через значение "величина", и отобразить "код" и  "величину"
    virtual void SetValue(double value) = 0;
    // Получить отображаемое значение "код"
    virtual int GetCode() = 0;
    // Получить отображаемое значение "величина"
    virtual double GetValue() = 0;
    // Отобразить Value на основе Code и коэффициента
    virtual void RecountVelue() = 0;
    // Узнать, отображается-ли корректное число
    virtual bool IsNumber() = 0;
    // Освободить память, занимаемую экземпляром класса
    virtual void Destroy() = 0;
};
//---------------------------------------------------------------------------
ICodeValueTextBoxNumber * CreateTextBoxNumber( // Создать экземпляр класса: ITextBoxNumber
    int minCode, // Минимально-возможное значение "кода"
    int maxCode, // Максимально-возможное значение "кода"
    int defCode, // Значение "кода" по умолчанию
    int digits, // Нужное нам кол-во знаков, после запятой в поле "величина"
    double codeToValue, // Коэффициент пересчёта "кода" в "величину"
    ActionSelf<const char*> * setTextCode, // Функция установки текста поля "код"
    ActionSelf<const char*> * setTextValue, // Функция установки текста поля "величина"
    ActionSelf<int> * setCursorCode, // Функция установки курсора в поле "код"
    ActionSelf<int> * setCursorValue // Функция установки курсора в поле "величина"
);
//---------------------------------------------------------------------------
// Освободить память, занимаемую экземпляром класса: ITextBoxNumber
void DestroyTextBoxNumber( ICodeValueTextBoxNumber * number );
   //DestroyTextBoxNumber
//---------------------------------------------------------------------------
#endif
