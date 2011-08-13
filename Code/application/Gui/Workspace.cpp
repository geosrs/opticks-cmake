/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#include "Workspace.h"
#include "DesktopServices.h"
#include "WorkspaceWindow.h"
#include "WorkspaceWindowImp.h"

using namespace std;

Workspace::Workspace(QWidget* parent) :
   QMdiArea(parent),
   mbCustomTiling(false),
   mMaxFirst(true),
   mTilingType(TILE_GRID)
{
   // This controls how subwindows are tiled and/or cascaded by the base class.
   setActivationOrder(QMdiArea::StackingOrder);
}

void Workspace::resizeEvent(QResizeEvent * e)
{
   QMdiArea::resizeEvent(e);
   if (mbCustomTiling)
   {
      QList<QMdiSubWindow*> windows = subWindowList();
      QMdiSubWindow* pSubWindow = NULL;

      int numViews = mTileWindows.size();
      bool listValid = (numViews > 0);
      for (int i = 0; i < numViews; i++)
      {
         pSubWindow = mTileWindows[i];
         if (!windows.contains(pSubWindow))
         {
            listValid = false;
         }
      }

      if (listValid)
      {
         refreshCustomView();
      }
      else
      {
         mbCustomTiling = false;
         mTileWindows.clear();
      }
   }
}

void Workspace::refreshCustomView()
{
   if (mbCustomTiling)
   {
      int numViews = mTileWindows.size();

      // if vector of windows is empty, tile all windows
      if (numViews < 1)
      {
         QList<QMdiSubWindow*> workspaceWindows = subWindowList();
         numViews = workspaceWindows.size();
         for (int i = 0; i < numViews; ++i)
         {
            mTileWindows.push_back(workspaceWindows.at(i));
         }
      }

      int x;
      int y;
      int rowHeight;
      int colWidth;
      int leftOver;

      switch (mTilingType)
      {
      case TILE_GRID:
         {
            // handle special case for 1 window in list
            if (mTileWindows.size() == 1)
            {
               setSubWindow(mTileWindows.front(), 0, 0, width(), height());
               break;
            }

            bool odd(numViews % 2 == 1);
            int startAt(0);
            int evenColStart(0);
            int runTo(numViews-1);
            int halfViews = numViews / 2;
            colWidth = width() / halfViews;
            int oddColWidth(0);
            y = 0;
            if (odd)
            {
               rowHeight = height();
               colWidth = width() / (halfViews+1);
               oddColWidth = width() - colWidth * halfViews;
               QMdiSubWindow* pSubWindow = NULL;
               if (mMaxFirst)
               {
                  pSubWindow = mTileWindows.at(startAt++);
                  x = 0;
                  evenColStart = oddColWidth;
               }
               else
               {
                  pSubWindow = mTileWindows.at(runTo--);
                  x = halfViews * colWidth;
               }
               setSubWindow(pSubWindow, x, y, oddColWidth, rowHeight);
            }

            rowHeight = height() / 2;
            leftOver = width() - oddColWidth - colWidth * halfViews;

            int colPad(leftOver);
            if (leftOver > 0)
            {
               ++colWidth;
            }
            else
            {
               colPad = -1;
            }

            x = evenColStart;
            for (int i = startAt; i < startAt + halfViews; ++i)
            {
               if (colPad-- == 0)
               {
                  --colWidth;
               }
               setSubWindow(mTileWindows.at(i), x, y, colWidth, rowHeight);
               x += colWidth;
            }

            y += rowHeight;
            x = evenColStart;
            colPad = leftOver;
            if (leftOver > 0)
            {
               ++colWidth;
            }
            else
            {
               colPad = -1;
            }
            for (int i = startAt + halfViews; i <= runTo; ++i)
            {
               if (colPad-- == 0)
               {
                  --colWidth;
               }
               setSubWindow(mTileWindows.at(i), x, y, colWidth, rowHeight);
               x += colWidth;
            }
         }
         break;

      case TILE_HORIZONTAL:
         rowHeight = height();
         colWidth = width() / numViews;
         leftOver = width() - colWidth * numViews;
         if (leftOver > 0)
         {
            ++colWidth;
         }
         x = 0;
         y = 0;
         for (int i = 0; i < numViews ; ++i)
         {
            if (leftOver-- == 0)
            {
               --colWidth;
            }
            setSubWindow(mTileWindows.at(i), x, y, colWidth, rowHeight);
            x += colWidth;
         }
         break;

      case TILE_VERTICAL:
         rowHeight = height() / numViews;
         colWidth = width();
         leftOver = height() - rowHeight * numViews;
         if (leftOver > 0)
         {
            ++rowHeight;
         }
         x = 0;
         y = 0;
         for (int i = 0; i < numViews ; ++i)
         {
            if (leftOver-- == 0)
            {
               --rowHeight;
            }
            setSubWindow(mTileWindows.at(i), x, y, colWidth, rowHeight);
            y += rowHeight;
         }
         break;
      default:
         return;
         break;
      }

      Service<DesktopServices> pDesktop;
      if (pDesktop.get() != NULL)
      {
         WorkspaceWindow* pWork = dynamic_cast<WorkspaceWindow*>(mTileWindows.front());
         if (pWork != NULL)
         {
            pDesktop->setCurrentWorkspaceWindow(pWork);
         }
      }
   }
}

