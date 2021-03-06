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
 * VMethodStyle.h
 *
 *  Created on: Feb 4, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VMETHODSTYLE_H_
#define VMETHODSTYLE_H_

#include "../oovisualization_api.h"


#include "VisualizationBase/headers/items/TextStyle.h"
#include "VisualizationBase/headers/items/VListStyle.h"
#include "VisualizationBase/headers/items/StaticStyle.h"
#include "VisualizationBase/headers/layouts/PanelBorderLayoutStyle.h"
#include "VisualizationBase/headers/layouts/SequentialLayoutStyle.h"

namespace OOVisualization {

class OOVISUALIZATION_API VMethodStyle : public Visualization::ItemStyle
{
	private:
		Visualization::PanelBorderLayoutStyle layout_;
		Visualization::TextStyle nameDefault_;
		Visualization::TextStyle namePublic_;
		Visualization::TextStyle namePrivate_;
		Visualization::TextStyle nameProtected_;
		Visualization::TextStyle nameStaticDefault_;
		Visualization::TextStyle nameStaticPublic_;
		Visualization::TextStyle nameStaticPrivate_;
		Visualization::TextStyle nameStaticProtected_;
		Visualization::StaticStyle icon_;
		Visualization::SequentialLayoutStyle header_;
		Visualization::VListStyle content_;
		Visualization::VListStyle arguments_;
		Visualization::VListStyle results_;

	public:
		void load(Visualization::StyleLoader& sl);

		const Visualization::PanelBorderLayoutStyle& layout() const;
		const Visualization::TextStyle& nameDefault() const;
		const Visualization::TextStyle& namePublic() const;
		const Visualization::TextStyle& namePrivate() const;
		const Visualization::TextStyle& nameProtected() const;
		const Visualization::TextStyle& nameStaticDefault() const;
		const Visualization::TextStyle& nameStaticPublic() const;
		const Visualization::TextStyle& nameStaticPrivate() const;
		const Visualization::TextStyle& nameStaticProtected() const;
		const Visualization::StaticStyle& icon() const;
		const Visualization::SequentialLayoutStyle& header() const;
		const Visualization::VListStyle& content() const;
		const Visualization::VListStyle& arguments() const;
		const Visualization::VListStyle& results() const;
};

inline const Visualization::PanelBorderLayoutStyle& VMethodStyle::layout() const { return layout_; }
inline const Visualization::TextStyle& VMethodStyle::nameDefault() const { return nameDefault_; }
inline const Visualization::TextStyle& VMethodStyle::namePublic() const { return namePublic_; }
inline const Visualization::TextStyle& VMethodStyle::namePrivate() const { return namePrivate_; }
inline const Visualization::TextStyle& VMethodStyle::nameProtected() const { return nameProtected_; }
inline const Visualization::TextStyle& VMethodStyle::nameStaticDefault() const { return nameStaticDefault_; }
inline const Visualization::TextStyle& VMethodStyle::nameStaticPublic() const { return nameStaticPublic_; }
inline const Visualization::TextStyle& VMethodStyle::nameStaticPrivate() const { return nameStaticPrivate_; }
inline const Visualization::TextStyle& VMethodStyle::nameStaticProtected() const { return nameStaticProtected_; }
inline const Visualization::StaticStyle& VMethodStyle::icon() const { return icon_; }
inline const Visualization::SequentialLayoutStyle& VMethodStyle::header() const { return header_; }
inline const Visualization::VListStyle& VMethodStyle::content() const { return content_; }
inline const Visualization::VListStyle& VMethodStyle::arguments() const { return arguments_; }
inline const Visualization::VListStyle& VMethodStyle::results() const { return results_; }

}

#endif /* VMETHODSTYLE_H_ */
