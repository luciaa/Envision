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
 * VLibrary.cpp
 *
 *  Created on: Feb 9, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "top_level/VLibrary.h"

#include "VisualizationBase/headers/layouts/PanelBorderLayout.h"
#include "VisualizationBase/headers/layouts/PositionLayout.h"
#include "VisualizationBase/headers/items/VText.h"
#include "VisualizationBase/headers/items/Static.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VLibrary, "item")

VLibrary::VLibrary(Item* parent, OOModel::Library* node, const VLibraryStyle* style) :
	ItemWithNode<LayoutProvider<PanelBorderLayout>, Library>(parent, node, style),
	header(new SequentialLayout(nullptr, &style->header())),
	name( new VText(nullptr, node->nameNode(), &style->name())),
	content(new PositionLayout(nullptr, &style->content()))
{
	layout()->setTop(true);
	layout()->top()->setMiddle(header);
	header->append(new Static(nullptr, &style->icon()));
	header->append(name);
	layout()->setContent(content);
}

VLibrary::~VLibrary()
{
	// These were automatically deleted by LayoutProvider's destructor
	header = nullptr;
	name = nullptr;
	content = nullptr;
}

void VLibrary::determineChildren()
{
	// TODO: find a better way and place to determine the style of children. Is doing this causing too many updates?
	// TODO: consider the performance of this. Possibly introduce a style updated boolean for all items so that they know
	//			what's the reason they are being updated.
	// The style needs to be updated every time since if our own style changes, so will that of the children.
	header->setStyle(&style()->header());
	name->setStyle(&style()->name());
	content->setStyle(&style()->content());
	layout()->setStyle(&style()->layout());
	header->at<Static>(0)->setStyle(&style()->icon());

	header->synchronizeMid(name, node()->nameNode(), &style()->name(), 1);

	QList<Model::Node*> nodes;
	for (int k = 0; k<node()->projects()->size(); ++k) nodes.append(node()->projects()->at(k));
	for (int k = 0; k<node()->libraries()->size(); ++k) nodes.append(node()->libraries()->at(k));
	for (int k = 0; k<node()->modules()->size(); ++k) nodes.append(node()->modules()->at(k));
	for (int k = 0; k<node()->classes()->size(); ++k) nodes.append(node()->classes()->at(k));
	content->synchronizeWithNodes(nodes, renderer());
}

}
