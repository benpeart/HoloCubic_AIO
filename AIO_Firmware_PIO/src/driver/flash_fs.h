#include <Arduino.h>
#include "FS.h"

class FlashFS
{
private:
    fs::FS *m_fs;
public:
    FlashFS();

    ~FlashFS();

    void listDir(const char *dirname, uint8_t levels);

    // void createDir(const char *path);

    // void removeDir(const char *path);

    uint16_t readFile(const char *path, uint8_t *info);

    void writeFile(const char *path, const char *message);

    void appendFile(const char *path, const char *message);

    void renameFile(const char *src, const char *dst);

    void deleteFile(const char *path);

    // Write to multi-level recursive file path
    // void writeFile2(const char *path, const char *message);

    // Delete multi-level recursive file
    // void deleteFile2(const char *path);

private:
    void testFileIO(const char *path);
};

bool analyseParam(char *info, int argc, char **argv);