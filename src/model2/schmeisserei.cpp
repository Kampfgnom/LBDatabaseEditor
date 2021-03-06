#include "schmeisserei.h"

#include "player.h"
#include "round.h"



const QString SchmeissereisContext::Name("schmeissereis");
const QString Schmeisserei::Name("schmeisserei");

Schmeisserei::Schmeisserei(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QString Schmeisserei::type() const
{
	return value(SchmeissereiProperties::TypeAttribute).value<QString>();
}

void Schmeisserei::setType(const QString &type)
{
	if(type == this->type())
		return;
	setValue(SchmeissereiProperties::TypeAttribute,QVariant::fromValue<QString>(type));
	emit typeChanged(type);
}

Player *Schmeisserei::player() const
{
	return relation<Player>(SchmeissereiProperties::PlayerRelation)->firstEntity();
}

Round *Schmeisserei::round() const
{
	return relation<Round>(SchmeissereiProperties::RoundRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

SchmeissereisContext::SchmeissereisContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Schmeisserei>();
}

Schmeisserei *SchmeissereisContext::schmeisserei(int id) const
{
	return static_cast<Schmeisserei *>(entity(id));
}

