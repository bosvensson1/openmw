#ifndef MWGUI_LIST_HPP
#define MWGUI_LIST_HPP

#include <MyGUI.h>

namespace MWGui
{
    namespace Widgets
    {
        /**
         * \brief a very simple list widget that supports word-wrapping entries
         * \note does not handle changing the width of the list at runtime
         */
        class MWList : public MyGUI::Widget
        {
            MYGUI_RTTI_DERIVED(MWList)
        public:
            MWList();

            typedef MyGUI::delegates::CMultiDelegate1<std::string> EventHandle_String;

            /**
             * Event: Item selected with the mouse.
             * signature: void method(std::string itemName)
             */
            EventHandle_String eventItemSelected;

            void addItem(const std::string& name);
            void removeItem(const std::string& name);
            bool hasItem(const std::string& name);
            unsigned int getItemCount();
            std::string getItemNameAt(unsigned int at);
            void clear();

        protected:
            void initialiseOverride();

            void redraw(bool scrollbarShown = false);

            void onMouseWheel(MyGUI::Widget* _sender, int _rel);
            void onItemSelected(MyGUI::Widget* _sender);

        private:
            MyGUI::ScrollView* mScrollView;
            MyGUI::Widget* mClient;

            std::vector<std::string> mItems;

            int mItemHeight; // height of all items
        };
    }
}

#endif
