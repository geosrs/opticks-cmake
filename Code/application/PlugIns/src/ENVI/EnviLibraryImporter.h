/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef ENVILIBRARYIMPORTER_H
#define ENVILIBRARYIMPORTER_H

#include "EnviField.h"
#include "ImporterShell.h"

#include <string>
#include <vector>

class PlugInArgList;
class Progress;
class SignatureLibrary;
class Step;

class EnviLibraryImporter : public ImporterShell
{
public:
   EnviLibraryImporter();
   ~EnviLibraryImporter();

   std::vector<ImportDescriptor*> getImportDescriptors(const std::string& filename);
   unsigned char getFileAffinity(const std::string& filename);
   bool getInputSpecification(PlugInArgList*& pArgList);
   bool getOutputSpecification(PlugInArgList*& pArgList);
   bool execute(PlugInArgList* pInArgList, PlugInArgList* pOutArgList);

protected:
   bool extractPlugInArgs(PlugInArgList* pArgList);
   std::string findDataFile(const std::string& headerFilename);
   std::string findHeaderFile(const std::string& dataFilename);
   std::string findFileByExtension(const std::string& filename, const std::string& fileExtension,
                                   const std::string& openMode);

private:
   Step* mpStep;

   Progress* mpProgress;
   SignatureLibrary* mpSignatureLibrary;

   EnviField mFields;
};

#endif
