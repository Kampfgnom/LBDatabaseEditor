#ifndef PROJECTSTATSSTORAGE_H
#define PROJECTSTATSSTORAGE_H

#include <LBDatabase/LBDatabase.h>

class CategorieassignmentsContext;
class RoundsContext;
class CategoriesContext;
class RulesContext;
class SchmeissereisContext;
class DokoofflinegamebuddysContext;
class DrinksContext;
class GamesContext;
class LivegamedrinksContext;
class OfflinegameinformationsContext;
class PlacesContext;
class PlayersContext;

class ProjectStatsStorage : public LBDatabase::Storage
{
public:
	ProjectStatsStorage(const QString &fileName, QObject *parent = 0);

	CategorieassignmentsContext *categorieassignmentsContext() const;
	RoundsContext *roundsContext() const;
	CategoriesContext *categoriesContext() const;
	RulesContext *rulesContext() const;
	SchmeissereisContext *schmeissereisContext() const;
	DokoofflinegamebuddysContext *dokoofflinegamebuddysContext() const;
	DrinksContext *drinksContext() const;
	GamesContext *gamesContext() const;
	LivegamedrinksContext *livegamedrinksContext() const;
	OfflinegameinformationsContext *offlinegameinformationsContext() const;
	PlacesContext *placesContext() const;
	PlayersContext *playersContext() const;
};

#endif // PROJECTSTATSSTORAGE_H
