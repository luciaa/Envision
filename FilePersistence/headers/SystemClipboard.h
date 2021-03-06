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
 * SystemClipboard.h
 *
 *  Created on: Jan 21, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef SYSTEMCLIPBOARD_H_
#define SYSTEMCLIPBOARD_H_

#include "filepersistence_api.h"
#include "XMLModel.h"

#include "ModelBase/headers/persistence/ClipboardStore.h"

namespace Model { class PersistedNode; }

namespace FilePersistence {

class FILEPERSISTENCE_API SystemClipboard : public Model::ClipboardStore
{
	public:
		SystemClipboard();
		virtual ~SystemClipboard();

		// Methods from Persistent Store
		virtual void saveStringValue(const QString &value);
		virtual void saveIntValue(int value);
		virtual void saveDoubleValue(double value);
		virtual void saveNode(const Model::Node *node, const QString &name, bool partialLoadHint);

		virtual QList<Model::LoadedNode> loadAllSubNodes(Model::Node* parent);
		virtual Model::Node* loadSubNode(Model::Node* parent, const QString& name);
		virtual QString currentNodeType() const;
		virtual QList<Model::LoadedNode> loadPartialNode(Model::Node* partialNode);
		virtual Model::PersistedNode* loadCompleteNodeSubtree(const QString& modelName, Model::NodeIdType persistenceUnitId, Model::NodeIdType nodeId);

		virtual int loadIntValue();
		virtual QString loadStringValue();
		virtual double loadDoubleValue();

		// Methods from ClipboardStore
		virtual void putNode(const Model::Node* node);
		virtual void putNodes(const QList<const Model::Node*>& nodes);

		virtual bool readClipboard();
		virtual int numNodes() const;
		virtual bool hasNext() const;
		virtual void next();
		virtual Model::Node* create(Model::Model* model, Model::Node* parent);

	protected:
		virtual void saveModel(Model::Model* model, const QString &name);
		virtual Model::Node* loadModel(Model::Model* model, const QString &name);

	private:
		XMLModel* xml;
		int numNodes_;

		void saveNodeFromOldStore(Model::PersistedNode* node);
		Model::LoadedNode loadNode(Model::Node* parent);
};

}

#endif /* SYSTEMCLIPBOARD_H_ */
