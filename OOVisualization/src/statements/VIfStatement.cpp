/***********************************************************************************************************************
 * VIfStatement.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "statements/VIfStatement.h"

#include "VisualizationBase/headers/layouts/PanelBorderLayout.h"
#include "VisualizationBase/headers/layouts/SequentialLayout.h"
#include "VisualizationBase/headers/icons/SVGIcon.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VIfStatement)

VIfStatement::VIfStatement(Item* parent, NodeType* node, const StyleType* style) :
	ItemWithNode<LayoutProvider<PanelBorderLayout>, IfStatement>(parent, node, style),
	header(new SequentialLayout(NULL, &style->header())),
	conditionBackground(new SequentialLayout(NULL, &style->condition())),
	condition(NULL),
	content(new SequentialLayout(NULL, &style->content())),
	thenBranchBackground(new SequentialLayout(NULL, &style->thenBranch())),
	elseBranchBackground(NULL),
	thenBranch(NULL),
	elseBranch(NULL)
{
	layout()->setTop(true);
	layout()->top()->setFirst(header);
	header->append(new SVGIcon(NULL, &style->icon()));
	header->append(conditionBackground);
	layout()->setContent(content);
	content->append(thenBranchBackground);
}

VIfStatement::~VIfStatement()
{
	// These were automatically deleted by LayoutProvider's destructor
	header = NULL;
	conditionBackground = NULL;
	condition = NULL;
	content = NULL;
	thenBranchBackground = NULL;
	elseBranchBackground = NULL;
	thenBranch = NULL;
	elseBranch = NULL;
}

void VIfStatement::determineChildren()
{
	conditionBackground->synchronizeFirst(condition, node()->condition());
	thenBranchBackground->synchronizeFirst(thenBranch, node()->thenBranch());

	// TODO Find a better way to synchronize the Else background. Perhaps use make a new layout for Single items. That
	// would be more of a shape provider.

	if (elseBranch && elseBranch->node() != node()->elseBranch())
	{
		content->removeAll(elseBranchBackground);
		elseBranch = NULL;
		elseBranchBackground = NULL;
	}

	if (!elseBranch && node()->elseBranch())
	{
		elseBranchBackground = new SequentialLayout(NULL, &style()->elseBranch());
		elseBranch = renderer()->render(NULL, node()->elseBranch());
		elseBranchBackground->append(elseBranch);
		content->append(elseBranchBackground);
	}

	// TODO: find a better way and place to determine the style of children. Is doing this causing too many updates?
	// TODO: consider the performance of this. Possibly introduce a style updated boolean for all items so that they know
	//			what's the reason they are being updated.
	// The style needs to be updated every time since if our own style changes, so will that of the children.
	layout()->setStyle(&style()->layout());
	header->setStyle(&style()->header());
	header->at<SVGIcon>(0)->setStyle(&style()->icon());
	conditionBackground->setStyle( &style()->condition() );
	content->setStyle(&style()->content());
	thenBranchBackground->setStyle( &style()->thenBranch() );
}

}