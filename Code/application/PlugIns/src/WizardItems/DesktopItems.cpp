/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
 


#include "DesktopItems.h"

DesktopItems::DesktopItems()
{
   setShortDescription("Wizard Desktop Item");
}

DesktopItems::~DesktopItems()
{
}

bool DesktopItems::setBatch()
{
   mbInteractive = false;
   return false;
}

bool DesktopItems::setInteractive()
{
   mbInteractive = true;
   return true;
}

 
