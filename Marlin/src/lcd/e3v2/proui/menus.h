/**
 * Menu functions for ProUI
 * Author: Miguel A. Risco-Castillo
<<<<<<< HEAD
 * Version: 1.7.1
 * Date: 2022/08/11
=======
 * Version: 1.5.1
 * Date: 2022/05/23
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
#pragma once

#include "dwinui.h"

<<<<<<< HEAD
#define MENU_CHAR_LIMIT  24
#define MENU_MAX_ITEMS   TERN(SDSORT_LIMIT, SDSORT_LIMIT, 64)

=======
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
typedef struct {
  int32_t MaxValue     = 0;        // Auxiliar max integer/scaled float value
  int32_t MinValue     = 0;        // Auxiliar min integer/scaled float value
  int8_t dp            = 0;        // Auxiliar decimal places
  int32_t Value        = 0;        // Auxiliar integer / scaled float value
  int16_t *P_Int       = nullptr;  // Auxiliar pointer to 16 bit integer variable
  float *P_Float       = nullptr;  // Auxiliar pointer to float variable
  void (*Apply)()      = nullptr;  // Auxiliar apply function
  void (*LiveUpdate)() = nullptr;  // Auxiliar live update function
} MenuData_t;

extern MenuData_t MenuData;
extern void (*onCursorErase)(const int8_t line);
extern void (*onCursorDraw)(const int8_t line);

// Auxiliary Macros ===========================================================

// Create and add a MenuItem object to the menu array
<<<<<<< HEAD
#define SET_MENU(I,L,V...) SetMenu(I, GET_TEXT_F(L), V)
#define BACK_ITEM(H) MenuItemAdd(ICON_Back, GET_TEXT_F(MSG_BUTTON_BACK), onDrawMenuItem, H)
#define MENU_ITEM(I,L,V...) MenuItemAdd(I, GET_TEXT_F(L), V)
#define EDIT_ITEM(I,L,V...) EditItemAdd(I, GET_TEXT_F(L), V)
#define SET_MENU_F(I,L,V...) SetMenu(I, F(L), V)
#define MENU_ITEM_F(I,L,V...) MenuItemAdd(I, F(L), V)
#define EDIT_ITEM_F(I,L,V...) EditItemAdd(I, F(L), V)

// Menu Classes ===============================================================

class CustomMenuItemClass;
class MenuItemClass;

typedef void (*OnDrawCustomItem)(CustomMenuItemClass*  menuitem, int8_t line);
typedef void (*OnDrawItem)(MenuItemClass*  menuitem, int8_t line);
typedef void (*OnClickItem)();

class CustomMenuItemClass {
public:
  int8_t pos = 0;
  OnDrawItem onDraw = nullptr;
  void (*onClick)() = nullptr;
  CustomMenuItemClass() {};
  CustomMenuItemClass(OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  virtual ~CustomMenuItemClass(){};
  virtual void draw(int8_t line);
  void redraw(bool erase=false);
};

class MenuItemClass: public CustomMenuItemClass {
public:
  uint8_t icon = 0;
  char caption[MENU_CHAR_LIMIT] = "";
  uint8_t frameid = 0;
  rect_t frame = {0};
  using CustomMenuItemClass::CustomMenuItemClass;
  MenuItemClass(uint8_t cicon, const char * const text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  MenuItemClass(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  void SetFrame(uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  void SetCaption(const char * const text = nullptr);
=======
#define BACK_ITEM(H) MenuItemsAdd(ICON_Back, GET_TEXT_F(MSG_BUTTON_BACK), onDrawMenuItem, H)
#define MENU_ITEM(V...) MenuItemsAdd(V)
#define EDIT_ITEM(V...) MenuItemsAdd(V)
#define MENU_ITEM_F(I,L,V...) MenuItemsAdd(I, GET_TEXT_F(L), V)
#define EDIT_ITEM_F(I,L,V...) MenuItemsAdd(I, GET_TEXT_F(L), V)

// Menu Classes ===============================================================

class MenuItemClass {
protected:
public:
  int8_t pos = 0;
  uint8_t icon = 0;
  char caption[32] = "";
  uint8_t frameid = 0;
  rect_t frame = {0};
  void (*onDraw)(MenuItemClass* menuitem, int8_t line) = nullptr;
  void (*onClick)() = nullptr;
  MenuItemClass() {};
  MenuItemClass(uint8_t cicon, const char * const text=nullptr, void (*ondraw)(MenuItemClass* menuitem, int8_t line)=nullptr, void (*onclick)()=nullptr);
  // MenuItemClass(uint8_t cicon, FSTR_P text = nullptr, void (*ondraw)(MenuItemClass* menuitem, int8_t line)=nullptr, void (*onclick)()=nullptr) : MenuItemClass(cicon, FTOP(text), ondraw, onclick){}
  MenuItemClass(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, void (*ondraw)(MenuItemClass* menuitem, int8_t line)=nullptr, void (*onclick)()=nullptr);
  void SetFrame(uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  virtual ~MenuItemClass(){};
  virtual void draw(int8_t line);
  void redraw();
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
};

class MenuItemPtrClass: public MenuItemClass {
public:
  void *value = nullptr;
  using MenuItemClass::MenuItemClass;
<<<<<<< HEAD
  MenuItemPtrClass(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val);
  MenuItemPtrClass(uint8_t cicon, FSTR_P text, OnDrawItem ondraw, OnClickItem onclick, void* val) : MenuItemPtrClass(cicon, FTOP(text), ondraw, onclick, val){}
=======
  MenuItemPtrClass(uint8_t cicon, const char * const text, void (*ondraw)(MenuItemClass* menuitem, int8_t line), void (*onclick)(), void* val);
  MenuItemPtrClass(uint8_t cicon, FSTR_P text, void (*ondraw)(MenuItemClass* menuitem, int8_t line), void (*onclick)(), void* val) : MenuItemPtrClass(cicon, FTOP(text), ondraw, onclick, val){}
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
};

class MenuClass {
public:
  int8_t topline = 0;
  int8_t selected = 0;
  TitleClass MenuTitle;
  MenuClass();
  virtual ~MenuClass(){};
  inline int8_t line() { return selected - topline; };
  inline int8_t line(uint8_t pos) {return pos - topline; };
  int8_t count();
  virtual void draw();
  virtual void onScroll(bool dir);
  void onClick();
<<<<<<< HEAD
  CustomMenuItemClass* SelectedItem();
  static CustomMenuItemClass** Items();
=======
  MenuItemClass* SelectedItem();
  static MenuItemClass** Items();
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
};
extern MenuClass *CurrentMenu;
extern MenuClass *PreviousMenu;
extern void (*onMenuDraw)(MenuClass* menu);

// Menuitem Drawing functions =================================================

void Draw_Title(TitleClass* title);
void Draw_Menu(MenuClass* menu);
void Draw_Menu_Cursor(const int8_t line);
void Erase_Menu_Cursor(const int8_t line);
<<<<<<< HEAD
void Erase_Menu_Text(const int8_t line);
void Draw_Menu_Line(const uint8_t line, const uint8_t icon=0, const char * const label=nullptr, bool more=false, bool selected=false);
void Draw_Menu_Line(const uint8_t line, const uint8_t icon=0, FSTR_P label=nullptr, bool more=false, bool selected=false);
=======
void Draw_Menu_Line(const uint8_t line, const uint8_t icon=0, const char * const label=nullptr, bool more=false);
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
void Draw_Chkb_Line(const uint8_t line, const bool checked);
void Draw_Menu_IntValue(uint16_t bcolor, const uint8_t line, uint8_t iNum, const int32_t value=0);
void onDrawMenuItem(MenuItemClass* menuitem, int8_t line);
void onDrawSubMenu(MenuItemClass* menuitem, int8_t line);
void onDrawIntMenu(MenuItemClass* menuitem, int8_t line, int32_t value);
void onDrawPIntMenu(MenuItemClass* menuitem, int8_t line);
void onDrawPInt8Menu(MenuItemClass* menuitem, int8_t line);
void onDrawPInt32Menu(MenuItemClass* menuitem, int8_t line);
void onDrawFloatMenu(MenuItemClass* menuitem, int8_t line, uint8_t dp, const float value);
<<<<<<< HEAD
void onDrawPFloatMenu(MenuItemClass* menuitem, int8_t line, uint8_t dp);
inline void onDrawPFloatMenu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, UNITFDIGITS); };
inline void onDrawPFloat2Menu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 2); };
inline void onDrawPFloat3Menu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 3); };
inline void onDrawPFloat4Menu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 4); };
=======
void onDrawPFloatMenu(MenuItemClass* menuitem, int8_t line);
void onDrawPFloat2Menu(MenuItemClass* menuitem, int8_t line);
void onDrawPFloat3Menu(MenuItemClass* menuitem, int8_t line);
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
void onDrawChkbMenu(MenuItemClass* menuitem, int8_t line, bool checked);
void onDrawChkbMenu(MenuItemClass* menuitem, int8_t line);

// On click functions =========================================================

void SetOnClick(uint8_t process, const int32_t lo, const int32_t hi, uint8_t dp, const int32_t val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetValueOnClick(uint8_t process, const int32_t lo, const int32_t hi, const int32_t val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetValueOnClick(uint8_t process, const float lo, const float hi, uint8_t dp, const float val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetIntOnClick(const int32_t lo, const int32_t hi, const int32_t val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetPIntOnClick(const int32_t lo, const int32_t hi, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetFloatOnClick(const float lo, const float hi, uint8_t dp, const float val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetPFloatOnClick(const float lo, const float hi, uint8_t dp, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);

// HMI user control functions =================================================

void HMI_Menu();
<<<<<<< HEAD
void HMI_SetDraw();
void HMI_SetNoDraw();
void HMI_SetPInt();
=======
void HMI_SetInt();
void HMI_SetPInt();
void HMI_SetIntNoDraw();
void HMI_SetFloat();
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
void HMI_SetPFloat();

// Menu auxiliary functions ===================================================

// Create a new menu
bool SetMenu(MenuClass* &menu, FSTR_P title, int8_t totalitems);

<<<<<<< HEAD
// Invalidate CurrentMenu to prepare for full menu drawing
void InvalidateMenu();

=======
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
//Update the Menu and Draw if it is valid
void UpdateMenu(MenuClass* &menu);

//Redraw the current Menu if it is valid
void ReDrawMenu(bool force = false);

// Clear MenuItems array and free MenuItems elements
void MenuItemsClear();

// Prepare MenuItems array
void MenuItemsPrepare(int8_t totalitems);

<<<<<<< HEAD
// Is the current menu = menu?
bool IsMenu(MenuClass* menu);

// Add elements to the MenuItems array
CustomMenuItemClass* MenuItemAdd(OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
MenuItemClass* MenuItemAdd(uint8_t cicon, const char * const text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
inline MenuItemClass* MenuItemAdd(uint8_t cicon, FSTR_P text = nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr) {
  return MenuItemAdd(cicon, FTOP(text), ondraw, onclick);
}
MenuItemClass* MenuItemAdd(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
MenuItemClass* EditItemAdd(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val);
inline MenuItemClass* EditItemAdd(uint8_t cicon, FSTR_P text, OnDrawItem ondraw, OnClickItem onclick, void* val) {
  return EditItemAdd(cicon, FTOP(text), ondraw, onclick, val);
=======
// Add elements to the MenuItems array
MenuItemClass* MenuItemsAdd(uint8_t cicon, const char * const text=nullptr, void (*ondraw)(MenuItemClass* menuitem, int8_t line)=nullptr, void (*onclick)()=nullptr);
inline MenuItemClass* MenuItemsAdd(uint8_t cicon, FSTR_P text = nullptr, void (*ondraw)(MenuItemClass* menuitem, int8_t line)=nullptr, void (*onclick)()=nullptr) {
  return MenuItemsAdd(cicon, FTOP(text), ondraw, onclick);
}
MenuItemClass* MenuItemsAdd(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, void (*ondraw)(MenuItemClass* menuitem, int8_t line)=nullptr, void (*onclick)()=nullptr);
MenuItemClass* MenuItemsAdd(uint8_t cicon, const char * const text, void (*ondraw)(MenuItemClass* menuitem, int8_t line), void (*onclick)(), void* val);
inline MenuItemClass* MenuItemsAdd(uint8_t cicon, FSTR_P text, void (*ondraw)(MenuItemClass* menuitem, int8_t line), void (*onclick)(), void* val) {
  return MenuItemsAdd(cicon, FTOP(text), ondraw, onclick, val);
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
}
