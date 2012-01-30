#include "categoryassignment.h"




const QString CategorieassignmentsContext::Name("categorieassignments");
const QString Categoryassignment::Name("categoryassignment");

Categoryassignment::Categoryassignment(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Categoryassignment::categorieId() const
{
	return value(CategoryassignmentProperties::CategorieIdAttribute).value<int>();
}

int Categoryassignment::elementId() const
{
	return value(CategoryassignmentProperties::ElementIdAttribute).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END
CategorieassignmentsContext::CategorieassignmentsContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Categoryassignment>();
}

Categoryassignment *CategorieassignmentsContext::categoryassignment(int id) const
{
	return static_cast<Categoryassignment *>(entity(id));
}

