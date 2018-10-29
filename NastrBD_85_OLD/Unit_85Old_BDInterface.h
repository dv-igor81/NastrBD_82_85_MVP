//---------------------------------------------------------------------------
#ifndef BDInterfaceH
#define BDInterfaceH
//---------------------------------------------------------------------------
int OpenRS(int n); // установить соединение с БД
int CloseRS();     // закрыть порт
int SetIndAdr(unsigned char Adr);      // установить индивидуальный адрес БД
int GetIndAdr(unsigned char *Adr);     // считать индивидуальный адрес БД
int SetGrpAdr(unsigned char Adr);      // установить групповой адрес БД
int GetGrpAdr(unsigned char *Adr);     // считать групповой адрес БД
int GetTemp(unsigned int *Temp);       // считать текущую температуру процессора БД
int GetUhi(unsigned int *Temp);        // считать значение высокого напряжения
int SetUhi(unsigned int Temp);        // установить значение высокого напряжения
int ARCHCon(unsigned char State);      // управление системой АРЧ 1-включить, 0-отключить
int SpectrCon(unsigned char State);    // управление снятием спектра импульса 1-включить, 0-отключить
int GetLEDAmp(unsigned int *Ampl);      // получить амплитуду импульса от светодиода
int SetLEDAmp(unsigned int Ampl);       // задать амплитуду импульса светодиода
int IncFreqLEDImp(unsigned char State); // увеличение частоты импульсов от светодиода
int GetCountImp(unsigned int *CImp);   // получить счет за 0,2 сек
int GetSpectr(unsigned int *Spectr);   // получить спектр импульса
int GetPSWBD(unsigned char *PSWBD);    // получить слово состояния программы БД
int WriteFlash(unsigned int Adr,unsigned long Data);  // запись байта данных в FLASH/EE DATA MEMORY процессора
int ReadFlash(unsigned int Adr, unsigned long *Data); // считывание байта данных из FLASH/EE DATA MEMORY процессора
int WriteRAM(unsigned char Adr, unsigned char Data);  // запись байта данных во внутреннюю память данных процессора
                                                      // (256 байт) процессора
int ReadRAM(unsigned char Adr,unsigned char *Data);        // чтение байта данных из внутренней памяти данных процессора (256 байт) процессора
int GetDNU(unsigned int *DNU);         // измерить напряжение на выходе дискриминатора нижнего уровня
int GetDVU(unsigned int *DVU);         // измерить напряжение на выходе дискриминатора верхнего уровня
int SetDNU(unsigned int DNU);          // установить порог дискриминации нижнего уровня
int SetDVU(unsigned int DVU);          // установить порог дискриминации верхнего уровня
int GetSSP(unsigned char *SSP);        // получить слово состояния программы БД
int SetTimeInterval(unsigned char TimeInt); // установить время счета БД при TimeInt=255(установлен в БД по умолчанию)
                                            // БД не вырабатывает собственные временные интервалы счета (только по UART)
                                            // при TimeInt отличной от 255 БД начинает самостоятельно вырабатывать
                                            // интервалы счета (время считается так TimeInt*25=ХХХ мсек)
int GetSIM3(unsigned int *SIM3);//получение значения периода ШИМ
int GetVersia(unsigned char *Versia);
int SetARH(unsigned char KodRS);//1-обратная связь включена    0-нет
int GetARH(unsigned char *KodRS);

int GetSIM4(unsigned int *SIM4);//получение длительности ШИМ
int GetTimeInterval(unsigned char *TimeInt);

int SetSIM3(unsigned int PWMzn);
int SetSIM4(unsigned int PWMzn);
#endif
