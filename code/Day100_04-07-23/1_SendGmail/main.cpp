#include "EmailSender.h"
#include <vector>
#include <iostream>

int main()
{
    EmailSender emailSender;

    std::vector<std::string> recipients = {"spam.mhered@gmail.com", "manolo.heredia@gmail.com"};
    std::string subject = "Test " + getRFC5322FormattedCurrentDateTime();
    std::string body = "This is a test email sent from a C++ program using libcurl.";

    if (emailSender.sendEmail(recipients, subject, body))
    {
        std::cout << "Email sent successfully." << std::endl;
    }
    else
    {
        std::cerr << "Failed to send the email." << std::endl;
    }

    return 0;
}