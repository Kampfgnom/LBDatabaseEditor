#include "attribute.h"
#include "attribute_p.h"

#include "attributevalue.h"
#include "column.h"
#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "row.h"
#include "storage.h"
#include "table.h"

#include <QStringList>
#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** AttributePrivate
*/
void AttributePrivate::init()
{
    Q_Q(Attribute);
    name = row->data(Attribute::NameColumn).toString();
    displayName = row->data(Attribute::DisplayNameColumn).toString();
    calculated = row->data(Attribute::CalculatedColumn).toBool();
    cacheData = row->data(Attribute::CacheDataColumn).toBool();
    editable = row->data(Attribute::EditableColumn).toBool();

    type = static_cast<Attribute::Type>(row->data(Attribute::TypeColumn).toInt());

    entityType = storage->entityType(row->data(Attribute::EntityTypeIdColumn).toInt());
    if(!entityType) {
        qWarning() << "No such entity type:" << row->data(Attribute::EntityTypeIdColumn).toInt();
        return;
    }

    columnIndex = -1;
    if(!calculated)
        columnIndex = entityType->context()->table()->column(name)->index();
    entityType->addAttribute(q);
    entityType->context()->addAttribute(q);
}

void AttributePrivate::addPropertyValueToEntities()
{
    foreach(Entity *entity, entityType->entities()) {
        addPropertyValue(entity);
    }
}

void AttributePrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Attribute);
    entity->addAttributeValue(new AttributeValue(q, entity));
}

void AttributePrivate::fetchValues()
{
}

/******************************************************************************
** Attribute
*/
/*!
  \class Attribute
  \brief The Attribute class represents a simple single-value property of an
  EntityType.

  \ingroup highlevel-database-classes

  \todo Document when class is done.

  */

/*!
  \var Attribute::d_ptr
  \internal
  */

/*!
  \enum Attribute::Type

  This enumeration describes the type stored in the attribute.

  */

/*!
  \enum Attribute::PrefetchStrategy
  \brief Describes if and when the value of an attribute will be prefetched.
  */

/*!
  The name of 'name' column.
  */
const QString Attribute::NameColumn("name");
/*!
  The name of 'displayName' column.
  */
const QString Attribute::DisplayNameColumn("displayName");
/*!
  The name of 'entityTypeId' column.
  */
const QString Attribute::EntityTypeIdColumn("entityTypeId");
const QString Attribute::CalculatedColumn("calculated");
const QString Attribute::CacheDataColumn("cacheData");
const QString Attribute::TypeColumn("type");
const QString Attribute::EditableColumn("editable");

/*!
  Creates an attribute, which contains the meta data from \a row in the given \a
  storage.
  */
Attribute::Attribute(Row *row, Storage *parent) :
    Property(parent),
    d_ptr(new AttributePrivate)
{
    Q_D(Attribute);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

Attribute::Attribute(AttributePrivate &dd, Row *row, Storage *parent) :
    Property(parent),
    d_ptr(&dd)
{
    Q_D(Attribute);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

/*!
  Adds an AttributeValue instance to every existing Entity of the corrent
  EntityType.
  */
void Attribute::addPropertyValueToEntities()
{
    Q_D(Attribute);
    d->addPropertyValueToEntities();
}

/*!
  Adds an AttributeValue instance to the given \a entity.
  */
void Attribute::addPropertyValue(Entity *entity)
{
    Q_D(Attribute);
    d->addPropertyValue(entity);
}

void Attribute::fetchValues()
{
    Q_D(Attribute);
    d->fetchValues();
}

/*!
  Destroys the attribute.
  */
Attribute::~Attribute()
{
}

/*!
  Returns the storage-global ID of the attribute.
  */
int Attribute::id() const
{
    Q_D(const Attribute);
    return d->row->id();
}

/*!
  Returns the name of the attribute. if the attribute is stored in the database
  this name is the name of the column where it is stored.
  */
QString Attribute::name() const
{
    Q_D(const Attribute);
    return d->name;
}

bool Attribute::isCalculated() const
{
    Q_D(const Attribute);
    return d->calculated;
}

bool Attribute::cacheData() const
{
    Q_D(const Attribute);
    return d->cacheData;
}

bool Attribute::isEditable() const
{
    Q_D(const Attribute);
    return d->editable;
}

/*!
  Returns the display name of the attribute. Since each Attribute can only be
  part of one Context, the \a context parameter will be ignored.
  */
QString Attribute::displayName(const Context *context) const
{
    Q_UNUSED(context);
    Q_D(const Attribute);
    return d->displayName;
}

/*!
  Sets the display name of the attribute to \a displayName. Since each Attribute
  can only be part of one Context, the \a context parameter will be ignored.
  */
void Attribute::setDisplayName(const QString &displayName, const Context *context)
{
    Q_D(Attribute);
    Q_UNUSED(context);
    if(d->displayName == displayName)
        return;

    d->row->setData(Attribute::DisplayNameColumn, QVariant(displayName));
    d->displayName = displayName;
    emit displayNameChanged(displayName, d->entityType->context());
}

/*!
  Return the internal index of the column of this attribute.
  */
int Attribute::columnIndex() const
{
    Q_D(const Attribute);
    return d->columnIndex;
}

Attribute::Type Attribute::type() const
{
    Q_D(const Attribute);
    return d->type;
}

QString Attribute::typeName() const
{
    Q_D(const Attribute);
    return Attribute::typeToName(d->type);
}

QString Attribute::typeToName(Type type)
{
    return Attribute::typeNames().at(static_cast<int>(type));
}

QStringList Attribute::typeNames()
{
    QStringList names;
    names << "Unkown" <<
    "Text" <<
    "Integer" <<
    "Real" <<
    "Icon" <<
    "Pixmap" <<
    "DateTime" <<
    "Time" <<
    "Bool" <<
    "Color" <<
    "Enum";
    return names;
}

QString Attribute::qtType() const
{
    Q_D(const Attribute);
    return Attribute::typeToQtType(d->type);
}

QString Attribute::typeToQtType(Type type)
{
    return Attribute::qtTypeNames().at(static_cast<int>(type));
}

QStringList Attribute::qtTypeNames()
{
    QStringList names;
    names << "QVariant" << //Unknown
    "QString" << //Text
    "int" << //Integer
    "double" << //Real
    "QIcon" << //Icon
    "QPixmap" << //Pixmap
    "QDateTime" << //DateTime
    "QTime" << //Time
    "bool" << //Bool
    "QColor" << //Color
    "Enum"; //Enum
    return names;
}

} // namespace LBDatabase
