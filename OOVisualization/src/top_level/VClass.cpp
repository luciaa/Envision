/***********************************************************************************************************************
 * VClass.cpp
 *
 *  Created on: Feb 4, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "top_level/VClass.h"
#include "OOVisualizationException.h"
#include "icons/ClassIcon.h"

#include "VisualizationBase/headers/layouts/PanelBorderLayout.h"
#include "VisualizationBase/headers/layouts/PositionLayout.h"
#include "VisualizationBase/headers/items/VText.h"
#include "VisualizationBase/headers/items/VList.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VClass)

VClass::VClass(Item* parent, NodeType* node, const StyleType* style) :
	ItemWithNode<LayoutProvider<PanelBorderLayout>, Class>(parent, node, style),
	header_( new SequentialLayout(NULL, &style->header()) ),
	icon_( new ClassIcon(NULL, &style->icon()) ),
	name_(new VText(NULL, node->nameNode(), &style->nameDefault()) ),
	baseClasses_( new VList(NULL, node->baseClasses(), &style->baseClasses()) ),
	content_( new PositionLayout(NULL, &style->content()) ),
	fieldContainer_(new SequentialLayout(NULL, &style->fieldContainer()) ),
	publicFieldArea_(new SequentialLayout(NULL, &style->publicFieldArea()) ),
	privateFieldArea_(new SequentialLayout(NULL, &style->privateFieldArea()) ),
	protectedFieldArea_(new SequentialLayout(NULL, &style->protectedFieldArea()) ),
	defaultFieldArea_(new SequentialLayout(NULL, &style->defaultFieldArea()) )
{
	layout()->setTop(true);
	layout()->top()->setFirst(header_);
	header_->append(icon_);
	header_->append(name_);
	header_->append(baseClasses_);

	layout()->setLeft(true);
	layout()->left()->setFirst(fieldContainer_);
	fieldContainer_->append(publicFieldArea_);
	fieldContainer_->append(protectedFieldArea_);
	fieldContainer_->append(defaultFieldArea_);
	fieldContainer_->append(privateFieldArea_);

	layout()->setContent(content_);
}

VClass::~VClass()
{
	// These were automatically deleted by LayoutProvider's destructor
	header_ = NULL;
	icon_ = NULL;
	name_ = NULL;
	baseClasses_ = NULL;
	content_ = NULL;
	fieldContainer_ = NULL;
	publicFieldArea_ = NULL;
	privateFieldArea_ = NULL;
	protectedFieldArea_ = NULL;
	defaultFieldArea_ = NULL;
}

void VClass::determineChildren()
{
	const TextStyle* nameStyle = NULL;

	if (node()->visibility() == Visibility::DEFAULT) nameStyle = &style()->nameDefault();
	else if (node()->visibility() == Visibility::PUBLIC) nameStyle = &style()->namePublic();
	else if (node()->visibility() == Visibility::PRIVATE) nameStyle = &style()->namePrivate();
	else if (node()->visibility() == Visibility::PROTECTED) nameStyle = &style()->nameProtected();
	else throw OOVisualizationException("Unknown visibility in VClass::determineChildren");

	// TODO: find a better way and place to determine the style of children. Is doing this causing too many updates?
	// TODO: consider the performance of this. Possibly introduce a style updated boolean for all items so that they know
	//			what's the reason they are being updated.
	// The style needs to be updated every time since if our own style changes, so will that of the children.
	layout()->setStyle( &style()->layout() );
	icon_->setStyle(&style()->icon());
	header_->setStyle( &style()->header() );
	name_->setStyle( nameStyle );
	content_->setStyle( &style()->content() );
	baseClasses_->setStyle( &style()->baseClasses() );
	fieldContainer_->setStyle( &style()->fieldContainer() );
	publicFieldArea_->setStyle( &style()->publicFieldArea() );
	privateFieldArea_->setStyle( &style()->privateFieldArea() );
	protectedFieldArea_->setStyle( &style()->protectedFieldArea() );
	defaultFieldArea_->setStyle( &style()->defaultFieldArea() );

	// Synchronize header
	header_->synchronizeMid(name_, node()->nameNode(), nameStyle, 1);
	header_->synchronizeLast(baseClasses_, node()->baseClasses(), &style()->baseClasses());

	// Synchronize methods
	content_->synchronizeWithNodes(node()->methods()->nodes().toList(), renderer());

	// Synchronize fields
	QList<Model::Node*> publicFields;
	QList<Model::Node*> privateFields;
	QList<Model::Node*> protectedFields;
	QList<Model::Node*> defaultFields;
	for (int i = 0; i< node()->fields()->size(); ++i)
	{
		if (node()->fields()->at(i)->visibility() == Visibility::PUBLIC) publicFields.append(node()->fields()->at(i));
		else if (node()->fields()->at(i)->visibility() == Visibility::PRIVATE) privateFields.append(node()->fields()->at(i));
		else if (node()->fields()->at(i)->visibility() == Visibility::PROTECTED) protectedFields.append(node()->fields()->at(i));
		else if (node()->fields()->at(i)->visibility() == Visibility::DEFAULT) defaultFields.append(node()->fields()->at(i));
		else throw OOVisualizationException("Unknown visibility value when updating VClass instance.");
	}

	publicFieldArea_->synchronizeWithNodes(publicFields, renderer());
	privateFieldArea_->synchronizeWithNodes(privateFields, renderer());
	protectedFieldArea_->synchronizeWithNodes(protectedFields, renderer());
	defaultFieldArea_->synchronizeWithNodes(defaultFields, renderer());
}

}