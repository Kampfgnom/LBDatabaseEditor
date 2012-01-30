#ifndef CATEGORYASSIGNMENT_H
#define CATEGORYASSIGNMENT_H

#include <LBDatabase/LBDatabase.h>


namespace CategoryassignmentProperties {
const QString CategorieIdAttribute("categorieId");
const QString ElementIdAttribute("elementId");
} // namespace CategoryassignmentProperties


class Categoryassignment : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Categoryassignment(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int categorieId() const;
	int elementId() const;


};

class CategorieassignmentsContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE CategorieassignmentsContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Categoryassignment *categoryassignment(int id) const;
};

#endif // CATEGORYASSIGNMENT_H
