/*
 * This is a part of PolyORB-HI-C distribution, a minimal
 * middleware written for generated code from AADL models.
 * You should use it with the Ocarina toolsuite.
 *
 * For more informations, please visit http://taste.tuxfamily.org/wiki
 *
 * Copyright (C) 2014 ESA & ISAE.
 */

#ifndef _INC_PER_UTIL_H
#define _INC_PER_UTIL_H


#ifdef  __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif


#ifndef WORD_SIZE
#define WORD_SIZE	8
#endif

typedef int asn1SccSint32;
typedef unsigned int asn1SccUint32;

typedef unsigned char byte;


#if WORD_SIZE==8
typedef long long asn1SccSint64;
typedef unsigned long long asn1SccUint64;
typedef asn1SccUint64 asn1SccUint;
typedef asn1SccSint64 asn1SccSint;
#else
typedef asn1SccUint32 asn1SccUint;
typedef asn1SccSint32 asn1SccSint;

#endif


typedef int flag;

typedef char NullType;

typedef struct {
	byte* buf;
	long count;
	long currentByte;
	/* Next available bit for writting. Possible vallues 0..7, 0 is most significant bit of current byte*/
	int currentBit; 
} BitStream;

typedef struct {
	byte* buf;
	long count;
	long currentByte;
	flag EncodeWhiteSpace;
} ByteStream;

typedef struct {
	int TokenID;
	char Value[100];
} Token;

typedef struct {
	char Name[50];
	char Value[100];
} XmlAttribute;

typedef struct {
	XmlAttribute attrs[20];
	int nCount;
} XmlAttributeArray;


#define ERR_INSUFFICIENT_DATA	101
#define ERR_INCORRECT_PER_STREAM	102
#define ERR_INVALID_CHOICE_ALTERNATIVE	103
#define ERR_INVALID_XML_FILE	200
#define ERR_INVALID_BER_FILE	201
#define ERR_BER_LENGTH_MISMATCH	202

/* Bit strean functions */

void BitStream_Init(BitStream* pBitStrm, unsigned char* buf, long count);
void BitStream_AttachBuffer(BitStream* pBitStrm, unsigned char* buf, long count);
void BitStream_AppendBit(BitStream* pBitStrm, flag v);
void BitStream_AppendBits(BitStream* pBitStrm, const byte* srcBuffer, int nBitsToWrite);
void BitStream_AppendByte(BitStream* pBitStrm, byte v, flag negate);
void BitStream_AppendByte0(BitStream* pBitStrm, byte v);


void ByteStream_Init(ByteStream* pStrm, byte* buf, long count); 
void ByteStream_AttachBuffer(ByteStream* pStrm, unsigned char* buf, long count);
asn1SccSint ByteStream_GetLength(ByteStream* pStrm);

asn1SccSint BitStream_GetLength(BitStream* pBitStrm);
void BitStream_AppendBitOne(BitStream* pBitStrm);
void BitStream_AppendBitZero(BitStream* pBitStrm);
flag BitStream_ReadBit(BitStream* pBitStrm, flag* v);
flag BitStream_ReadBits(BitStream* pBitStrm, byte* BuffToWrite, int nBitsToRead);
flag BitStream_ReadByte(BitStream* pBitStrm, byte* v);

/* Integer functions */


void BitStream_EncodeUnConstraintWholeNumber(BitStream* pBitStrm, asn1SccSint v);
void BitStream_EncodeSemiConstraintWholeNumber(BitStream* pBitStrm, asn1SccSint v, asn1SccSint min);
void BitStream_EncodeConstraintWholeNumber(BitStream* pBitStrm, asn1SccSint v, asn1SccSint min, asn1SccSint max);

flag BitStream_DecodeUnConstraintWholeNumber(BitStream* pBitStrm, asn1SccSint* v);
flag BitStream_DecodeSemiConstraintWholeNumber(BitStream* pBitStrm, asn1SccSint* v, asn1SccSint min);
flag BitStream_DecodeConstraintWholeNumber(BitStream* pBitStrm, asn1SccSint* v, asn1SccSint min, asn1SccSint max);






void BitStream_EncodeReal(BitStream* pBitStrm, double v);
flag BitStream_DecodeReal(BitStream* pBitStrm, double* v);



void CalculateMantissaAndExponent(double d, int* exp, asn1SccUint* mantissa);
double GetDoubleByMantissaAndExp(asn1SccUint mantissa, int exp);

int GetNumberOfBitsForNonNegativeInteger(asn1SccUint v);

