/*
********************************************************************************************
* Copyright (c) 2019 MINTROBOT Co., Ltd.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the <MINTROBOT Co, Ltd.> nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************************
**/

#include "WidgetProjectEditorNodeView.h"

//_______________________________________CONSTRUCTOR__________________________________//
WidgetProjectEditorNodeView::WidgetProjectEditorNodeView(QWidget *parent) : MTPWidget(parent) {

    // Scroll Area
    __pScrollArea = new QScrollArea(this);
    __pWidgetScrollArea = new QWidget(this);
    __pLayoutScrollArea = new QHBoxLayout();
    __pWidgetScrollArea->setLayout(__pLayoutScrollArea);
    __pWidgetIndexMarker = new QWidget(__pWidgetScrollArea);
    __pWidgetNodeList = new QWidget(__pWidgetScrollArea);
    __pLayoutScrollArea->addWidget(__pWidgetIndexMarker);
    __pLayoutScrollArea->addWidget(__pWidgetNodeList);

    // Index Marter Area
    __pLabelIndexMarker = new WidgetLabel(__pWidgetIndexMarker);

    // Node List Area
    __pWidgetNodeListDummyTop = new QWidget(__pWidgetScrollArea);
    __pVBoxLayoutNodes = new QVBoxLayout();
    __pVBoxLayoutNodes->addStretch(0);
    __pVBoxLayoutNodes->setSpacing(0);
    __pVBoxLayoutNodes->setMargin(0);
    __pWidgetNodeList->setLayout(__pVBoxLayoutNodes);
    __pVBoxLayoutNodes->addWidget(__pWidgetNodeListDummyTop);


    // Scroll Area Final Setting. This codes should be placed after setting of layouts
    __pScrollArea->setWidget(__pWidgetScrollArea);
    __pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    __pScrollArea->setStyleSheet("background-color:transparent;");


}

WidgetProjectEditorNodeView::~WidgetProjectEditorNodeView() {
    delete __pScrollArea;
}

//_______________________________________PUBLIC_______________________________________//

const QList<QString>& WidgetProjectEditorNodeView::listVariableName() {
    return __listVariableName;
}
const QHash<QUuid, WidgetUINode*>& WidgetProjectEditorNodeView::hashUINode() {
    return __hashUINode;
}

