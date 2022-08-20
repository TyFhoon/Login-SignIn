
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>

std::string Check2Char(std::string Char1, std::string Char2, std::string& CharInp)
{
    while ((CharInp != Char1 && CharInp != Char2))
    {
        std::cout << "Please try again\n";
        std::cin >> CharInp;
    }
    return CharInp;
}
std::string LogSignInput(std::string& sInpFirst, std::string& sInpLast, std::string& sInpPass)
{

    std::cout << "First Name: \n";
    std::cin >> sInpFirst;
    std::transform(sInpFirst.begin(), sInpFirst.end(), sInpFirst.begin(), ::tolower);

    std::cout << "Last Name: \n";
    std::cin >> sInpLast;
    std::transform(sInpLast.begin(), sInpLast.end(), sInpLast.begin(), ::tolower);

    std::cout << "Password: \n";
    std::cin >> sInpPass;
    std::transform(sInpPass.begin(), sInpPass.end(), sInpPass.begin(), ::tolower);
    //retruns to login or sign up
    return sInpFirst, sInpLast, sInpPass;

}

void TestMenu()
{
    std::cout << "====== A MENU =======";
}
void Login()
{
    system("cls");
    std::cout << "\n============\n"
        "---LOGIN--- \n"
        "============\n\n";
    std::string sInpFirst;
    std::string sInpLast;
    std::string sInpPass;
    LogSignInput(sInpFirst, sInpLast, sInpPass);

    bool bLogCheck = false;

    std::vector<std::string> vSplit;
    std::string line = "";
    std::string sResult = "";

    std::ifstream File("UserDetails.txt");

    while (File.is_open())
    {
        //While the func has found what it's looking for or if it doesnt end
        while ((bLogCheck == false) && (std::getline(File, line)))
        {
            std::stringstream ssSplit(line);

            vSplit.resize(0);

            while (std::getline(ssSplit, sResult, ','))
            {
                vSplit.push_back(sResult);
            }

            /*std::cout << vSplit[0] << "\n";
            std::cout << vSplit[1] << "\n";
            std::cout << vSplit[2] << "\n";
            std::cout << vSplit[3] << "\n";
            std::cout << vSplit[4] << "\n";*/

            if (vSplit[0] == sInpFirst && vSplit[1] == sInpLast && vSplit[2] == sInpPass)
            {
                bLogCheck = true;
            }
        }


        File.close();
    }
    /*std::cout << vSplit[0] << "\n";
    std::cout << vSplit[1] << "\n";
    std::cout << vSplit[2] << "\n";
    std::cout << vSplit[3] << "\n";
    std::cout << vSplit[4] << "\n";*/

    //stores the current users ID and if they have admin access
    std::ofstream UserFile("LoggedIn.txt");
    while (UserFile.is_open())
    {
        //ID , Admin
        UserFile << vSplit[3] << "," << vSplit[4];
        UserFile.close();
    }

    if (bLogCheck == true)
    {
        TestMenu();
    }
    else if (bLogCheck == false)
    {
        std::cout << "Your name or password is wrong";
        Sleep(1700);
        system("cls");
        Login();

    }
}

void SignUp() 
{
    //Sign up, login info to be added to the user CSV
    system("cls");
    std::cout << "=============\n"
        "---SIGN UP---\n"
        "=============\n\n";

    std::string sInpFirst;
    std::string sInpLast;
    std::string sInpPass;
    LogSignInput(sInpFirst, sInpLast, sInpPass);


    //User ID
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(10000, 99999);

    auto iGenID = dist(rng);


    bool bCheckAdmin = false;
    if (sInpFirst == "sean" && sInpLast == "shearing")
    {
        bCheckAdmin = true;
    }


    std::ofstream File("UserDetails.txt", std::ios::app);
    //Writes the structure into the csv and then closes
    if (File.is_open())
    {
        File << sInpFirst << ","
            << sInpLast << ","
            << sInpPass << ","
            << iGenID << ","
            << bCheckAdmin << "\n";


        File.close();
    }
    else
    {
        std::cout << "Error occured opening file";
    }
    std::cout << "Successfully Saved \n";
    Sleep(1000);
    Login();
}
int main()
{
    std::cout << "\n\n===== LOGIN OR SIGN UP =====\n\n"
        <<".LOGIN (L)\n"
        <<".SIGN UP (S)\n\n"
        <<"Type \"l\" or \"s\" to login or sign up\n";
    
    std::string Char1 = "l";
    std::string Char2 = "s";
    std::string CharInp = "";

    std::cin >> CharInp;

    Check2Char(Char1, Char2, CharInp);
    std::cout << CharInp << "\n";

    if (CharInp == Char1)
    {
        Login();
    }
    else if (CharInp == Char2)
    {
        SignUp();
    }

}