int GetCharIndex(char ch, byte allowedCharSet[], int setLen);


/* 
                                                                                                                                                       
       db         ,ad8888ba,   888b      88           88888888888                                             88                                       
      d88b       d8"'    `"8b  8888b     88           88                                               ,d     ""                                       
     d8'`8b     d8'            88 `8b    88           88                                               88                                              
    d8'  `8b    88             88  `8b   88           88aaaaa  88       88  8b,dPPYba,    ,adPPYba,  MM88MMM  88   ,adPPYba,   8b,dPPYba,   ,adPPYba,  
   d8YaaaaY8b   88             88   `8b  88           88"""""  88       88  88P'   `"8a  a8"     ""    88     88  a8"     "8a  88P'   `"8a  I8[    ""  
  d8""""""""8b  Y8,            88    `8b 88           88       88       88  88       88  8b            88     88  8b       d8  88       88   `"Y8ba,   
 d8'        `8b  Y8a.    .a8P  88     `8888           88       "8a,   ,a88  88       88  "8a,   ,aa    88,    88  "8a,   ,a8"  88       88  aa    ]8I  
d8'          `8b  `"Y8888Y"'   88      `888           88        `"YbbdP'Y8  88       88   `"Ybbd8"'    "Y888  88   `"YbbdP"'   88       88  `"YbbdP"
*/

void Acn_AlignToNextByte(BitStream* pBitStrm);
void Acn_AlignToNextWord(BitStream* pBitStrm);
void Acn_AlignToNextDWord(BitStream* pBitStrm);

