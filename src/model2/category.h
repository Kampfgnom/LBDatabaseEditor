#ifndef CATEGORY_H
#define CATEGORY_H

#include <LBDatabase/LBDatabase.h>

namespace CategoryProperties {
const QString ContentTypeAttribute("contentType");
const QString OrderIndicatorAttribute("orderIndicator");
const QString NameAttribute("name");
const QString IconAttribute("icon");
const QString TypeAttribute("type");
const QString ParentCategoryRelation("parentCategory");
}

class Category;
class Category;

class Category : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Category(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int contentType() const;
	int orderIndicator() const;
	QString name() const;
	QString icon() const;
	int type() const;

	QList<Category *> parentCategory() const;
};

class CategoriesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE CategoriesContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Category *category(int id) const;
};

#endif // CATEGORY_H