bool WidgetProjectEditorNodeView::exportToProject(ModelProject* pModelProject) {

    // Variables for handling current and previous node
    WidgetUINode* pUINodeCur;
    WidgetUINode* pUINodePrev;
    ModelNode* pModelNodeCur;
    ModelNode* pModelNodePrev;

    // Variables for handling duplicated conditional blocks
    int depthConditional = 0;
    QList<ModelNodeConditional*> listModelConditionalDepth;
    QList<ModelNodeConditional::CONDITIONALTYPE> listConditionalTypeDepth;
    QList<QList<ModelNode*>> listConditionalEndNodesDepth;

    // The routine when there are more than 2 nodes (most common situation)
    if (__listNode.size() >= 2) {
        for (int i = 1; i < __listNode.size(); i++) {
            pUINodeCur = __listNode.at(i);
            pUINodePrev = __listNode.at(i-1);
            pModelNodeCur = pUINodeCur->pModelNode;
            pModelNodePrev = pUINodePrev->pModelNode;
            pModelProject->getHashNode()->insert(pModelNodePrev->getNodeID(), pModelNodePrev);

            pModelNodePrev->nextNodeID = pModelNodeCur->getNodeID();

            // The situation that the current node is the new child node in the recent conditional block
            if (pUINodeCur->cal > pUINodePrev->cal) {
                if (ModelNode::CONDITIONAL == pModelNodePrev->getNodeType()) {
                    listModelConditionalDepth.insert(depthConditional, static_cast<ModelNodeConditional*>(pModelNodePrev));
                    listConditionalTypeDepth.insert(depthConditional,static_cast<ModelNodeConditional*>(pModelNodePrev)->conditionalType);
                    listConditionalEndNodesDepth.insert(depthConditional, QList<ModelNode*>());
                    depthConditional++;
                }
            }
            // The situation that closing conditonal block by dummy or other conditional node such as elseif or else node
            else if (pUINodeCur->cal < pUINodePrev->cal && (depthConditional > 0)) {
                listModelConditionalDepth.at(depthConditional - 1)->nextNodeID_conditionFalse = pModelNodeCur->getNodeID();
                QList<ModelNode*> childList = listConditionalEndNodesDepth.at(depthConditional - 1);
                childList.append(pModelNodePrev);

                // The situation that the current node is dummy node, which means the end of the conditional block
                if (ModelNode::DUMMY == pModelNodeCur->getNodeType()) {
                    if (ModelNodeConditional::LOOP == listConditionalTypeDepth.at(depthConditional - 1)) {
                        for (int i = 0; i < childList.size(); i++) {
                            childList.at(i)->nextNodeID = listModelConditionalDepth.at(depthConditional - 1)->getNodeID();
                        }
                    }
                    else {
                        for (int i = 0; i < childList.size(); i++) {
                            childList.at(i)->nextNodeID = pModelNodeCur->getNodeID();
                        }
                    }
                    listModelConditionalDepth.pop_back();
                    listConditionalTypeDepth.pop_back();
                    listConditionalEndNodesDepth.pop_back();
                    depthConditional--;
                }
            }
            // The situation of most general case
            else if (pUINodeCur->cal == pUINodePrev->cal) {
                // The situation of empty conditional block
                if (ModelNode::CONDITIONAL == pModelNodePrev->getNodeType() && ModelNode::CONDITIONAL == pModelNodeCur->getNodeType()) {

                    ModelNodeConditional* pModelNodeConditioanl = static_cast<ModelNodeConditional*>(pModelNodeCur);
                    ModelNodeConditional* pModelNodeConditioanlPrev = static_cast<ModelNodeConditional*>(pModelNodePrev);
                    pModelNodeConditioanlPrev->nextNodeID_conditionFalse = pModelNodeConditioanl->getNodeID();
                    pModelNodeConditioanlPrev->nextNodeID = pModelNodeConditioanl->getNodeID();
                }
                // The situation of other nodes
                else {
                    pModelNodePrev->nextNodeID = pModelNodeCur->getNodeID();
                }
            }

            if (i == __listNode.size() - 1) {
                pModelProject->getHashNode()->insert(pModelNodeCur->getNodeID(), pModelNodeCur);
            }
        }
    }
    // Routine that there is only 1 node
    else if (__listNode.size() == 1) {
        pUINodeCur = __listNode.at(0);
        pModelNodeCur = pUINodeCur->pModelNode;
        pModelProject->getHashNode()->insert(pModelNodeCur->getNodeID(), pModelNodeCur);
    }
    // Routine that there is no node
    else {
        return false;
    }
    pModelProject->IDStartNode = __listNode.at(0)->pModelNode->getNodeID();
    return true;
}

