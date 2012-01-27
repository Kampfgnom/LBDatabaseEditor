#include "dokoofflinegamebuddy.h"



const QString DokoofflinegamebuddysContext::Name("dokoofflinegamebuddys");
DokoofflinegamebuddysContext::DokoofflinegamebuddysContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Dokoofflinegamebuddy>();
}

Dokoofflinegamebuddy *DokoofflinegamebuddysContext::dokoofflinegamebuddy(int id) const
{
	return static_cast<Dokoofflinegamebuddy *>(entity(id));
}

const QString Dokoofflinegamebuddy::Name("dokoofflinegamebuddy");

Dokoofflinegamebuddy::Dokoofflinegamebuddy(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Dokoofflinegamebuddy::rounds() const
{
	return value(DokoofflinegamebuddyProperties::RoundsAttribute).value<int>();
}

int Dokoofflinegamebuddy::wins() const
{
	return value(DokoofflinegamebuddyProperties::WinsAttribute).value<int>();
}
