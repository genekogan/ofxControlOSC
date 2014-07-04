#include "ofxControlOSC.h"

//--------
ofxControlOSCWidget::ofxControlOSCWidget(string name, float x, float y, float w, float h) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->min = -1;
    this->max = 1;
    this->address = "/"+name;
    this->fillColor = "#ccc";
    this->strokeColor = "#aaa";
}

//--------
string ofxControlOSCWidget::getCoreJson() {
    string json;
    json += "\t\"name\" : \""+name+"\",\n";
    json += "\t\"type\" : \""+type+"\",\n";
    json += "\t\"x\" : "+ofToString(x)+", \"y\" : "+ofToString(y)+",\n";
    json += "\t\"width\" : "+ofToString(w)+", \"height\" : "+ofToString(h)+",\n";
    json += "\t\"address\" : \""+address+"\",\n";
    json += "\t\"min\":"+ofToString(min)+", \"max\":"+ofToString(max)+",\n";
    json += "\t\"color\" : \""+fillColor+"\",\n";
    json += "\t\"stroke\" : \""+strokeColor+"\",\n";
    return json;
}

//--------
string ofxControlOSCLabel::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    json += "\t\"value\" : \""+name+"\",\n";
    json += verticalCenter ? "\t\"verticalCenter\" : true,\n" : "\t\"verticalCenter\" : false,\n";
    json += "}";
    return json;
}
//--------
string ofxControlOSCButton::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    if (mode == MOMENTARY) {
        json += "\t\"mode\" : \"momentary\",\n";
    } else if (mode == TOGGLE) {
        json += "\t\"mode\" : \"toggle\",\n";
    }
    json += "\t\"label\" : \""+label+"\",\n";
    json += "}";
    return json;
}

//--------
string ofxControlOSCMultiButton::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    if (mode == MOMENTARY) {
        json += "\t\"mode\" : \"momentary\",\n";
    } else if (mode == TOGGLE) {
        json += "\t\"mode\" : \"toggle\",\n";
    }
    json += "\t\"label\" : \""+label+"\",\n";
    json += "\t\"rows\" : "+ofToString(rows)+", \"columns\" : "+ofToString(cols)+",\n";
    json += "}";
    return json;
}

//--------
string ofxControlOSCSlider::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    json += isVertical ? "\t\"isVertical\": true,\n" : "\t\"isVertical\": false,\n";
    json += "}";
    return json;
}

//--------
string ofxControlOSCMultiSlider::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    json += isVertical ? "\t\"isVertical\": true,\n" : "\t\"isVertical\": false,\n";
    json += "\t\"numberOfSliders\" : "+ofToString(numSliders)+",\n";
    json += "}";
    return json;
}

//--------
string ofxControlOSCKnob::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    json += "\t\"radius\" : "+ofToString(radius)+",\n";
    json += centerZero ? "\t\"centerZero\": true,\n" : "\t\"centerZero\": false,\n";
    json += usesRotation ? "\t\"usesRotation\": true,\n" : "\t\"usesRotation\": false,\n";
    json += "}";
    return json;
}

//--------
string ofxControlOSCMultiTouchXY::getJson() {
    string json;
    json += "{\n";
    json += getCoreJson();
    json += "\t\"maxTouches\" : "+ofToString(maxTouches)+",\n";
    json += isMomentary ? "\t\"isMomentary\" : true,\n" : "\t\"isMomentary\" : false,\n";
    json += "}";
    return json;
}

//--------
Page::Page(string name) {
    this->name = name;
}

//--------
ofxControlOSCLabel * Page::addLabel(string name, float x, float y, float w, float h) {
    ofxControlOSCLabel *label = new ofxControlOSCLabel(name, x, y, w, h);
    label->setAddress("/"+getName()+"/"+label->getName());
    widgets.push_back(label);
    return label;
}

//--------
ofxControlOSCButton * Page::addButton(string name, float x, float y, float w, float h) {
    ofxControlOSCButton *button = new ofxControlOSCButton(name, x, y, w, h);
    button->setLabel(button->getName());
    button->setMode(MOMENTARY);
    button->setAddress("/"+getName()+"/"+button->getName());
    widgets.push_back(button);
    return button;
}

