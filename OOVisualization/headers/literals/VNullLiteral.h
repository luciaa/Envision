/***********************************************************************************************************************
 * VNullLiteral.h
 *
 *  Created on: Feb 11, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VNULLLITERAL_H_
#define VNULLLITERAL_H_

#include "../oovisualization_api.h"

#include "VisualizationBase/headers/items/ModelItem.h"
#include "VisualizationBase/headers/items/Symbol.h"
#include "VisualizationBase/headers/Styles.h"

#include "OOModel/headers/expressions/NullLiteral.h"

namespace OOVisualization {

class OOVISUALIZATION_API VNullLiteral : public Visualization::ModelItem
{
	ITEM_COMMON_CUSTOM_STYLENAME(VNullLiteral, Visualization::ModelItem, Visualization::SymbolStyle)

	public:
		VNullLiteral(Item* parent, OOModel::NullLiteral *literal, const Visualization::SymbolStyle *style = Visualization::Styles::item<VNullLiteral>("default"));
		virtual ~VNullLiteral();

		virtual bool focusChild(FocusTarget location);

	protected:
		virtual void determineChildren();
		virtual void updateGeometry(int availableWidth, int availableHeight);

	private:
		Visualization::Symbol* vis_;
};

}

#endif /* VNULLLITERAL_H_ */