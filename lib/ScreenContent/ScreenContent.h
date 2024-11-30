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
    
};

class ScreenContent
{

public:
    ScreenContent();
    ~ScreenContent();

    void init_screen();

    void refresh();
    
    void setState(bool newState) {isActive = newState;}

    bool getState() const {return isActive;}
    
private:
    unsigned short uid;
    bool isActive;

};


#endif //PAWS_LIB_VISUCONTROL_SCREENCONTENT_H