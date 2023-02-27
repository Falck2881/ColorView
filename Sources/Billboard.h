#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <QString>
namespace Fk {
class Image;
}

class Billboard
{
    public:
        virtual ~Billboard() = default;
        Fk::Image toImage() const;
        virtual bool save(const QString newAbsPathToFile, const QString newFormats) = 0;
    private:
        Billboard* const derivative;
    protected:
        Billboard(Billboard* const derivative);
};

#endif // BILLBOARD_H
