/* auteur : F.J. Hurkmans
 * datum  : November 4th 2013
 * code   : Ansi C
 * versie : 1
 */

#include "bmp.h"
#include "stegano.h"
#include "unity.h"

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "resource_detector.h"

// I rather dislike keeping line numbers updated, so I made my own macro to
// ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)


void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
    const char* FilenamesToDeleteAfterTest[] = {
        "demux_ImageCitroen2Cv.bmp",
        "demux_TextFontys.txt",
        "demux_ImageRedFerrari_0.bmp",
        "demux_ImageRedFerrari_1.bmp",
        "demux_ImageRedFerrari_4.bmp",
        "demux_ImageRedFerrari_7.bmp",
        "demux_ImageRedFerrari_8.bmp",
        "demux_ImageTrabant_0.bmp",
        "demux_ImageTrabant_1.bmp",
        "demux_ImageTrabant_4.bmp",
        "demux_ImageTrabant_7.bmp",
        "demux_ImageTrabant_8.bmp",
        "mux_ImageCitroen2Cv.bmp_TextFontys.txt.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_0.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_1.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_2.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_3.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_4.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_5.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_6.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_7.bmp",
        "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_8.bmp"
    };

    for (size_t i = 0; i < (sizeof(FilenamesToDeleteAfterTest) /
                         sizeof(FilenamesToDeleteAfterTest[0]));
         i++)
    {
        remove(FilenamesToDeleteAfterTest[i]);
    }
}

static int GetFileSize(FILE* FilePtr)
{
    int CurrPos = ftell(FilePtr);
    int EndPos = 0;
    TEST_ASSERT_EQUAL(0, fseek(FilePtr, 0L, SEEK_END));
    EndPos = ftell(FilePtr);
    TEST_ASSERT_EQUAL(0, fseek(FilePtr, CurrPos, SEEK_SET));
    return EndPos;
}

static void Assert2FilesEqual(char* File1, char* File2)
{
    const size_t BufferSize = 4096;
    FILE* File1Ptr = fopen(File1, "rb");
    TEST_ASSERT_NOT_NULL(File1Ptr);
    FILE* File2Ptr = fopen(File2, "rb");
    TEST_ASSERT_NOT_NULL(File2Ptr);

    int File1Size = GetFileSize(File1Ptr);
    int File2Size = GetFileSize(File2Ptr);

    TEST_ASSERT_EQUAL(File1Size, File2Size);

    char* File1Buffer = malloc(BufferSize);
    TEST_ASSERT_NOT_NULL(File1Buffer);
    char* File2Buffer = malloc(BufferSize);
    TEST_ASSERT_NOT_NULL(File2Buffer);

    size_t File1Read = 0;
    size_t File2Read = 0;

    do
    {
        File1Read = fread(File1Buffer, 1, BufferSize, File1Ptr);
        File2Read = fread(File2Buffer, 1, BufferSize, File2Ptr);
        TEST_ASSERT_EQUAL(File1Read, File2Read);
        if (File1Read > 0)
        {
            TEST_ASSERT_EQUAL_INT8_ARRAY(File1Buffer, File2Buffer, File1Read);
        }
    } while ((File1Read > 0) && (File2Read > 0));

    free(File1Buffer);
    free(File2Buffer);

    fclose(File1Ptr);
    fclose(File2Ptr);
}

static void
CheckBmp(char* Filename, const uint32_t* CorrectHeader,
         const uint8_t* FirstPixels, const uint8_t* LastPixels)
{
    const int NrHeaderInts = 13;
    const int NrPixels = 8;
    const int BytesPerPixel = 3;
    char message[300];
    sprintf(message, "CheckBmp on filename: %s", Filename);
    FILE* FilePtr = NULL;
    uint32_t Header[NrHeaderInts];
    uint8_t PixelData[NrPixels * BytesPerPixel];
    int Result = 0;

    FilePtr = fopen(Filename, "rb");
    TEST_ASSERT_NOT_NULL(FilePtr);


    fseek(FilePtr, 0x02, SEEK_SET);// skip 'BM' magic
    TEST_ASSERT_EQUAL_MESSAGE(
                NrHeaderInts,
                fread(&Header, sizeof(Header[0]), NrHeaderInts, FilePtr),
                message);
    TEST_ASSERT_EQUAL_HEX32_ARRAY_MESSAGE(
                CorrectHeader, Header, NrHeaderInts, message);

    fseek(FilePtr,
          sizeof(BMP_MAGIC_t) + sizeof(BMP_FILE_t) + sizeof(BMP_INFO_t),
          SEEK_SET);
    Result = fread(PixelData, sizeof(PixelData[0]), NrPixels * BytesPerPixel,
                      FilePtr);
    TEST_ASSERT_EQUAL_MESSAGE(NrPixels * BytesPerPixel, Result, message);
    TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
                FirstPixels, PixelData, NrPixels * BytesPerPixel, message);

    fseek(FilePtr, -1 * NrPixels * BytesPerPixel, SEEK_END);
    Result = fread(PixelData, sizeof(PixelData[0]), NrPixels * BytesPerPixel,
                      FilePtr);
    TEST_ASSERT_EQUAL_MESSAGE(NrPixels * BytesPerPixel, Result, message);
    TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
                LastPixels, PixelData, NrPixels * BytesPerPixel, message);

    fclose(FilePtr);
}


