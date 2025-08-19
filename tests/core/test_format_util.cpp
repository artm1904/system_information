#include <gtest/gtest.h>
#include "Utils/format_util.h" 

// Тестовый набор для класса FormatUtil
class FormatUtilTest : public ::testing::Test {};

TEST_F(FormatUtilTest, HandlesBytes)
{
    EXPECT_EQ(FormatUtil::formatBytes(0), "0 B");
    EXPECT_EQ(FormatUtil::formatBytes(512), "512 B");
    EXPECT_EQ(FormatUtil::formatBytes(1023), "1023 B");
}

TEST_F(FormatUtilTest, HandlesKibibytes)
{
    // 1024 B = 1.0 KiB
    EXPECT_EQ(FormatUtil::formatBytes(1024), "1.0 KiB");
    // 1.5 KiB
    EXPECT_EQ(FormatUtil::formatBytes(1536), "1.5 KiB");
}

TEST_F(FormatUtilTest, HandlesMebibytes)
{
    const quint64 one_mebibyte = 1ULL << 20; // 1024*1024
    EXPECT_EQ(FormatUtil::formatBytes(one_mebibyte), "1.00 MiB");

    const quint64 one_and_a_half_mebibytes = one_mebibyte + (one_mebibyte / 2);
    EXPECT_EQ(FormatUtil::formatBytes(one_and_a_half_mebibytes), "1.50 MiB");
}

TEST_F(FormatUtilTest, HandlesGibibytes)
{
    const quint64 one_gibibyte = 1ULL << 30;
    EXPECT_EQ(FormatUtil::formatBytes(one_gibibyte), "1.00 GiB");
}

TEST_F(FormatUtilTest, HandlesTebibytes)
{
    const quint64 one_tebibyte = 1ULL << 40;
    EXPECT_EQ(FormatUtil::formatBytes(one_tebibyte), "1.00 TiB");
}