// PeriodicTableStudyer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>


typedef struct tagElement
{
    // number will be array index + 1
    const char* symbol = 0;
    const char* name = 0;

} element;

class sStr
{
public:
    char* str = 0;
    sStr(char* s) : str(s) {}
    
    ~sStr()
    {
        if (str)
        {
            delete[] str;
            str = 0;
        }
    }

    operator char* ()
    {
        return str;
    }
};

bool isNum(char c)
{
    return c >= '0' && c <= '9';
}

int getNum(char* str)
{
    size_t i = 0;
    int result = 0;
    while (isNum(str[i]))
    {
        result *= 10;
        result += str[i] - '0';
        ++i;
    }
    return result;
}

char toUpper(char c)
{
    if (c >= 'a' && c <= 'z')
        c -= 'a' - 'A';
    return c;
}

sStr toUpper(char* str)
{
    size_t arraySize = strlen(str) + 1;
    char* result = new char[arraySize];
    for (size_t i = 0; i < arraySize; ++i)
    {
        result[i] = toUpper(str[i]);
    }
    return (sStr)result;
}

char toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 'a' - 'A';
    return c;
}

sStr toLower(char* str)
{
    size_t arraySize = strlen(str) + 1;
    char* result = new char[arraySize];
    for (size_t i = 0; i < arraySize; ++i)
    {
        result[i] = toLower(str[i]);
    }
    return (sStr)result;
}

bool _myStrcmp(char* str1, char* str2)
{
    // returns true if the strings are the same
    // not sure how to use the std one, so I made my own
    size_t i = 0;
    while (str1[i] == str2[i])
    {
        if (str1[i] == 0)
            return true;
        ++i;
    }
    return false;
}

// Globals
char input[50] = "";
int elNum = -1;
bool typing = false;
bool randomMode = false;
bool gotSymbol = false;
bool gotName = false;

const element elmnts[] = { {"H", "hydrogen"},       {"He", "helium"},
        {"Li", "lithium"}, {"Be", "beryllium"},         {"B", "boron"}, {"C", "carbon"}, {"N", "nitrogen"}, {"O", "oxygen"}, {"F", "fluorine"}, {"Ne", "neon"},
        {"Na", "sodium"}, {"Mg", "magnesium"},          {"Al", "aluminium"}, {"Si", "silicon"}, {"P", "phosphorus"}, {"S", "sulfur"}, {"Cl", "chlorine"}, {"Ar", "argon"},
        {"K", "potassium"}, {"Ca", "calcium"}, {"Sc", "scandium"}, {"Ti", "titanium"}, {"V", "vanadium"}, {"Cr", "chromium"}, {"Mn", "manganese"}, {"Fe", "iron"}, {"Co", "cobalt"}, {"Ni", "nickel"}, {"Cu", "copper"}, {"Zn", "zinc"}, {"Ga", "gallium"}, {"Ge", "germanium"}, {"As", "arsenic"}, {"Se", "selenium"}, {"Br", "bromine"}, {"Kr", "krypton"},
        {"Rb", "rubidium"}, {"Sr", "strontium"}, {"Y", "yttrium"}, {"Zr", "zirconium"}, {"Nb", "niobium"}, {"Mo", "molybdenum"}, {"Tc", "technetium"}, {"Ru", "ruthenium"}, {"Rh", "rhodium"}, {"Pd", "palladium"}, {"Ag", "silver"}, {"Cd", "cadmium"}, {"In", "indium"}, {"Sn", "tin"}, {"Sb", "antimony"}, {"Te", "tellurium"}, {"I", "iodine"}, {"Xe", "xenon"},
        {"Cs", "cesium"}, {"Ba", "barium"},
        {"La", "lanthanum"}, {"Ce", "cerium"}, {"Pr", "praseodymium"}, {"Nd", "neodymium"}, {"Pm", "promethium"}, {"Sm", "samarium"}, {"Eu", "europium"}, {"Gd", "gadolinium"}, {"Tb", "terbium"}, {"Dy", "dysprosium"}, {"Ho", "holmium"}, {"Er", "erbium"}, {"Tm", "thulium"}, {"Yb", "ytterbium"}, {"Lu", "lutetium"},
        {"Hf", "hafnium"}, {"Ta", "tantalum"}, {"W", "tungsten"}, {"Re", "rhenium"}, {"Os", "osmium"}, {"Ir", "iridium"}, {"Pt", "platinum"}, {"Au", "gold"}, {"Hg", "mercury"}, {"Tl", "thallium"}, {"Pb", "lead"}, {"Bi", "bismuth"}, {"Po", "polonium"}, {"At", "astatine"}, {"Rn", "radon"},
        {"Fr", "francium"}, {"Ra", "radium"},
        {"Ac", "actinium"}, {"Th", "thorium"}, {"Pa", "protactinium"}, {"U", "uranium"}, {"Np", "neptunium"}, {"Pu", "plutonium"}, {"Am", "americium"}, {"Cm", "curium"}, {"Bk", "berkelium"}, {"Cf", "californium"}, {"Es", "einsteinium"}, {"Fm", "fermium"}};

