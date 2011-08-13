/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#include "AppVerify.h"
#include "ConvolutionMatrixWidget.h"
#include "DynamicObject.h"
#include "DesktopServices.h"
#include "Executable.h"
#include "LayerList.h"
#include "PlugInArgList.h"
#include "PlugInResource.h"
#include "ProgressResource.h"
#include "RasterElement.h"
#include "RasterLayer.h"
#include "SpatialDataView.h"

#include <ossim/matrix/newmat.h>
#include <QtGui/QBitmap>
#include <QtGui/QHeaderView>
#include <QtGui/QMessageBox>

namespace
{
   /* XPM */
   const char* const lock_xpm[] = {
      "32 22 62 1",
      " 	c None",
      ".	c #FFFFFF",
      "+	c #FBFEFF",
      "@	c #FAFAFD",
      "#	c #E8DB99",
      "$	c #E1E4EC",
      "%	c #E0ECF6",
      "&	c #D5F0F1",
      "*	c #D1C795",
      "=	c #D0D7E6",
      "-	c #CEC48B",
      ";	c #C9FFFF",
      ">	c #C7D0D9",
      ",	c #C6D2ED",
      "'	c #C5CFD8",
      ")	c #C3BB8C",
      "!	c #C1B784",
      "~	c #C0CBD4",
      "{	c #B6C2CC",
      "]	c #B3BFCA",
      "^	c #ACB9C4",
      "/	c #A9B7C2",
      "(	c #A2B0BC",
      "_	c #A1AFB9",
      ":	c #9FAEBA",
      "<	c #9CABB8",
      "[	c #97A7B4",
      "}	c #95A5B2",
      "|	c #92A2B0",
      "1	c #8D9EAC",
      "2	c #8B9CAA",
      "3	c #8A9A9F",
      "4	c #889AA8",
      "5	c #8897A2",
      "6	c #878C99",
      "7	c #8395A4",
      "8	c #8093A2",
      "9	c #7E91A0",
      "0	c #7D9A9F",
      "a	c #7C8396",
      "b	c #798D9C",
      "c	c #768A9A",
      "d	c #738898",
      "e	c #71838F",
      "f	c #6C8192",
      "g	c #697F90",
      "h	c #656351",
      "i	c #62798A",
      "j	c #607789",
      "k	c #5E7587",
      "l	c #5E727E",
      "m	c #4E6370",
      "n	c #4B4B45",
      "o	c #4B4B43",
      "p	c #4B4A42",
      "q	c #415864",
      "r	c #374F5C",
      "s	c #2F4755",
      "t	c #2F343A",
      "u	c #294250",
      "v	c #23262C",
      "w	c #161A25",
      "                                ",
      "                                ",
      "                                ",
      "            nwwwwhh             ",
      "          tt3...$66v            ",
      "          tt3...$66v            ",
      "         n00&wwww==ann          ",
      "         w;;w    ww,ww          ",
      "         w;;w    ww,ww          ",
      "         w;;w    ww,ww          ",
      "       wwwwwwwwwwwwwwww         ",
      "       wwwwwwwwwwwwwwww         ",
      "       ww'~~{^^([117bbw         ",
      "       wwsssrqqmlee5__w         ",
      "       wwsssrqqmlee5__w         ",
      "       ww]//:[[17ccfiiw         ",
      "       wwsssrqqmlee5__w         ",
      "       wwsssrqqmlee5__w         ",
      "       ww:111bbcgjjkkkw         ",
      "       wwwwwwwwwwwwwwww         ",
      "       wwwwwwwwwwwwwwww         ",
      "                                "};

