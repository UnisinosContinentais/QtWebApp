#include <iostream>
#include <QString>
#include <QCoreApplication>
#include <continental/fuzzy/service/fuzzy/FuzzyService.h>

using namespace continental::fuzzy::service::fuzzy;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QStringList args = app.arguments();

    std::cout << "CONSOLE CONTINENTAL FUZZY" << std::endl;

    new FuzzyService();

    return 0;
}
