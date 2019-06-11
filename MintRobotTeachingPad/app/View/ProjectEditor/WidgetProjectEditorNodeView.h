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

#ifndef WIDGETPROJECTEDITORNODEVIEW_H
#define WIDGETPROJECTEDITORNODEVIEW_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QMessageBox>

#include "dialog/DialogNodeAssignVariable.h"
#include "dialog/DialogNodeMoveRobot.h"
#include "dialog/DialogNodeCondition.h"
#include "dialog/DialogNodeDelay.h"
#include "dialog/DialogNodeDigitalInOut.h"

#include "app/view/util/MTPWidget.h"
#include "app/model/project/ModelProject.h"
#include "app/model/SingletonFactoryModelNode.h"

#include "WidgetUINode.h"


class WidgetProjectEditorNodeView : public MTPWidget {

    Q_OBJECT
    typedef enum node_click_mode {
        NORMAL,
        EXECUTE,
        EDIT,
        REMOVE,
    } NODE_CLICK_MODE;


public:
    WidgetProjectEditorNodeView(QWidget *parent);
    virtual ~WidgetProjectEditorNodeView() override;

    // Function to access list in the view widget
    const QList<QString>& listVariableName();
    const QHash<QUuid, WidgetUINode*>& hashUINode();

    // Import and Export functions
    bool exportToProject(ModelProject* pModelProject);
    bool importFromProject(ModelProject* pModelProject);


protected:
    virtual void resizeEvent(QResizeEvent * event) override;


private:
    // Variables to calculate widget size
    double __ratioMargin = 3;
    double __ratioSizeIndexMarker = 3;
    double __ratioWidthNode = 60;
    double __ratioHeightNode = 5;

    int __widthMargin;
    int __heightMargin;
    int __sizeIndexMarker;
    int __sizeUtilityButtons;
    int __widthNode;
    int __heightNode;

    // Widget Members
    WidgetLabel* __pLabelIndexMarker;

    QScrollArea* __pScrollArea;
    QWidget* __pWidgetScrollArea;
    QHBoxLayout* __pLayoutScrollArea;

    QWidget* __pWidgetIndexMarker;
    QWidget* __pWidgetNodeList;
    QWidget* __pWidgetNodeListDummyTop;
    QVBoxLayout* __pVBoxLayoutNodes;


    // --- Members for new tree ---//
    // Members for node tree
    QList<WidgetUINode*> __listNode;
    QList<QString> __listVariableName;
    QHash<QUuid, WidgetUINode*> __hashUINode;

    int __index = 0;
    NODE_CLICK_MODE __nodeClickMode = NORMAL;

    void __reformNodeArea();
    void __renumbering();


    void __executeNode(ModelNode* modelNode);


signals:
    void signalEditNode(QUuid uuidEditNode);


public slots:
    // Slots when the buttons in toolbar
    void slotSetNormalMode();
    void slotSetExecuteMode();
    void slotSetEditMode();
    void slotSetDeleteMode();
    void slotIndexUp();
    void slotIndexDown();

    // Slots when UI node clicked
    void slotProcessClickedNode(int row, int cal);

    // Slots the specific actions of node view
    void insertNode(WidgetUINode* pUINode);
};

#endif // WIDGETPROJECTEDITORNODEVIEW_H
