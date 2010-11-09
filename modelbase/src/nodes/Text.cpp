/***********************************************************************************************************************
 * Text.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "nodes/Text.h"
#include "commands/TextSet.h"

namespace Model {

NODE_DEFINE_TYPE_REGISTRATION_METHODS(Text)

Text::Text(Node *parent) :
	Node(parent)
{
}

Text::Text(Node *parent, NodeIdType id, PersistentStore &store, bool) :
	Node(parent, id)
{
	text = store.loadStringValue();
}

QString Text::get()
{
	return text;
}

void Text::set(const QString &newText)
{
	execute(new TextSet(this, &text, newText));
}

void Text::save(PersistentStore &store)
{
	store.saveStringValue(text);
}

}