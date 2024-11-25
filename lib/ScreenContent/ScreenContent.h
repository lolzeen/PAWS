#ifndef PAWS_LIB_SCREENCONTENT_H
#define PAWS_LIB_SCREENCONTENT_H

const unsigned short HELLO_SCREEN = 1;
const unsigned short MAIN_MENU_SCREEN = 2;
const unsigned short SETTINGS_SCREEN = 3;
const unsigned short CONNECT_SCREEN = 4;
const unsigned short LIVE_DATA_SCREEN = 5;

struct StaticContent {
    unsigned short uid;
    char background[1024];
    
}

class ScreenContent
{
private:
    unsigned short uid;
    bool isActive;

public:
    ScreenContent();
    ~ScreenContent();

    void refresh();
    
    void setState(bool newState) {isActive = newState;}

    bool getState() const {return isActive;}
    

};

ScreenContent::ScreenContent()
{

}

ScreenContent::~ScreenContent()
{
}


#endif //PAWS_LIB_VISUCONTROL_SCREENCONTENT_H