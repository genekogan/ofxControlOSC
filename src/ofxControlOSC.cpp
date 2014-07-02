#include "ofxControlOSC.h"

//--------
string Widget::getJson() {
    string json;
    
    if (address == "") {
        address = "/"+name;
    }
    if (label == "") {
        label = name;
    }
    
    // core properties
    json += "{\n";
    json += "\t\"name\" : \""+name+"\",\n";
    json += "\t\"x\" : "+ofToString(x)+", \"y\" : "+ofToString(y)+",\n";
    json += "\t\"width\" : "+ofToString(w)+", \"height\" : "+ofToString(h)+",\n";
    json += "\t\"address\"  : \""+address+"\",\n";
    json += "\t\"min\":"+ofToString(min)+", \"max\":"+ofToString(max)+",\n";
    json += "\t\"label\" : \""+label+"\",\n";
    
    // color
    json += "\t\"color\": \"#ccc\",\n"; // check color
    json += "\t\"stroke\": \"#aaa\",\n";
    
    // widget type specific properties
    switch (type) {
        case BUTTON:
            json += "\t\"type\" : \"Button\",\n";
            json += "\t\"mode\" : \"momentary\",\n";
            break;
            
        case MULTIBUTTON:
            json += "\t\"type\" : \"MultiButton\",\n";
            json += "\t\"mode\" : \"momentary\",\n";
            json += "\t\"rows\" : "+ofToString(nrows)+", \"columns\" : "+ofToString(ncols)+",\n";
            break;
            
        case SLIDER:
            json += "\t\"type\" : \"Slider\",\n";
            json += isVertical ? "\t\"isVertical\": true,\n" : "\t\"isVertical\": false,\n";
            break;
            
        case MULTISLIDER:
            json += "\t\"type\" : \"MultiSlider\",\n";
            json += "\t\"numberOfSliders\" : "+ofToString(numSliders)+",\n";
            json += isVertical ? "\t\"isVertical\": true,\n" : "\t\"isVertical\": false,\n";
            break;
            
        case PAGE_SELECT:
            json += "\t\"type\" : \"Button\",\n";
            json += "\t\"isLocal\" : true,\n";
            json += "\t\"mode\" : \"contact\",\n";
            json += "\t\"ontouchstart\": \"control.changePage("+ofToString(idxPage)+")\",\n";
            break;
            
        case REFRESH:
            json += "\t\"type\" : \"Button\",\n";
            json += "\t\"isLocal\" : true,\n";
            json += "\t\"startingValue\" : 0,\n";
            json += "\t\"mode\" : \"contact\",\n";
            json += "\t\"ontouchstart\": \"interfaceManager.refreshInterface()\",\n";
            json += "\t\"label\" : \"refresh\",\n";
            break;
            
        default:
            break;
    }
    json += "}";
    return json;
}

//--------
Page::Page(string name) {
    this->name = name;
}

//--------
string Page::getJson() {
    string pageJson;
    for (int i=0; i<widgets.size(); i++) {
        if (i>0) pageJson += ",\n";
        pageJson += widgets[i].getJson();
    }
    return pageJson;
}

//--------
void Page::addWidget(Widget widget) {
    widgets.push_back(widget);
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
string ofxControlOSC::getHeader() {
    string header;
    for (int i=0; i<pages.size(); i++) {
        Widget pageButton;
        pageButton.type = PAGE_SELECT;
        pageButton.name = "p"+ofToString(i);
        pageButton.idxPage = i;
        pageButton.x = 0.16*i;
        pageButton.y = 0.0;
        pageButton.w = 0.12;
        pageButton.h = 0.1;
        pageButton.label = pages[i]->getName();
        header += pageButton.getJson() + ",";
    }
    
    Widget refresh;
    refresh.type = REFRESH;
    refresh.name = "refresh";
    refresh.x = 0.85;
    refresh.y = 0.0;
    refresh.w = 0.14;
    refresh.h = 0.1;
    
    header += refresh.getJson();
    return header;
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
        if (pages.size() > 1) {
            json += getHeader() + ",";
        }
        json += pages[p]->getJson();
        json += "]";
    }
    json += "];";
    return json;
}

//-------
void ofxControlOSC::uploadToControlP5(string ipAddress) {
    string json = getJson();
    ofxOscSender osc;
    osc.setup(ipAddress, CONTROLOSC_PORT);
    ofxOscMessage m;
    m.setAddress("/pushInterface");
    m.addStringArg(json);
    osc.sendMessage(m);    
}

//-------
void ofxControlOSC::saveToFile(string path) {
    ofFile file(path, ofFile::WriteOnly);
    file << getJson();
    file.close();
}