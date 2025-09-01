#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <memory>

#include "Tools/service_tool.h"
#include "Utils/command_ulit.h"
#include "Utils/file_util.h"
#include "Utils/format_util.h"
#include "Utils/i_command_executor.h"

//------------------------------- Тестовый набор для класса FormatUtil -----------------------------
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

//-------------------------------- Тестовый набор для класса FileUtil -----------------------------
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

//-------------------------- Тестовый набор для класса CommandUtil ------------------------------
// Нужны интеграционные тесты

class CommandUtilTest : public ::testing::Test {};

// TEST_F(CommandUtilTest, SudoExec) {

//     QString result = CommandUtil::SudoExec("ls");

// }

TEST_F(CommandUtilTest, Exec) {
    CommandUtil commandUtil;
    QStringList args{"-al"};

    QString result = commandUtil.Exec("ls", args);
    EXPECT_FALSE(result.isEmpty());
}

TEST_F(CommandUtilTest, IsExecutableReturnTrueForExecutableCommand) {
    CommandUtil commandUtil;
    QString comamnd{"ls"};
    EXPECT_TRUE(commandUtil.IsExecutable(comamnd));
}

TEST_F(CommandUtilTest, IsExecutableReturnFalseForNonExecutableCommand) {
    CommandUtil commandUtil;
    QString command{"no_existinng_command"};
    EXPECT_FALSE(commandUtil.IsExecutable(command));
}

//-------------------------------- Тестовый набор для класса ServiceTool ---------------------------

class MockCommandExecutor : public ICommandExecutor {
   public:
    MOCK_METHOD(QString, SudoExec, (const QString& command, QStringList args), (override));
    MOCK_METHOD(QString, Exec, (const QString& command, const QStringList& args), (override));
};

class ServiceToolTest : public ::testing::Test {
   protected:
    std::shared_ptr<MockCommandExecutor> mockCommandExecutor;

    std::unique_ptr<ServiceTool> serviceTool;

    // Перед каждым тестом создаем свежий экземпляр мока и ServiceTool
    void SetUp() override {
        mockCommandExecutor = std::make_shared<MockCommandExecutor>();
        serviceTool = std::make_unique<ServiceTool>(mockCommandExecutor);
    }
};

TEST_F(ServiceToolTest, GetServicesWithSystemctl) {
    QString commamd{"systemctl"};
    QString active{"active"};
    QString inactive{"inactive"};

    QStringList args{"list-unit-files",          "--type=service", "--all",
                     "--state=enabled,disabled", "--no-legend",    "--no-pager"};

    QString mock_output =
        "cups.service    enabled\n"
        "ssh.service     disabled\n"
        "getty@.service  enabled\n";  // Этот сервис должен быть пропущен

    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, args)).WillOnce(::testing::Return(mock_output));
    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, QStringList{"is-active", "cups.service"}))
        .WillOnce(::testing::Return(active));
    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, QStringList{"is-active", "ssh.service"}))
        .WillOnce(::testing::Return(inactive));

    QList<Service> services = serviceTool->GetServicesWithSystemctl();
    EXPECT_FALSE(services.isEmpty());
    ASSERT_EQ(services.size(), 2);  // Проверяем, что сервис с '@' был отфильтрован.

    EXPECT_EQ(services[0].name, "cups.service");
    EXPECT_TRUE(services[0].status);  // enabled
    EXPECT_TRUE(services[0].active);  // active

    EXPECT_EQ(services[1].name, "ssh.service");
    EXPECT_FALSE(services[1].status);  // disabled
    EXPECT_FALSE(services[1].active);  // inactive
}

TEST_F(ServiceToolTest, ServiceIsActiveReturnsTrueForActiveService) {
    QString commamd{"systemctl"};
    QString serviceName{"cups.service"};
    QStringList args{"is-active", serviceName};
    QString activeState{"active"};

    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, args)).WillOnce(::testing::Return(activeState));
    bool isActive = serviceTool->ServiceIsActive(serviceName);
    EXPECT_TRUE(isActive);
}

TEST_F(ServiceToolTest, ServiceIsActiveReturnsFalseForInactiveService) {
    QString commamd{"systemctl"};
    QString serviceName{"cups.service"};
    QStringList args{"is-active", serviceName};
    QString inactiveState{"inactive"};

    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, args))
        .WillOnce(::testing::Return(inactiveState));
    bool isActive = serviceTool->ServiceIsActive(serviceName);
    EXPECT_FALSE(isActive);
}

TEST_F(ServiceToolTest, ServiceIsEnableReturnsTrueForEnableService) {
    QString commamd{"systemctl"};
    QString serviceName{"cups.service"};
    QStringList args{"is-enabled", serviceName};
    QString enabledState{"enabled"};

    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, args))
        .WillOnce(::testing::Return(enabledState));
    bool isEnable = serviceTool->ServiceIsEnable(serviceName);
    EXPECT_TRUE(isEnable);
}

TEST_F(ServiceToolTest, ServiceIsEnableReturnsFalseForDisableService) {
    QString commamd{"systemctl"};
    QString serviceName{"cups.service"};
    QStringList args{"is-enabled", serviceName};
    QString disabledState{"disabled"};

    EXPECT_CALL(*mockCommandExecutor, Exec(commamd, args))
        .WillOnce(::testing::Return(disabledState));
    bool isEnable = serviceTool->ServiceIsEnable(serviceName);
    EXPECT_FALSE(isEnable);
}

TEST_F(ServiceToolTest, ChangeServiceStatusWithSuccess) {
    QString commamd{"systemctl"};
    QString serviceName{"cups.service"};

    EXPECT_CALL(*mockCommandExecutor, SudoExec(commamd, QStringList{"enable", serviceName}))
        .WillOnce(::testing::Return(""));
    EXPECT_TRUE(serviceTool->ChangeServiceStatus(serviceName, true));
}

TEST_F(ServiceToolTest, ChangeServiceStatusReturnsFalseWhenExecutorThrows) {
    QString commamd{"systemctl"};
    QString serviceName{"no_exist.service"};
    EXPECT_CALL(*mockCommandExecutor, SudoExec(commamd, QStringList{"enable", serviceName}))
        .WillOnce(::testing::Throw(QString{"Failed to execute"}));

    EXPECT_FALSE(serviceTool->ChangeServiceStatus(serviceName, true));
}

TEST_F(ServiceToolTest, ChangeServiceActive) {
    QString commamd{"systemctl"};
    QString serviceName{"cups.service"};

    EXPECT_CALL(*mockCommandExecutor, SudoExec(commamd, QStringList{"stop", serviceName}))
        .WillOnce(::testing::Return(""));
    EXPECT_TRUE(serviceTool->ChangeServiceActive(serviceName, false));
}

//-------------------------------- Тестовый набор для класса  ---------------------------

//-------------------------------- Тестовый набор для класса  ---------------------------

//-------------------------------- Тестовый набор для класса  ---------------------------

//-------------------------------- Тестовый набор для класса  ---------------------------