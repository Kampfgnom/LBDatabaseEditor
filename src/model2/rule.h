#ifndef RULE_H
#define RULE_H

#include <LBDatabase/LBDatabase.h>

namespace RuleProperties {
const QString AttributeNameAttribute("attributeName");
const QString ConstraintIdAttribute("constraintId");
const QString ParameterAttribute("parameter");
const QString ParentRuleIdAttribute("parentRuleId");
const QString TypeAttribute("type");
}


class Rule : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Rule(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString attributeName() const;
	int constraintId() const;
	QString parameter() const;
	int parentRuleId() const;
	int type() const;

};

class RulesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE RulesContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Rule *rule(int id) const;
};

#endif // RULE_H
