/***********************************************************************************************************************
**
** Copyright (c) 2011, ETH Zurich
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
** following conditions are met:
**
**    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
**      disclaimer.
**    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
**      following disclaimer in the documentation and/or other materials provided with the distribution.
**    * Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products
**      derived from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
***********************************************************************************************************************/

/***********************************************************************************************************************
 * VField.cpp
 *
 *  Created on: Feb 4, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "elements/VField.h"
#include "OOVisualizationException.h"

#include "VisualizationBase/headers/items/VText.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VField, "item")

VField::VField(Item* parent, NodeType* node, const StyleType* style) :
	ItemWithNode< LayoutProvider<>, Field >(parent, node, style),
	name_(new VText(nullptr, node->nameNode(), &style->nameDefault()) ),
	type_(nullptr)
{
	layout()->append(name_);
}

VField::~VField()
{
	// These were automatically deleted by LayoutProvider's destructor
	name_ = nullptr;
	type_ = nullptr;
}

void VField::determineChildren()
{
	const TextStyle* nameStyle = nullptr;
	if (node()->storageSpecifier() == StorageSpecifier::INSTANCE_VARIABLE)
	{
		if (node()->visibility() == Visibility::DEFAULT) nameStyle = &style()->nameDefault();
		else if (node()->visibility() == Visibility::PRIVATE) nameStyle = &style()->namePrivate();
		else if (node()->visibility() == Visibility::PROTECTED) nameStyle = &style()->nameProtected();
		else if (node()->visibility() == Visibility::PUBLIC) nameStyle = &style()->namePublic();
		else throw OOVisualizationException("Unknown visibility type in VField::determineChildren");
	}
	else if (node()->storageSpecifier() == StorageSpecifier::CLASS_VARIABLE)
	{
		if (node()->visibility() == Visibility::DEFAULT) nameStyle = &style()->nameStaticDefault();
		else if (node()->visibility() == Visibility::PRIVATE) nameStyle = &style()->nameStaticPrivate();
		else if (node()->visibility() == Visibility::PROTECTED) nameStyle = &style()->nameStaticProtected();
		else if (node()->visibility() == Visibility::PUBLIC) nameStyle = &style()->nameStaticPublic();
		else throw OOVisualizationException("Unknown visibility type in VField::determineChildren");
	}
	else throw OOVisualizationException("Unknown static type in VField::determineChildren");

	layout()->synchronizeFirst(name_, node()->nameNode(), nameStyle);
	layout()->synchronizeLast(type_, node()->type());

	// TODO: find a better way and place to determine the style of children. Is doing this causing too many updates?
	// TODO: consider the performance of this. Possibly introduce a style updated boolean for all items so that they know
	//			what's the reason they are being updated.
	// The style needs to be updated every time since if our own style changes, so will that of the children.
	layout()->setStyle( &style()->layout() );
	name_->setStyle(nameStyle);
}
}
