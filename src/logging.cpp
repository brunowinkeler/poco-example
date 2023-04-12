#include "Poco/ConsoleChannel.h"
#include "Poco/SimpleFileChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "Poco/File.h"

using Poco::AutoPtr;
using Poco::ConsoleChannel;
using Poco::File;
using Poco::FileChannel;
using Poco::Logger;
using Poco::SimpleFileChannel;

bool createLoggingDirectory(std::string path)
{
    // Create a File object with the folder path
    Poco::File folder(path);

    // Check if the folder already exists
    if (!folder.exists())
    {
        return folder.createDirectory();
    }

    return true;
}

int main(int argc, char **argv)
{
    if (!createLoggingDirectory("log"))
    {
        return 0;
    }

    AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);

    AutoPtr<SimpleFileChannel> pSimpleFileChannel(new SimpleFileChannel);
    pSimpleFileChannel->setProperty("path", "log/SimpleFileChannel.log");
    pSimpleFileChannel->setProperty("rotation", "2 K");

    AutoPtr<FileChannel> pFileChannel(new FileChannel);
    pFileChannel->setProperty("path", "log/FileChannel.log");
    pFileChannel->setProperty("rotation", "2 K");
    pFileChannel->setProperty("purgeCount", "6");

    Logger &logger = Logger::root();

    logger.setChannel(pSimpleFileChannel);

    for (int i = 0; i < 1000; ++i)
    {
        const std::string str = "0123456789 " + std::to_string(i);
        logger.information(str);
    }

    logger.setChannel(pFileChannel);

    for (int i = 0; i < 1000; ++i)
    {
        const std::string str = "0123456789 " + std::to_string(i);
        logger.information(str);
    }

    return 0;
}
