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
 * VBreakStatementCF.cpp
 *
 *  Created on: Feb 25, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "items/VBreakStatementCF.h"

#include "OOModel/headers/statements/BreakStatement.h"

using namespace Visualization;
using namespace OOModel;
using namespace OOVisualization;

namespace ControlFlowVisualization {

ITEM_COMMON_DEFINITIONS(VBreakStatementCF, "item")

VBreakStatementCF::VBreakStatementCF(Item* parent, NodeType* node, const StyleType* style) :
	ItemWithNode<ControlFlowItem, BreakStatement>(parent, node, style),
	vis_(nullptr)
{
}

VBreakStatementCF::~VBreakStatementCF()
{
	SAFE_DELETE_ITEM(vis_);
}

void VBreakStatementCF::determineChildren()
{
	synchronizeItem<VBreakStatement>(vis_, node(), nullptr);
}

void VBreakStatementCF::updateGeometry(int availableWidth, int availableHeight)
{
	clearConnectors();
	breaks_.clear();

	if (! showAsControlFlow() )
	{
		Item::updateGeometry(vis_, availableWidth, availableHeight);
		return;
	}
	else
	{
		vis_->setPos(style()->pinLength(), style()->pinLength());
		setSize(vis_->width() + 2*style()->pinLength(), vis_->height() + 2*style()->pinLength());
	}

	if (preferredBreakExit_ == ControlFlowItem::EXIT_LEFT)
	{
		breaks_.append( QPoint(0, height()/2));
		addConnector(breaks_.first() + QPoint(style()->pinLength(),0), breaks_.first(), false);
	}
	else
	{
		breaks_.append( QPoint(width(), height()/2));
		addConnector(breaks_.first()- QPoint(style()->pinLength(),0), breaks_.first(), false);
	}

	entrance_ = QPoint(width()/2, 0);
	exit_ = QPoint(0,0);
	addConnector(entrance_, entrance_ + QPoint(0, style()->pinLength()), true);
}

bool VBreakStatementCF::focusChild(FocusTarget location)
{
	return vis_->focusChild(location);
}

}