      /* XPM */
      const char* const unlock_xpm[] = {
         "32 22 59 1",
         " 	c None",
         ".	c #FFFFFF",
         "+	c #FBFEFF",
         "@	c #F9FAFD",
         "#	c #E1E4EC",
         "$	c #E0ECF6",
         "%	c #D5F0F1",
         "&	c #D0D7E6",
         "*	c #C9FFFF",
         "=	c #C7D0D9",
         "-	c #C6D2ED",
         ";	c #C6D0D9",
         ">	c #C5CFD8",
         ",	c #C0CBD4",
         "'	c #B6C2CC",
         ")	c #B3BFCA",
         "!	c #B1BAC3",
         "~	c #ACB9C4",
         "{	c #A9B7C2",
         "]	c #A6AEB8",
         "^	c #A2B0BC",
         "/	c #A1AFB9",
         "(	c #9FAEBA",
         "_	c #9CABB8",
         ":	c #97A7B4",
         "<	c #95A5B2",
         "[	c #92A2B0",
         "}	c #8D9EAC",
         "|	c #8B9CAA",
         "1	c #8A9A9F",
         "2	c #889AA8",
         "3	c #8898A2",
         "4	c #8395A4",
         "5	c #8093A2",
         "6	c #7E91A0",
         "7	c #7D9A9F",
         "8	c #7C8396",
         "9	c #7A7F8C",
         "0	c #798D9C",
         "a	c #768A9A",
         "b	c #738898",
         "c	c #71838F",
         "d	c #6C8192",
         "e	c #697F90",
         "f	c #62798A",
         "g	c #607789",
         "h	c #5E7587",
         "i	c #5E727E",
         "j	c #585F69",
         "k	c #4E6370",
         "l	c #4D535D",
         "m	c #424852",
         "n	c #415864",
         "o	c #374F5C",
         "p	c #2F4755",
         "q	c #2C333D",
         "r	c #294250",
         "s	c #212530",
         "t	c #161A25",
         "                                ",
         "                                ",
         "                                ",
         "                 mmttttjj       ",
         "                q11...#99s      ",
         "                q11...#99s      ",
         "               m7%%tttt&&8ll    ",
         "               t*tt    tt-tt    ",
         "               t*tt    tt-tt    ",
         "               t*tt    tt-tt    ",
         "    tttttttttttttttt   ttttt    ",
         "    tttttttttttttttt   ttttt    ",
         "    tt>,,'~~^::}400t            ",
         "    ttppponnkiic3]]t            ",
         "    ttppponnkiic3]]t            ",
         "    tt){{(::}44adfft            ",
         "    ttppponnkiic3((t            ",
         "    ttppponnkiic3((t            ",
         "    tt(}}}00aeeghhht            ",
         "    tttttttttttttttt            ",
         "    tttttttttttttttt            ",
         "                                "};

   int sliderToSize(int slider)
   {
      return slider * 2 + 1;
   }

   int sizeToSlider(int size)
   {
      return (size - 1) / 2;
   }
}

NumberItem::NumberItem() : QTableWidgetItem("0", NumberItem::Type)
{
}

NumberItem::NumberItem(const NumberItem& other) : QTableWidgetItem(other)
{
}

NumberItem::~NumberItem()
{
}

QTableWidgetItem* NumberItem::clone() const
{
   NumberItem* pItem = new NumberItem(*this);
   pItem->setData(Qt::EditRole, data(Qt::EditRole));
   return pItem;
}

void NumberItem::setData(int role, const QVariant& value)
{
   bool ok = true;
   if (role == Qt::DisplayRole || role == Qt::EditRole)
   {
      QString tmp = value.toString();
      tmp.toDouble(&ok);
      if (!ok)
      {
         tmp.toInt(&ok);
      }
   }
   if (ok)
   {
      QTableWidgetItem::setData(role, value);
   }
}

ConvolutionMatrixWidget::ConvolutionMatrixWidget(QWidget* pParent) : QWidget(pParent)
{
   setupUi(this);

   QPixmap lockPixmap(lock_xpm);
   lockPixmap.setMask(lockPixmap.createHeuristicMask());
   mpLockIcon = new QIcon(lockPixmap);
   QPixmap unlockPixmap(unlock_xpm);
   unlockPixmap.setMask(unlockPixmap.createHeuristicMask());
   mpUnlockIcon = new QIcon(unlockPixmap);

   QPalette palette = mpFilter->palette();
   NumberItem* pProto = new NumberItem();
   pProto->setTextAlignment(Qt::AlignCenter);
   pProto->setBackgroundColor(palette.color(QPalette::Base));
   mpFilter->setItemPrototype(pProto);
   palette.setColor(QPalette::Base, palette.color(QPalette::Window));
   mpFilter->setPalette(palette);
   mpFilter->verticalHeader()->hide();
   mpFilter->verticalHeader()->setDefaultSectionSize(mpFilter->fontMetrics().height());
   mpFilter->horizontalHeader()->hide();
   mpFilter->horizontalHeader()->setDefaultSectionSize(mpFilter->fontMetrics().width("00.000"));

   mpPresetButtons->addButton("Load", QDialogButtonBox::ActionRole);
   mpPresetButtons->addButton("Remove", QDialogButtonBox::DestructiveRole);

   VERIFYNR(connect(mpLink, SIGNAL(toggled(bool)), this, SLOT(linkToggled(bool))));
   VERIFYNR(connect(mpWidthSlider, SIGNAL(valueChanged(int)), this, SLOT(resizeFilter())));
   VERIFYNR(connect(mpHeightSlider, SIGNAL(valueChanged(int)), this, SLOT(resizeFilter())));
   VERIFYNR(connect(mpMatrixButtons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(matrixButtonPressed(QAbstractButton*))));
   VERIFYNR(connect(mpPresetButtons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(presetButtonPressed(QAbstractButton*))));

   setMinimumHeight(50);

   linkToggled(true);
   resizeFilter();

   loadFromConfigurationSettings();
}

