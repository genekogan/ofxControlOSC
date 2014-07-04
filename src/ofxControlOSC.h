#pragma once

#include "ofMain.h"

enum ControlButtonMode { MOMENTARY, TOGGLE };
enum Orientation { PORTRAIT, LANDSCAPE };


//--------
class ofxControlOSCWidget
{
public:
    ofxControlOSCWidget(string name, float x, float y, float w, float h);
    
    void setName(string name) { this->name = name; }
    void setAddress(string address) { this->address = address; }
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setW(float w) { this->w = w; }
    void setH(float h) { this->h = h; }
    void setMin(float min) { this->min = min; }
    void setMax(float max) { this->max = max; }
    string setColors(string fillColor, string strokeColor) { this->fillColor = fillColor; this->strokeColor = strokeColor; }

    string getName() { return name; }
    string getAddress() { return address; }
    float getX() { return x; }
    float getY() { return y; }
    float getW() { return w; }
    float getH() { return h; }
    string getColorFill() { return fillColor; }
    string getColorStroke() { return strokeColor; }
    
    string getCoreJson();
    virtual string getJson() {};
    
protected:
    string type;
    string name;
    string address;
    float x, y, w, h;
    float min, max;
    string fillColor;
    string strokeColor;
};


//--------
class ofxControlOSCLabel : public ofxControlOSCWidget
{
public:
    ofxControlOSCLabel(string name, float x, float y, float w, float h)
        : ofxControlOSCWidget(name, x, y, w, h) { type = "Label"; };
    
    void setVerticalCenter(bool verticalCenter) { this->verticalCenter = verticalCenter; }
    bool getVerticalCenter() { return verticalCenter; }
    
    string getJson();
    
protected:
    bool verticalCenter;
};


//--------
class ofxControlOSCButton : public ofxControlOSCWidget
{
public:
    ofxControlOSCButton(string name, float x, float y, float w, float h)
        : ofxControlOSCWidget(name, x, y, w, h) { type = "Button"; };
    
    void setLabel(string label) { this->label = label; }
    void setMode(ControlButtonMode mode) { this->mode = mode; }
    
    string getLabel() { return label; }
    ControlButtonMode getMode() { return mode; }
    
    string getJson();
    
protected:
    ControlButtonMode mode;
    string label;
};


//--------
class ofxControlOSCMultiButton : public ofxControlOSCButton
{
public:
    ofxControlOSCMultiButton(string name, float x, float y, float w, float h)
        : ofxControlOSCButton(name, x, y, w, h) { type = "MultiButton"; };
    
    void setRows(int rows) { this->rows = rows; }
    void setCols(int cols) { this->cols = cols; }
    
    int getRows() { return rows; }
    int getCols() { return cols; }
    
    string getJson();
    
protected:
    int rows, cols;
};


//--------
class ofxControlOSCSlider : public ofxControlOSCWidget
{
public:
    ofxControlOSCSlider(string name, float x, float y, float w, float h)
        : ofxControlOSCWidget(name, x, y, w, h) { type = "Slider"; };
    
    void setIsVertical(bool isVertical) { this->isVertical = isVertical; }
    bool getIsVertical() { return isVertical; }
    
    string getJson();
    
protected:
    bool isVertical;
};


//--------
class ofxControlOSCMultiSlider : public ofxControlOSCSlider
{
public:
    ofxControlOSCMultiSlider(string name, float x, float y, float w, float h)
        : ofxControlOSCSlider(name, x, y, w, h) { type = "MultiSlider"; };
    
    void setNumSliders(int numSliders) { this->numSliders = numSliders; }
    int getNumSliders() { return numSliders; }
    
    string getJson();
    
protected:
    int numSliders;
};


//--------
class ofxControlOSCKnob : public ofxControlOSCWidget
{
public:
    ofxControlOSCKnob(string name, float x, float y, float rad)
        : ofxControlOSCWidget(name, x, y, 0.1, 0.1) { type = "Knob"; };
    
    void setRadius(float radius) { this->radius = radius; }
    void setCenterZero(bool centerZero) { this->centerZero = centerZero; }
    void setUsesRotation(bool usesRotation) { this->usesRotation = usesRotation; }
    
    float getRadius() { return radius; }
    bool getCenterZero() { return centerZero; }
    bool getUsesRotation() { return usesRotation; }
    
    string getJson();
    
protected:
    float radius;
    bool centerZero, usesRotation;
};


//--------
class ofxControlOSCMultiTouchXY : public ofxControlOSCWidget
{
public:
    ofxControlOSCMultiTouchXY(string name, float x, float y, float w, float h)
        : ofxControlOSCWidget(name, x, y, w, h) { type = "MultiTouchXY"; };
    
    void setMaxTouches(int maxTouches) { this->maxTouches = maxTouches; }
    void setIsMomentary(bool isMomentary) { this->isMomentary = isMomentary; }
    
    int getMaxTouches() { return maxTouches; }
    bool getIsMomentary() { return isMomentary; }
    
    string getJson();
    
protected:
    int maxTouches;
    bool isMomentary;
};


//--------
class Page
{
public:
    Page(string name);
    string getName() { return name; }
    
    ofxControlOSCLabel * addLabel(string name, float x, float y, float w, float h);
    ofxControlOSCButton * addButton(string name, float x, float y, float w, float h);
    ofxControlOSCMultiButton * addMultiButton(string name, float x, float y, float w, float h, int rows, int cols);
    ofxControlOSCButton * addToggle(string name, float x, float y, float w, float h);
    ofxControlOSCMultiButton * addMultiToggle(string name, float x, float y, float w, float h, int rows, int cols);
    ofxControlOSCSlider * addSlider(string name, float x, float y, float w, float h);
    ofxControlOSCMultiSlider * addMultiSlider(string name, float x, float y, float w, float h, int numSliders);
    ofxControlOSCKnob * addKnob(string name, float x, float y, float rad);
    ofxControlOSCMultiTouchXY * addMultiTouchXY(string name, float x, float y, float w, float h, int maxTouches);

    string getJson();

protected:
    vector<ofxControlOSCWidget *> widgets;
    string name;
};


//--------
class ofxControlOSC
{
public:
    void setup(string name, Orientation orientation);
    Page* addPage(string name);
    string getJson();
    void saveToFile(string path);
    
protected:
    vector<Page *> pages;
    string name;
    Orientation orientation;
};
