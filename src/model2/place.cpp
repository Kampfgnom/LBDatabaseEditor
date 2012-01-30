#include "place.h"

#include "game.h"
#include "player.h"
#include <QIcon>


#include "placecalculator.h"

const QString PlacesContext::Name("places");
const QString Place::Name("place");

Place::Place(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Place::plz() const
{
	return value(PlaceProperties::PlzAttribute).value<int>();
}

QString Place::ort() const
{
	return value(PlaceProperties::OrtAttribute).value<QString>();
}

QString Place::strasse() const
{
	return value(PlaceProperties::StrasseAttribute).value<QString>();
}

int Place::nummer() const
{
	return value(PlaceProperties::NummerAttribute).value<int>();
}

QString Place::comment() const
{
	return value(PlaceProperties::CommentAttribute).value<QString>();
}

QIcon Place::iconPath() const
{
	return value(PlaceProperties::IconPathAttribute).value<QIcon>();
}

int Place::gameCount() const
{
	return value(PlaceProperties::GameCountAttribute).value<int>();
}

QList<Game *> Place::games() const
{
	return relation<Game>(PlaceProperties::GamesRelation)->entities();
}

QList<Player *> Place::player() const
{
	return relation<Player>(PlaceProperties::PlayerRelation)->entities();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END
PlacesContext::PlacesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Place>();
	registerCalculatorClass<Place,PlaceCalculator>();

}

Place *PlacesContext::place(int id) const
{
	return static_cast<Place *>(entity(id));
}

