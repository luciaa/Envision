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
 * TextRenderer.h
 *
 *  Created on: Jan 12, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef TEXTRENDERER_H_
#define TEXTRENDERER_H_

#include "../visualizationbase_api.h"

#include "Item.h"
#include "ItemMacros.h"
#include "TextStyle.h"
#include "ModelBase/headers/nodes/Node.h"

namespace Visualization {

class VISUALIZATIONBASE_API TextRenderer : public Item
{
	ITEM_COMMON_CUSTOM_STYLENAME(TextRenderer, TextStyle)

	private:
			QString text_;

			qreal xOffset;
			qreal yOffset;

			bool editable;

			/**
			 * selectionBegin and selectionEnd indicate the character positions at which the selection begins and ends. If
			 * the user selected the text by dragging from right to left then selectionEnd < selectionBegin.
			 *
			 * If the entire text is selected then selectionBegin=0 and selectionEnd=text.length() (or vice versa).
			 */
			static int selectionBegin;
			static int selectionEnd;

			/**
			 * selectionXBegin and selectionXEnd indicate the beginning and end (along the X direction) where the selection
			 * background must be drawn.
			 */
			static int selectionXBegin;
			static int selectionXEnd;

			static int caretX;

		protected:
			virtual void determineChildren();
			virtual void updateGeometry(int availableWidth, int availableHeight);

			/**
			 * Returns the text of that is represented by the current item.
			 *
			 * This is an up-to-date value that may differ from the value of text(). E.G. If this is an instance of
			 * ItemWithNode<TextRenderer, Text> and the text of the node has just changed, this method will returned the
			 * current value of the node, whereas text() will still return the old value.
			 *
			 * When the TextRenderer is updated the value returned by currentText() is cached and will be subsequently
			 * returned by text() and visualized on the screen.
			 */
			virtual QString currentText() = 0;

		public:
			TextRenderer(Item* parent, const StyleType *style, const QString& text = QString());

			/**
			 * Sets the text of this item.
			 *
			 * Returns true if the text has been set, false otherwise.
			 *
			 * @param newText
			 * 				the string to set as the new text.
			 */
			virtual bool setText(const QString& newText);

			/**
			 * Returns the text of that is currently cached in this TextRenderer item.
			 *
			 * This is the last string that was visualized by this TextRenderer. This could be different compared to the
			 * value of the text represented by this Item. E.G. If this is an instance of ItemWithNode<TextRenderer, Text>
			 * and the text of the node has changed, this change is not automatically reflected. Only when the TextRenderer
			 * is updated will the new text be cached.
			 */
			QString text();
			QString selectedText();

			bool isEditable();
			void setEditable(bool editable);

			virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

			void selectAll();
			void setSelectedByDrag(int xBegin, int xEnd);
			void setSelectedCharacters(int first, int last);
			void setCaretPosition(int beforeCharacter);

			static int caretPosition();
			static int selectionFirstInxed();
			static int selectionLastIndex();

};


inline QString TextRenderer::text() { return text_; }
inline bool TextRenderer::isEditable() { return editable; }
inline void TextRenderer::setEditable(bool editable_) { editable = editable_; }
inline int TextRenderer::selectionFirstInxed() { return selectionBegin < selectionEnd ? selectionBegin : selectionEnd; }
inline int TextRenderer::selectionLastIndex() { return selectionBegin > selectionEnd ? selectionBegin : selectionEnd; }
inline int TextRenderer::caretPosition() { return selectionEnd; }
inline void TextRenderer::setCaretPosition(int beforeCharacter) { setSelectedCharacters(beforeCharacter,beforeCharacter);}

}

#endif /* TEXTRENDERER_H_ */