ConvolutionMatrixWidget::~ConvolutionMatrixWidget()
{
}

void ConvolutionMatrixWidget::resizeFilter()
{
   mpFilter->setColumnCount(sliderToSize(mpWidthSlider->value()));
   mpFilter->setRowCount(sliderToSize(mpHeightSlider->value()));
   for (int row = 0; row < mpFilter->rowCount(); ++row)
   {
      for (int col = 0; col < mpFilter->columnCount(); ++col)
      {
         if (mpFilter->item(row, col) == NULL)
         {
            mpFilter->setItem(row, col, mpFilter->itemPrototype()->clone());
         }
      }
   }
}

void ConvolutionMatrixWidget::linkToggled(bool locked)
{
   mpLink->setIcon(locked ? *mpLockIcon : *mpUnlockIcon);
   if (locked)
   {
      VERIFYNR(connect(mpWidthSlider, SIGNAL(valueChanged(int)), mpHeightSlider, SLOT(setValue(int))));
      VERIFYNR(connect(mpHeightSlider, SIGNAL(valueChanged(int)), mpWidthSlider, SLOT(setValue(int))));
      int height = mpHeightSlider->value();
      int width = mpWidthSlider->value();
      if (height < width)
      {
         mpWidthSlider->setValue(height);
         resizeFilter();
      }
      else if (width < height)
      {
         mpHeightSlider->setValue(width);
         resizeFilter();
      }
   }
   else
   {
      VERIFYNR(disconnect(mpWidthSlider, SIGNAL(valueChanged(int)), mpHeightSlider, SLOT(setValue(int))));
      VERIFYNR(disconnect(mpHeightSlider, SIGNAL(valueChanged(int)), mpWidthSlider, SLOT(setValue(int))));
   }
}

void ConvolutionMatrixWidget::matrixButtonPressed(QAbstractButton* pButton)
{
   if (mpMatrixButtons->buttonRole(pButton) == QDialogButtonBox::ResetRole)
   {
      mpWidthSlider->setValue(0);
      mpLink->setChecked(true);
      linkToggled(true);
      mpFilter->clear();
      resizeFilter();
      mpDivisor->setValue(1.0);
      mpFilterName->setEditText(QString());
   }
   else if (mpMatrixButtons->buttonRole(pButton) == QDialogButtonBox::ApplyRole)
   {
      NEWMAT::Matrix kernel = getCurrentMatrix() / mpDivisor->value();

      // execute convolution
      ProgressResource progress("Convolve data");
      SpatialDataView* pView = dynamic_cast<SpatialDataView*>(
         Service<DesktopServices>()->getCurrentWorkspaceWindowView());
      if (pView == NULL)
      {
         progress->updateProgress("Active view is not a spatial data view.", 0, ERRORS);
         return;
      }
      RasterLayer* pLayer = dynamic_cast<RasterLayer*>(pView->getActiveLayer());
      RasterElement* pRaster = (pLayer == NULL) ? NULL : static_cast<RasterElement*>(pLayer->getDataElement());
      if (pRaster == NULL)
      {
         pRaster = pView->getLayerList()->getPrimaryRasterElement();
      }
      VERIFYNRV(pRaster != NULL);
      ExecutableResource pConv("Generic Convolution", std::string(), progress.get(), false);
      if (pConv->getPlugIn() == NULL)
      {
         progress->updateProgress("Generic convolution plug-in is not available.", 0, ERRORS);
         return;
      }
      pConv->getInArgList().setPlugInArgValue(Executable::DataElementArg(), pRaster);
      pConv->getInArgList().setPlugInArgValue(Executable::ViewArg(), pView);
      std::string resultName = pRaster->getName() + ":Convolved";
      pConv->getInArgList().setPlugInArgValue("Result Name", &resultName);
      pConv->getInArgList().setPlugInArgValueLoose("Kernel", &kernel);
      pConv->execute();
   }
}

