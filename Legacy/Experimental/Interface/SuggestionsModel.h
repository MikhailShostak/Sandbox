#pragma once

#include <UI>

namespace UI
{

class BaseSuggestionsComponent : public ItemAdapter
{
    struct SuggestionsWindow : public ASingleton<SuggestionsWindow>
    {
        Window *window = nullptr;
        SuggestionsWindow()
        {
            window = Create<Window>();
            window->setFlags(WindowFlags::Menu);
        }
    };
public:

    SharedReference<ListView> listView = SharedReference<ListView>(Create<ListView>());
    Array<String> suggestions;
    View *view = nullptr;
    bool upDirection = false;

    BaseSuggestionsComponent()
    {
        listView->setSizePolicy(SizePolicy::ContentWrapped);
        listView->setAdapter(this);
    }

    SizeType getCountItems(const AObject &sender) const { return suggestions.size(); }
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index)
    {
        return SharedReference<Label>(Create<Label>(suggestions[index]));
    }

    bool useTypedWordOnly = false;

    bool hasWords(const String &text, const Array<String> &words)
    {
        const String &lowerString = boost::to_lower_copy(text);
        for (const String &word : words)
        {
            if (lowerString.find_first_of(boost::to_lower_copy(word)) == String::size_type(-1))
            {
                return false;
            }
        }
        return true;
    }

    virtual void updateSuggestions(const String &text) = 0;

    void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index)
    {
        static_cast<TextField *>(view)->setText(suggestions[index]);
        SuggestionsWindow::getInstance().window->hide();
    }

    void addView(TextField &view)
    {
        view.eventChannel.registerDelegate([this](TextEditedEvent &event) {
            this->view = &event.getView();
            updateSuggestions(event.getText());
            listView->notifyUpdateAllItems();
            if (!suggestions.empty())
            {
                Math::IntegerVector contentSize = listView->getContentSize();
                Math::IntegerVector localPosition = Math::IntegerVector{ 0, upDirection ? -contentSize.y : event.getView().getSize().y };
                Math::IntegerVector positionInWindow = mapFromLocalSpaceToScreenSpace(event.getView(), localPosition);
                Math::IntegerVector windowPosition = event.getView().getOwner()->getWindow()->getGeometry().position;
                auto &window = *SuggestionsWindow::getInstance().window;
                window.setGeometry(Math::IntegerRectangle{ windowPosition + positionInWindow, contentSize });
                window.setView(listView);
                window.show();

                listView->setPosition(Math::Vector());
                listView->requestUpdate();
            }
            else
            {
                SuggestionsWindow::getInstance().window->hide(); //TODO: Show "No suggestions" message for user...
            }
        });
    }
};

class SuggestionsComponent : public BaseSuggestionsComponent
{
public:
    Array<String> items;

    void updateSuggestions(const String &text) override
    {
        suggestions.clear();
        Array<String> words;
        boost::split(words, text, boost::is_any_of(" "));
        for (const String &item : items)
        {
            if (hasWords(item, words))
            {
                suggestions.push_back(item);
            }
        }
    }
};

}
