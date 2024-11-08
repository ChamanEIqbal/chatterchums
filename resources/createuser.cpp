#include <iostream>
#include "database/userDao.h"

sqlite3* UserDAO::db = nullptr;

#include <vector>

using namespace std;

int main() {
std::vector<std::string> randomUsernames = {
    "AliceJohnson", "BobDavis", "CharlieSmith", "DavidBrown", "EvaMiller",
    "FrankWilliams", "GraceJones", "JohnAnderson", "LindaGarcia", "RobertMartinez",
    "SophiaRobinson", "WilliamDavis", "OliviaRodriguez", "JamesSmith", "EmmaJohnson",
    "BenjaminGarcia", "AvaBrown", "MiaDavis", "EthanMartinez", "IsabellaRodriguez",
    "OliverSmith", "SophieJohnson", "MasonDavis", "ChloeGarcia", "LoganRobinson",
    "LiamSmith", "AriaDavis", "JacksonBrown", "AmeliaJohnson", "LucasGarcia",
    "HarperRodriguez", "ElijahSmith", "LilyDavis", "DanielMartinez", "GraceRobinson",
    "AidenSmith", "ZoeJohnson", "CalebGarcia", "EmilyDavis", "MadisonBrown",
    "IsaacSmith", "EllaRodriguez", "AveryDavis", "AubreySmith", "WyattJohnson",
    "SofiaDavis", "EvelynRobinson", "EzraBrown", "HudsonGarcia", "AddisonSmith",
    "LeviRodriguez", "CamilaJohnson", "LunaDavis", "JaydenSmith", "PeytonGarcia",
    "MichaelRobinson", "ScarlettBrown", "NicholasDavis", "AbigailSmith", "NoraJohnson",
    "EliGarcia", "HazelRodriguez", "AlexanderSmith", "AuroraDavis", "EmmaRobinson",
    "CarolineJohnson", "MateoSmith", "LeoBrown", "JulianGarcia", "ClaireDavis",
    "GraceSmith", "AnnaRodriguez", "SamuelJohnson", "AidenRobinson", "LucyDavis",
    "IsaiahSmith", "LiamGarcia", "PenelopeBrown", "AbigailDavis", "MadelineJohnson",
    "EleanorSmith", "XavierRobinson", "ChaseGarcia", "AriaRodriguez", "DavidDavis",
    "SophiaSmith", "GabrielBrown", "MilaJohnson", "OliviaRobinson", "JackDavis",
    "EmmaGarcia", "LandonSmith", "EllaBrown", "CarterRobinson", "CharlotteJohnson",
    "AverySmith", "DanielDavis", "HarperRodriguez", "MasonGarcia", "AubreyRobinson"
};

UserDAO dao;
for(int i = 3; i < 100; i++) {
    dao.insert(randomUsernames[i], "password");
    cout << "done!" << endl;
}

    system("pause");
    return 0;
}