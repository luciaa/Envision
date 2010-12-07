/***********************************************************************************************************************
 * NameChange.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "commands/NameChange.h"
#include "nodes/Node.h"
#include "Model.h"

namespace Model {

NameChange::NameChange(Node *target, const QString& oldName_, const QString& newName_, UndoCommand* command_) :
	UndoCommand(target, "Change name"), oldName(oldName_), newName(newName_), command(command_)
{
}

NameChange::~NameChange()
{
	delete command;
}

void NameChange::redo()
{
	command->redo();
	UndoCommand::getTarget()->getModel()->emitNameModified(UndoCommand::getTarget(), oldName);
}

void NameChange::undo()
{
	command->undo();
	UndoCommand::getTarget()->getModel()->emitNameModified(UndoCommand::getTarget(), newName);
}

}