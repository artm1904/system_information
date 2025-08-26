#include <gtest/gtest.h>

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>

#include "Utils/command_ulit.h"
#include "Utils/file_util.h"
#include "Utils/format_util.h"

// Тестовый набор для класса FormatUtil
class FormatUtilTest : public ::testing::Test {};

TEST_F(FormatUtilTest, HandlesBytes) {
    EXPECT_EQ(FormatUtil::FormatBytes(0), "0 B");
    EXPECT_EQ(FormatUtil::FormatBytes(512), "512 B");
    EXPECT_EQ(FormatUtil::FormatBytes(1023), "1023 B");
}

TEST_F(FormatUtilTest, HandlesKibibytes) {
    // 1024 B = 1.0 KiB
    EXPECT_EQ(FormatUtil::FormatBytes(1024), "1.0 KiB");
    // 1.5 KiB
    EXPECT_EQ(FormatUtil::FormatBytes(1536), "1.5 KiB");
}

TEST_F(FormatUtilTest, HandlesMebibytes) {
    const quint64 one_mebibyte = 1ULL << 20;  // 1024*1024
    EXPECT_EQ(FormatUtil::FormatBytes(one_mebibyte), "1.00 MiB");

    const quint64 one_and_a_half_mebibytes = one_mebibyte + (one_mebibyte / 2);
    EXPECT_EQ(FormatUtil::FormatBytes(one_and_a_half_mebibytes), "1.50 MiB");
}

TEST_F(FormatUtilTest, HandlesGibibytes) {
    const quint64 one_gibibyte = 1ULL << 30;
    EXPECT_EQ(FormatUtil::FormatBytes(one_gibibyte), "1.00 GiB");
}

TEST_F(FormatUtilTest, HandlesTebibytes) {
    const quint64 one_tebibyte = 1ULL << 40;
    EXPECT_EQ(FormatUtil::FormatBytes(one_tebibyte), "1.00 TiB");
}

class FileUtilTest : public ::testing::Test {};

TEST_F(FileUtilTest, ReadStringFromFile) {
    QFile file{"test.txt"};
    file.open(QIODevice::WriteOnly);
    QTextStream stream{&file};
    stream << "Hello, world!";
    file.close();

    QString result = FileUtil::ReadStringFromFile("test.txt");
    EXPECT_EQ(result, "Hello, world!");
    QFile::remove("test.txt");
}

TEST_F(FileUtilTest, ReadListFromFile) {
    QFile file{"test2.txt"};
    file.open(QIODevice::WriteOnly);
    QTextStream stream{&file};
    stream << "Line 1\nLine 2\nLine 3";
    file.close();

    QStringList result = FileUtil::ReadListFromFile("test2.txt");
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Line 1");
    EXPECT_EQ(result[1], "Line 2");
    EXPECT_EQ(result[2], "Line 3");
    QFile::remove("test2.txt");
}

TEST_F(FileUtilTest, WriteFile) {
    QString filePath{"test3.txt"};
    QString fileData{"This is a test file"};

    bool success = FileUtil::WriteFile(filePath, fileData);
    EXPECT_TRUE(success);

    QString fileContent = FileUtil::ReadStringFromFile(filePath);
    EXPECT_EQ(fileContent, fileData);

    QFile::remove(filePath);
}

TEST_F(FileUtilTest, DirectoryList) {
    QString path{"./test_dir_for_list"};
    QDir{}.mkdir(path);

    QFile file1{path + "/file1.txt"};
    file1.open(QIODevice::WriteOnly);
    file1.close();

    QFile file2{path + "/file2.txt"};
    file2.open(QIODevice::WriteOnly);
    file2.close();

    QStringList result = FileUtil::DirectoryList(path);
    result.sort();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "file1.txt");
    EXPECT_EQ(result[1], "file2.txt");

    QDir{path}.removeRecursively();
}

TEST_F(FileUtilTest, GetFileSize) {
    QString path{"./test_dir_for_get_size"};
    const QString content{"This is a test file"};  // 19 байт
    QDir{}.mkdir(path);

    QFile file1{path + "/file1.txt"};
    file1.open(QIODevice::WriteOnly);
    QTextStream stream1{&file1};
    stream1 << content;
    file1.close();

    QFile file2{path + "/file2.txt"};
    file2.open(QIODevice::WriteOnly);
    QTextStream stream2{&file2};
    stream2 << content;
    file2.close();

    quint64 result = FileUtil::GetFileSize(path);
    EXPECT_EQ(result, 38);
    EXPECT_EQ(result, static_cast<quint64>(content.toUtf8().size() * 2));  // 19 * 2 = 38

    QDir{path}.removeRecursively();
}

class CommandUtilTest : public ::testing::Test {};

//TEST_F(CommandUtilTest, SudoExec) { QString result = CommandUtil::SudoExec("ls"); }

TEST_F(CommandUtilTest, Exec) {
    QString result = CommandUtil::Exec("ls");
    EXPECT_FALSE(result.isEmpty());
}

TEST_F(CommandUtilTest, IsExecutable) {
    EXPECT_TRUE(CommandUtil::IsExecutable("ls"));
    EXPECT_FALSE(CommandUtil::IsExecutable("nonexistent_command"));
}


