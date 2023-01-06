#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

namespace Base
{
    class Command: public QObject
    {
        Q_OBJECT

        public:
            virtual ~Command() = default;
        public slots:
            virtual void execute() = 0;
        protected:
            Command() = default;
    };

}
#endif // COMMAND_H
