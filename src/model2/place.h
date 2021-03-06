#ifndef PLACE_H
#define PLACE_H

#include <LBDatabase/LBDatabase.h>

#include <QIcon>

namespace PlaceProperties {
const QString PlzAttribute("plz");
const QString OrtAttribute("ort");
const QString StrasseAttribute("strasse");
const QString NummerAttribute("nummer");
const QString CommentAttribute("comment");
const QString IconPathAttribute("iconPath");
const QString GameCountAttribute("gameCount");
const QString GamesRelation("GameSite");
const QString PlayerRelation("PlayersAndPlaces");
} // namespace PlaceProperties

class Game;
class Player;

class Place : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Place(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int plz() const;
	QString ort() const;
	QString strasse() const;
	int nummer() const;
	QString comment() const;
	QIcon iconPath() const;
	int gameCount() const;

	void setPlz(int plz);
	void setOrt(const QString &ort);
	void setStrasse(const QString &strasse);
	void setNummer(int nummer);
	void setComment(const QString &comment);


	QList<Game *> games() const;
	QList<Player *> player() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
	void plzChanged(int plz);
	void ortChanged(QString ort);
	void strasseChanged(QString strasse);
	void nummerChanged(int nummer);
	void commentChanged(QString comment);
};

class PlacesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE PlacesContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Place *place(int id) const;
};

#endif // PLACE_H