bool WidgetProjectEditorNodeView::importFromProject(ModelProject* pModelProject) {

    WidgetUINode* pUINode = nullptr;
    ModelNode* pNode = nullptr;
    ModelNode* pNodeNext = nullptr;

    // Variable for handling duplicated conditional blocks
    int depthLoop = 0;
    int depthConditional = 0;
    QList<ModelNodeConditional*> listLoopDepth;
    QList<ModelNodeConditional*> listConditionalDepth;
    QList<int> listConditionalDepthType;

    bool flagStop = false;
    bool flagNewUINode = false;
    int row = 0;
    int cal = 0;

    pNodeNext = pModelProject->getFirstNode();
    if (pNodeNext == nullptr) {
        return false;
    }


    // ----------------------------------------------------------------------------- //
    // There can be only 3 situaion in terms of the type of the next node
    // 1. Dummy which only can appear after conditional node
    // 2. Conditional node which can first or after the previous conditional node
    // 3. Other nodes which can appear anytime
    // ------------------------------------------------------------------------------//
    while (flagStop == false) {

        pNode = pNodeNext;
        flagNewUINode = true;

        // 1. The situation for dummy node
        if (ModelNode::DUMMY == pNode->getNodeType()) {

            // If the new node is dummy node, it can only appear when there was a conditional node before
            if (depthConditional > 0 || depthLoop > 0) {

                pUINode = new WidgetUINode(nullptr);
                ModelNode* pNodeConditionalFalse = nullptr;
                // The recent conditional block was loop block
                if (listConditionalDepthType.last() == 1) {
                    pNodeConditionalFalse = pModelProject->getNode(listLoopDepth.at(depthLoop - 1)->nextNodeID_conditionFalse);
                    listLoopDepth.pop_back();
                    listConditionalDepthType.pop_back();
                    depthLoop--;
                }
                // The recent conditional block was if block
                else {
                    pNodeConditionalFalse = pModelProject->getNode(listConditionalDepth.at(depthConditional - 1)->nextNodeID_conditionFalse);
                    listConditionalDepth.pop_back();
                    listConditionalDepthType.pop_back();
                    depthConditional--;
                }

                // Bellow condition means the dummy node is closing LOOP or single If block
                if (pNodeConditionalFalse->getNodeID() == pNode->getNodeID()) {
                    pUINode->setColor(SingletonColor::GetInstance().ColorNodeConditional);
                    pUINode->pModelNode = pNode;
                    pUINode->flagContainerBottom = true;
                    pUINode->cal = cal - 1;
                    pNodeNext = pModelProject->getNode(pNode->nextNodeID);
                }
                // Bellow condition means the conditional has another condition block such as elseif or else
                else {
                    pUINode->setColor(SingletonColor::GetInstance().ColorNodeConditional);
                    pUINode->pModelNode = pNode;
                    pUINode->flagContainerBottom = true;
                    pUINode->cal = cal - 1;
                    pNodeNext = pModelProject->getNode(pNode->nextNodeID);
                }
                cal--;
            }
            else {
                // If the code entered here, it means somethings wrong
            }
        }
        // 2. The situation for the conditional node
        else if (ModelNode::CONDITIONAL == pNode->getNodeType()) {

            pUINode = new WidgetUINode(nullptr);
            ModelNodeConditional* pModelNodeConditional = static_cast<ModelNodeConditional*>(pNode);

            pUINode->setColor(SingletonColor::GetInstance().ColorNodeConditional);
            pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeConditional);

            // Situation for new IF conditional block
            if (ModelNodeConditional::IF == pModelNodeConditional->conditionalType) {
                listConditionalDepth.insert(depthConditional, pModelNodeConditional);
                depthConditional++;

                pUINode->flagContainerTop = true;
                pNodeNext = pModelProject->getNode(pNode->nextNodeID);

                pUINode->cal = cal;
                cal++;
                listConditionalDepthType.append(0);
            }
            else if (ModelNodeConditional::LOOP == pModelNodeConditional->conditionalType) {

                // Situation that the process for the nodes in the current loop block has finished, so it returned back to the loop block again
                if (depthLoop > 0 && pModelNodeConditional->getNodeID() == listLoopDepth.at(depthLoop - 1)->getNodeID()) {
                    ModelNode* pNodeConditionalFalse = pModelProject->getNode(listLoopDepth.at(depthLoop - 1)->nextNodeID_conditionFalse);
                    pNodeNext = pNodeConditionalFalse;
                    delete pUINode;
                    flagNewUINode = false;
                }
                // Situation that there is new loop block
                else {
                    pUINode->flagContainerTop = true;
                    listLoopDepth.insert(depthLoop, pModelNodeConditional);
                    depthLoop++;
                    pUINode->cal = cal;
                    pNodeNext = pModelProject->getNode(pNode->nextNodeID);
                    listConditionalDepthType.append(1);
                    cal++;
                }
            }
            // ELSEIF or ELSE only
            else {
                listConditionalDepth[depthConditional - 1] = pModelNodeConditional;
                pNodeNext = pModelProject->getNode(pNode->nextNodeID);
                pUINode->flagContainerBetween = true;
                pUINode->cal = cal - 1;
            }
        }
        // 3. The situation for other nodes
        else {
            pUINode = new WidgetUINode(nullptr);

            if (ModelNode::ASSIGN_VARIABLE == pNode->getNodeType()) {
                pUINode->setColor(SingletonColor::GetInstance().ColorNodeAssignVariable);
                ModelNodeAssignVariable* pModelNodeAssignVariable = static_cast<ModelNodeAssignVariable*>(pNode);
                pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeAssignVariable);

                if (!__listVariableName.contains(pModelNodeAssignVariable->variableName)) {
                        __listVariableName.append(pModelNodeAssignVariable->variableName);
                }
            }
            else if (ModelNode::MOVE_ROBOT == pNode->getNodeType()) {
                pUINode->setColor(SingletonColor::GetInstance().ColorNodeMoveRobot);
                ModelNodeMoveRobot* pModelNodeMoveRobotJoint = static_cast<ModelNodeMoveRobot*>(pNode);
                pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeMoveRobotJoint);
            }
            else if (ModelNode::DELAY == pNode->getNodeType()) {
                pUINode->setColor(SingletonColor::GetInstance().ColorNodeDelay);
                ModelNodeDelay* pModelNodeDelay = static_cast<ModelNodeDelay*>(pNode);
                pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeDelay);
            }
            else if (ModelNode::DIGITAL_INOUT == pNode->getNodeType()) {
                pUINode->setColor(SingletonColor::GetInstance().ColorNodeDigitalIO);
                ModelNodeDigitalIO* pModelNodeSetDigitalOut = static_cast<ModelNodeDigitalIO*>(pNode);
                pUINode->pModelNode = static_cast<ModelNode*>(pModelNodeSetDigitalOut);
            }
            pNodeNext = pModelProject->getNode(pNode->nextNodeID);
            pUINode->cal = cal;
        }


        if (flagNewUINode) {
            pUINode->row = row;
            pUINode->updateText();
            __hashUINode.insert(pUINode->pModelNode->getNodeID(), pUINode);

            connect(pUINode, SIGNAL(onClickUINode(int, int)), this, SLOT(slotProcessClickedNode(int, int)));
            __listNode.insert(row, pUINode);
            __pVBoxLayoutNodes->insertWidget(row + 1, pUINode);

            pUINode->setMaximumWidth(__widthNode + pUINode->cal * __heightNode);
            pUINode->setMinimumWidth(__widthNode + pUINode->cal * __heightNode);
            pUINode->setMaximumHeight(__heightNode);
            pUINode->setMinimumHeight(__heightNode);
            row++;
        }

        if (pNodeNext == nullptr) {
            flagStop = true;
        }
    }

    __reformNodeArea();
    __renumbering();

    return true;

}

