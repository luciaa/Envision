/***********************************************************************************************************************
 * VProjectStyle.cpp
 *
 *  Created on: Feb 2, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "top_level/VProjectStyle.h"
#include "VisualizationBase/headers/Styles.h"

namespace OOVisualization {

VProjectStyle* VProjectStyle::getDefault()
{
	static VProjectStyle defaultStyle;
	return &defaultStyle;
}

void VProjectStyle::load()
{
	ItemStyle::load();
	Visualization::Styles::load("layout", layout_);
	Visualization::Styles::load("header", header_);
	Visualization::Styles::load("name", name_);
	Visualization::Styles::load("icon", icon_);
	Visualization::Styles::load("content", content_);
}

}