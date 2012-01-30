#include "livegamecalculator.h"

LiveGameCalculator::LiveGameCalculator(QObject *parent) :
	Calculator(parent)
{
}

EntityVariantHash LiveGameCalculator::points(const LBDatabase::Entity *entity) const
{
	//! \todo IMPLEMENT ME
	return EntityVariantHash();
}