void ConvolutionMatrixWidget::presetButtonPressed(QAbstractButton* pButton)
{
   if (mpPresetButtons->buttonRole(pButton) == QDialogButtonBox::AcceptRole) // Save
   {
      QString filterName = mpFilterName->currentText();
      if (!filterName.isEmpty())
      {
         mPresets[filterName] = qMakePair(getCurrentMatrix(), mpDivisor->value());
         if (mpFilterName->findText(mpFilterName->currentText()) == -1)
         {
            mpFilterName->addItem(mpFilterName->currentText());
         }
         saveToConfigurationSettings();
      }
   }
   else if (mpPresetButtons->buttonRole(pButton) == QDialogButtonBox::DestructiveRole) // Remove
   {
      QString filterName = mpFilterName->currentText();
      QMap<QString, QPair<NEWMAT::Matrix, double> >::iterator pos = mPresets.find(filterName);
      if (pos != mPresets.end() &&
          (QMessageBox::question(this, "Confirm removal",
           QString("Are you sure you want to remove the %1 filter?").arg(filterName),
           QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes))
      {
         mpFilterName->removeItem(mpFilterName->currentIndex());
         mPresets.erase(pos);
         saveToConfigurationSettings();
      }
   }
   else if (mpPresetButtons->buttonRole(pButton) == QDialogButtonBox::ActionRole) // Load
   {
      QString filterName = mpFilterName->currentText();
      QMap<QString, QPair<NEWMAT::Matrix, double> >::iterator pos = mPresets.find(filterName);
      if (pos != mPresets.end())
      {
         NEWMAT::Matrix kernel = pos->first;
         mpLink->setChecked(kernel.Nrows() == kernel.Ncols());
         mpHeightSlider->setValue(sizeToSlider(kernel.Nrows()));
         mpWidthSlider->setValue(sizeToSlider(kernel.Ncols()));
         for (int row = 0; row < kernel.Nrows(); ++row)
         {
            for (int col = 0; col < kernel.Ncols(); ++col)
            {
               mpFilter->item(row, col)->setData(Qt::DisplayRole, QVariant(kernel(row+1, col+1)));
            }
         }
         mpDivisor->setValue(pos->second);
      }
   }
}

NEWMAT::Matrix ConvolutionMatrixWidget::getCurrentMatrix() const
{
   NEWMAT::Matrix kernel(mpFilter->rowCount(), mpFilter->columnCount());
   for (int row = 0; row < kernel.Nrows(); ++row)
   {
      for (int col = 0; col < kernel.Ncols(); ++col)
      {
         kernel(row+1, col+1) = mpFilter->item(row, col)->data(Qt::DisplayRole).toDouble();
      }
   }
   return kernel;
}

void ConvolutionMatrixWidget::saveToConfigurationSettings() const
{
   FactoryResource<DynamicObject> pPresetsDo;
   for (QMap<QString, QPair<NEWMAT::Matrix, double> >::const_iterator preset = mPresets.begin();
      preset != mPresets.end(); ++preset)
   {
      std::string presetPrefix = preset.key().toStdString();
      pPresetsDo->setAttributeByPath(presetPrefix + "/divisor", preset->second);
      pPresetsDo->setAttributeByPath(presetPrefix + "/rowcount", preset->first.Nrows());
      pPresetsDo->setAttributeByPath(presetPrefix + "/colcount", preset->first.Ncols());
      std::vector<double> elements;
      elements.reserve(preset->first.Storage());
      for (int row = 1; row <= preset->first.Nrows(); ++row)
      {
         for (int col = 1; col <= preset->first.Ncols(); ++col)
         {
            elements.push_back(preset->first(row, col));
         }
      }
      pPresetsDo->setAttributeByPath(presetPrefix + "/kernel", elements);
   }
   Service<ConfigurationSettings>()->setSetting("ConvolutionMatrixEditor/Presets", *(pPresetsDo.get()));
}

void ConvolutionMatrixWidget::loadFromConfigurationSettings()
{
   mPresets.clear();
   const DataVariant& var = Service<ConfigurationSettings>()->getSetting("ConvolutionMatrixEditor/Presets");
   const DynamicObject* pPresetsDo = var.getPointerToValue<DynamicObject>();
   if (pPresetsDo == NULL)
   {
      return;
   }
   std::vector<std::string> names;
   pPresetsDo->getAttributeNames(names);
   for (std::vector<std::string>::const_iterator name = names.begin(); name != names.end(); ++name)
   {
      double divisor = dv_cast<double>(pPresetsDo->getAttributeByPath(*name + "/divisor"), 1.0);
      int rowcount = dv_cast<int>(pPresetsDo->getAttributeByPath(*name + "/rowcount"), 0);
      int colcount = dv_cast<int>(pPresetsDo->getAttributeByPath(*name + "/colcount"), 0);
      std::vector<double> elements = dv_cast<std::vector<double> >(
         pPresetsDo->getAttributeByPath(*name + "/kernel"), std::vector<double>());
      if (rowcount == 0 || colcount == 0 || elements.size() != (rowcount * colcount))
      {
         continue;
      }
      NEWMAT::Matrix kernel(rowcount, colcount);
      std::vector<double>::const_iterator element = elements.begin();
      for (int row = 1; row <= rowcount; ++row)
      {
         for (int col = 1; col <= colcount; ++col)
         {
            kernel(row, col) = *element++;
         }
      }
      mPresets[QString::fromStdString(*name)] = qMakePair(kernel, divisor);
      mpFilterName->addItem(QString::fromStdString(*name));
   }
}