//_______________________________________PROTECTED____________________________________//
void WidgetProjectEditorNodeView::resizeEvent(QResizeEvent * event) {

    Q_UNUSED(event);

    __widthMargin = static_cast<int>(width() * __ratioMargin / 100);
    __heightMargin = static_cast<int>(height() * __ratioMargin / 100);

    __sizeIndexMarker = static_cast<int>(width() * __ratioSizeIndexMarker / 100);
    __sizeUtilityButtons = static_cast<int>(width() * __ratioSizeIndexMarker / 100);

    __widthNode = static_cast<int>(width() * __ratioWidthNode / 100);
    __heightNode = static_cast<int>(height() * __ratioHeightNode / 100);

    // Reform Node Scroll Area
    WidgetUINode* pUINode;
    for (int i = 0; i < __listNode.size(); i++) {
        pUINode = __listNode.at(i);
        pUINode->setMaximumWidth(__widthNode);
        pUINode->setMinimumWidth(__widthNode);
        pUINode->setMaximumHeight(__heightNode);
        pUINode->setMinimumHeight(__heightNode);
    }

    __pWidgetNodeListDummyTop->setGeometry(0, 0, width() - __sizeUtilityButtons - __sizeIndexMarker, __sizeIndexMarker/2);
    __pWidgetNodeListDummyTop->setMaximumWidth(width() - __sizeUtilityButtons);
    __pWidgetNodeListDummyTop->setMinimumWidth(width() - __sizeUtilityButtons);
    __pWidgetNodeListDummyTop->setMaximumHeight(__sizeIndexMarker/2);
    __pWidgetNodeListDummyTop->setMinimumHeight(__sizeIndexMarker/2);

    __reformNodeArea();

    // Place Index Marker
    QPixmap pixmap = SingletonImage::GetInstance().getPixmap(SingletonImage::GetInstance().ID_ARROW_RIGHT, __sizeIndexMarker, __sizeIndexMarker);
    __pLabelIndexMarker->setPixmap(pixmap);
    __pLabelIndexMarker->setGeometry(0, __index * __heightNode, __sizeIndexMarker, __sizeIndexMarker);

}


