#include "PencilBox.h"

Fk::PencilBox::PencilBox():
    color(QColor(Qt::black)),
    cursor(QPixmap(":/Normal/pencil-normal.png")),
    readiness(Readiness::Show),
    width(5)
{

}
