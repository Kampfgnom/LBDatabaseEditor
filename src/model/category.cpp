#include "category.h"

#include "category.h"



const QString CategoriesContext::Name("Categories");
const QString Category::Name("category");

Category::Category(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Category::contentType() const
{
	return value(CategoryProperties::ContentTypeAttribute).value<int>();
}

int Category::orderIndicator() const
{
	return value(CategoryProperties::OrderIndicatorAttribute).value<int>();
}

QString Category::name() const
{
	return value(CategoryProperties::NameAttribute).value<QString>();
}

QString Category::icon() const
{
	return value(CategoryProperties::IconAttribute).value<QString>();
}

int Category::type() const
{
	return value(CategoryProperties::TypeAttribute).value<int>();
}

Category *Category::parentCategory() const
{
	return relation<Category>(CategoryProperties::ParentCategoryRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Category::displayName() const
{
    return Entity::displayName();
}
	// END

CategoriesContext::CategoriesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Category>();
}

Category *CategoriesContext::category(int id) const
{
	return static_cast<Category *>(entity(id));
}

