/***********************************************************************************************************************
 * VMethod.h
 *
 *  Created on: Feb 4, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VMETHOD_H_
#define VMETHOD_H_

#include "../oovisualization_api.h"
#include "VMethodStyle.h"

#include "OOModel/headers/top_level/Method.h"

#include "VisualizationBase/headers/items/ItemWithNode.h"
#include "VisualizationBase/headers/items/LayoutProvider.h"
#include "VisualizationBase/headers/Styles.h"

namespace Visualization {
	class VText;
	class VList;
	class PanelBorderLayout;
}

namespace OOVisualization {

class MethodIcon;

class OOVISUALIZATION_API VMethod : public Visualization::ItemWithNode< Visualization::LayoutProvider<Visualization::PanelBorderLayout>, OOModel::Method>
{
	ITEM_COMMON(VMethod)

	public:
		VMethod(Item* parent, NodeType* node, const StyleType* style = Visualization::Styles::item<VMethod>("default"));
		virtual ~VMethod();

	protected:
		void determineChildren();

	private:
		Visualization::SequentialLayout* header_;
		MethodIcon* icon_;
		Visualization::VText* name_;
		Visualization::VList* arguments_;
		Visualization::VList* content_;
		Visualization::VList* results_;
};

}

#endif /* VMETHOD_H_ */