//--------
ofxControlOSCMultiButton * Page::addMultiButton(string name, float x, float y, float w, float h, int rows, int cols) {
    ofxControlOSCMultiButton *multiButton = new ofxControlOSCMultiButton(name, x, y, w, h);
    multiButton->setLabel(multiButton->getName());
    multiButton->setMode(MOMENTARY);
    multiButton->setRows(rows);
    multiButton->setCols(cols);
    multiButton->setAddress("/"+getName()+"/"+multiButton->getName());
    widgets.push_back(multiButton);
    return multiButton;
}

//--------
ofxControlOSCButton * Page::addToggle(string name, float x, float y, float w, float h) {
    ofxControlOSCButton *toggle = new ofxControlOSCButton(name, x, y, w, h);
    toggle->setLabel(toggle->getName());
    toggle->setMode(TOGGLE);
    toggle->setAddress("/"+getName()+"/"+toggle->getName());
    widgets.push_back(toggle);
    return toggle;
}

//--------
ofxControlOSCMultiButton * Page::addMultiToggle(string name, float x, float y, float w, float h, int rows, int cols) {
    ofxControlOSCMultiButton *multiToggle = new ofxControlOSCMultiButton(name, x, y, w, h);
    multiToggle->setLabel(multiToggle->getName());
    multiToggle->setMode(TOGGLE);
    multiToggle->setRows(rows);
    multiToggle->setCols(cols);
    multiToggle->setAddress("/"+getName()+"/"+multiToggle->getName());
    widgets.push_back(multiToggle);
    return multiToggle;
}

//--------
ofxControlOSCSlider * Page::addSlider(string name, float x, float y, float w, float h) {
    ofxControlOSCSlider *slider = new ofxControlOSCSlider(name, x, y, w, h);
    if (h > w) {
        slider->setIsVertical(true);
    } else {
        slider->setIsVertical(false);
    }
    slider->setAddress("/"+getName()+"/"+slider->getName());
    widgets.push_back(slider);
    return slider;
}

//--------
ofxControlOSCMultiSlider * Page::addMultiSlider(string name, float x, float y, float w, float h, int numSliders) {
    ofxControlOSCMultiSlider *multiSlider = new ofxControlOSCMultiSlider(name, x, y, w, h);
    if (h > w/numSliders) {
        multiSlider->setIsVertical(true);
    } else {
        multiSlider->setIsVertical(false);
    }
    multiSlider->setNumSliders(numSliders);
    multiSlider->setAddress("/"+getName()+"/"+multiSlider->getName());
    widgets.push_back(multiSlider);
    return multiSlider;
}

//--------
ofxControlOSCKnob * Page::addKnob(string name, float x, float y, float rad) {
    ofxControlOSCKnob *knob = new ofxControlOSCKnob(name, x, y, rad);
    knob->setRadius(rad);
    knob->setAddress("/"+getName()+"/"+knob->getName());
    widgets.push_back(knob);
    return knob;
}

//--------
ofxControlOSCMultiTouchXY * Page::addMultiTouchXY(string name, float x, float y, float w, float h, int maxTouches) {
    ofxControlOSCMultiTouchXY *multiTouch = new ofxControlOSCMultiTouchXY(name, x, y, w, h);
    multiTouch->setMaxTouches(maxTouches);
    multiTouch->setAddress("/"+getName()+"/"+multiTouch->getName());
    widgets.push_back(multiTouch);
    return multiTouch;
}

//--------
string Page::getJson() {
    string pageJson;
    for (int i=0; i<widgets.size(); i++) {
        if (i>0) pageJson += ",\n";
        pageJson += widgets[i]->getJson();
    }
    return pageJson;
}

//--------
void ofxControlOSC::setup(string name, Orientation orientation) {
    this->name = name;
    this->orientation = orientation;
}

//--------
Page* ofxControlOSC::addPage(string name) {
    Page *newPage = new Page(name);
    pages.push_back(newPage);
    return newPage;
}

//-------
string ofxControlOSC::getJson() {
    string json;
    string orientationString = (orientation == PORTRAIT) ? "portrait" : "landscape";
    
    json +=  "loadedInterfaceName = \""+name+"\";\n";
    json += "interfaceOrientation = \""+orientationString+"\";\n";
    json += "pages = [\n";
    
    for (int p=0; p<pages.size(); p++) {
        if (p>0) json += ",\n";
        json += "[";
        json += pages[p]->getJson();
        json += "]";
    }
    
    json += "];";
    return json;
}

//-------
void ofxControlOSC::saveToFile(string path) {
    ofFile file(path, ofFile::WriteOnly);
    file << getJson();
    file.close();
}