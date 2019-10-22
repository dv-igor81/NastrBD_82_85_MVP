//---------------------------------------------------------------------------
#ifndef FileDirectExtensiveH
#define FileDirectExtensiveH
//---------------------------------------------------------------------------
class FileDirectExtensive
{
public:
    FileDirectExtensive();
    ~FileDirectExtensive();

    bool LoadFromFile( const char * fileName );

    bool SaveToFile( const char * fileName );

    bool DiaFileExists();

    void ReadString (
        char *& retVal, // [OUT]
        const char * paramName, // [IN]
        const char * def, // [IN]
        bool * flagError );

    void WriteString (
        char * value, // [IN]
        const char * paramName); // [IN]

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
    char _chString[255];    

    bool CheckFileName( const char * fileName );
    void ReadStringHelper( // retVal := chText
        char *& retVal, // [OUT]
        const char * chText ); // [IN]

};
//---------------------------------------------------------------------------
#endif
