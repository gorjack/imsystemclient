#ifndef _FILE_HELPER_H_
#define _FILE_HELPER_H_

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

namespace utils
{
    class UTILS_EXPORT FileHelper
    {
    public:

        // used to open binary file
        static bool open(const string filename, string& content)
        {
            FILE *file = fopen(filename.c_str(), "rb");

            if (file == NULL)
                return false;

            fseek(file, 0, SEEK_END);
            int len = ftell(file);
            rewind(file);

            char *buffer = new char[len];
            fread(buffer, sizeof(char), len, file);
            content.assign(buffer, len);
            delete []buffer;

            fclose(file);
            return true;
        }

        static unsigned getFileSize(const string filename)
        {
            FILE *file = fopen(filename.c_str(), "rb");
            if (NULL == file)
            {
                return -1;
            }

            fseek(file, 0, SEEK_END);
            unsigned fileSize = ftell(file);
            rewind(file);

            return (fileSize);

            fclose(file);
        }

        static bool open(const string filename, string& content, unsigned nStart, unsigned nSize)
        {
            FILE *file = fopen(filename.c_str(), "rb");
            if (NULL == file)
            {
                return false;
            }

            fseek(file, nStart, SEEK_SET);
            char *buffer = new char[nSize];


            if (!fread(buffer, sizeof(char), nSize, file))
            {
                return false;
            }

            content.assign(buffer, nSize);
            delete[]buffer;

            fclose(file);
            return true;
        }

        // used to open binary file
        static bool open(const string filename, std::list<string>& contents)
        {
            FILE *file = fopen(filename.c_str(), "rb");
            string content;
            int64_t offsetX = 0;
            int64_t eachfilesize = 512 * 1024;


            if (file == NULL)
                return false;

            fseek(file, 0, SEEK_END);
            int len = ftell(file);
            rewind(file);

            while (offsetX <= len)
            {
                fseek(file, offsetX, SEEK_SET);

                if (offsetX + eachfilesize < len)
                {
                    offsetX += eachfilesize;
                    //len -= offsetX;

                    char *buffer = new char[eachfilesize];
                    size_t nBypes = fread(buffer, sizeof(char), eachfilesize, file);
                    if (nBypes < eachfilesize)
                    {
                        return false;
                    }
                    content.assign(buffer, eachfilesize);
                    delete[]buffer;
                    contents.push_back(content);
                }
                else
                {
                    int nTempBytes = len - offsetX;
                    offsetX = len;

                    char *buffer = new char[nTempBytes];
                    size_t nBypes = fread(buffer, sizeof(char), nTempBytes, file);
                    if (nBypes < nTempBytes)
                    {
                        return false;
                    }
                    content.assign(buffer, nTempBytes);
                    delete[]buffer;
                    contents.push_back(content);
                }


            }
            fclose(file);
            return true;
        }

        // used to open text file
        static bool open(const string file_name, vector<string>& lines)
        {
            ifstream file(file_name.c_str(), ios::in);
            if (!file) 
            {
                return false;
            }

            lines.clear();
            char buffer[buffer_size];

            while (file.getline(buffer, buffer_size, '\n'))
            {
                lines.push_back(buffer);
            }

            return true;
        }
        
        static bool write(const std::string filename, std::string& content)
        {
            FILE* outf = fopen(filename.c_str(), "wb");
            if (outf == NULL)
            {
                return false;
            }

            size_t pos = 0;
            size_t bytesWritten = 0;
            while(pos < content.size())
            {
                bytesWritten = fwrite(&content[pos], 1, content.size() - pos, outf);
                pos += bytesWritten;

                if (bytesWritten <= 0)
                {
                    fclose(outf);
                    return false;
                }
            }
            fclose(outf);

            return true;
        }

        

    private:

        enum { buffer_size = 3000 };
    };

} // namespace MUtils

#endif // _FILE_HELPER_H_