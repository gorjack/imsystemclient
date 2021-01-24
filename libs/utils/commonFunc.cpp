#include "commonFunc.h"
#include <QDataStream>
#include <QFile>

namespace utils
{

    std::wstring qToStdWString(const QString& str)
    {
#   ifdef _MSC_VER
        return std::wstring((const wchar_t*)str.utf16());
#   else
        return str.toStdWString();
#endif
    }

    QString stdWToQString(const std::wstring &str)
    {
#    ifdef _MSC_VER
        return QString::fromUtf16((const ushort*)str.c_str());
#    else
        return QString::fromStdWString(str);
#endif
    }

    int getWavFileTimeSpan(QString qsWavFilePath)
    {
        QFile wavFile(qsWavFilePath);
        if (!wavFile.open(QFile::ReadOnly))
        {
            return -1;
        }
        QByteArray wavFileContent = wavFile.readAll();
        char fileType[4];
        qint32 fileSize;
        char waveName[4];
        char fmtName[4];
        qint32 fmtLength;
        qint16 fmtType;
        qint16 numberOfChannels;
        qint32 sampleRate;
        qint32 sampleRateXBitsPerSampleXChanngelsDivEight;
        qint16 bitsPerSampleXChannelsDivEightPointOne;
        qint16 bitsPerSample;
        char dataHeader[4];
        qint32 dataSize;

        QDataStream analyzeHeaderDS(&wavFileContent, QIODevice::ReadOnly);
        analyzeHeaderDS.setByteOrder(QDataStream::LittleEndian);
        analyzeHeaderDS.readRawData(fileType, 4);
        analyzeHeaderDS >> fileSize;
        analyzeHeaderDS.readRawData(waveName, 4);
        analyzeHeaderDS.readRawData(fmtName, 4);
        analyzeHeaderDS >> fmtLength;
        analyzeHeaderDS >> fmtType;
        analyzeHeaderDS >> numberOfChannels;
        analyzeHeaderDS >> sampleRate;
        analyzeHeaderDS >> sampleRateXBitsPerSampleXChanngelsDivEight;
        analyzeHeaderDS >> bitsPerSampleXChannelsDivEightPointOne;
        analyzeHeaderDS >> bitsPerSample;
        analyzeHeaderDS.readRawData(dataHeader, 4);
        analyzeHeaderDS >> dataSize;

        return (dataSize / sampleRateXBitsPerSampleXChanngelsDivEight + 0.5);
    }

}