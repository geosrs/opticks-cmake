/*
 * The information in this file is
 * Copyright(c) 2010 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#include "AppVerify.h"
#include "ViewResolutionWidget.h"

#include <QtGui/QBitmap>
#include <QtGui/QCheckBox>
#include <QtGui/QIcon>
#include <QtGui/QIntValidator>
#include <QtGui/QLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

namespace
{
   /* XPM */
   const char* const lock_xpm[] =
   {
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
      "                                "
   };

   /* XPM */
   const char* const unlock_xpm[] =
   {
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
      "                                "
   };
};

ViewResolutionWidget::ViewResolutionWidget(QWidget* pParent) :
   QWidget(pParent)
{
   // Use View Resolution check box
   mpViewResolutionCheck = new QCheckBox("Use View Resolution", this);

   // Width and height edits
   QIntValidator* pValidator = new QIntValidator(this);
   pValidator->setBottom(2);

   mpWidthEdit = new QLineEdit(this);
   mpWidthEdit->setValidator(pValidator);

   mpHeightEdit = new QLineEdit(this);
   mpHeightEdit->setValidator(pValidator);

   // Aspect lock button
   QPixmap lockPixmap(lock_xpm);
   lockPixmap.setMask(lockPixmap.createHeuristicMask());
   QPixmap unlockPixmap(unlock_xpm);
   unlockPixmap.setMask(unlockPixmap.createHeuristicMask());

   QIcon lockIcon;
   lockIcon.addPixmap(lockPixmap, QIcon::Normal, QIcon::On);
   lockIcon.addPixmap(unlockPixmap, QIcon::Normal, QIcon::Off);

   mpAspectLockButton = new QPushButton(lockIcon, QString(), this);
   mpAspectLockButton->setCheckable(true);
   mpAspectLockButton->setChecked(true);
   mpAspectLockButton->setToolTip("Lock the resolution aspect ratio.");

   // Layout
   QGridLayout* pLayout = new QGridLayout(this);
   pLayout->setMargin(0);
   pLayout->setSpacing(10);
   pLayout->addWidget(mpViewResolutionCheck, 0, 0, 1, 2, Qt::AlignLeft);
   pLayout->addWidget(mpWidthEdit, 1, 0);
   pLayout->addWidget(mpHeightEdit, 2, 0);
   pLayout->addWidget(mpAspectLockButton, 1, 1, 2, 1, Qt::AlignCenter);
   pLayout->setColumnStretch(2, 10);

   // Connections
   VERIFYNR(connect(mpViewResolutionCheck, SIGNAL(toggled(bool)), this, SLOT(viewResolutionToggled(bool))));
   VERIFYNR(connect(mpWidthEdit, SIGNAL(editingFinished()), this, SLOT(widthEdited())));
   VERIFYNR(connect(mpHeightEdit, SIGNAL(editingFinished()), this, SLOT(heightEdited())));

   // Initialization after connections so that slots are called
   setResolution(QSize());
}

ViewResolutionWidget::~ViewResolutionWidget()
{}

void ViewResolutionWidget::setResolution(const QSize& size)
{
   if (size.isEmpty() == true)
   {
      mpViewResolutionCheck->setChecked(true);
      mResolution = QSize();
      return;
   }

   mpViewResolutionCheck->setChecked(false);

   const QValidator* pWidthValidator = mpWidthEdit->validator();
   VERIFYNRV(pWidthValidator != NULL);

   const QValidator* pHeightValidator = mpHeightEdit->validator();
   VERIFYNRV(pHeightValidator != NULL);

   QString widthStr = QString::number(size.width());
   QString heightStr = QString::number(size.height());
   int pos = 0;

   if ((pWidthValidator->validate(widthStr, pos) == QValidator::Acceptable) &&
      (pHeightValidator->validate(heightStr, pos) == QValidator::Acceptable))
   {
      mpWidthEdit->setText(widthStr);
      mpHeightEdit->setText(heightStr);
      mResolution = size;
   }
}

QSize ViewResolutionWidget::getResolution() const
{
   return mResolution;
}

void ViewResolutionWidget::updateResolution()
{
   if (mpViewResolutionCheck->isChecked() == true)
   {
      mResolution = QSize();
   }
   else
   {
      mResolution.setWidth(mpWidthEdit->text().toInt());
      mResolution.setHeight(mpHeightEdit->text().toInt());
   }
}

void ViewResolutionWidget::viewResolutionToggled(bool useViewResolution)
{
   mpWidthEdit->setDisabled(useViewResolution);
   mpHeightEdit->setDisabled(useViewResolution);
   mpAspectLockButton->setDisabled(useViewResolution);

   // Update the member resolution
   updateResolution();
}

void ViewResolutionWidget::widthEdited()
{
   VERIFYNRV(mpViewResolutionCheck->isChecked() == false);

   // Adjust the width to an even number
   unsigned int resWidth = mpWidthEdit->text().toUInt();
   if ((resWidth % 2) != 0)
   {
      ++resWidth;
      mpWidthEdit->setText(QString::number(resWidth));
   }

   // Adjust the height based on the aspect ratio
   if (mpAspectLockButton->isChecked() == true)
   {
      unsigned int newHeight = resWidth;
      if (mResolution.isEmpty() == false)
      {
         newHeight = (resWidth * mResolution.height()) / static_cast<double>(mResolution.width());
      }

      if ((newHeight % 2) != 0)
      {
         ++newHeight;
      }

      mpHeightEdit->setText(QString::number(newHeight));
   }

   // Update the member resolution
   updateResolution();
}

void ViewResolutionWidget::heightEdited()
{
   VERIFYNRV(mpViewResolutionCheck->isChecked() == false);

   // Adjust the height to an even number
   unsigned int resHeight = mpHeightEdit->text().toUInt();
   if ((resHeight % 2) != 0)
   {
      ++resHeight;
      mpHeightEdit->setText(QString::number(resHeight));
   }

   // Adjust the width based on the aspect ratio
   if (mpAspectLockButton->isChecked() == true)
   {
      unsigned int newWidth = resHeight;
      if (mResolution.isEmpty() == false)
      {
         newWidth = (resHeight * mResolution.width()) / static_cast<double>(mResolution.height());
      }

      if ((newWidth % 2) != 0)
      {
         ++newWidth;
      }

      mpWidthEdit->setText(QString::number(newWidth));
   }

   // Update the member resolution
   updateResolution();
}