bool validId(size_t id)
{
    return id < ((sizeof(elmnts) / sizeof(elmnts[0])));
}



void nextElement()
{   
    if (randomMode)
    {
        elNum = (double)rand() / RAND_MAX * (((sizeof(elmnts) / sizeof(elmnts[0]))) - 1);
    }
    else
        elNum += 1;
    
    gotSymbol = false;
    gotName = false;
}

bool singleCharComands(char c)
{
    // returns true and sets typing to false if there was a command
    switch (c)
    {
        // Escape Char
    case '-':
        // Next element
        
        if (elNum + 1 >= 0)
                std::cout << elNum + 2 << ' ' << elmnts[elNum + 1].symbol << ' ' << elmnts[elNum + 1].name << std::endl;

        if (validId(elNum + 1))
        {
            
            nextElement();
        }
        typing = false;
        return true;
    case '/':
        // Activate/Deactivate random mode
        randomMode = !randomMode;
        if (randomMode)
            std::cout << "\nRandom mode activated.\n";
        else
            std::cout << "\nRandom mode deactivated.\n";
        return true;
    default:
        return false;
    }
}


int main()
{
    time_t tmStart = 0;
    time(&tmStart);
    srand(tmStart);
    while(!_myStrcmp(toLower(input), (char*)"exit"))
    {
        if (!validId(elNum + 1))
        {
            std::cout << "\nYou finished the first 100!!! (The rest are not included in this)\n";
            typing = false;
            elNum = -1;
        }

        if (!typing)
        {
            input[0] = _getch();
            if (singleCharComands(input[0]))
                goto skipFullType;
        }

        std::cout << "\nType element " << elNum + 2 << ": ";
    avoidDisplayType:
        
        typing = true;
        std::cin >> input;

    
        if (isNum(input[0]))
        {
            elNum = getNum(input) - 1;
            if (elNum >= 0)
                std::cout << elNum + 1 << ' ' << elmnts[elNum].symbol << ' ' << elmnts[elNum].name << std::endl;
            gotSymbol = false;
            gotName = false;
        }

        if (input[0] && !(bool)input[1])
        {
            if (singleCharComands(input[0]))
            {
                gotSymbol = false;
                gotName = false;
            }
        }
    
    skipFullType:

        if (!gotSymbol && validId(elNum + 1) && _myStrcmp(input, (char*)elmnts[elNum + 1].symbol))
        {
            // Symbol needs correct caps
            gotSymbol = true;
            std::cout << " Got Symbol! ";
            if (!gotName)
                goto avoidDisplayType;
            else
            {
                std::cout << "You Got Element " << elNum + 2 << "!!\n";
                nextElement();
                continue;
            }
        }
        if (!gotName && validId(elNum + 1) && _myStrcmp(toLower(input), (char*)elmnts[elNum + 1].name))
        {
            // Name is not case-sensative
            gotName = true;
            std::cout << " Got Name! ";
            if (!gotSymbol)
                goto avoidDisplayType;
            else
            {
                std::cout << "You Got Element " << elNum + 2 << "!!\n";
                nextElement();
                continue;
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
