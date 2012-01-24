#include "projectstatsstorage.h"

#include "categoryassignment.h"
#include "round.h"
#include "category.h"
#include "rule.h"
#include "schmeisserei.h"
#include "dokoofflinegamebuddy.h"
#include "drink.h"
#include "game.h"
#include "livegamedrink.h"
#include "offlinegameinformation.h"
#include "place.h"
#include "player.h"

ProjectStatsStorage::ProjectStatsStorage(const QString &fileName, QObject *parent) :
	Storage(fileName, parent)
{
	registerContextType<CategorieassignmentsContext>();
	registerContextType<RoundsContext>();
	registerContextType<CategoriesContext>();
	registerContextType<RulesContext>();
	registerContextType<SchmeissereisContext>();
	registerContextType<DokoofflinegamebuddysContext>();
	registerContextType<DrinksContext>();
	registerContextType<GamesContext>();
	registerContextType<LivegamedrinksContext>();
	registerContextType<OfflinegameinformationsContext>();
	registerContextType<PlacesContext>();
	registerContextType<PlayersContext>();
}

CategorieassignmentsContext *ProjectStatsStorage::categorieassignmentsContext() const
{
	return static_cast<CategorieassignmentsContext *>(context(CategorieassignmentsContext::Name));
}

RoundsContext *ProjectStatsStorage::roundsContext() const
{
	return static_cast<RoundsContext *>(context(RoundsContext::Name));
}

CategoriesContext *ProjectStatsStorage::categoriesContext() const
{
	return static_cast<CategoriesContext *>(context(CategoriesContext::Name));
}

RulesContext *ProjectStatsStorage::rulesContext() const
{
	return static_cast<RulesContext *>(context(RulesContext::Name));
}

SchmeissereisContext *ProjectStatsStorage::schmeissereisContext() const
{
	return static_cast<SchmeissereisContext *>(context(SchmeissereisContext::Name));
}

DokoofflinegamebuddysContext *ProjectStatsStorage::dokoofflinegamebuddysContext() const
{
	return static_cast<DokoofflinegamebuddysContext *>(context(DokoofflinegamebuddysContext::Name));
}

DrinksContext *ProjectStatsStorage::drinksContext() const
{
	return static_cast<DrinksContext *>(context(DrinksContext::Name));
}

GamesContext *ProjectStatsStorage::gamesContext() const
{
	return static_cast<GamesContext *>(context(GamesContext::Name));
}

LivegamedrinksContext *ProjectStatsStorage::livegamedrinksContext() const
{
	return static_cast<LivegamedrinksContext *>(context(LivegamedrinksContext::Name));
}

OfflinegameinformationsContext *ProjectStatsStorage::offlinegameinformationsContext() const
{
	return static_cast<OfflinegameinformationsContext *>(context(OfflinegameinformationsContext::Name));
}

PlacesContext *ProjectStatsStorage::placesContext() const
{
	return static_cast<PlacesContext *>(context(PlacesContext::Name));
}

PlayersContext *ProjectStatsStorage::playersContext() const
{
	return static_cast<PlayersContext *>(context(PlayersContext::Name));
}