static void test_GetSubstring(void)
{
    const uint8_t TestData[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08,
        0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08,
        0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
        0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
        0x40, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08,
        0x10, 0x20, 0x40, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x03, 0x06,
        0x0c, 0x18, 0x30, 0x60, 0xc0, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x02,
        0x04, 0x08, 0x10, 0x20, 0x40, 0x05, 0x0a, 0x14, 0x28, 0x50, 0xa0, 0x02,
        0x04, 0x08, 0x10, 0x20, 0x40, 0x05, 0x0a, 0x14, 0x28, 0x50, 0xa0, 0x06,
        0x0c, 0x18, 0x30, 0x60, 0xc0, 0x04, 0x08, 0x10, 0x20, 0x40, 0x0a, 0x14,
        0x28, 0x50, 0xa0, 0x05, 0x0a, 0x14, 0x28, 0x50, 0x0a, 0x14, 0x28, 0x50,
        0xa0, 0x0d, 0x1a, 0x34, 0x68, 0xd0, 0x14, 0x28, 0x50, 0xa0, 0x0a, 0x14,
        0x28, 0x50, 0x15, 0x2a, 0x54, 0xa8, 0x1a, 0x34, 0x68, 0xd0, 0x14, 0x28,
        0x50, 0x2a, 0x54, 0xa8, 0x35, 0x6a, 0xd4, 0x54, 0xa8, 0x6a, 0xd4
    };
    uint8_t Src = 0xd4;
    uint8_t SrcPos;
    uint8_t NrBits;
    uint8_t DestPos;
    int TestDataIndex = 0;

    for (int j = 1; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int k = 0; k < 8; k++)
            {
                if ((i + j <= 8) && (k + j <= 8))
                {
                    SrcPos = i;
                    NrBits = j;
                    DestPos = k;
                    char message[80];
                    sprintf(message, "SrcPos: %i, NrBits: %i, DestPos: %i",
                                SrcPos, NrBits, DestPos);
                    TEST_ASSERT_EQUAL_HEX8_MESSAGE(
                                TestData[TestDataIndex++],
                                SteganoGetSubstring(
                                            Src, SrcPos, NrBits, DestPos),
                                message);
                }
            }
        }
    }
}

