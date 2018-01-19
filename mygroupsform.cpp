#include "costumelightlistmodel.h"
#include "lightlistmodel.h"
#include "mygrouplistmodel.h"
#include "mygroupsform.h"
#include "ui_mygroupsform.h"
#include <algorithm>

MyGroupsForm::MyGroupsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyGroupsForm),
    index_(),
    group_()
{
    ui->setupUi(this);
    ui->rightSideBar->hide();

    myGroupModel_ = new MyGroupListModel();
    ui->listView->setModel(myGroupModel_);

    llAll_ = new LightListModel();
    ui->allLights->setModel(llAll_);

    llMY_ = new CostumeLightListModel();
    ui->myLights->setModel(llMY_);
    connect(ui->allLights, &QListView::doubleClicked, this, &MyGroupsForm::addLight);
    connect(ui->myLights, &QListView::doubleClicked, this, &MyGroupsForm::removeLight);
    connect(
        ui->form,
        &FormSingleLight::changed,
        [=](Light l, QModelIndex index){
            myGroupModel_->setGroup(index, l);
        }
    );
}

MyGroupsForm::~MyGroupsForm()
{
    delete ui;
}

void MyGroupsForm::on_addGroup_clicked()
{
    Group n;
    n.setName("New Group");
    myGroupModel_->addGroup(n);
    checkForEmptyList();
}

void MyGroupsForm::on_removeGroup_clicked()
{
    QItemSelectionModel *selectionMod = ui->listView->selectionModel();
    QModelIndexList indexS = selectionMod->selectedIndexes();
    if (!indexS.isEmpty() && indexS.first().row() >= 0 && selectionMod->isSelected(indexS.first())) {
        myGroupModel_->removeGroup(indexS.first());
        selectionMod->reset();
        checkForEmptyList();
    }
}

void MyGroupsForm::on_listView_clicked(const QModelIndex &index)
{
    QItemSelectionModel *selectionMod = ui->listView->selectionModel();
    QModelIndexList indexS = selectionMod->selectedIndexes();
    group_ = myGroupModel_->getGroup(index);
    index_ = index;
    showForm();
}

void MyGroupsForm::showForm(){
    FormSingleLight *l = static_cast<FormSingleLight*>(ui->form);
    ui->rightSideBar->show();
    auto shr_ptr = group_.lock();
    if(!shr_ptr) return;
    l->setLight(*shr_ptr, index_);
    llMY_->resetList(shr_ptr->lights());
}


void MyGroupsForm::checkForEmptyList(){
    ui->removeGroup->setDisabled(myGroupModel_->rowCount() == 0);
}

void MyGroupsForm::on_pushToMy_clicked()
{
    addLight();
    ui->removeFromMy->setDisabled(false);
}

void MyGroupsForm::on_removeFromMy_clicked()
{
    removeLight();
    auto group = group_.lock();
    if(!group) return;
    if(group->lights().size() == 0) ui->removeFromMy->setDisabled(true);
}

void MyGroupsForm::addLight(){
    auto group = group_.lock();
    if(!group) return;
    QItemSelectionModel *selectionMod = ui->allLights->selectionModel();
    QModelIndexList indexS = selectionMod->selectedIndexes();
    auto light_ptr = llAll_->lightAt(indexS.first()).lock();
    if(!light_ptr || indexS.isEmpty() || allready_contained(light_ptr) || light_ptr->parentGroup().lock()) return;
    llMY_->addLight(light_ptr);
    group->addLight(group, light_ptr);
    Light cpy = *light_ptr;
    cpy.appendStateChanges(*group);
    llAll_->setLight(indexS.first(), cpy);

}

bool MyGroupsForm::allready_contained(std::shared_ptr<Light> l){
    auto group = group_.lock();
    if(!group) return false;
    std::vector<std::weak_ptr<Light>> lights = group->lights();
    auto it = std::find_if(lights.begin(), lights.end(), [l](const std::weak_ptr<Light>& rhs) -> bool {
        auto rhS = rhs.lock();
        if(!rhS) return false;
        return l->id() == rhS->id();
    });
    return it != lights.end();
}

void MyGroupsForm::removeLight() {
    auto group = group_.lock();
    if(!group) return;
    QItemSelectionModel *selectionMod = ui->myLights->selectionModel();
    QModelIndexList indexS = selectionMod->selectedIndexes();
    if(indexS.isEmpty()) return;
    llMY_->removeLight(indexS.first());
    group->removeLight(indexS.first().row());
    selectionMod->reset();
}


