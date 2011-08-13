/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#include "AppAssert.h"
#include "AppVersion.h"

#include <sstream>
#include <string>

void AppAssert(const char *pExpression, const char *pFilename, unsigned int line)
{
   std::stringstream text;
   text << "Internal " << APP_NAME << " Error: Assertion Failed\n\nAssert(" << pExpression 
      << ")\n   File: " << pFilename << "\n   Line: " << line;

   throw AssertException(text.str().c_str());
}
