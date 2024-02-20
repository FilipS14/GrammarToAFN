 #include "Grammar.h"

void Grammar::readGrammar() {
    std::ifstream fin{ "fisier.txt" };
    if (!fin.is_open()) {
        std::cout << "Nu s-a putut deschide fisierul!\n";
    }
    
    {
        char word;
        uint32_t number;

        fin >> number;//citim numarul de elemente pentru multimea VN
        for (size_t i = 0; i < number; i++)
        {
            fin >> word;
            Vn.emplace_back(word);
        }

        fin >> number;//citim numarul de elemente pentru multimea VT
        for (size_t i = 0; i < number; i++)
        {
            fin >> word;
            Vt.emplace_back(word);
        }

        fin >> Start;//citim carcterul de start;


        std::string prod1, prod2;
        fin >> number;//citim numarul de productii;
        for (size_t i = 0; i < number; i++)
        {
            fin >> prod1 >> prod2;
            Production.push_back(std::make_pair( prod1, prod2 ));
        }
    }
    fin.close();
}

void Grammar::printGrammar() {
    for (const auto& word : Vn)
    {
        std::cout << word << ' ';
    }
    std::cout << '\n';

    for (const auto& word : Vt)
    {
        std::cout << word << ' ';
    }
    std::cout << '\n';

    std::cout << Start << '\n';

    for (const auto& word : Production)
    {
        std::cout << word.first << ' ' << word.second << '\n';
    }
}

std::pair<std::string, std::string> Grammar::generareRandom(std::vector<std::pair<std::string, std::string>>& v)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<>distr(0, v.size() - 1);
    return v[distr(eng)];
}

void Grammar::generateWord() {
    std::string result;
    std::pair<std::string, std::string> word;
    std::vector<std::pair<std::string, std::string>> randomCh;

    for (const auto& ch : Production) {
        if (ch.first == std::string(1, Start)) {
            randomCh.emplace_back(ch);
        }
    }
    
    word = generareRandom(randomCh);
    result = word.second;
    std::cout << "INLOCUIRE: " << Start << " -> " << result << '\n';
    if (result == "@") {
        std::cout << "REZULTAT: " << " " << '\n';
        return;
    }
    std::cout << "REZULTAT: " << result << '\n';
    word.first.clear();
    word.second.clear();
    randomCh.clear();

    while (true) {
        for (const auto& ch : Production) {
            if (result.find(ch.first) != std::string::npos) {
                randomCh.emplace_back(ch);
            }
        }
        if (randomCh.empty())
            return;
        word = generareRandom(randomCh);
        std::cout << "INLOCUIRE " << word.first << " -> " << word.second << '\n';

        randomCh.clear();
        if (word.first.empty() && word.second.empty())
            return;

        size_t found = result.find(word.first);
        if (found != std::string::npos) {
            if (word.second == "@") {
                result.erase(found, word.first.length());
            }
            else
                result.replace(found, word.first.length(), word.second);
            found = result.find(word.first);
        }
        std::cout << "REZULTAT: " << result << '\n';
        word.first.clear();
        word.second.clear();
    }
}

std::string Grammar::getGenerateWord() {
    std::string result;
    std::pair<std::string, std::string> word;
    std::vector<std::pair<std::string, std::string>> randomCh;

    for (const auto& ch : Production) {
        if (ch.first == std::string(1, Start)) {
            randomCh.emplace_back(ch);
        }
    }

    word = generareRandom(randomCh);
    result = word.second;

    if (result == "@") {
        return "";
    }

    while (!result.empty()) {
        for (const auto& ch : Production) {
            if (result.find(ch.first) != std::string::npos) {
                randomCh.emplace_back(ch);
            }
        }

        if (randomCh.empty())
            return result;

        word = generareRandom(randomCh);

        randomCh.clear();
        if (word.first.empty() && word.second.empty())
            break;

        size_t found = result.find(word.first);
        if (found != std::string::npos) {
            if (word.second == "@") {
                result.erase(found, word.first.length());
            }
            else {
                result.replace(found, word.first.length(), word.second);
            }
        }
    }
    return result;
}

bool Grammar::intersectionVnWithVt() {
    std::vector<char> cVn(Vn.begin(), Vn.end()), cVt(Vt.begin(), Vt.end());
    std::vector<char>intersctionResult;
    std::sort(cVn.begin(), cVn.end());
    std::sort(cVt.begin(), cVt.end());

    auto it = std::set_intersection(cVn.begin(), cVn.end(), cVt.begin(), cVt.end(), std::back_inserter(intersctionResult));

    return !intersctionResult.empty();
}

bool Grammar::isStartInVn() {
    auto it = std::find(Vn.begin(), Vn.end(), Start);
    return it != Vn.end();
}

bool Grammar::hasNonterminalOnLeft() {
    for (const auto& word : Production)
    {
        bool ok{ false };
        for (const auto& element : word.first)
        {
            if (std::find(Vn.begin(), Vn.end(), element) != Vn.end()) {
                ok = true;
                break;
            }
        }
        if (ok == false)
            return false;
    }
    return true;
}

bool Grammar::hasSProduction() {
    for (const auto& word : Production){
        if (word.first.size() == 1) {
            if (std::find(word.first.begin(), word.first.end(), Start) != word.first.end())
                return true;
        }
    }
    return false;
}

bool Grammar::onlyElementFromVnAndVt() {
    std::unordered_set<char> caractere;
    caractere.emplace('@');
    for (const auto& ch : Vn)
    {
        caractere.emplace(ch);
    }
    for (const auto& ch : Vt)
    {
        caractere.emplace(ch);
    }
    for (auto const& productie : Production)
    {
        for (auto const& letter : productie.first)
        {
            if (caractere.find(letter) == caractere.end())
                return false;
        }
        for (auto const& letter : productie.second)
        {
            if (caractere.find(letter) == caractere.end())
                return false;
        }
    }
    return true;
}

bool Grammar::CanGenerateLambda() const noexcept
{
    return true;
}

bool Grammar::verifyGrammar() {
    if (intersectionVnWithVt()) {
        return false;
    }

    if (!isStartInVn()) {
        return false;
    }

    if (!hasNonterminalOnLeft()) {
        return false;
    }

    if (!hasSProduction()) {
        return false;
    }

    if (!onlyElementFromVnAndVt()) {
        return false;
    }

    std::cout << "Grammar verification successful.\n";
    return true;
}

bool Grammar::isRegular() {
    for (const auto& production : Production) {
        short countU{ 0 };
        for (auto& character : production.first)
        {
            if (isupper(character))
                countU++;
        }
        if (countU != 1)
            return false;

        short countL{ 0 };
        if (production.second.at(0) == '@')
            continue;
        for (auto& character : production.second)
        {
            if (islower(character))
                countL++;
        }
        if (countL != 1)
            return false;
    }
    return true;
}

std::vector<char> Grammar::getVn() const {
    return Vn;
}

std::vector<char> Grammar::getVt() const {
    return Vt;
}

char Grammar::getStart() const {
    return Start;
}

std::vector<std::pair<std::string, std::string>> Grammar::getProduction() const {
    return Production;
}
