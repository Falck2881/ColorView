#include "Allocation.h"
#include "Image.h"
#include <QDebug>
#include <QByteArray>
#include <exception>

Fk::Allocation::Allocation(const std::pair<QString,QString>& newContent):
    content(newContent)
{

}

std::unique_ptr<Billboard> Fk::Allocation::operator()()
{
    std::unique_ptr<Billboard> billbord;

            billbord = make();

        return billbord;


}

bool Fk::Allocation::checkContentPair() const
{
    return content.first != "" && content.second != "" ? true: throw std::logic_error("Variable 'Content' have  empty  strings");
}

std::unique_ptr<Billboard> Fk::Allocation::make() const
{
    QString nameFile = content.first;
    QByteArray bArr = content.second.toLatin1();
    return std::make_unique<Fk::Image>(nameFile,bArr.data());
}
