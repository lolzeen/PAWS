#ifndef PAWS_LIB_SCREENCONTROLLER_H
#define PAWS_LIB_SCREENCONTROLLER_H
#include "ScreenVariables.h"

namespace ScreenContents
{
    class ScreenContent
    {
    public:
        ScreenContent()
        {
            currentContent = ScreenVariable::PossibleContents::INIT;
        };
        ~ScreenContent() {};

        ScreenVariable::PossibleContents getCurrentContent() { return currentContent; }
        void updateContent(ScreenVariable::ScreenActions action);
        void getResultOfButtonAction();
        void getResultOfEncoderAction(ScreenVariable::ScreenActions action);

    private:
        enum ScreenVariable::PossibleContents currentContent;
        enum ScreenVariable::PossibleFocus currentFocus;
    };
}

#endif // PAWS_LIB_SCREENCONTROLLER_H