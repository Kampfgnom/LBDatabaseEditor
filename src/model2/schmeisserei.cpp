#include "schmeisserei.h"



const QString SchmeissereisContext::Name("schmeissereis");
SchmeissereisContext::SchmeissereisContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Schmeisserei>();
}

Schmeisserei *SchmeissereisContext::schmeisserei(int id) const
{
	return static_cast<Schmeisserei *>(entity(id));
}

const QString Schmeisserei::Name("schmeisserei");

Schmeisserei::Schmeisserei(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Schmeisserei::type() const
{
	return value(SchmeissereiProperties::TypeAttribute).value<int>();
}