//_______________________________________PRIVATE______________________________________//
void WidgetProjectEditorNodeView::__reformNodeArea() {

    // calculate necessary column counts
    int heightScrollArea = __listNode.size() * __heightNode + __sizeIndexMarker;

    __pScrollArea->setGeometry(0, 0, width(), height());
    __pWidgetScrollArea->setGeometry(0, 0, width(), heightScrollArea);

    __pWidgetIndexMarker->setMaximumWidth(__sizeIndexMarker);
    __pWidgetIndexMarker->setMinimumWidth(__sizeIndexMarker);
    __pWidgetIndexMarker->setMaximumHeight(heightScrollArea);
    __pWidgetIndexMarker->setMinimumHeight(heightScrollArea);

    __pWidgetNodeList->setMaximumWidth(width());
    __pWidgetNodeList->setMinimumWidth(width());
    __pWidgetNodeList->setMaximumHeight(heightScrollArea);
    __pWidgetNodeList->setMinimumHeight(heightScrollArea);

    // reform index marker
    __pLabelIndexMarker->setGeometry(0, __index * __heightNode, __sizeIndexMarker, __sizeIndexMarker);
}

void WidgetProjectEditorNodeView::__renumbering() {
    for (int i = 0; i < __listNode.size(); i++) {
        WidgetUINode* pUINode = __listNode.at(i);
        pUINode->row = i;
        pUINode->updateText();
    }
}

void WidgetProjectEditorNodeView::__executeNode(ModelNode* pModelMode) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Execute Node",
                       pModelMode->getCommandString() + pModelMode->getArgumentsString(),
                       QMessageBox::Yes | QMessageBox::No, this,
                       Qt::FramelessWindowHint);

    msgBox.setStyleSheet("background-color: red; border: none; ");
    int res = msgBox.exec();

    if (res == QMessageBox::Ok) {
        pModelMode->execute();
    }
}

//_______________________________________SLOTS________________________________________//
void WidgetProjectEditorNodeView::slotSetNormalMode() {
    __nodeClickMode = NORMAL;
}

void WidgetProjectEditorNodeView::slotSetExecuteMode() {
    __nodeClickMode = EXECUTE;
}

void WidgetProjectEditorNodeView::slotSetEditMode() {
    __nodeClickMode = EDIT;
}

void WidgetProjectEditorNodeView::slotSetDeleteMode() {
    __nodeClickMode = REMOVE;
}

