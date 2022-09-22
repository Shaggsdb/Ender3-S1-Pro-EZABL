/**
 * ToolBar for PRO UI
 * Author: Miguel A. Risco-Castillo (MRISCOC)
<<<<<<< HEAD
 * version: 1.3.1
 * Date: 2022/08/05
=======
 * version: 1.2.1
 * Date: 2022/07/10
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

<<<<<<< HEAD
#include "../../../inc/MarlinConfig.h"
=======
#include "../../../inc/MarlinConfigPre.h"
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

#if BOTH(DWIN_LCD_PROUI, HAS_TOOLBAR)

#include "toolbar.h"
<<<<<<< HEAD
#include "toolbar_def.h"
#include "menus.h"

TBItem_t TBItem;
ToolBarClass ToolBar;

uint8_t ToolBarClass::OptCount() {
  return COUNT(TBItemA);
}

=======
#include "dwin.h"
#include "menus.h"

>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
void onDrawTBItem(MenuItemClass* menuitem, int8_t line) {
  const bool focused = (checkkey == Menu);
  const int8_t sel = ToolBar.selected;
  const uint8_t tw = focused ? MENU_CHR_W * TBMaxCaptionWidth : 0;
  const uint8_t xoff = (DWIN_WIDTH - (B_XPos * ToolBar.count() + tw)) / 2;
  const uint8_t xp = xoff + line * B_XPos + (line > sel ? tw : 0);
  if (focused && (line == sel)) {
    DWIN_Draw_Box(1, Color_Bg_Window, xp - 2, TBYPos, B_XPos, TBHeight);
    DWINUI::Draw_String(xp + B_XPos, B_YPos + 1, menuitem->caption);
  }
  DWINUI::Draw_Icon(menuitem->icon, xp, B_YPos);
};

void Draw_ToolBar(bool force /*=false*/) {
  if (force || (CurrentMenu != &ToolBar)) {
    CurrentMenu = &ToolBar;
    MenuItemsPrepare(TBMaxOpt);
    LOOP_L_N(i,TBMaxOpt) {
      TBGetItem(PRO_data.TBopt[i]);
<<<<<<< HEAD
      if (TBItem.icon) MENU_ITEM_F(TBItem.icon, TBItem.caption, onDrawTBItem, TBItem.onClick);
=======
      if (TBItem.icon) MENU_ITEM(TBItem.icon, TBItem.caption, onDrawTBItem, TBItem.onClick);
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
    }
    ToolBar.onExit = &Exit_ToolBar;
  }
  ToolBar.draw();
}

void UpdateTBSetupItem(MenuItemClass* menuitem, uint8_t val) {
  TBGetItem(val);
  menuitem->icon = TBItem.icon ?: ICON_Info;
  strcpy_P(menuitem->caption, FTOP(TBItem.caption));
}

void DrawTBSetupItem(bool focused, uint8_t line) {
  const uint16_t ypos = MYPOS(line);
  DWINUI::Draw_Box(1, focused ? Color_Bg_Black : HMI_data.Background_Color, {15, ypos, DWIN_WIDTH - 15, MLINE - 1});
<<<<<<< HEAD
  onDrawMenuItem(static_cast<MenuItemClass*>(CurrentMenu->SelectedItem()), line);
  if (focused) DWINUI::Draw_Char(VALX + 24, MBASE(line), 18);
}

void TBGetItem(uint8_t item) {
  const uint8_t N = ToolBar.OptCount() - 1;
  if (WITHIN(item, 0, N))
    TBItem = TBItemA[item];
  else
    TBItem = {0, GET_TEXT_F(MSG_OPTION_DISABLED), nullptr};
}

=======
  onDrawMenuItem(CurrentMenu->SelectedItem(), line);
  if (focused) DWINUI::Draw_Char(VALX + 24, MBASE(line), 18);
}

>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
#endif // BOTH(DWIN_LCD_PROUI, HAS_TOOLBAR)