/*ACN Integer functions*/
void Acn_Enc_Int_PositiveInteger_ConstSize(BitStream* pBitStrm, asn1SccSint intVal, int encodedSizeInBits);
void Acn_Enc_Int_PositiveInteger_ConstSize_8(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_ConstSize_big_endian_16(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_ConstSize_big_endian_32(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_ConstSize_big_endian_64(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_ConstSize_little_endian_16(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_ConstSize_little_endian_32(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_ConstSize_little_endian_64(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_PositiveInteger_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint intVal);

void Acn_Enc_Int_TwosComplement_ConstSize(BitStream* pBitStrm, asn1SccSint intVal, int encodedSizeInBits);
void Acn_Enc_Int_TwosComplement_ConstSize_8(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_ConstSize_big_endian_16(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_ConstSize_big_endian_32(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_ConstSize_big_endian_64(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_ConstSize_little_endian_16(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_ConstSize_little_endian_32(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_ConstSize_little_endian_64(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_TwosComplement_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint intVal);

void Acn_Enc_Int_BCD_ConstSize(BitStream* pBitStrm, asn1SccSint intVal, int encodedSizeInNibbles);
void Acn_Enc_Int_BCD_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_BCD_VarSize_NullTerminated(BitStream* pBitStrm, asn1SccSint intVal); //encoding ends when 'F' is reached

void Acn_Enc_Int_ASCII_ConstSize(BitStream* pBitStrm, asn1SccSint intVal, int encodedSizeInBytes);
void Acn_Enc_Int_ASCII_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint intVal);
void Acn_Enc_Int_ASCII_VarSize_NullTerminated(BitStream* pBitStrm, asn1SccSint intVal); //encoding ends when 0x0 is reached



/*ACN Decode Integer functions*/
flag Acn_Dec_Int_PositiveInteger_ConstSize(BitStream* pBitStrm, asn1SccSint* pIntVal, int encodedSizeInBits);
flag Acn_Dec_Int_PositiveInteger_ConstSize_8(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_ConstSize_big_endian_16(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_ConstSize_big_endian_32(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_ConstSize_big_endian_64(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_ConstSize_little_endian_16(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_ConstSize_little_endian_32(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_ConstSize_little_endian_64(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_PositiveInteger_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint* pIntVal);

flag Acn_Dec_Int_TwosComplement_ConstSize(BitStream* pBitStrm, asn1SccSint* pIntVal, int encodedSizeInBits);
flag Acn_Dec_Int_TwosComplement_ConstSize_8(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_ConstSize_big_endian_16(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_ConstSize_big_endian_32(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_ConstSize_big_endian_64(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_ConstSize_little_endian_16(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_ConstSize_little_endian_32(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_ConstSize_little_endian_64(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_TwosComplement_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint* pIntVal);

flag Acn_Dec_Int_BCD_ConstSize(BitStream* pBitStrm, asn1SccSint* pIntVal, int encodedSizeInNibbles);
flag Acn_Dec_Int_BCD_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint* pIntVal);
//encoding ends when 'F' is reached
flag Acn_Dec_Int_BCD_VarSize_NullTerminated(BitStream* pBitStrm, asn1SccSint* pIntVal);

flag Acn_Dec_Int_ASCII_ConstSize(BitStream* pBitStrm, asn1SccSint* pIntVal, int encodedSizeInBytes);
flag Acn_Dec_Int_ASCII_VarSize_LengthEmbedded(BitStream* pBitStrm, asn1SccSint* pIntVal);
flag Acn_Dec_Int_ASCII_VarSize_NullTerminated(BitStream* pBitStrm, asn1SccSint* pIntVal);
//flag Acn_Dec_Int_ASCII_NullTerminated_FormattedInteger(BitStream* pBitStrm, const char* format, asn1SccSint* pIntVal);


/* Boolean Decode */

flag BitStream_ReadBitPattern(BitStream* pBitStrm, const byte* patternToRead, int nBitsToRead, flag* pBoolValue);

/*Real encoding functions*/
void Acn_Enc_Real_IEEE754_32_big_endian(BitStream* pBitStrm, double realValue);
void Acn_Enc_Real_IEEE754_64_big_endian(BitStream* pBitStrm, double realValue);
void Acn_Enc_Real_IEEE754_32_little_endian(BitStream* pBitStrm, double realValue);
void Acn_Enc_Real_IEEE754_64_little_endian(BitStream* pBitStrm, double realValue);

flag Acn_Dec_Real_IEEE754_32_big_endian(BitStream* pBitStrm, double* pRealValue);
flag Acn_Dec_Real_IEEE754_64_big_endian(BitStream* pBitStrm, double* pRealValue);
flag Acn_Dec_Real_IEEE754_32_little_endian(BitStream* pBitStrm, double* pRealValue);
flag Acn_Dec_Real_IEEE754_64_little_endian(BitStream* pBitStrm, double* pRealValue);


/* Length Determinant functions*/
void Acn_Enc_Length(BitStream* pBitStrm, asn1SccSint lengthValue, int lengthSizeInBits);

flag Acn_Dec_Length(BitStream* pBitStrm, asn1SccSint* pLengthValue, int lengthSizeInBits);



void BitStream_AppendNBitZero(BitStream* pBitStrm, int nbits);
void BitStream_EncodeNonNegativeInteger(BitStream* pBitStrm, asn1SccUint v);
void BitStream_AppendNBitOne(BitStream* pBitStrm, int nbits);
void BitStream_EncodeNonNegativeIntegerNeg(BitStream* pBitStrm, asn1SccUint v, flag negate);
flag BitStream_DecodeNonNegativeInteger(BitStream* pBitStrm, asn1SccUint* v, int nBits);
flag BitStream_ReadPartialByte(BitStream* pBitStrm, byte *v, byte nbits);
void BitStream_AppendPartialByte(BitStream* pBitStrm, byte v, byte nbits, flag negate);


void Xer_EncodeXmlHeader(ByteStream* pByteStrm, const char* xmlHeader);
flag Xer_EncodeComment(ByteStream* pByteStrm, const char* comment, int *pErrCode);

flag Xer_EncodeInteger(ByteStream* pByteStrm, const char* elementTag, asn1SccSint value, int *pErrCode, int level);
flag Xer_EncodeBoolean(ByteStream* pByteStrm, const char* elementTag, flag value, int *pErrCode, int level);
flag Xer_EncodeEnumerated(ByteStream* pByteStrm, const char* elementTag, const char* value, int *pErrCode, int level);
flag Xer_EncodeReal(ByteStream* pByteStrm, const char* elementTag, double value, int *pErrCode, int level);
flag Xer_EncodeString(ByteStream* pByteStrm, const char* elementTag, const char* value, int *pErrCode, int level);
flag Xer_EncodeOctetString(ByteStream* pByteStrm, const char* elementTag, const byte value[], int nCount, int *pErrCode, int level);
flag Xer_EncodeBitString(ByteStream* pByteStrm, const char* elementTag, const byte value[], int nCount, int *pErrCode, int level);



flag Xer_DecodeInteger(ByteStream* pByteStrm, const char* elementTag, asn1SccSint* value, int *pErrCode);
flag Xer_DecodeBoolean(ByteStream* pByteStrm, const char* elementTag, flag* value, int *pErrCode);
flag Xer_DecodeEnumerated(ByteStream* pByteStrm, const char* elementTag, char* value, int *pErrCode);
flag Xer_DecodeReal(ByteStream* pByteStrm, const char* elementTag, double* value, int *pErrCode);
flag Xer_DecodeString(ByteStream* pByteStrm, const char* elementTag, char* value, int *pErrCode);
flag Xer_DecodeOctetString(ByteStream* pByteStrm, const char* elementTag, byte value[], long* nCount, int *pErrCode);
flag Xer_DecodeBitString(ByteStream* pByteStrm, const char* elementTag, byte value[], long* nCount, int *pErrCode);
flag Xer_EncodeComplexElementStart(ByteStream* pByteStrm, const char* elementTag, XmlAttributeArray* pAttrs, int *pErrCode, int level);
flag Xer_EncodeComplexElementEnd(ByteStream* pByteStrm, const char* elementTag, int *pErrCode, int level);
flag Xer_DecodeComplexElementStart(ByteStream* pByteStrm, const char* elementTag, XmlAttributeArray* pAttrs, int *pErrCode);
flag Xer_DecodeComplexElementEnd(ByteStream* pByteStrm, const char* elementTag, int *pErrCode);
flag Xer_NextEndElementIs(ByteStream* pByteStrm, const char* elementTag);
flag Xer_NextStartElementIs(ByteStream* pByteStrm, const char* elementTag);
flag Xer_LA_NextElementTag(ByteStream* pByteStrm, char* elementTag);
flag LoadXmlFile(const char* fileName, ByteStream* pStrm, int* nBytesLoaded);




typedef asn1SccUint BerTag;




flag BerEncodeTag(ByteStream* pByteStrm, BerTag tag, int *pErrCode);
flag BerDecodeTag(ByteStream* pByteStrm, BerTag tag, int *pErrCode);

flag BerEncodeLengthStart(ByteStream* pByteStrm, int *pErrCode);
flag BerEncodeLengthEnd(ByteStream* pByteStrm, int *pErrCode);

flag BerDecodeLength(ByteStream* pByteStrm, int* value, int *pErrCode);
flag BerDecodeTwoZeroes(ByteStream* pByteStrm, int *pErrCode);


flag BerEncodeInteger(ByteStream* pByteStrm, BerTag tag, asn1SccSint value, int *pErrCode);
flag BerDecodeInteger(ByteStream* pByteStrm, BerTag tag, asn1SccSint *value, int *pErrCode);

flag BerEncodeBoolean(ByteStream* pByteStrm, BerTag tag, flag value, int *pErrCode);
flag BerDecodeBoolean(ByteStream* pByteStrm, BerTag tag, flag *value, int *pErrCode);

flag BerEncodeReal(ByteStream* pByteStrm, BerTag tag, double value, int *pErrCode);
flag BerDecodeReal(ByteStream* pByteStrm, BerTag tag, double *value, int *pErrCode);

flag BerEncodeIA5String(ByteStream* pByteStrm, BerTag tag, const char* value, int length, int *pErrCode);
flag BerDecodeIA5String(ByteStream* pByteStrm, BerTag tag, char* value, int maxLength, int *pErrCode);

flag BerEncodeNull(ByteStream* pByteStrm, BerTag tag, int *pErrCode);
flag BerDecodeNull(ByteStream* pByteStrm, BerTag tag, int *pErrCode);

flag BerEncodeBitString(ByteStream* pByteStrm, BerTag tag, const byte* value, int bitCount, int *pErrCode);
flag BerDecodeBitString(ByteStream* pByteStrm, BerTag tag, byte* value, int *bitCount, int maxBitCount, int *pErrCode);

flag BerEncodeOctetString(ByteStream* pByteStrm, BerTag tag, const byte* value, int octCount, int *pErrCode);
flag BerDecodeOctetString(ByteStream* pByteStrm, BerTag tag, byte* value, int *octCount, int maxOctCount, int *pErrCode);


flag NextTagMatches(ByteStream* pByteStrm, BerTag tag);

int GetStrmPos(ByteStream* pByteStrm);
flag LA_Next_Two_Bytes_00(ByteStream* pByteStrm);




#define CHECK_BIT_STREAM(pBitStrm)	assert((pBitStrm)->currentByte*8+(pBitStrm)->currentBit<=(pBitStrm)->count*8)

#ifdef _MSC_VER
#pragma warning( disable : 4127)
#endif

#define ASSERT_OR_RETURN_FALSE(_Expression) do { assert(_Expression); if (!(_Expression)) return FALSE;} while(0)

#ifdef  __cplusplus
}
#endif


#endif