void WidgetProjectEditorNodeView::slotIndexUp() {
    __index--;
    if (__index < 0) {
        __index = 0;
    }
    __pLabelIndexMarker->setGeometry(0, __index * __heightNode, __sizeIndexMarker, __sizeIndexMarker);
}

void WidgetProjectEditorNodeView::slotIndexDown() {
    __index++;
    if (__index > __listNode.size()) {
        __index = __listNode.size();
    }
    __pLabelIndexMarker->setGeometry(0, __index * __heightNode, __sizeIndexMarker, __sizeIndexMarker);
}

void WidgetProjectEditorNodeView::slotProcessClickedNode(int row, int cal) {
    Q_UNUSED(cal);

    __index = row;

    if (__nodeClickMode == EDIT) {
        WidgetUINode* pUINode = __listNode.at(__index);
        emit signalEditNode(pUINode->pModelNode->getNodeID());
    }
    else if (__nodeClickMode == EXECUTE) {
        WidgetUINode* pUINode = __listNode.at(__index);
        ModelNode::NODETYPE nodeType = pUINode->pModelNode->getNodeType();

        switch (nodeType) {
        case ModelNode::MOVE_ROBOT:
        case ModelNode::DIGITAL_INOUT:
            __executeNode(pUINode->pModelNode);
            break;

        default:
            break;
        }
    }
    else if (__nodeClickMode == REMOVE) {
        WidgetUINode* pUINode = __listNode.at(__index);
        if (pUINode->flagContainerTop) {
            int calParent = pUINode->cal;
            bool flagBreak = false;
            __listNode.removeAt(__index);
            delete pUINode;
            while(!flagBreak) {
                pUINode = __listNode.at(__index);
                __listNode.removeAt(__index);
                if (calParent == pUINode->cal && pUINode->flagContainerBottom) {
                    flagBreak = true;
                }
                delete pUINode;
            }
        }
        else if (pUINode->flagContainerBottom) {
            int calParent = pUINode->cal;
            bool flagBreak = false;
            __listNode.removeAt(__index);
            delete pUINode;
            while(!flagBreak) {
                __index--;
                pUINode = __listNode.at(__index);
                __listNode.removeAt(__index);
                if (calParent == pUINode->cal && pUINode->flagContainerTop) {
                    flagBreak = true;
                }
                delete pUINode;
            }
        }
        else if (pUINode->flagContainerBetween) {
            int calParent = pUINode->cal;
            int calChild;
            __listNode.removeAt(__index);
            delete pUINode;
            while(true) {
                pUINode = __listNode.at(__index);
                calChild = pUINode->cal;
                if (calParent == calChild) {
                    break;
                }
                __listNode.removeAt(__index);
                delete pUINode;
            }
        }
        else {
            __listNode.removeAt(__index);
            delete pUINode;
        }
        __reformNodeArea();
        __renumbering();
    }
}