void Workspace::cascadeSubWindows()
{
   mbCustomTiling = false;
   mTileWindows.clear();
   QMdiArea::cascadeSubWindows();
}

void Workspace::tile(const TilingType eType)
{
   mbCustomTiling = false;
   mTilingType = eType;
   mTileWindows.clear();

   QList<QMdiSubWindow*> windows = subWindowList();
   int numWindows = windows.count();
   if (numWindows < 2)
   {
      QMdiArea::tileSubWindows();
      return;
   }

   int leftOver(0);
   switch (mTilingType)
   {
   case TILE_GRID:
      QMdiArea::tileSubWindows();
      break;
   case TILE_HORIZONTAL:
      {
         int wWidth = width() / numWindows;
         leftOver = width() - wWidth * numWindows;
         if (leftOver > 0)
         {
            ++wWidth;
         }
         int x = 0;
         QMdiSubWindow* pSubWindow(NULL);
         for (int i = 0; i < numWindows; ++i)
         {
            pSubWindow = windows.at(i);
            if (pSubWindow != NULL)
            {
               if (leftOver-- == 0)
               {
                  --wWidth;
               }
               setSubWindow(pSubWindow, x, 0, wWidth, height());
               x += wWidth;
            }
         }
      }
      break;
   case TILE_VERTICAL:
      {
         int wHeight = height() / numWindows;
         leftOver = height() - wHeight * numWindows;
         if (leftOver > 0)
         {
            ++wHeight;
         }
         int y = 0;
         QMdiSubWindow* pSubWindow(NULL);
         for (int i = 0; i < numWindows; ++i)
         {
            pSubWindow = windows.at(i);
            if (pSubWindow != NULL)
            {
               if (leftOver-- == 0)
               {
                  --wHeight;
               }
               setSubWindow(pSubWindow, 0, y, width(), wHeight);
               y += wHeight;
            }
         }
      }
      break;
   default:
      break;
   }
}

bool Workspace::tileWindows(const vector<WorkspaceWindow*>& windows, bool maxFirst, const TilingType eType)
{
   mbCustomTiling = false;
   mTilingType = eType;
   mTileWindows.clear();

   QList<QMdiSubWindow*> workspaceWindows = subWindowList();
   for (vector<WorkspaceWindow*>::const_iterator iter = windows.begin(); iter != windows.end(); ++iter)
   {
      WorkspaceWindowImp* pWindow = dynamic_cast<WorkspaceWindowImp*>(*iter);
      if (pWindow != NULL)
      {
         if (workspaceWindows.contains(pWindow) == true)
         {
            mTileWindows.push_back(pWindow);
         }
      }
   }

   if (windows.size() != mTileWindows.size())
   {
      return false;
   }

   mbCustomTiling = true;
   mMaxFirst = maxFirst;
   refreshCustomView();

   return true;
}

void Workspace::setSubWindow(QMdiSubWindow* pSubWindow, int x, int y, int winWidth, int winHeight)
{
   if (pSubWindow == NULL)
   {
      return;
   }

   pSubWindow->showNormal();
   pSubWindow->resize(winWidth, winHeight);
   pSubWindow->move(x, y);
   pSubWindow->raise();
}
