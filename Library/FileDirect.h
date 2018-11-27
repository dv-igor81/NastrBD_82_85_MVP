//---------------------------------------------------------------------------
#ifndef FileDirectH
#define FileDirectH
//---------------------------------------------------------------------------
class FileDirect
{
public:
    FileDirect();
    ~FileDirect();

    bool LoadFromFile( const char * fileName );

    bool SaveToFile( const char * fileName );

    bool DiaFileExists();

    void ReadInteger (
        int * retVal, // [OUT]
        const char * paramName, // [IN]
        int min, int def, int max, // [IN]
        bool * flagError); // [IN/OUT]

    void WriteInteger (
        int value, // [IN]
        const char * paramName); // [IN]

    void ReadByte (
        unsigned char * retVal, // [OUT]
        const char * paramName, // [IN]
        unsigned char min, unsigned char def, unsigned char max, // [IN]
        bool * flagError); // [IN/OUT]

    void WriteBool (
        bool value, // [IN]
        const char * paramName); // [IN]

    void ReadWord (
        unsigned short * retVal, // [OUT]
        const char * paramName, // [IN]
        unsigned short min, unsigned short def, unsigned short max, // [IN]
        bool * flagError); // [IN/OUT]

    void ReadBool (
        bool * retVal, // [OUT]
        const char * paramName, // [IN]
        bool def, // [IN]
        bool * flagError); // [IN/OUT]        

private:
    class impl;
    impl * pImpl;
    bool _fileIsReading;

    bool CheckFileName( const char * fileName );
};
//---------------------------------------------------------------------------
#endif