void WidgetProjectEditorNodeView::insertNode(WidgetUINode* pUINode) {

    connect(pUINode, SIGNAL(onClickUINode(int, int)), this, SLOT(slotProcessClickedNode(int, int)));
    __listNode.insert(__index, pUINode);
    __hashUINode.insert(pUINode->pModelNode->getNodeID(), pUINode);

    __pVBoxLayoutNodes->insertWidget(__index + 1, pUINode);
    pUINode->row = __index;

    // Calculate cal of new node
    WidgetUINode* pUINodeCurrent;
    int calumnCurrent;
    if (__index > 0) {
        pUINodeCurrent = __listNode.at(__index - 1);
        calumnCurrent = pUINodeCurrent->cal;

        // Situation that new elseif or else node is added bellow the existing elseif or else node
        // So, the cal will be same to the exiting elseif or else node
        if (pUINode->flagContainerBetween && (pUINodeCurrent->flagContainerTop || pUINodeCurrent->flagContainerBetween)) {
            pUINode->cal = calumnCurrent;

            // The ID of next and conditional false next node of the existing conditional node should be the ID of newly inserted node
            // Also, he ID of next and conditional flase next node of the newly inserted node should be the ID of the conditional false
            // node of the previous conditional node
            ModelNodeConditional* pNodeConditionalPrevious = static_cast<ModelNodeConditional*>(pUINodeCurrent->pModelNode);
            ModelNodeConditional* pNodeConditional = static_cast<ModelNodeConditional*>(pUINode->pModelNode);
            pNodeConditionalPrevious->nextNodeID = pNodeConditional->getNodeID();
            pNodeConditionalPrevious->nextNodeID_conditionFalse = pNodeConditional->getNodeID();
            pNodeConditional->nextNodeID = pNodeConditionalPrevious->nextNodeID_conditionFalse;
            pNodeConditional->nextNodeID_conditionFalse = pNodeConditionalPrevious->nextNodeID_conditionFalse;

        }
        // Situation that elseif or else node are newly inserted bellow the existing children node
        else if (pUINode->flagContainerBetween && calumnCurrent > 0) {
            pUINode->cal = calumnCurrent - 1;
        }
        else {
            if((pUINodeCurrent->flagContainerTop || pUINodeCurrent->flagContainerBetween) && !pUINode->flagContainerBetween) {
                pUINode->cal = calumnCurrent + 1;
            }
            else {
                pUINode->cal = calumnCurrent;
            }
        }
    }
    else {
        pUINode->cal = 0;
    }

    pUINode->setMaximumWidth(__widthNode + pUINode->cal * __heightNode);
    pUINode->setMinimumWidth(__widthNode + pUINode->cal * __heightNode);
    pUINode->setMaximumHeight(__heightNode);
    pUINode->setMinimumHeight(__heightNode);

    __index++;

    // Situation that the new node is the top of conditional node
    // So, there should be new dummy node for closing the conditional block
    if (pUINode->flagContainerTop) {
        WidgetUINode* pDummyNode = new WidgetUINode();
        pDummyNode->setColor(SingletonColor::GetInstance().ColorNodeConditional);
        pDummyNode->pModelNode = SingletonFactoryModelNode::GetInstance().createNodeDummy();
        pDummyNode->flagContainerBottom = true;

        // The the ID of next and conditional false next node of the the inserted new node should be the new dummy node
        // because there would be no children nodes at the first time
        ModelNodeConditional* pNodeConditional = static_cast<ModelNodeConditional*>(pUINode->pModelNode);
        pNodeConditional->nextNodeID = pDummyNode->pModelNode->getNodeID();
        pNodeConditional->nextNodeID_conditionFalse = pDummyNode->pModelNode->getNodeID();

        connect(pDummyNode, SIGNAL(onClickUINode(int, int)), this, SLOT(slotProcessClickedNode(int, int)));
        __listNode.insert(__index, pDummyNode);
        __pVBoxLayoutNodes->insertWidget(__index + 1, pDummyNode);
        pDummyNode->row = __index;
        pDummyNode->cal = pUINode->cal;
        pDummyNode->setMaximumWidth(__widthNode + pDummyNode->cal * __heightNode);
        pDummyNode->setMinimumWidth(__widthNode + pDummyNode->cal * __heightNode);
        pDummyNode->setMaximumHeight(__heightNode);
        pDummyNode->setMinimumHeight(__heightNode);
    }

    // Process to add varible name list
    if (ModelNode::ASSIGN_VARIABLE == pUINode->pModelNode->getNodeType()) {
        ModelNodeAssignVariable* pNodeAssignVariable = static_cast<ModelNodeAssignVariable*>(pUINode->pModelNode);
        if (!__listVariableName.contains(pNodeAssignVariable->variableName)) {
                __listVariableName.append(pNodeAssignVariable->variableName);
        }
    }
    __reformNodeArea();
    __renumbering();
}
