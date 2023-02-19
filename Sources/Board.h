#ifndef BOARD_H
#define BOARD_H

#include <QString>
namespace Fk {
class Image;
}

class Billboard
{
    public:
        virtual ~Billboard() = default;
        virtual bool save(const QString newAbsPathToFile, const char* newFormats) = 0;
    protected:
        Billboard() = default;
};

#endif // BOARD_H
