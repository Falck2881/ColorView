#include "Items.h"

QString App::Base::Item::messageAboutAction() const
{
    return note;
}

void App::Base::Item::writeNoteAboutAction(const QString &newNote)
{
    note = newNote;
}