static void test_MultiplexTwoImages(void)
{
    const char* File1 = "ImageTrabant.bmp";
    const char* File2 = "ImageRedFerrari.bmp";
    SteganoMultiplex(File1, File2);

    uint32_t CorrectHeader0[] = { 0xc8a36, 0x1ac0280, 0x36, 0x28,    0x280,
                                  0x1ac,   0x180001,  0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,       0x0 };
    uint8_t CorrectFirstBytes0[] = { 0x58, 0x5d, 0x5e, 0x4e, 0x53, 0x54,
                                     0x4e, 0x53, 0x54, 0x58, 0x5d, 0x5e,
                                     0x57, 0x5c, 0x5d, 0x4d, 0x52, 0x53,
                                     0x4d, 0x52, 0x55, 0x57, 0x5c, 0x5f };
    uint8_t CorrectLastBytes0[] = { 0x11, 0x58, 0x48, 0x11, 0x5a, 0x4a,
                                    0x13, 0x5b, 0x4e, 0x1b, 0x63, 0x56,
                                    0x22, 0x67, 0x5c, 0x17, 0x5c, 0x51,
                                    0x11, 0x54, 0x4b, 0x19, 0x5c, 0x53 };
    CheckBmp("mux_ImageTrabant.bmp_ImageRedFerrari.bmp_0.bmp", CorrectHeader0,
             CorrectFirstBytes0, CorrectLastBytes0);
    uint32_t CorrectHeader1[] = { 0xc8a36, 0x1ac0280, 0x36, 0x28,    0x280,
                                  0x1ac,   0x180001,  0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,       0x1 };
    uint8_t CorrectFirstBytes1[] = { 0x59, 0x5d, 0x5f, 0x4f, 0x53, 0x55,
                                     0x4f, 0x53, 0x55, 0x59, 0x5d, 0x5f,
                                     0x57, 0x5d, 0x5d, 0x4d, 0x53, 0x53,
                                     0x4d, 0x53, 0x55, 0x57, 0x5d, 0x5f };
    uint8_t CorrectLastBytes1[] = { 0x10, 0x58, 0x48, 0x10, 0x5a, 0x4a,
                                    0x12, 0x5a, 0x4e, 0x1a, 0x62, 0x56,
                                    0x22, 0x66, 0x5c, 0x16, 0x5c, 0x50,
                                    0x10, 0x54, 0x4a, 0x18, 0x5c, 0x52 };
    CheckBmp("mux_ImageTrabant.bmp_ImageRedFerrari.bmp_1.bmp", CorrectHeader1,
             CorrectFirstBytes1, CorrectLastBytes1);
    uint32_t CorrectHeader4[] = { 0xc8a36, 0x1ac0280, 0x36, 0x28,    0x280,
                                  0x1ac,   0x180001,  0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,       0x4 };
    uint8_t CorrectFirstBytes4[] = { 0x5d, 0x5d, 0x5d, 0x4d, 0x5d, 0x5d,
                                     0x4d, 0x5d, 0x5d, 0x5d, 0x5d, 0x5d,
                                     0x5d, 0x5d, 0x5d, 0x4d, 0x5d, 0x5d,
                                     0x4d, 0x5d, 0x5d, 0x5d, 0x5d, 0x5d };
    uint8_t CorrectLastBytes4[] = { 0x10, 0x50, 0x40, 0x10, 0x50, 0x40,
                                    0x10, 0x50, 0x40, 0x10, 0x60, 0x50,
                                    0x20, 0x60, 0x50, 0x10, 0x50, 0x50,
                                    0x10, 0x50, 0x40, 0x10, 0x50, 0x50 };
    CheckBmp("mux_ImageTrabant.bmp_ImageRedFerrari.bmp_4.bmp", CorrectHeader4,
             CorrectFirstBytes4, CorrectLastBytes4);
    uint32_t CorrectHeader7[] = { 0xc8a36, 0x1ac0280, 0x36, 0x28,    0x280,
                                  0x1ac,   0x180001,  0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,       0x7 };
    uint8_t CorrectFirstBytes7[] = { 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
                                     0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
                                     0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
                                     0x69, 0x69, 0x69, 0x69, 0x69, 0x69 };
    uint8_t CorrectLastBytes7[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CheckBmp("mux_ImageTrabant.bmp_ImageRedFerrari.bmp_7.bmp", CorrectHeader7,
             CorrectFirstBytes7, CorrectLastBytes7);
    uint32_t CorrectHeader8[] = { 0xc8a36, 0x1ac0280, 0x36, 0x28,    0x280,
                                  0x1ac,   0x180001,  0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,       0x8 };
    uint8_t CorrectFirstBytes8[] = { 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3,
                                     0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3,
                                     0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3,
                                     0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3 };
    uint8_t CorrectLastBytes8[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CheckBmp("mux_ImageTrabant.bmp_ImageRedFerrari.bmp_8.bmp", CorrectHeader8,
             CorrectFirstBytes8, CorrectLastBytes8);
}

static void test_DemultiplexTwoImages(void)
{
    const char* File1 = "ImageTrabant.bmp";
    const char* File2 = "ImageRedFerrari.bmp";
    SteganoMultiplex(File1, File2);

    SteganoDemultiplex(
                "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_0.bmp",
                "demux_ImageTrabant_0.bmp", "demux_ImageRedFerrari_0.bmp");
    SteganoDemultiplex(
                "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_1.bmp",
                "demux_ImageTrabant_1.bmp", "demux_ImageRedFerrari_1.bmp");
    SteganoDemultiplex(
                "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_4.bmp",
                "demux_ImageTrabant_4.bmp", "demux_ImageRedFerrari_4.bmp");
    SteganoDemultiplex(
                "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_7.bmp",
                "demux_ImageTrabant_7.bmp", "demux_ImageRedFerrari_7.bmp");
    SteganoDemultiplex(
                "mux_ImageTrabant.bmp_ImageRedFerrari.bmp_8.bmp",
                "demux_ImageTrabant_8.bmp", "demux_ImageRedFerrari_8.bmp");
    uint32_t CorrectHeader0[] = { 0xc8a36, 0x0,      0x36, 0x28,    0x280,
                                  0x1ac,   0x180001, 0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,      0x0 };
    uint8_t CorrectFirstBytes0[] = { 0x50, 0x50, 0x50, 0x40, 0x50, 0x50,
                                     0x40, 0x50, 0x50, 0x50, 0x50, 0x50,
                                     0x50, 0x50, 0x50, 0x40, 0x50, 0x50,
                                     0x40, 0x50, 0x50, 0x50, 0x50, 0x50 };
    uint8_t CorrectLastBytes0[] = { 0x10, 0x50, 0x40, 0x10, 0x50, 0x40,
                                    0x10, 0x50, 0x40, 0x10, 0x60, 0x50,
                                    0x20, 0x60, 0x50, 0x10, 0x50, 0x50,
                                    0x10, 0x50, 0x40, 0x10, 0x50, 0x50 };
    CheckBmp("demux_ImageTrabant_4.bmp", CorrectHeader0, CorrectFirstBytes0,
             CorrectLastBytes0);
    uint32_t CorrectHeader1[] = { 0xc8a36, 0x0,      0x36, 0x28,    0x280,
                                  0x1ac,   0x180001, 0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,      0x0 };
    uint8_t CorrectFirstBytes1[] = { 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2,
                                     0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2,
                                     0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2,
                                     0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2 };
    uint8_t CorrectLastBytes1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CheckBmp("demux_ImageRedFerrari_7.bmp", CorrectHeader1, CorrectFirstBytes1,
             CorrectLastBytes1);
    uint32_t CorrectHeader2[] = { 0xc8a36, 0x0,      0x36, 0x28,    0x280,
                                  0x1ac,   0x180001, 0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,      0x0 };
    uint8_t CorrectFirstBytes2[] = { 0x58, 0x5c, 0x5e, 0x4e, 0x52, 0x54,
                                     0x4e, 0x52, 0x54, 0x58, 0x5c, 0x5e,
                                     0x56, 0x5c, 0x5c, 0x4c, 0x52, 0x52,
                                     0x4c, 0x52, 0x54, 0x56, 0x5c, 0x5e };
    uint8_t CorrectLastBytes2[] = { 0x10, 0x58, 0x48, 0x10, 0x5a, 0x4a,
                                    0x12, 0x5a, 0x4e, 0x1a, 0x62, 0x56,
                                    0x22, 0x66, 0x5c, 0x16, 0x5c, 0x50,
                                    0x10, 0x54, 0x4a, 0x18, 0x5c, 0x52 };
    CheckBmp("demux_ImageTrabant_1.bmp", CorrectHeader2, CorrectFirstBytes2,
             CorrectLastBytes2);
    uint32_t CorrectHeader3[] = { 0xc8a36, 0x0,      0x36, 0x28,    0x280,
                                  0x1ac,   0x180001, 0x0,  0xc8a00, 0xec4,
                                  0xec4,   0x0,      0x0 };
    uint8_t CorrectFirstBytes3[] = { 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
                                     0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
                                     0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
                                     0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0 };
    uint8_t CorrectLastBytes3[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CheckBmp("demux_ImageRedFerrari_4.bmp", CorrectHeader3, CorrectFirstBytes3,
             CorrectLastBytes3);

    Assert2FilesEqual("ImageTrabant.bmp", "demux_ImageTrabant_0.bmp");
    Assert2FilesEqual("ImageRedFerrari.bmp", "demux_ImageRedFerrari_8.bmp");
}

static void test_MultiplexTextAndImage(void)
{
    const char* File1 = "ImageCitroen2Cv.bmp";
    const char* File2 = "TextFontys.txt";
    SteganoMultiplexText(File1, File2);

    uint32_t CorrectHeader0[] = { 0x56616, 0x115d,   0x36, 0x28,    0x1b8,
                                  0x10c,   0x180001, 0x0,  0x565e0, 0x0,
                                  0x0,     0x0,      0x0 };
    uint8_t CorrectFirstBytes0[] = { 0x74, 0x86, 0x8b, 0x98, 0xab, 0xae,
                                     0x61, 0x74, 0x76, 0x7c, 0x91, 0x8e,
                                     0x91, 0xa4, 0xa3, 0x88, 0x9e, 0x9a,
                                     0x93, 0xa8, 0xa3, 0x8c, 0xa3, 0x9c };
    uint8_t CorrectLastBytes0[] = { 0x3e, 0x5d, 0x36, 0x4a, 0x69, 0x42,
                                    0x39, 0x58, 0x33, 0x37, 0x56, 0x31,
                                    0x32, 0x50, 0x2d, 0x32, 0x50, 0x2d,
                                    0x30, 0x4e, 0x2b, 0x36, 0x54, 0x31 };
    CheckBmp("mux_ImageCitroen2Cv.bmp_TextFontys.txt.bmp", CorrectHeader0,
             CorrectFirstBytes0, CorrectLastBytes0);
}

static void test_DemultiplexTextAndImage(void)
{
    const char* File1 = "ImageCitroen2Cv.bmp";
    const char* File2 = "TextFontys.txt";
    SteganoMultiplexText(File1, File2);

    SteganoDemultiplexText(
                "mux_ImageCitroen2Cv.bmp_TextFontys.txt.bmp",
                "demux_ImageCitroen2Cv.bmp", "demux_TextFontys.txt");
    uint32_t CorrectHeader0[] = { 0x56616, 0x0,      0x36, 0x28,    0x1b8,
                                  0x10c,   0x180001, 0x0,  0x565e0, 0x0,
                                  0x0,     0x0,      0x0 };
    uint8_t CorrectFirstBytes0[] = { 0x74, 0x86, 0x8a, 0x98, 0xaa, 0xae,
                                     0x60, 0x74, 0x76, 0x7c, 0x90, 0x8e,
                                     0x90, 0xa4, 0xa2, 0x88, 0x9e, 0x9a,
                                     0x92, 0xa8, 0xa2, 0x8c, 0xa2, 0x9c };
    uint8_t CorrectLastBytes0[] = { 0x3e, 0x5d, 0x36, 0x4a, 0x69, 0x42,
                                    0x39, 0x58, 0x33, 0x37, 0x56, 0x31,
                                    0x32, 0x50, 0x2d, 0x32, 0x50, 0x2d,
                                    0x30, 0x4e, 0x2b, 0x36, 0x54, 0x31 };
    CheckBmp("demux_ImageCitroen2Cv.bmp", CorrectHeader0, CorrectFirstBytes0,
             CorrectLastBytes0);
    uint32_t CorrectHeader1[] = { 0x6945202a, 0x6f68646e, 0x206e6576,
                                  0x0d2a2a2a, 0x440a0d0a, 0x65542065,
                                  0x696e6863, 0x65686373, 0x696e5520,
                                  0x73726576, 0x69657469, 0x69452074,
                                  0x6f68646e };
    uint8_t CorrectFirstBytes1[] = { 0x76, 0x65, 0x6e, 0x20, 0x65, 0x6e,
                                     0x20, 0x46, 0x6f, 0x6e, 0x74, 0x79,
                                     0x73, 0x20, 0x48, 0x6f, 0x67, 0x65,
                                     0x73, 0x63, 0x68, 0x6f, 0x6c, 0x65 };
    uint8_t CorrectLastBytes1[] = { 0x6e, 0x74, 0x79, 0x73, 0x2e, 0x6e,
                                    0x6c, 0x0d, 0x0a, 0x0d, 0x0a, 0x2d,
                                    0x2d, 0x20, 0x65, 0x69, 0x6e, 0x64,
                                    0x65, 0x20, 0x2d, 0x2d, 0x0d, 0x0a };
    CheckBmp("demux_TextFontys.txt", CorrectHeader1, CorrectFirstBytes1,
             CorrectLastBytes1);

    Assert2FilesEqual("TextFontys.txt", "demux_TextFontys.txt");
}

int main(int argc, char* argv[])
{
    UnityBegin();

    MY_RUN_TEST(test_GetSubstring);
    MY_RUN_TEST(test_MultiplexTwoImages);
    MY_RUN_TEST(test_DemultiplexTwoImages);
    MY_RUN_TEST(test_MultiplexTextAndImage);
    MY_RUN_TEST(test_DemultiplexTextAndImage);

    return UnityEnd();
}
