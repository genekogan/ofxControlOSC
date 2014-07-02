#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


#define CONTROLOSC_PORT 8080

enum Orientation {
    PORTRAIT, LANDSCAPE };

enum WidgetType {
    BUTTON, MULTIBUTTON,
    SLIDER, MULTISLIDER,
    PAGE_SELECT, REFRESH };


//-----------------------------------
struct Widget {
    WidgetType  type;
    string      name;
    float       x, y, w, h;
    float       min = -1;
    float       max = +1;
    string      address;
    string      label;
    
    // Multisliders
    int         numSliders = 1;
    
    // Multibuttons
    int         nrows = 1;
    int         ncols = 1;
    
    // Sliders, Multislider
    bool        isVertical = false;
    bool        isXFader = false;
    
    // Knobs
    float       radius = 0.1;
    bool        centerZero = false;
    bool        usesRotation = false;
    
    // Page selection button
    int         idxPage = 0;
    
    string      getJson();
};


//-----------------------------------
class Page
{
public:
    Page(string name);
    void addWidget(Widget widget);
    string getName() { return name; }
    string getJson();
private:
    vector<Widget> widgets;
    string name;
};


//-----------------------------------
class ofxControlOSC
{
public:
    void setup(string name, Orientation orientation);
    Page* addPage(string name);
    string getJson();
    void uploadToControlP5(string ipAddress);
    void saveToFile(string path);
private:
    string getHeader();
    vector<Page *> pages;
    string name;
    Orientation orientation;
};
