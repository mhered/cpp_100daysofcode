#include <string>
#include <iostream>
#include <vector>

struct Morse
{
    const static int DOT = 1; // time unit
    const static int DASH = 3;
    const static int COMP_SP = 1;
    const static int LETTER_SP = 3;
    const static int WORD_SP = 7;

    std::string symbol;
    std::string morse;

    Morse(std::string symbol, std::string morse) : symbol(symbol), morse(morse){};
};

const Morse MORSE_TABLE[] = {{"A", ".-"},
                             {"B", "-..."},
                             {"C", "-.-."},
                             {"D", "-.."},
                             {"E", "."},
                             {"F", "..-."},
                             {"G", "--."},
                             {"H", "...."},
                             {"I", ".."},
                             {"J", ".---"},
                             {"K", "-.-"},
                             {"L", ".-.."},
                             {"M", "--"},
                             {"N", "-."},
                             {"O", "---"},
                             {"P", ".--."},
                             {"Q", "--.-"},
                             {"R", ".-."},
                             {"S", "..."},
                             {"T", "-"},
                             {"U", "..-"},
                             {"V", "...-"},
                             {"W", ".--"},
                             {"X", "-..-"},
                             {"Y", "-.--"},
                             {"Z", "--.."},
                             {"1", ".----"},
                             {"2", "..---"},
                             {"3", "...--"},
                             {"4", "....-"},
                             {"5", "....."},
                             {"6", "-...."},
                             {"7", "--..."},
                             {"8", "---.."},
                             {"9", "----."},
                             {"0", "-----"},
                             {".", ".-.-.-"},
                             {",", "--..--"},
                             {"?", "..--.."},
                             {"!", "-.-.--"},
                             {"(", "-.--."},
                             {")", "-.--.-"},
                             {":", "---..."},
                             {"<CT>", "-.-.-"},
                             {"<SK>", "...-.-"},
                             {"<AS>", ".-..."},
                             {"<SN>", "...-."},
                             {"<HH>", "........"},
                             {"<SOS>", "...---..."}};

std::string symbol_to_morse(std::string symbol)
{
    for (auto elem : MORSE_TABLE)
    {
        if (elem.symbol == symbol)
            return elem.morse;
    }
    return "#"; // not found
}

bool endswith(std::string s, std::string suffix)
{
    return s.find(suffix, s.length() - suffix.length()) != std::string::npos;
}

bool startswith(std::string s, std::string prefix)
{
    return (s.rfind(prefix, 0) == 0);
}

std::string trim(const std::string &str,
                 const std::string &whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string cleanup(const std::string &str,
                    const std::string &fill = " ",
                    const std::string &whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

std::string allcaps(std::string msg)
{
    std::string result;
    for (int i = 0; i < msg.size(); i++)
    {
        result.push_back(toupper(msg[i]));
    }
    return result;
}

std::string preprocess(std::string msg)
{
    // clean up: remove leading, trailing and repeated spaces
    msg = cleanup(msg);
    msg = allcaps(msg);

    // if needed prepend Start Prosign
    if (msg.size() < 4 || !startswith(msg, "<CT>"))
        msg = "<CT> " + msg;

    // if needed append End of Message prosign
    if (msg.size() < 4 || !endswith(msg, "<SK>"))
        msg += " <SK>";

    return msg;
}

std::string translate(std::string msg, bool verbose = false)
{
    msg = preprocess(msg);

    std::string result;

    for (int i = 0; i < msg.size(); i++)
    {
        std::string s(1, toupper(msg[i]));
        if (s == " ") // word separation
        {
            result += "/";
            continue;
        };

        if (s == "<") // greedy capture of prosigns
        {
            while (true)
            {
                s += msg[++i];
                if (msg[i] == '>')
                    break;
            }
        }
        std::string morse_letter = symbol_to_morse(s);
        result += morse_letter + " "; // add letter separator
    }

    if (verbose)
    {
        std::cout << "\"" << result << "\"" << std::endl;
    }
    return result;
}

std::string translate2(std::string morse_str, bool verbose = false)
{

    std::string result;

    for (int i = 0; i < morse_str.size(); i++)
    {
        std::string s(1, morse_str[i]);
        if (morse_str[i] == '.') // dot
            result += std::string(Morse::DOT, '1') + std::string(Morse::COMP_SP, '0');
        else if (morse_str[i] == '-') // dash
            result += std::string(Morse::DASH, '1') + std::string(Morse::COMP_SP, '0');
        else if (morse_str[i] == ' ') // add letter separator
            result += std::string(Morse::LETTER_SP - Morse::COMP_SP, '0');
        else if (s == "/") // word separation
            result += std::string(Morse::WORD_SP - Morse::LETTER_SP, '0');
        else if (!(s == "#")) // skip if not translated
            result += std::string(Morse::LETTER_SP - Morse::COMP_SP, '0');
    }

    if (verbose)
    {
        std::cout << "\"" << result << "\"" << std::endl;
    }
    return result;
}