#include <gtest/gtest.h>
#include "EmailExtractor.h"
#include "ParseBody.h"
#include <fstream>

// Test fixture for EmailExtractor
class EmailExtractorTest : public ::testing::Test
{
protected:
    EmailExtractor emailExtractor;

    void SetUp() override
    {
        // Initialize the EmailExtractor before each test
    }
};

// Test case for extracting email fields
TEST(EmailExtractorTest, ExtractEmailFieldsBasic)
{
    // Sample email response
    std::string emailResponse = "Date: Mon, 01 Jan 2023 12:34:56 +0000\r\n"
                                "From: sender@example.com\r\n"
                                "To: recipient@example.com\r\n"
                                "Subject: Test Email\r\n"
                                "Content-Type: multipart/mixed; boundary=\"boundary123\"\r\n"
                                "\r\n"
                                "--boundary123\r\n"
                                "Content-Type: text/plain\r\n"
                                "\r\n"
                                "This is the plain text body.\r\n"
                                "\r\n"
                                "--boundary123\r\n"
                                "Content-Type: text/html\r\n"
                                "\r\n"
                                "<html><body><p>This is the HTML body.</p></body></html>\r\n"
                                "--boundary123--\r\n";

    EmailExtractor emailExtractor;

    // Extract email fields
    Email email = emailExtractor.extractEmailFields(emailResponse);

    // Check extracted fields
    EXPECT_EQ(email.date, "Mon, 01 Jan 2023 12:34:56 +0000");
    EXPECT_EQ(email.from, "sender@example.com");
    EXPECT_EQ(email.to, "recipient@example.com");
    EXPECT_EQ(email.subject, "Test Email");
    EXPECT_EQ(email.plainTextBody, "\r\n\r\nThis is the plain text body.\r\n\r\n");
    EXPECT_EQ(email.htmlBody, "\r\n\r\n<html><body><p>This is the HTML body.</p></body></html>\r\n");
}

// Test case for extracting email fields, reads from file
TEST(EmailExtractorTest, TestCaseFromFile1)
{
    // Read the input from the file testcase1.txt
    std::ifstream inputFile("./testcase1.txt");
    if (!inputFile)
    {
        FAIL() << "Failed to open testcase1.txt";
        return;
    }

    // Read the contents of the file into a string
    std::string emailResponse((std::istreambuf_iterator<char>(inputFile)),
                              (std::istreambuf_iterator<char>()));

    // Close the file
    inputFile.close();

    EmailExtractor emailExtractor; // Create an EmailExtractor instance

    // Extract email fields
    Email email = emailExtractor.extractEmailFields(emailResponse);

    // Assert expected values
    EXPECT_EQ(email.date, "Fri, 21 Jul 2023 01:38:11 +0200");
    EXPECT_EQ(email.from, "Manuel Heredia <spam.mhered@gmail.com>");
    EXPECT_EQ(email.to, "watchtower.test2023@gmail.com");
    EXPECT_EQ(email.subject, "test1");
    EXPECT_EQ(email.plainTextBody, "\r\n\r\nhello world\r\n\r\n");
    EXPECT_EQ(email.htmlBody, "\r\n\r\n<div dir=\"ltr\">hello world<br></div>\r\n\r\n");
}

// Test case for extracting email fields, reads from file
TEST(EmailExtractorTest, TestCaseFromFile2)
{
    // Read the input from the file testcase1.txt
    std::ifstream inputFile("./testcase2.txt");
    if (!inputFile)
    {
        FAIL() << "Failed to open testcase2.txt";
        return;
    }

    // Read the contents of the file into a string
    std::string emailResponse((std::istreambuf_iterator<char>(inputFile)),
                              (std::istreambuf_iterator<char>()));

    // Close the file
    inputFile.close();

    EmailExtractor emailExtractor; // Create an EmailExtractor instance

    // Extract email fields
    Email email = emailExtractor.extractEmailFields(emailResponse);

// Assert expected values
    EXPECT_EQ(email.date, "Sun, 3 Sep 2023 15:22:15 +0200");
    EXPECT_EQ(email.from, "Manuel Heredia <spam.mhered@gmail.com>");
    EXPECT_EQ(email.to, "watchtower.test2023@gmail.com");
    EXPECT_EQ(email.subject, "another test");
    EXPECT_EQ(email.plainTextBody,
              "\r\n\r\n#link:\r\nhttp://blog.aergenium.es/\r\n#title:\r\naergenium\r\n#comment:\r\na very forgotten blog\r\n\r\n");
    EXPECT_EQ(email.htmlBody,
              "\r\n\r\n<div dir=\"ltr\"><div>#link:</div><div><a href=\"http://blog.aergenium.es/\">http://blog.aergenium.es/</a></div><div>#title:</div><div>aergenium<br></div><div>#comment: <br></div>a very forgotten blog<br></div>\r\n\r\n");
}

// Test case for extracting email fields, reads from file
TEST(EmailExtractorTest, ParseTestCaseFromFile2)
{
    // Read the input from the file testcase1.txt
    std::ifstream inputFile("./testcase2.txt");
    if (!inputFile)
    {
        FAIL() << "Failed to open testcase2.txt";
        return;
    }

    // Read the contents of the file into a string
    std::string emailResponse((std::istreambuf_iterator<char>(inputFile)),
                              (std::istreambuf_iterator<char>()));

    // Close the file
    inputFile.close();

    EmailExtractor emailExtractor; // Create an EmailExtractor instance

    // Extract email fields
    Email email = emailExtractor.extractEmailFields(emailResponse);

    std::string link = extractLink(email.plainTextBody);
    std::string comment = extractComment(email.plainTextBody);
    std::string title = extractTitle(email.plainTextBody);

// Assert expected values
    EXPECT_EQ(link, "http://blog.aergenium.es/");
    EXPECT_EQ(title, "aergenium");
    EXPECT_EQ(comment, "a very forgotten blog");
    }






int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
