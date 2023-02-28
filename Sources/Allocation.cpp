#include "Allocation.h"
#include "Image.h"
#include <QDebug>
#include <QByteArray>
#include <exception>

Fk::Allocation::Allocation(const QString& nameFile):
    nameFile(nameFile)
{

}

std::unique_ptr<Billboard> Fk::Allocation::operator()()
{
    std::unique_ptr<Billboard> billboard;

    try {
        std::unique_ptr<Billboard> billboard;

        if(checkContentPair())
            return make();

    }  catch (const std::logic_error& exce) {
        qDebug() << exce.what();
        billboard = make();
        throw;
    }
    return billboard;
}

bool Fk::Allocation::checkContentPair() const
{
    return nameFile != "" && nameFile != "" ? true: throw std::logic_error("Variable 'Content' have  empty  strings");
}

std::unique_ptr<Billboard> Fk::Allocation::make() const
{
    return std::make_unique<Fk::Image>(nameFile);
}
