#include "rule.h"




const QString RulesContext::Name("Rules");
const QString Rule::Name("rule");

Rule::Rule(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QString Rule::attributeName() const
{
	return value(RuleProperties::AttributeNameAttribute).value<QString>();
}

int Rule::constraintId() const
{
	return value(RuleProperties::ConstraintIdAttribute).value<int>();
}

QString Rule::parameter() const
{
	return value(RuleProperties::ParameterAttribute).value<QString>();
}

int Rule::parentRuleId() const
{
	return value(RuleProperties::ParentRuleIdAttribute).value<int>();
}

int Rule::type() const
{
	return value(RuleProperties::TypeAttribute).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Rule::displayName() const
{
    return Entity::displayName();
}
	// END

RulesContext::RulesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Rule>();
}

Rule *RulesContext::rule(int id) const
{
	return static_cast<Rule *>(entity(id));
}

